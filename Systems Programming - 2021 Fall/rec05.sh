index=0
grades[0]=0
function curve() {
	incr=$1
	shift
	index=0
	for grade in "$@"
	do
		arr[index]=$grade
		let index++
	done
	index=0
	for i in "${arr[@]}"
	do
		let grades[index]=$i+$incr
		let index++
	done
}

if [[ $# -ne 1 ]]; then
	echo "usage: ./rec05.sh <curve amount>"
	exit
fi

for i in {1,2,3,4,5}
do
	printf "Enter QUIZ #%d: " $i
	read grades[$i-1]
done

curve $1 ${grades[@]}

echo "Curved Grades:"
index=0
for g in "${grades[@]}"
do
	printf "grades[%d] = %d\n" $index $g
	let index++
done
