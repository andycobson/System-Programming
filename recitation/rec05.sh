#! /bin/bash
# asj0108 - CSCE3600.283
curve()
{
	incr=$1;
	index=0
	shift;
	arr=("$@")
	for x in "${arr[@]}"
	do
		let grades[$index]=$x+$incr
		let index++
	done
}

if [ $# -ne 1 ]
then
	echo "usage: ./rec05.sh <curve amount>"
else
	for i in 1 2 3 4 5
	do
		read -p "Enter Quiz #$i: " grades[$i-1]
	done
fi

curve "$1" "${grades[@]}"
echo "Curved Grades:"

for (( i=0 ; $i<${#grades[*]} ; i=$i+1 ))
do
	echo "grades[$i] = ${grades[$i]}"
done
