
base=../bin
#size=$((2**24))
size=$((2**30))
msg_len=0
msg_step=$((2**12))
max_msg_len=$((2**30))
expo=12
max_expo=30
outfile=../data/bw_$1.txt
rm -f ${outfile}

while [ ${expo} -le ${max_expo} ]
do

msg_len=$((2**${expo}))
expo=$((${expo} + 1))

########## HOST (receiver) ##############
${base}/sink ${size} ${msg_len} >> ${outfile} &

########## MIC (sender) #############
micnativeloadex ${base}/source -a "${size} ${msg_len}"

usleep 10000
done

killall micnativeloadex
