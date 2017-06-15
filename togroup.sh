#########
#	Change pending jobs to desired job group
#########
if [ $# -gt 0 ]; then
	group=$1
	user=$2
	id=$3
	pipe=temp_pipe

	if [ ! -e $pipe ]; then
		mkfifo $pipe
	fi
	echo "made fifo. write to fifo"

	bjobs -p | grep $id | sed 's/ ascott.*//g' > $pipe &

	while read line; do
		echo "bmod -g $group $line"
		bmod -g $group $line
	done <$pipe &
else
	echo "Usage: bash togroup.sh \"group name\" \"username\" \"job identifier\""
	echo "note: username input is currently not working. make your own copy of this, then change the username in sed to your own"
fi
