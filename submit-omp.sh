#!/usr/bin/env bash
#
#SBATCH -A scw1563                   # Project/Account (use your own)
##SBATCH --mail-user=YOUREMAILADDRESS@bangor.ac.uk  # Where to send mail
#SBATCH --mail-type=END,FAIL         # Mail events (NONE, BEGIN, END, FAIL, ALL)
#SBATCH --job-name=RT-openmp         # Job name
#SBATCH --output ray_tracing-%j.out  #
#SBATCH --error ray_tracing-%j.err   #
#SBATCH --nodes=1                    # Use one node
#SBATCH --ntasks-per-node=1          # Number of tasks per node
#SBATCH --cpus-per-task=1            # Number of cores per task
#SBATCH --mem=600mb                  # Total memory limit
#SBATCH --time=10:00:00              # Time limit hrs:min:sec

# Clear the environment from any previously loaded modules
module purge > /dev/null 2>&1
module load cmake

COMPILER=`gcc --version |head -1`

# Uncomment if your are using the intel compiler
#module load compiler/intel/2020/2 #compiler/gnu/9/2.0
#COMPILER=`icc --version |head -1`

TEMP=`lscpu|grep "Model name:"`
IFS=':' read -ra CPU_MODEL <<< "$TEMP"

width=128
height=128

if [ ! -f timing.csv ];
then
    echo "CPU,Parallelisation,Number of threads per node,Number of nodes,Compiler,Image size,Runtime in sec" > timing.csv
fi

for thread_number in 160 80 40 24 16 8 4 1
do
    echo Run ./main-omp with $thread_number threads.
    
    export OMP_NUM_THREADS=$thread_number
    
    /usr/bin/time --format='%e' ./main-omp --size $width $height --jpeg openmp-$thread_number-${width}x$height.jpg 2> temp

    RUNTIME=`cat temp`

    echo ${CPU_MODEL[1]},OpenMP,$thread_number,1,$COMPILER,${width}x$height,$RUNTIME >> timing.csv
    rm temp

done
