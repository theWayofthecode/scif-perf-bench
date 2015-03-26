
base=../bin
size=$((2**30))
msg_len=0
msg_step=$((2**7))
max_msg_len=$((2**12))
expo=20
max_expo=30

outfile=../data/$1.txt
rm -f ${outfile}

while [ ${expo} -le ${max_expo} ]
do

msg_len=$((2**${expo}))
killall micnativeloadex

########### HOST (receiver) ##############
#${base}/sink ${size} ${msg_len} &>> ${outfile} &
#
########### MIC (sender) #############
#Micnativeloadex ${base}/source -a "${size} ${msg_len}"

########## MIC (receiver) ##############
micnativeloadex ${base}/sink.k1om -a "${size} ${msg_len}" &>> ${outfile} &
echo "micnativeloadex ${base}/sink.k1om -a \"${size} ${msg_len}\" &>> ${outfile} &"

########## HOST (sender) #############
echo "${base}/source.x86_64 ${size} ${msg_len}"
${base}/source.x86_64 ${size} ${msg_len}

expo=$((${expo} + 1))

wait ${!}

done

