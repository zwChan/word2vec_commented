make
time ~/data/code/word2vec_commented/word2phrase -train ~/data/wikidata/depth4/token.txt  -output ~/data/wikidata/depth4/token-p2.txt -threshold 200 -showNumber 1000000 -debug 2 > ~/data/wikidata/depth4/token-vectors.phrase2
time ~/data/code/word2vec_commented/word2phrase -train ~/data/wikidata/depth4/token-p2.txt  -output ~/data/wikidata/depth4/token-p4.txt -threshold 100 -showNumber 1000000 -debug 2 > ~/data/wikidata/depth4/token-vectors.phrase4
time ~/data/code/word2vec_commented/word2vec -train ~/data/wikidata/depth4/token-p4.txt -output ~/data/wikidata/depth4/token-vectors-phrase.bin -cbow 0 -size 300 -window 5 -negative 5 -hs 0 -sample 1e-4 -threads 20 -binary 1 -iter 15  -save-vocab  ~/data/wikidata/depth4/token-vectors-phrase.vocab
#./distance vectors-phrase.bin
