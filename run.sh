PROBLEM=plantilla.cpp

if [ $# == 1 ] 
then
    PROBLEM=$1
fi

g++ -std=c++11 ${PROBLEM}

./a.out < case.in > case.out
rm a.out