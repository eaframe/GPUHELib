make

for chosen_m in 1000 10000 100000 200000 300000 400000
do
	echo "Running on chosen m of $chosen_m"
	echo "RUNNING MASTER"
	time ./Test_GPUHE_HELib_master $chosen_m &> out_master_$chosen_m.txt
	cat out_master_$chosen_m.txt
	echo "RUNNING MODIFIED"
	time ./Test_GPUHE_HELib_modified $chosen_m &> out_modified_$chosen_m.txt
	cat out_modified_$chosen_m.txt
done
