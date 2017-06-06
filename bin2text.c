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

const long long max_size = 2000;         // max length of strings
const long long N = 40;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries

int main(int argc, char **argv) {
  FILE *f;
  char st1[max_size];
  char *bestw[N];
  char file_name[max_size], st[100][max_size];
  float dist, len, bestd[N], vec[max_size];
  long long words, size, a, b, c, d, cn, bi[100];
  //char ch;
  float M[10000];
  char vocab[max_w];
  if (argc < 2) {
    printf("Usage: ./distance <binary-file>\nwhere FILE contains word projections in the BINARY FORMAT\nOutput to stdout.\n");
    return 0;
  }
  strcpy(file_name, argv[1]);
  f = fopen(file_name, "rb");
  if (f == NULL) {
    printf("Input file not found\n");
    return -1;
  }
  fscanf(f, "%lld", &words);
  fscanf(f, "%lld", &size);
  fprintf(stdout,"%lld %lld\n",words,size);
  for (b = 0; b < words; b++) {
    a = 0;
    while (1) {
      vocab[a] = fgetc(f);
      if (feof(f) || (vocab[a] == ' ')) break;
      if ((a < max_w) && (vocab[a] != '\n')) a++;
    }
    vocab[a] = 0;
    fprintf(stdout,"%s ", vocab);
    for (a = 0; a < size; a++) fread(&M[a], sizeof(float), 1, f);
    for (a = 0; a < size; a++) fprintf(stdout,"%lf ",M[a]);
    fprintf(stdout,"\n");
  }
  fclose(f);

  return 0;
}
