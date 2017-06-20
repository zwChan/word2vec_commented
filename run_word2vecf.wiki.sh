#!/bin/sh
~/data/code/word2vec_commented/count_and_filter -train ~/data/wikidata/depth4/context.txt -min-count 5 -wvocab ~/data/wikidata/depth4/wvocab.txt -cvocab ~/data/wikidata/depth4/cvocab.txt

~/data/code/word2vec_commented/word2vecf -train ~/data/wikidata/depth4/context.txt -output ~/data/wikidata/depth4/context-vector.bin -size 300 -negative 5 -threads 24 -sample 1e-4 -alpha 0.025 -iters 15 -binary 1 -dumpcv ~/data/wikidata/depth4/vector_context.bin -wvocab ~/data/wikidata/depth4/wvocab.txt -cvocab ~/data/wikidata/depth4/cvocab.txt
