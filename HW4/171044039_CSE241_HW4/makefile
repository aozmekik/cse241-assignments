shapes = Rectangle.o Triangle.o Circle.o

objects =  Polyline.o Polygon.o ComposedShape.o

run : 171044039_main.o $(shapes) $(objects)
	g++ -o run 171044039_main.o $(shapes) $(objects)

Polygon.o : Polygon.cpp Polygon.h 
	g++ -c -std=c++11 -Wall Polygon.cpp

Polyline.o : Polyline.cpp Polyline.h Polygon.o
	g++ -c -std=c++11 -Wall Polyline.cpp 
 
ComposedShape.o : ComposedShape.cpp ComposedShape.h Polygon.o
	g++ -c -std=c++11 -Wall ComposedShape.cpp 
	
Rectangle.o : Rectangle.cpp Rectangle.h 
	g++ -c -std=c++11 -Wall Rectangle.cpp

Circle.o : Circle.cpp Circle.h
	g++ -c -std=c++11 -Wall Circle.cpp

Triangle.o : Triangle.cpp Triangle.h
	g++ -c -std=c++11 -Wall Triangle.cpp

171044039_main.o : 171044039_main.cpp $(shapes) $(objects)
	g++ -c -std=c++11 -Wall 171044039_main.cpp 

clean:
	rm *.o *.svg run 

