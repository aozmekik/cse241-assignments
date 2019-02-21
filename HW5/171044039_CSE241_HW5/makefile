shapes = Rectangle.o Triangle.o Circle.o

objects = ComposedShape.o PolygonDyn.o Shape.o PolygonVect.o Polygon.o

run : 171044039_main.o $(shapes) $(objects) 
	g++ $(shapes) $(objects) 171044039_main.o -o run  

ComposedShape.o : ComposedShape.cpp ComposedShape.h Shape.o
	g++ -c -std=c++11 -Wall ComposedShape.cpp 
	
Rectangle.o : Rectangle.cpp Rectangle.h Shape.o
	g++ -c -std=c++11 -Wall Rectangle.cpp

Circle.o : Circle.cpp Circle.h Shape.o
	g++ -c -std=c++11 -Wall Circle.cpp

Triangle.o : Triangle.cpp Triangle.h Shape.o
	g++ -c -std=c++11 -Wall Triangle.cpp

Shape.o : Shape.cpp Shape.h
	g++ -c -std=c++11 -Wall Shape.cpp

Polygon.o : Polygon.cpp Polygon.h Shape.o
	g++ -c -std=c++11 -Wall Polygon.cpp

PolygonDyn.o: PolygonDyn.cpp PolygonDyn.h Polygon.o
	g++ -c -std=c++11 -Wall PolygonDyn.cpp

PolygonVect.o: PolygonVect.cpp PolygonVect.h Polygon.o
	g++ -c -std=c++11 -Wall PolygonVect.cpp 

171044039_main.o : 171044039_main.cpp $(shapes) $(objects) Shape.o
	g++ -c -std=c++11 -Wall 171044039_main.cpp 

clean:
	rm *.o *.svg run 

