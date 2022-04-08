#!/bin/bash

echo "Hello World, let's compare our 2 programs"
echo ""

uname_res=$(uname)

if [ $uname_res = "Darwin" ]; then
	sed_cmd="sed -i '.bckup'"
elif [ $uname_res = "Linux" ]; then
	sed_cmd="sed -i"
fi


ft_42="ft_42"
std_42="std_42"

ft_my="ft_my"
std_my="std_my"

make re
mv containerz $ft_42

$sed_cmd s/STD=0/STD=1/g Makefile
make re
mv containerz $std_42

$sed_cmd s/main_42.cpp/my_main.cpp/g Makefile
$sed_cmd s/STD=1/STD=0/g Makefile
make re
mv containerz $ft_my

$sed_cmd s/STD=0/STD=1/g Makefile
make re
mv containerz $std_my

$sed_cmd s/my_main.cpp/main_42.cpp/g Makefile
$sed_cmd s/STD=1/STD=0/g Makefile

mkdir diffs

echo "start of my_tester diff:"
diff <(./ft_my) <(./std_my) > diffs/diff2
echo "end of diff"
echo ""

rm  "Makefile'.bckup'"
make clean
