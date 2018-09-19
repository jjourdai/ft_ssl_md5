#/bin/bash

make
nb=1000

for i in `seq 0 $nb`;
do
	cat /dev/urandom | head -c 4000 > random.txt && base64 random.txt > KoolRasta

	echo $(cat KoolRasta) | ./ft_ssl base64 -d > test1
	echo $(cat KoolRasta) | base64 -D > test2
	diff -u test1 test2

	cat /dev/urandom | head -c 4001 > random.txt && base64 random.txt > KoolRasta
	cat KoolRasta | ./ft_ssl base64 -d > test1
	cat KoolRasta | base64 -D > test2
	diff -u test1 test2

	cat /dev/urandom | head -c 4002 > random.txt && base64 random.txt > KoolRasta
	./ft_ssl base64 -d -i KoolRasta > test1
	base64 -D KoolRasta > test2
	diff test1 test2
	# cat test1 test2
	echo $i
done

rm test1 test2 random.txt
