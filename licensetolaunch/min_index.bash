#!/bin/bash

MIN_FOUND=$1
MIN_INDEX=0
MIN_I=0

while [ $MIN_I -lt $# ]
do
	INDEXING=$(( $MIN_I + 1 ))
	MIN_FOUND_MAYBE=${!INDEXING}
	if [ $MIN_FOUND_MAYBE -lt $MIN_FOUND ]
	then
		MIN_FOUND=$MIN_FOUND_MAYBE
		MIN_INDEX=$MIN_I
	fi
	MIN_I=$(( $MIN_I + 1 ))
done
echo $MIN_INDEX

