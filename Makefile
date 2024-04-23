RBT	:main.o util.o RBT.o MM.o
	 g++ -Wall -o RBT main.o util.o RBT.o MM.o

main.o	:main.cpp data_structures.h util.h RBT.h MM.h
	 g++ -Wall -c main.cpp

util.o	:util.cpp data_structures.h util.h
	 g++ -Wall -c util.cpp

RBT.o	:RBT.cpp data_structures.h RBT.h
	 g++ -Wall -c RBT.cpp

MM.o	:MM.cpp data_structures.h MM.h
	 g++ -Wall -c MM.cpp

clean	:
	rm *.o RBT
