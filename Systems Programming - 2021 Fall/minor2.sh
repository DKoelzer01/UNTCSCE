#Daniel Koelzer
#Section 001
#10/4/2021

#CTRL_C_Count - Counts number of times ^C has been pressed.
ctrlccount=0
#User_Count - Tracks number of users. Only updated AFTER checking for changes in users.
userCount=0
#Users - List of uid's of users currently on. Only updated AFTER checking for changes in users.
users=$(who|cut -c1-7)
#Cur Time - Current formatted time
curTime=$(date +"%a %b %d %H:%M:%S %Z %Y")

#user defined exit function. called upon trapping SIGINT
function userDefExit()
{
	let ctrlccount++
	if [[ $ctrlccount == 1 ]]; then
		echo "(SIGINT) ignored. enter ^C 1 more time to terminate program."
	fi
	if [[ $ctrlccount == 2 ]]; then
		exit
	fi
}

#Formatting for any user log ins
function userLogIn()
{
	for v in "$@"
	do
		echo ">"$v" logged in to "$HOSTNAME
	done
}

#Formatting for any user log outs
function userLogOut()
{
	for v in "$@"
	do
		echo ">"$v" logged out of "$HOSTNAME
	done
}

#Initial user login output
echo $curTime ") initial users logged in"
for s in $(who|cut -c1-7)
do
	userLogIn $s
done

#Main loop. Compares Users to TempUsers, the CURRENT users at this exact moment.
#Checks if the number of users has changed. If it is lower, there was a log out, if it is higher, a log in.
#For log ins, check if the OLD user list contains each user in the CURRENT list. Any matches are deleted to allow for duplicate logins. Call the userLogIn function
#For log outs, check if the OLD user list contains each user in the CURRENT list. Any matches are deleted to allow for duplicate logouts. Call the userLogOut function
while true
do
	tempUsers=$(who|cut -c1-7)
	if [[ $userCount < $(who|wc -l) ]]; then
		for s in $tempUsers
		do
			if [[ $users != *$s* ]]; then
				userLogIn $s
			else
				users=${users//$s/}
			fi
		done
	elif [[ $userCount > $(who|wc -l) ]]; then
		for s in $users
		do
			if [[ $tempUsers != *$s* ]]; then
				userLogOut $s
			else
				tempUsers=${tempUsers//$s/}
			fi
		done
	fi
	
	#Update users, userCount, and time.
	users=$(who|cut -c1-7)
	userCount=$(who|wc -l)
	curTime=$(date +"%a %b %d %H:%M:%S %Z %Y")
	echo $curTime ") # of users: " $userCount
	
	trap userDefExit SIGINT
	sleep 10
done

