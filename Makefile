OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: program.o Chromosome.o Organism.o Specie.o
	g++ -o program.exe *.o

Chromosome.o: Chromosome.cc Chromosome.hh
	g++ -c Chromosome.cc $(OPCIONS)

Organism.o: Organism.cc Organism.hh Chromosome.hh
	g++ -c Organism.cc $(OPCIONS)

Specie.o: Specie.cc Specie.hh Organism.hh
	g++ -c Specie.cc $(OPCIONS)

program.o: program.cc Specie.hh Organism.hh
	g++ -c program.cc $(OPCIONS)

doc:
	doxygen

tar:
	zip -r html.zip html
	tar -cvf practica.tar *.cc *.hh Makefile Doxyfile html.zip

clean:
	touch program.o
	rm *.o
	touch program.exe
	rm *.exe
	touch practica.tar
	rm practica.tar
	touch html.zip
	rm html.zip
	touch html
	rm -rf html