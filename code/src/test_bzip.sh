make clean
make fast
./sim -pipewidth 1 ../traces/bzip2.ptr.gz > ../results/A1.bzip2.res

cat ../results/A1.bzip2.res
