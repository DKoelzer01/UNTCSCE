#/bin/bash
number=$(( ($RANDOM % 10) + 1))
guess=0
while [ $guess -ne $number ]
do
	echo -e "Enter a number between 1 and 10: \c "
	read guess
	if [ $guess -eq $number ]
	then
		echo "Congratulations, the number is $number."
	else
		echo "Sorry, you are not correct. Try again!"
	fi
done
