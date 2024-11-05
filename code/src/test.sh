make clean
#make debug
make fast
../src/sim -pipewidth 2 -enablememfwd -enableexefwd -bpredpolicy 2 ../traces/sml.ptr.gz > ../results/B1.sml.res
cat ../results/B1.sml.res

echo "EXPECTED RESULTS"
cat ../ref/results/B1.sml.res
