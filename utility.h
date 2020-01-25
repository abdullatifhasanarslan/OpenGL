#ifndef UTILITY_H
#define UTILITY_H
#include "Variables.h"
#include <string>
#define Line(x1,y1,x2,y2) 	glBegin(GL_LINES);\
								glVertex2f((x1),(y1));\
								glVertex2f((x2),(y2));\
							glEnd();
template <class T>
std::ostream& operator<<(std::ostream& out, const Variable<T>& variable) {
    out << variable.name << "=" << variable.value;
    return out;
}

void print(std::string text, int x, int y);
#endif