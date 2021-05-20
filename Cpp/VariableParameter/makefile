main : main.o
	g++ main.o -o main

main.o : main.cpp
	g++ -c main.cpp -o main.o

.PHONY : clean
clean :
	rm -rf main.o main
