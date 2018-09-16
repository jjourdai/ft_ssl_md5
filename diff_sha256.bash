#/bin/bash

make
nb=1000

for i in `seq 0 $nb`;
do
	cat /dev/urandom | head -c 4000 > random.txt
	# cat random.txt | shasum -a 256 > test1
	# cat random.txt | ./ft_ssl sha256 > test2
	echo -n $(cat random.txt) | echo $(./ft_ssl sha256 | head -c 64) > test1
	echo -n $(cat random.txt) | echo $(shasum -a 256 | head -c 64) > test2

	# ./ft_ssl sha256 -r random.txt > test1
	# shasum -a 256 random.txt > test2
#	cat test1 test2
	diff -u test1 test2
done

rm test1 test2 random.txt
