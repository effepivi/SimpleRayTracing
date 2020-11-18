#!/usr/bin/env bash

width=2048
height=2048

module purge > /dev/null
module load cmake mpi/intel

for thread_number in 16 #160 80 40 24 16 8 4 1
do
	echo "#!/usr/bin/env bash" > submit-pthread-$thread_number.sh
	echo "#" >> submit-pthread-$thread_number.sh
	echo "#SBATCH -A scw1563                   # Project/Account (use your own)" >> submit-pthread-$thread_number.sh
	echo "##SBATCH --mail-user=YOUREMAILADDRESS@bangor.ac.uk  # Where to send mail" >> submit-pthread-$thread_number.sh
	echo "#SBATCH --mail-type=END,FAIL         # Mail events (NONE, BEGIN, END, FAIL, ALL)" >> submit-pthread-$thread_number.sh
	echo "#SBATCH --job-name=RT-$thread_number-pthreads       # Job name" >> submit-pthread-$thread_number.sh
	echo "#SBATCH --output ray_tracing-%j.out  #" >> submit-pthread-$thread_number.sh
	echo "#SBATCH --error ray_tracing-%j.err   #" >> submit-pthread-$thread_number.sh
	echo "#SBATCH --nodes=1                    # Use one node" >> submit-pthread-$thread_number.sh
	echo "#SBATCH --ntasks-per-node=1          # Number of tasks per node" >> submit-pthread-$thread_number.sh
        echo "#SBATCH --exclude=ccs[2103-2114]     # Make sure we always use the same CPU." >> submit-pthread-$thread_number.sh

 	if [ "$thread_number" -ge "40" ]
	then
		echo "#SBATCH --cpus-per-task=40            # Number of cores per task" >> submit-pthread-$thread_number.sh
		echo "#SBATCH --time=00:25:00              # Time limit hrs:min:sec" >> submit-pthread-$thread_number.sh
	else
		echo "#SBATCH --cpus-per-task=$thread_number            # Number of cores per task" >> submit-pthread-$thread_number.sh
		echo "#SBATCH --time=00:50:00              # Time limit hrs:min:sec" >> submit-pthread-$thread_number.sh
	fi

	echo "#SBATCH --mem=600mb                  # Total memory limit" >> submit-pthread-$thread_number.sh

	echo "thread_number=$thread_number"  >> submit-pthread-$thread_number.sh

	# Clear the environment from any previously loaded modules
	echo "module purge > /dev/null 2>&1" >> submit-pthread-$thread_number.sh
	echo "module load cmake mpi/intel" >> submit-pthread-$thread_number.sh

	echo "COMPILER=\"`gcc --version |head -1`\"" >> submit-pthread-$thread_number.sh

	# Uncomment if your are using the intel compiler
	#module load compiler/intel/2020/2 #compiler/gnu/9/2.0
    echo "COMPILER=\"`icc --version |head -1`\"" >> submit-pthread-$thread_number.sh

	echo "TEMP=\`lscpu|grep \"Model name:\"\`" >> submit-pthread-$thread_number.sh
	echo "IFS=':' read -ra CPU_MODEL <<< \"\$TEMP\"" >> submit-pthread-$thread_number.sh

	echo "width=$width" >> submit-pthread-$thread_number.sh
	echo "height=$height" >> submit-pthread-$thread_number.sh

	if [ ! -f timing.csv ];
	then
		echo "CPU,Parallelisation,Number of threads per node,Number of nodes,Compiler,Image size,Runtime in sec" > timing.csv
	fi

	echo "echo Run ./main-pthreads with $thread_number threads." >> submit-pthread-$thread_number.sh

	echo "/usr/bin/time --format='%e' ./bin-release-gcc/main-pthreads --size $width $height --jpeg pthreads-$thread_number-${width}x$height.jpg --threads $thread_number 2> temp-pthread-$thread_number" >> submit-pthread-$thread_number.sh

	echo "RUNTIME=\`cat temp-pthread-$thread_number\`" >> submit-pthread-$thread_number.sh

    echo "echo \${CPU_MODEL[1]},Pthread,\$thread_number,1,\$COMPILER,\${width}x\$height,\$RUNTIME >> timing-pthread-$thread_number.csv" >> submit-pthread-$thread_number.sh
    echo "#rm temp-pthread-$thread_number" >> submit-pthread-$thread_number.sh

	chmod +x submit-pthread-$thread_number.sh
	sbatch submit-pthread-$thread_number.sh
done
