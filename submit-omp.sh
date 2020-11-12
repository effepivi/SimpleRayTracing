#!/usr/bin/env bash

width=2048
height=2048

for thread_number in 160 80 40 24 16 8 4 1
do
	echo "#!/usr/bin/env bash" > submit-omp-$thread_number.sh
	echo "#" >> submit-omp-$thread_number.sh
	echo "#SBATCH -A scw1563                   # Project/Account (use your own)" >> submit-omp-$thread_number.sh
	echo "##SBATCH --mail-user=YOUREMAILADDRESS@bangor.ac.uk  # Where to send mail" >> submit-omp-$thread_number.sh
	echo "#SBATCH --mail-type=END,FAIL         # Mail events (NONE, BEGIN, END, FAIL, ALL)" >> submit-omp-$thread_number.sh
	echo "#SBATCH --job-name=RT-$thread_number-omp       # Job name" >> submit-omp-$thread_number.sh
	echo "#SBATCH --output ray_tracing-%j.out  #" >> submit-omp-$thread_number.sh
	echo "#SBATCH --error ray_tracing-%j.err   #" >> submit-omp-$thread_number.sh
	echo "#SBATCH --nodes=1                    # Use one node" >> submit-omp-$thread_number.sh
	echo "#SBATCH --ntasks-per-node=1          # Number of tasks per node" >> submit-omp-$thread_number.sh

 	if [ "$thread_number" -ge "40" ]
	then
		echo "#SBATCH --cpus-per-task=40            # Number of cores per task" >> submit-omp-$thread_number.sh
		echo "#SBATCH --time=00:25:00              # Time limit hrs:min:sec" >> submit-omp-$thread_number.sh
	else
		echo "#SBATCH --cpus-per-task=$thread_number            # Number of cores per task" >> submit-omp-$thread_number.sh
		echo "#SBATCH --time=00:50:00              # Time limit hrs:min:sec" >> submit-omp-$thread_number.sh
	fi

	echo "#SBATCH --mem=600mb                  # Total memory limit" >> submit-omp-$thread_number.sh

	echo "thread_number=$thread_number"  >> submit-omp-$thread_number.sh

	# Clear the environment from any previously loaded modules
	echo "module purge > /dev/null 2>&1" >> submit-omp-$thread_number.sh
	echo "module load cmake" >> submit-omp-$thread_number.sh

	echo "COMPILER=\"`gcc --version |head -1`\"" >> submit-omp-$thread_number.sh

	# Uncomment if your are using the intel compiler
	#module load compiler/intel/2020/2 #compiler/gnu/9/2.0
	#COMPILER=`icc --version |head -1`

	echo "TEMP=\`lscpu|grep \"Model name:\"\`" >> submit-omp-$thread_number.sh
	echo "IFS=':' read -ra CPU_MODEL <<< \"\$TEMP\"" >> submit-omp-$thread_number.sh

	echo "width=$width" >> submit-omp-$thread_number.sh
	echo "height=$height" >> submit-omp-$thread_number.sh

	if [ ! -f timing.csv ];
	then
		echo "CPU,Parallelisation,Number of threads per node,Number of nodes,Compiler,Image size,Runtime in sec" > timing.csv
	fi

	echo "echo Run ./main-omp with $thread_number threads." >> submit-omp-$thread_number.sh

  echo "export OMP_NUM_THREADS=$thread_number" >> submit-omp-$thread_number.sh

	echo "/usr/bin/time --format='%e' ./bin/main-omp --size $width $height --jpeg omp-$thread_number-${width}x$height.jpg 2> temp-$thread_number" >> submit-omp-$thread_number.sh

	echo "RUNTIME=\`cat temp-$thread_number\`" >> submit-omp-$thread_number.sh

  echo "echo \${CPU_MODEL[1]},omp,\$thread_number,1,\$COMPILER,\${width}x\$height,\$RUNTIME >> timing-omp-$thread_number.csv" >> submit-omp-$thread_number.sh
  echo "rm temp-$thread_number" >> submit-omp-$thread_number.sh
	chmod +x submit-omp-$thread_number.sh
	sbatch submit-omp-$thread_number.sh
done
