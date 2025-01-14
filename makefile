G = g++
CFLAGS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o AreaDeEspera.o Cluster.o Prioritat.o Processador.o Proces.o
	$(G) -o program.exe program.o AreaDeEspera.o Cluster.o Prioritat.o Processador.o Proces.o

program.o: program.cc
	$(G) -c program.cc $(CFLAGS)

Prioritat.o: Prioritat.cc
	$(G) -c Prioritat.cc $(CFLAGS)

Processador.o: Processador.cc
	$(G) -c Processador.cc $(CFLAGS)

AreaDeEspera.o: AreaDeEspera.cc
	$(G) -c AreaDeEspera.cc $(CFLAGS)

Cluster.o: Cluster.cc
	$(G) -c Cluster.cc $(CFLAGS)

Proces.o: Proces.cc
	$(G) -c Proces.cc $(CFLAGS)

clean:
	rm -f *.o
	rm -f *.exe








