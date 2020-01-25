#include <iostream>
#include "utility.h"
#include "Variables.cpp"
#include <string>

#define Line(x1,y1,x2,y2) 	glBegin(GL_LINES);\
								glVertex2f((x1),(y1));\
								glVertex2f((x2),(y2));\
							glEnd();
/*
void print(std::string text, int x, int y){
    void* font = GLUT_BITMAP_9_BY_15;

    for (std::string::iterator i = text.begin(); i != text.end(); ++i)
    {
        char c = *i;
        //this does nothing, color is fixed for Bitmaps when calling glRasterPos
        //glColor3f(1.0, 0.0, 1.0); 
        glutBitmapCharacter(font, c);
    }
}
*/