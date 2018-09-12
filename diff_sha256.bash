#/bin/bash

make
nb=1

for i in `seq 0 $nb`;
do
	cat /dev/urandom | head -n 10 > random.txt
	./ft_ssl "$(echo -n $(cat random.txt))" > test1
	echo -n $(cat random.txt) | shasum -a 256 > test2
#	cat test1 test2
	diff test1 test2
done

rm test1 test2 random.txt
