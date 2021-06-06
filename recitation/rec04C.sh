#! /bin/bash

let randNum=1+$RANDOM%10
userInt=-1
until [ $userInt -eq $randNum ]
do
if [ $userInt -ne -1 ]
then
	echo "Sorry, you are not correct. Try again!"
fi
	read -p "Enter a number between 1 and 10: " userInt
done
echo "Contratulations, the number is $userInt."
