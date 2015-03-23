
base=../bin
size=$((2**20))
msg_len=0
msg_step=$((2**7))
max_msg_len=$((2**12))
expo=20
max_expo=20

outfile=../data/$1.txt
rm -f ${outfile}

while [ ${expo} -le ${max_expo} ]
do

msg_len=$((2**${expo}))

########## HOST (receiver) ##############
${base}/sink ${size} ${msg_len} &>> ${outfile} &

########## MIC (sender) #############
micnativeloadex ${base}/source -a "${size} ${msg_len}"

expo=$((${expo} + 1))

wait $!
done

