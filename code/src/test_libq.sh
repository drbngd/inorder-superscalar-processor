make clean
make fast
./sim -pipewidth 1 ../traces/libq.ptr.gz > ../results/A1.libq.res

cat ../results/A1.libq.res
