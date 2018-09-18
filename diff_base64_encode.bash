#/bin/bash

make
nb=1000

for i in `seq 0 $nb`;
do
	cat /dev/urandom | head -c 400000 > random.txt
	echo $(cat random.txt) | ./ft_ssl base64 > test1
	echo $(cat random.txt) | base64 > test2
	diff -u test1 test2
	#
	cat random.txt | ./ft_ssl base64 > test1
	cat random.txt | base64 > test2
	diff -u test1 test2

	./ft_ssl base64 random.txt > test1
	base64 random.txt > test2
	diff test1 test2
	# cat test1 test2
	# echo $i
done

rm test1 test2 random.txt
