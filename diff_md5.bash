#/bin/bash

make
nb=1000

for i in `seq 0 $nb`;
do
	cat /dev/urandom | head -c 40000 > random.txt
	echo $(cat random.txt) | ./ft_ssl md5 > test1
	echo $(cat random.txt) | openssl md5 > test2

	# cat random.txt | ./ft_ssl md5 > test1
	# cat random.txt | openssl md5 > test2

	# ./ft_ssl md5 random.txt > test1
	# openssl md5 random.txt > test2
	# cat test1 test2
	# echo $i
	diff -u test1 test2
done

rm test1 test2 random.txt
