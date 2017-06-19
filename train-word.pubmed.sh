#!/bin/sh

input="/lustre/home-3/zc15d/zhanglab/Pubmed_abstract/*.out"
traintext="/lustre/home-3/zc15d/zhanglab/context/pubmed_train.txt"
vectorfile="/lustre/home-3/zc15d/zhanglab/context/word2vec_vectors.bin"
cat $input | awk '{print tolower($2);}'  | sed -e "s/鈥�/'/g" -e "s/鈥�/'/g" -e "s/''/ /g"  | tr -c "A-Za-z'_ \n" " " > $traintext
time ./word2vec -train $traintext -output $vectorfile -cbow 0 -size 300 -window 8 -negative 5  -sample 1e-4 -threads 24 -binary 1 -iter 10
# ./distance vectors.bin
