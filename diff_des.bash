#/bin/bash

make
nb=1000
K=133457799BBCDFF1

for i in `seq 0 $nb`;
do
	echo $i
	# cat /dev/urandom | head -c $RANDOM > random.txt

	# ./ft_ssl des -e -a -k $K -i random.txt > test1
	# openssl des-ecb -e -a -K $K -in random.txt > test2

	# ./ft_ssl des -d -a -k $K -i test1 > test3
	# openssl des-ecb -d -a -K $K -in test2 > test4
	# diff test3 test4
	# if [ "$(echo $?)" != "0" ]
	# 	then
	# 		exit
	# fi
	# ./ft_ssl des-cbc -e -a -k $K -v $K -i random.txt > test1
	# openssl des-cbc -e -a -K $K -iv $K -in random.txt > test2

	# ./ft_ssl des-cbc -d -a -k $K -v $K -i test1 > test3
	# openssl des-cbc -d -a -K $K -iv $K -in test2 > test4
	# diff test3 test4
	# if [ "$(echo $?)" != "0" ]
	# 	then
	# 		exit
	# fi
	# ./ft_ssl des3 -e -a -k $K -v $K -i random.txt > test1
	# openssl des3 -e -a -K $K -iv $K -in random.txt > test2

	# ./ft_ssl des3 -d -a -k $K -v $K -i test1 > test3
	# openssl des3 -d -a -K $K -iv $K -in test2 > test4
	# diff test3 test4
	# if [ "$(echo $?)" != "0" ]
	# 	then
	# 		exit
	# fi
	# ./ft_ssl des -e -k $K -i random.txt > test1
	# openssl des-ecb -e -K $K -in random.txt > test2

	# ./ft_ssl des -d -k $K -i test2 | xxd > test3
	# openssl des-ecb -d -K $K -in test1 | xxd > test4
	# diff test3 test4
	# if [ "$(echo $?)" != "0" ]
	# 	then
	# 		exit
	# fi
	# ./ft_ssl des-ecb -e -k $K -i random.txt > test1
	# openssl des-ecb -e -K $K -in random.txt > test2

	# ./ft_ssl des-ecb -d -k $K -i test2 | xxd > test3
	# openssl des-ecb -d -K $K -in test1 | xxd > test4
	# diff test3 test4
	# if [ "$(echo $?)" != "0" ]
	# 	then
	# 		exit
	# fi
	# ./ft_ssl des-cbc -e -k $K -v $K -i random.txt > test1
	# openssl des-cbc -e -K $K -iv $K -in random.txt > test2

	# ./ft_ssl des-cbc -d -k $K -v $K -i test2 | xxd > test3
	# openssl des-cbc -d -K $K -iv $K -in test1 | xxd > test4
	# diff test3 test4
	# if [ "$(echo $?)" != "0" ]
	# 	then
	# 		exit
	# fi
	# ./ft_ssl des3 -e -k $K -v $K -i random.txt > test1
	# openssl des3 -e -K $K -iv $K -in random.txt > test2

	# ./ft_ssl des3 -d -k $K -v $K -i test2 | xxd > test3
	# openssl des3 -d -K $K -iv $K -in test1 | xxd > test4
	# diff test3 test4
	# if [ "$(echo $?)" != "0" ]
	# 	then
	# 		exit
	# fi
	cat /dev/urandom | head -c $RANDOM > random.txt
	pass=$RANDOM

	# ./ft_ssl des-ecb -e -p $pass -s $K -i random.txt > test1
	# openssl des-ecb -e -pass pass:$pass -S $K -in random.txt > test2

	# ./ft_ssl des-ecb -d -p $pass -i test1 | xxd > test3
	# openssl des-ecb -d -pass pass:$pass -in test2 | xxd > test4
	# diff test3 test4
	# if [ "$(echo $?)" != "0" ]
	# 	then
	# 		exit
	# fi
	# ./ft_ssl des-cbc -e -p $pass -s $K -v $K -i random.txt > test1
	# openssl des-cbc -e -pass pass:$pass -S $K -iv $K -in random.txt > test2

	# ./ft_ssl des-cbc -d  -p $pass -i test2 -v $K | xxd > test3
	# openssl des-cbc -d -pass pass:$pass -iv $K -in test1 | xxd > test4
	# diff test3 test4
	# if [ "$(echo $?)" != "0" ]
	# 	then
	# 		exit
	# fi
	./ft_ssl des3 -e -p $pass -v $K -s $K -i random.txt > test1
	openssl des3 -e -pass pass:$pass -iv $K -S $K -in random.txt > test2
	# openssl des3 -e -pass pass:$pass -S $K -in random.txt > test2

	# ./ft_ssl des3 -d  -p $pass -v $K -i test2 | xxd > test3
	# openssl des3 -d -pass pass:$pass -iv $K  -in test2 | xxd > test4
	# diff test3 test4
	exit
	if [ "$(echo $?)" != "0" ]
		then
			exit
	fi
done

rm test1 test2 random.txt test3 test4


#openssl des-ecb -K 133457799BBCDFF1 -nosalt -in big_file_bro
#make && ./ft_ssl des -d -i test1
