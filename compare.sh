#!/bin/bash

echo "Hello World, let's compare our 2 programs"
echo ""

ft_42="ft_42"
std_42="std_42"

ft_my="ft_my"
std_my="std_my"

make -j 

mkdir diffs

echo ""
echo "start of school_tester diff:"
diff <(cat $ft_42) <(cat $std_42) > diffs/diff1
echo "end of diff"
echo ""

echo "start of my_tester diff:"
diff <(cat $ft_my) <(cat $std_my) > diffs/diff2
echo "end of diff"
echo ""

make fclean
