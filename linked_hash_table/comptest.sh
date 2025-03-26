clear

rm -f test

echo "\033[33m===== Compiling testcases.c =====\033[0m\n"
gcc -Wall -o test testcases.c

if [[ "$?" != 0 ]]; then
	echo
	exit
fi

echo "\033[92mCompiled Successfully\033[0m\n"

if [[ "$1" != "" ]]; then
	echo "\033[33m===== Executing '\033[31m./test $1\033[33m' =====\033[0m\n"
	./test $1
fi
