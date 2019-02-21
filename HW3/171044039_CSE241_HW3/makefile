objects = Rectangle.o Triangle.o Circle.o ComposedShape.o 

hw : $(objects) main.o 
	g++ -o hw main.o $(objects) 
 
ComposedShape.o : ComposedShape.cpp ComposedShape.h
	g++ -c -std=c++11 -Wall ComposedShape.cpp
	
Rectangle.o : Rectangle.cpp Rectangle.h
	g++ -c -std=c++11 -Wall Rectangle.cpp

Circle.o : Circle.cpp Circle.h
	g++ -c -std=c++11 -Wall Circle.cpp

Triangle.o : Triangle.cpp Triangle.h
	g++ -c -std=c++11 -Wall Triangle.cpp

main.o : main.cpp
	g++ -c -std=c++11 -Wall main.cpp

run : hw
	./hw

clean:
	rm *.o hw 

