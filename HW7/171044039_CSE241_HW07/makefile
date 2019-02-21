JFLAGS = -g
JC = javac
.SUFFIXES: .java .class

	
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
    Shape.java \
    Rectangle.java \
    Triangle.java \
    Main.java \
    DrawPanel.java \
    Circle.java \
    BadSize.java \
    ComposedShape.java \
    Polygon.java \
    PolygonVect.java \
    PolygonDyn.java \
    Global.java

default: classes

run: classes
	java Main

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class