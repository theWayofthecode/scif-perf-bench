#/usr/bin/bash

csvs=`find  ../data/csv -name bw_expo*.csv`

for f in $csvs
do
    python bw_plot_csvs.py `basename $f`
done
