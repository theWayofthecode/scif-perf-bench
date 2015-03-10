#/usr/bin/bash

raw_data=`find  ../data/raw -name *bw*.txt`

for f in $raw_data
do
    cat $f | awk -f raw_to_csv.awk > ../data/csv/`basename $f .txt`.csv
done
