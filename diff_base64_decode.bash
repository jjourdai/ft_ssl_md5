#/bin/bash

make
nb=100000

for i in `seq 0 $nb`;
do
	cat /dev/urandom | head -c 400000 > random.txt
	base64 random.txt > KoolRasta

	echo $(cat KoolRasta) | ./ft_ssl base64 > test1
	echo $(cat KoolRasta) | base64 -D > test2
	diff -u test1 test2
	#
	cat KoolRasta | ./ft_ssl base64 > test1
	cat KoolRasta | base64 -D > test2
	diff -u test1 test2

	./ft_ssl base64 KoolRasta > test1
	base64 -D KoolRasta > test2
	diff test1 test2
	# cat test1 test2
	# echo $i
done

rm test1 test2 random.txt
