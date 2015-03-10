
base=../build
#size=$((2**24))
size=133
msg_len=0
max_msg_len=256

outfile=data/raw/bw_linear_$1.txt
rm -f ${outfile}

while [ $msg_len -le $max_msg_len ]
do

msg_len=$(($msg_len + 128))

########## HOST (receiver) ##############
${base}/sink ${size} ${msg_len} & #>> ${outfile} &

########## MIC (sender) #############
micnativeloadex ${base}/source -a "${size} ${msg_len}"

usleep 10000
done

killall micnativeloadex
