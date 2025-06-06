#!/bin/bash

N_SAMPLES=$1
SAMPLE_SIZE=$2

rm -rf samples
mkdir -p samples

# Use 20-40 instead of 0-20 for seed repeat reasons
# For some reason small seeds sometimes bug out on the second generator
SEEDS=$( seq 20 $(( 20 + $N_SAMPLES )) )

for gen_num in {0..2}
do
  for seed in $SEEDS
  do
      destination="samples/gen-$gen_num-$seed-$SAMPLE_SIZE.txt"
      res=$(./gen.sh $gen_num $SAMPLE_SIZE $seed)
      if echo $res | grep -q "iterations"; then
        echo $res | sed -E 's/[0-9]+ iterations.*//g' | sed 's/ /\n/g' > $destination
      else
        echo $res | sed 's/ /\n/g' > $destination
      fi
  done
done

