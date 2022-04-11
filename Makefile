all: main

main: main.o BLAST_DB.o FASTAreadset_HT.o FASTAreadset_LL.o
	g++ -g -Wall -o main main.o BLAST_DB.o FASTAreadset_HT.o FASTAreadset_LL.o

main.o:
	g++ -g -Wall -o main.o -c main.cpp
BLAST_DB.o:
	g++ -g -Wall -o BLAST_DB.o -c BLAST_DB.cpp
FASTAreadset_HT.o:
	g++ -g -Wall -o FASTAreadset_HT.o -c FASTAreadset_HT.cpp
FASTAreadset_LL.o:
	g++ -g -Wall -o FASTAreadset_LL.o -c FASTAreadset_LL.cpp

clean:
	rm main main.o BLAST_DB.o FASTAreadset_HT.o FASTAreadset_LL.o