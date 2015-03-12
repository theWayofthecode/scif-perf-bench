#/usr/bin/bash

data_path=../data
raw_data=`find  $data_path -name *bw*.txt`

for f in $raw_data
do
    cat $f | awk -f raw_to_csv.awk > $data_path/`basename $f .txt`.csv
done
