clear

rm -f test.out

echo "\033[33m===== Compiling testcases.c =====\033[0m\n"
gcc -Wall -o test.out testcases.c

if [[ "$?" != 0 ]]; then
	echo
	exit
fi

echo "\033[92mCompiled Successfully\033[0m\n"

if [[ "$1" != "" ]]; then
	echo "\033[33m===== Executing '\033[31m./test.out $1\033[33m' =====\033[0m\n"
	./test.out $1
fi
