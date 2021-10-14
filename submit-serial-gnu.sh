#!/usr/bin/env bash
#
#SBATCH -A scw1563                   # Project/Account (use your own)
##SBATCH --mail-user=YOUREMAILADDRESS@bangor.ac.uk  # Where to send mail
#SBATCH --mail-type=END,FAIL         # Mail events (NONE, BEGIN, END, FAIL, ALL)
#SBATCH --job-name=RT-serial         # Job name
#SBATCH --output ray_tracing-gnu-%j.out  #
#SBATCH --error ray_tracing-gnu-%j.err   #
#SBATCH --nodes=1                    # Use one node
#SBATCH --ntasks-per-node=1          # Number of tasks per node
#SBATCH --cpus-per-task=1            # Number of cores per task
#SBATCH --mem=600mb                  # Total memory limit
#SBATCH --time=00:50:00              # Time limit hrs:min:sec
#SBATCH --exclude=ccs[2103-2114]     # Make sure we always use the same CPU.

# Clear the environment from any previously loaded modules
source env-gnu.sh

COMPILER=`gcc --version |head -1`

TEMP=`lscpu|grep "Model name:"`
IFS=':' read -ra CPU_MODEL <<< "$TEMP"

width=128
height=128

if [ ! -f timing.csv ];
then
    echo "CPU,Parallelisation,Number of threads/processes per node,Number of nodes,Compiler,Image size,Runtime in sec" > timing.csv
fi

/usr/bin/time --format='%e' ./bin-gnu/main --size $width $height --jpeg serial-gnu-${width}x$height.jpg 2> temp-serial

RUNTIME=`cat temp-serial`

echo ${CPU_MODEL[1]},None,0,1,$COMPILER,${width}x$height,$RUNTIME > timing-serial-gnu-${width}x$height.csv
#rm temp-serial
