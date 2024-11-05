make clean
make debug
#make fast
../src/sim -pipewidth 2 -enablememfwd -enableexefwd -bpredpolicy 2 ../traces/gcc.ptr.gz > ../results/B2.gcc.res.inc
cat ../results/B2.gcc.res

echo "EXPECTED RESULTS"
cat ../ref/results/B2.gcc.res
