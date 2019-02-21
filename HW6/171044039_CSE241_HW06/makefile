Interface = Set.h List.h Queue.h Collection.h

Obj = 171044039_main.o Iterator.o HashSet.o ArrayList.o LinkedList.o Collection.o Set.o List.o Queue.o 

run : $(Obj) 
	g++ -Wno-deprecated -std=c++11 -ansi -pedantic -Wall $(Obj) -o run

171044039_main.o : 171044039_main.cpp $(Obj)
	g++	-c -std=c++11 -Wno-deprecated -Wall 171044039_main.cpp

Iterator.o : Iterator.cpp 
	g++	-c -std=c++11 -Wno-deprecated -Wall Iterator.cpp

HashSet.o : HashSet.cpp 
	g++	-c -std=c++11 -Wno-deprecated -Wall HashSet.cpp

LinkedList.o : LinkedList.cpp 
	g++	-c -std=c++11 -Wno-deprecated -Wall LinkedList.cpp

ArrayList.o : ArrayList.cpp 
	g++	-c -std=c++11 -Wno-deprecated -Wall ArrayList.cpp

Collection.o : Collection.cpp 
	g++	-c -std=c++11 -Wno-deprecated -Wall Collection.cpp

Set.o : Set.cpp
	g++	-c -std=c++11 -Wno-deprecated -Wall Set.cpp

Queue.o : Queue.cpp 
	g++	-c -std=c++11 -Wno-deprecated -Wall Queue.cpp

List.o : List.cpp 
	g++	-c -std=c++11 -Wno-deprecated -Wall List.cpp 

clean:
	rm *.o run
