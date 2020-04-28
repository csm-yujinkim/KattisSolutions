#!/bin/bash

# Results discarded
read N_TIMES

read MIN_INDEX_ARGS
./min_index.bash $MIN_INDEX_ARGS
i=$(( $i + 1 ))

