

In this homework, you will write your first classes for the shapes. For each class you will write its
own header .h file and .cpp file for the separation of interface and implementation. As expected, you
should follow all object-oriented programming principles.

You will have 3 basic shape classes: **Rectangle, Triangle, Circle**. These classes are
defined as explained in HW1. They should have appropriate constructors, setter/getter functions for
their shape sizes and positions.

You will also have **ComposedShape** class that has a container shape and inner small shapes. This
class will hold two shape objects using composition in it. Many overloaded constructors for the class
should have parameters for container shape and inner small shape with different types. This class
should also have an **optimalFit** function that that fits inner small shapes into the container shape.
The optimized small shapes will be kept in a **vector** of shapes, which should have a getter function.

All of the above classes will have a **draw** member function that will take an **ofstream** object as
parameter and it will draw the shape in that file using SVG format.

You will also write a driver file that contains your main function. Your driver should make at least 4
objects of each class and should make array of objects of each class. Test each member function for
each class. You should include the result SVG files from the draw functions in your submission.

Notes:

- Do not use any C++ features that we did not learn during the lectures.
- You will use all the object oriented techniques that we learned in the class including **const,**
    **inline, declrtype, auto** keywords.
- Do not use anything that we did not learn in the lectures.
- Do not forget to indent your code and provide comments.
- You should submit your work to the moodle page.
- You should submit the SVG files, the header and source code files and sample output results.


