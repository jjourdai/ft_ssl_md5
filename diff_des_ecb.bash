#/bin/bash

make
nb=1000
K=133457799BBCDFF1

for i in `seq 0 $nb`;
do
	# cat /dev/urandom | head -c $RANDOM > random.txt
	# #cat include/ssl.h > random.txt

	# ./ft_ssl des -e -a -k $K -i random.txt > test1
	# openssl des-ecb -e -a -K $K -in random.txt > test2

	# ./ft_ssl des -d -k $K -i test2 | xxd > test3
	# openssl des-ecb -d -K $K -in test1 | xxd > test4
	# diff test3 test4
	cat /dev/urandom | head -c $RANDOM > random.txt

	./ft_ssl des -e -k $K -i random.txt > test1
	openssl des-ecb -e -K $K -in random.txt > test2

	./ft_ssl des -d -k $K -i test2 | xxd > test3
	openssl des-ecb -d -K $K -in test1 | xxd > test4
	diff test3 test4

	./ft_ssl des-ecb -e -k $K -i random.txt > test1
	openssl des-ecb -e -K $K -in random.txt > test2

	./ft_ssl des-ecb -d -k $K -i test2 | xxd > test3
	openssl des-ecb -d -K $K -in test1 | xxd > test4
	diff test3 test4
	echo $i
done

rm test1 test2 random.txt test3 test4


#openssl des-ecb -K 133457799BBCDFF1 -nosalt -in big_file_bro
#make && ./ft_ssl des -d -i test1
