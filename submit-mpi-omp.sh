#!/usr/bin/env bash

width=2048
height=2048

module purge > /dev/null 2>&1
module load cmake mpi/intel

export SCW_TPN_OVERRIDE=1

for NODES in 1 2 3 4
do
    for thread_number in 1 4 8 16 24 40 80 160
    do
        echo "#!/usr/bin/env bash" > submit-MPI-OMP-$NODES-$thread_number.sh
        echo "#" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "#SBATCH -A scw1563                   # Project/Account (use your own)" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "##SBATCH --mail-user=YOUREMAILADDRESS@bangor.ac.uk  # Where to send mail" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "#SBATCH --mail-type=END,FAIL         # Mail events (NONE, BEGIN, END, FAIL, ALL)" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "#SBATCH --job-name=RT-MPI-omp-$NODES-$thread_number       # Job name" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "#SBATCH --output ray_tracing-%j.out  #" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "#SBATCH --error ray_tracing-%j.err   #" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "#SBATCH --nodes=$NODES                    # Use one node" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "#SBATCH --ntasks-per-node=1         # Number of tasks per node" >> submit-MPI-OMP-$NODES-$thread_number.sh

     	if [ "$thread_number" -ge "40" ]
	    then
		    echo "#SBATCH --cpus-per-task=40            # Number of cores per task" >> submit-MPI-OMP-$NODES-$thread_number.sh
		    echo "#SBATCH --time=00:25:00              # Time limit hrs:min:sec" >> submit-MPI-OMP-$NODES-$thread_number.sh
	    else
		    echo "#SBATCH --cpus-per-task=$thread_number            # Number of cores per task" >> submit-MPI-OMP-$NODES-$thread_number.sh
		    echo "#SBATCH --time=00:50:00              # Time limit hrs:min:sec" >> submit-MPI-OMP-$NODES-$thread_number.sh
	    fi
	    
        echo "#SBATCH --mem=3000mb                  # Total memory limit" >> submit-MPI-OMP-$NODES-$thread_number.sh

        echo "thread_number=$thread_number"  >> submit-MPI-OMP-$NODES-$thread_number.sh

        # Clear the environment from any previously loaded modules
        echo "module purge > /dev/null 2>&1" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "source env-gnu.sh"             >> submit-MPI-OMP-$NODES-$thread_number.sh

        echo "COMPILER=\"`gcc --version |head -1`\"" >> submit-MPI-OMP-$NODES-$thread_number.sh

        # Uncomment if your are using the intel compiler
        #module load compiler/intel/2020/2 #compiler/gnu/9/2.0
        #echo "COMPILER=\"`icc --version |head -1`\"" >> submit-MPI-OMP-$NODES-$thread_number.sh

        echo "TEMP=\`lscpu|grep \"Model name:\"\`" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "IFS=':' read -ra CPU_MODEL <<< \"\$TEMP\"" >> submit-MPI-OMP-$NODES-$thread_number.sh

        echo "width=$width" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "height=$height" >> submit-MPI-OMP-$NODES-$thread_number.sh

        if [ ! -f timing.csv ];
        then
            echo "CPU,Parallelisation,Number of threads/processes per node,Number of nodes,Compiler,Image size,Runtime in sec" > timing.csv
        fi

        echo "echo Run ./main-mpi with $thread_number OpenMP threads on $NODES nodes." >> submit-MPI-OMP-$NODES-$thread_number.sh

        echo "export OMP_NUM_THREADS=$thread_number" >> submit-MPI-OMP-$NODES-$thread_number.sh

        echo "/usr/bin/time --format='%e' mpirun  ./bin-gnu/main-mpi-omp --size $width $height --jpeg mpi-omp-$NODES-$thread_number-${width}x$height.jpg 2> temp-mpi-$NODES-$thread_number" >> submit-MPI-OMP-$NODES-$thread_number.sh

        echo "RUNTIME=\`cat temp-mpi-$NODES-$thread_number\`" >> submit-MPI-OMP-$NODES-$thread_number.sh

        echo "echo \${CPU_MODEL[1]},MPI-omp,\$thread_number,$NODES,\$COMPILER,\${width}x\$height,\$RUNTIME >> timing-mpi-omp-$NODES-$thread_number.csv" >> submit-MPI-OMP-$NODES-$thread_number.sh
        echo "#rm temp-mpi-$NODES-$thread_number" >> submit-MPI-OMP-$NODES-$thread_number.sh
        chmod +x submit-MPI-OMP-$NODES-$thread_number.sh
        sbatch submit-MPI-OMP-$NODES-$thread_number.sh
    done
done
