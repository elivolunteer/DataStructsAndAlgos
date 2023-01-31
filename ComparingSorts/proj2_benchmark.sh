#!/bin/bash
DESTDIR=/dev/null

## Generate lists of random numbers
declare -i gen_counter=1
##while [ $gen_counter -le 7 ]
for ((i=1; i<=7; i++))
do
    echo Generateing $((10 ** i)) random numbers
    python3 num_gen.py $((10 ** i))
done

## Run volsort on generated arrays
declare string_modes="stl qsort merge quick"
for mode in $string_modes
do
    for ((i=1; i<=7; i++))
    do
        echo Running volsort $mode on $((10 ** i)) numbers
		START="$(date +%s)"
        (./volsort -m $mode -n < /tmp/$((10 ** i))_random_ints.txt) > $DESTDIR
		DURATION=$[ $(date +%s) - ${START} ]
		echo ${DURATION}
    done
done

