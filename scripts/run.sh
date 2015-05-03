
base=../bin
msg_len=0
msg_step=$((2**7))
max_msg_len=$((2**12))
expo=6
max_expo=11
size=$((2**27))

outfile=../data/$1.txt

while [ ${expo} -le ${max_expo} ]
do

msg_len=$((2**${expo}))
killall micnativeloadex

########### HOST (receiver) ##############
#${base}/sink.x86_64 ${size} ${msg_len} &>> ${outfile} &
#
########### MIC (sender) #############
#micnativeloadex ${base}/source.k1om -a "${size} ${msg_len}"

########## MIC (receiver) ##############
micnativeloadex ${base}/sink.k1om -a "${size} ${msg_len}" &>> ${outfile} &

########## HOST (sender) #############
${base}/source.x86_64 ${size} ${msg_len}

expo=$((${expo} + 1))

wait ${!}

done

