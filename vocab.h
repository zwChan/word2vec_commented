#ifndef _vocab_h
#define _vocab_h


struct vocab_word_f {
  long long cn;
  int *point;
  char *word, *code, codelen;
};

struct vocabulary_f {
   struct vocab_word_f *vocab;
   int *vocab_hash;
   long long vocab_max_size; //1000
   long vocab_size;
   long long word_count;
};


int ReadWordIndex_f(struct vocabulary_f *v, FILE *fin);
inline int GetWordHash_f(struct vocabulary_f *v, char *word);
int SearchVocab_f(struct vocabulary_f *v, char *word);
int AddWordToVocab_f(struct vocabulary_f *v, char *word);
void SortAndReduceVocab_f(struct vocabulary_f *v, int min_count);
struct vocabulary_f *CreateVocabulary_f();
void SaveVocab_f(struct vocabulary_f *v, char *vocab_file);
struct vocabulary_f *ReadVocab_f(char *vocab_file);
void EnsureVocabSize_f(struct vocabulary_f *v);

#endif
