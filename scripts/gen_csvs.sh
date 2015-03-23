#/usr/bin/bash

for f in "$@"
do
    cat $f | awk -f raw_to_csv.awk > `basename $f .txt`.csv
done
