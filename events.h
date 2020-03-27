#ifndef EVENTS_H
#define EVENTS_H 

void reshape(int w, int h);
void keyPressed(unsigned char key, int x, int y);
void specialPressed(int key, int x, int y);
void mousePressed(int button, int state, int x, int y);
void mouseDragged(int x, int y);
void IDLE();
#endif