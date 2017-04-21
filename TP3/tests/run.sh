#!/bin/sh

file=$1
g++ -Wall $file -o main
echo "#############inputmax max INFEASIBLE "
./main < example_BLP/inputmax.txt
echo "#############input -168"
./main < example_BLP/input.txt
echo "#############teste2 -159"
./main < example_BLP/teste2
echo "#############teste3 -168"
./main < example_BLP/teste3
echo "#############teste4 -407"
./main < example_BLP/teste4
echo "#############teste5 0"
./main < example_BLP/teste5
echo "#############teste6 -72"
./main < example_BLP/teste6
echo "#############teste7 71"
./main < example_BLP/teste7
echo "#############teste8 69"
./main < example_BLP/teste8
echo "#############teste9 INFEASIBLE"
./main < example_BLP/teste9
echo "#############teste10 0"
./main < example_BLP/teste10
echo "#############teste11 5"
./main < example_BLP/teste11
echo "#############teste12 9"
./main < example_BLP/teste12
echo "#############teste1 45 ----------- muito grande"
./main < example_BLP/teste1
