make clean
make debug
../src/sim -pipewidth 2 -enablememfwd -enableexefwd ../traces/gcc.ptr.gz > ../results/A3.gcc.res 
#cat ../results/A3.gcc.res

echo "EXPECTED RESULTS"
cat ../ref/results/A3.gcc.res
