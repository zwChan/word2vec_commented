#!/usr/bin/bash
./count_and_filter -train ~/zhanglab/context/context.txt -min-count 5 -wvocab ~/zhanglab/context/wvocab.txt -cvocab ~/zhanglab/context/cvocab.txt

./word2vecf -train ~/zhanglab/context/context.txt -output ~/zhanglab/context/vector.bin -size 300 -negative 5 -threads 24 -sample 1e-4 -alpha 0.025 -iters 10 -binary 1 -dumpcv ~/zhanglab/context/vector_context.bin -wvocab ~/zhanglab/context/wvocab.txt -cvocab ~/zhanglab/context/cvocab.txt
