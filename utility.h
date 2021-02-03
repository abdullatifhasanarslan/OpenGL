#ifndef UTILITY_H
#define UTILITY_H
#include "Variables.h"
#include <GL/glut.h>
#include <string>
#define Line(x1,y1,x2,y2) 	glBegin(GL_LINES);\
								glVertex2f((x1),(y1));\
								glVertex2f((x2),(y2));\
							glEnd();

#define Rectangle(x1,y1,x2,y2) 	glBegin(GL_POLYGON);\
								glVertex2f((x1),(y1));\
								glVertex2f((x2),(y1));\
								glVertex2f((x2),(y2));\
								glVertex2f((x1),(y2));\
							glEnd();

string int_to_string(int a){
	string str = std::to_string(a);
	return str;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Variable<T>& variable) {
    out << variable.name << "=" << variable.value;
    return out;
}

// void RenderString(int x, int y, const std::string &string){
// 	glColor3d(1.0, 0.0, 0.0);
// 	glRasterPos2f(x,y);
// 	for(uint n=0; n<string.size(); n++){
// 		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[n]);
// 	}
// }

/*
GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18
*/

#endif