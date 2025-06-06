#!/bin/bash

BINARY=./bin/main
GEN_TYPE=$1
COUNT=$2
SEED=$3
GEN0_ARGS=(7907,)
GEN3_ARGS="1 83 1337 2147483647"

run_gen() {
  $BINARY $GEN_TYPE $COUNT $SEED $@
}

if [ $GEN_TYPE == 0 ]; then
  run_gen $GEN0_ARGS[@];
elif [ $GEN_TYPE == 2 ]; then
  run_gen $GEN3_ARGS;
else
  run_gen
fi
