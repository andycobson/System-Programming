#! /bin/bash

# Andrew Jacobson
# CSCE 3600 002
# 02-26-2021
# Script monitors the number of processes per user.

stop="false"  		   # This variable will work with the trap to check if we should stop loop
trap 'stop="true"' SIGINT  # Trap to see if user presses ^C
term="n"		   # variable to test until loop

until [ $term = "y" ]      
do
	iter=0		   # Varible to check what iteration the until loop is on
	skipIter=0	   # Need every other element in array
	users=0		   # Total number of users
	processes=0	   # Total number of processes

	date
	printf "%-30s  %s\n" "User ID" "Count"
	outArr=( $(ps -Ao user | gawk '{if(NR>1)print}' | sort | uniq -c ) )
	# Get the output of process command, skipping the first line, and store into array

	for x in ${outArr[*]}
	do

		let skipIter=$iter%2	# Return either a 1 or 0
		if [ $# -eq 0 ] && [ $skipIter -eq 0 ]
		then
			let users++	# Increment number of users
			let processes+=${outArr[iter]}	# Add to total of processes
			printf "%-30s  %s\n" ${outArr[iter+1]} $x
		fi
		for parm # Iterate through the parameters
		do
			if [ "$x" == "$parm" ]
			then
				let users++
				let processes+=${outArr[iter-1]}
				printf "%-30s  %s\n" $x ${outArr[iter-1]}
			fi
		done
		let iter++
	if [ $users -eq $# ]  # Exit loop once we have the info we need
	then
		break
	fi

	done

	printf "  %s USERS, TOTAL PROCESSES %5s\n" $users $processes

	sleep 5
	if [ $stop = "true" ]
	then
		echo " (SIGINT) received"
		read -p "Terminate Program? (Y/N) " term
		term=$(echo "$term" | tr '[:upper:]' '[:lower:]')
	fi
done

echo "Terminating program"
