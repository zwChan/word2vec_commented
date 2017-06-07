//  Copyright 2013 Google Inc. All Rights Reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include "vocab.h"

const long long max_size = 2000;         // max length of strings
const long long N = 40;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries

int main(int argc, char **argv) {
  FILE *f,*wf;
  //char st1[max_size];
  //char *bestw[N];
  char ifile_name[max_size],wfile_name[max_size], st[100][max_size];
  //float dist, len, bestd[N], vec[max_size];
  long long words, size, a, b, c, d, cn, bi[100],cnt;
  //char ch;
  float *M;
  char *vocab;
  char  pickWord[max_size];
  struct vocabulary *wv = CreateVocabulary();

  if (argc < 3) {
    printf("Usage: ./pickVectors <binary-file>\nwhere FILE contains word projections in the BINARY FORMAT\n"
    		"vocabulary file: a word per line\n"
    		"Output to stdout.\n");
    return 0;
  }
  strcpy(ifile_name, argv[1]);
  strcpy(wfile_name, argv[2]);
  f = fopen(ifile_name, "rb");
  wf = fopen(wfile_name, "rb");
  if (f == NULL || wf == NULL) {
    printf("Input file or vocabulary file not found\n");
    return -1;
  }

  // build vocabulary for the chosen word
  while (EOF != fscanf(wf, "%s\n", pickWord)) {
	  AddWordToVocab(wv,pickWord);
  }
  fprintf(stderr,"chosen words number is %lld\n", wv->vocab_size);
  fclose(wf);

  fscanf(f, "%lld", &words);
  fscanf(f, "%lld", &size);
  vocab = (char *)malloc((long long)(wv->vocab_size) * max_w * sizeof(char));
  M = (float *)malloc((long long)(wv->vocab_size) * (long long)size * sizeof(float));
  if (M == NULL || vocab==NULL) {
    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    return -1;
  }
  cnt = 0;
  for (b = 0; b < words && cnt < wv->vocab_size; b++) {
    a = 0;
    while (1) {
      vocab[cnt*max_w + a] = fgetc(f);
      if (feof(f) || (vocab[cnt*max_w + a] == ' ')) break;
      if ((a < max_w) && (vocab[cnt*max_w + a] != '\n')) a++;
    }
    vocab[cnt*max_w + a] = 0;
    d = SearchVocab(wv,&vocab[cnt*max_w]);
    if (d >= 0) {
    	wv->vocab[d].cn += 10000; // add a big enough number to indicate it was found
    	for (a = 0; a < size; a++) fread(&M[a + cnt * size], sizeof(float), 1, f);
    	cnt++;
    }else{
    	// skip this vector
    	float tmp;
    	//for (a = 0; a < size; a++) fread(&tmp, sizeof(float), 1, f);
    	for (a = 0; a < size; a++) fread(&M[a + cnt * size], sizeof(float), 1, f);
    }
  }
  fclose(f);

  fprintf(stderr,"Found words number is %d\n", cnt);

  fprintf(stdout,"%lld %lld\n",cnt,size);
  for (b=0; b<cnt; b++) {
	  fprintf(stdout,"%s ", &vocab[b*max_w]);
	  for (a = 0; a < size; a++) {
		  fprintf(stdout,"%lf ",M[a]);
	  }
	  fprintf(stdout,"\n");
  }

  b = 0;
  for (a=0; a < wv->vocab_size; a++){
	  if (wv->vocab[a].cn < 10000) { // not found
		  b ++;
		  fprintf(stderr,"%s\n", wv->vocab[a].word);
	  }
	  fprintf(stderr,"total %d not found, found %d, all %d\n", b, cnt, wv->vocab_size);
  }
  fflush(stdout);
  fflush(stderr);
  return 0;
}
