objects = Rectangle.o Triangle.o Circle.o ComposedShape.o

hw : $(objects) 171044039_main.o 
	g++ -o hw 171044039_main.o $(objects) && ./hw
 
ComposedShape.o : ComposedShape.cpp ComposedShape.h
	g++ -c -std=c++11 -Wall ComposedShape.cpp

Rectangle.o : Rectangle.cpp Rectangle.h
	g++ -c -std=c++11 -Wall Rectangle.cpp

Circle.o : Circle.cpp Circle.h
	g++ -c -std=c++11 -Wall Circle.cpp

Triangle.o : Triangle.cpp Triangle.h
	g++ -c -std=c++11 -Wall Triangle.cpp

171044039_main.o : 171044039_main.cpp
	g++ -c -std=c++11 -Wall 171044039_main.cpp

clean:
	rm *.o hw 


