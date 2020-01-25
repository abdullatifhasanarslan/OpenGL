#include <iostream>
#include "utility.h"
#include "Variables.cpp"

#define Line(x1,y1,x2,y2) 	glBegin(GL_LINES);\
								glVertex2f((x1),(y1));\
								glVertex2f((x2),(y2));\
							glEnd();
