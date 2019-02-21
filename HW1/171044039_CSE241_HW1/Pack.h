/*
 * Pack.h
 */

#ifndef PACK_H_
#define PACK_H_


#define FILE_NAME "output.svg"

using namespace std;

struct Position{double x,y;}; // a point in the svg coordinate system

enum class Shape{tri, rect, cir};
struct Triangle {double len;};
struct Rectangle {double len1,len2;};
struct Circle{double rad;};

struct Container
{
	// all possible vars in one container 
	Shape main_shape, small_shape;

	Triangle  tri1,tri2;
	Rectangle rect1,rect2;
	Circle 	  cir1,cir2;
};

bool isValid(char chosen_shape); // sayıların da kontrolünü yap
//Post-Condition: given char can not be different than R,C,T 

char inputShape(bool is_main);
// Pre-Condition: 
// True: input of main_shape will be given later on
// False: input of small_shape 
// Helper function of setContainer()
// Post-Condition:
// Returns taken valid character input from user


void setMainShape(Container& c);
void setSmallShape(Container& c);
void setTriangle(Triangle& t);
void setRectangle(Rectangle& r);
void setCircle(Circle& c);
// Pre-Condition:
// Must have initialized container
// Helper functions of setContainer()
// Post-Condition:
// Take only valid input from user for requested shape 


void initContainer(Container& c);
void setContainer(Container& c);
void fitContainer(const Container& c);
// Pre-condition:
// setC must be called after initC 
// fitC must be called aftter setC
// Post-condition:
// setC takes only valid input from user  
// fitc outputs the main container's and packed small shape's svg code 
// into .svg file due to input  


void findBoundingBox(const Container& c, double& box_w, double& box_h);
// Helper function for fitContainer to determine view box of container 

void shiftForward(Position& p, Position shift);
void shiftBackward(Position& p, Position shift);
void shiftTriForward(Position p[], Position shift);
void shiftTriBackward(Position p[], Position shift);
// Shifting functions of 2D points in svg coordinate system
// They are used for not to effect the true values of positions while
// outputting the shapes into .svg in a way that we want  


void printRemainder(int total_shape, double area);
// Helper function for to print the given values to screen 

double areaRect(Rectangle r);
double areaCir(Circle c);
double areaTri(Triangle t);
// Pre-condition:
// Valid values for structure's component's 
// Post-condition:
// Return the area of given shape

void fitRInR(Rectangle r1, Rectangle r2);
void fitRInC(Circle c, Rectangle r);
void fitRInT(Triangle t, Rectangle r);
void fitCInR(Rectangle r, Circle c);
void fitCInC(Circle c1, Circle c2);
void fitTInR(Rectangle r, Triangle t);
void fitCInT(Triangle t, Circle c);
void fitTInC(Circle c, Triangle t);
void fitTInT(Triangle t1,Triangle t2);
// Pre-condition: 
// The structure of fit* functions are all similar to each other
// Must be called within the fitContainer() func which has the header codes of svg
// First parameter of the function must be main container shape(rect1,cir1,tri1)
// Post-condition:
// Output the shape codes into .svg file due to the calculated points for a given case      

int fillRinR(Rectangle r1, Rectangle r2, Position p, bool rotate);
int fillRinC(Circle c, Rectangle r);
int fillRinT(Triangle t, Rectangle r);
int fillCinR(Rectangle r, Circle c, Position p);
int fillCinC(Circle c1, Circle c2);
int fillCinT(Triangle t, Circle c);
int fillTinR(Rectangle r, Triangle t, Position shift);
int fillTinC(Circle c, Triangle t);
int fillTinT(Triangle t1, Triangle t2);
// Pre-Condition:
// Helper functions for fit* funcs, consist similar packing algorithms
// Must not be called alone, 'cause they don't consist header code's for svg
// Post-Condition:
// Returns fitted total shape into main container
// Output shape's svg code   



void printRect(Rectangle r, Position p, bool fill, bool rotate);
void printCir(Circle c, Position p, bool fill);
void printTri(Triangle t, Position p[], bool fill, bool rotate);
// Output the shape with given options into the .svg


int totalRinR(double r1_w,double r1_h, Rectangle r2);
// Returns sum of packed r2 in the r1 before calculating anything  

double circleFunc(double y, double r, Position c, bool small);
bool isInsideCircle(double x, double y, double r, Position c);
// Circle functions are used for to determine the boundaries and
// True points we need 


void setTriPoints(Triangle t, Position p[], double x, double y);
// p[3] for Triangle's points, with given (x,y) finds the rest of
// points and put them into a given array p[3]

#endif /* Pack_h */