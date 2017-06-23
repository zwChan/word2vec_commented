make
time ~/data/code/word2vec_commented/word2vec -train ~/data/wikidata/depth4/token.txt -output ~/data/wikidata/depth4/token-vectors.bin -cbow 0 -size 300 -window 5 -negative 5 -hs 0 -sample 1e-4 -threads 20 -binary 1 -iter 15  -save-vocab  ~/data/wikidata/depth4/token-vectors.vocab
#./distance vectors-phrase.bin
