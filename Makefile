objects = driver.o dgraph.o

output.out : $(objects)
	g++ -o output.out $(objects)

driver.o : driver.cpp dgraph.h
	g++ -c driver.cpp

dgraph.o : dgraph.cpp dgraph.h
	g++ -c dgraph.cpp

.PHONY : clean
clean : 
	-rm output.out $(objects)

.PHONY : val
val :
	valgrind -v ./output.out

.PHONY : run
run :
	./output.out