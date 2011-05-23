
#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <GL/glut.h>

using namespace std;

/********
 * Main *
 ********/
 //Display propetries
int WINDOW_WIDTH = 500;
int WINDOW_HEIGHT = 500;

//Timer properties

pthread_t thread;
pthread_mutex_t change;
time_t last;
time_t now;

//Square properties
float x = 0;
float y = 0;
float xsize = 0.2;
float ysize = 0.2;
float vx = 0.002;
float vy = 0.004;
float x2 = 0.5;
float y2 = 0.5;
float x2size = 0.4;
float y2size = 0.4;
float vx2 = -0.003;
float vy2 = -0.0016;

void draw () {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float posx = x;
    float posy = y;
    float posx2 = x2;
    float posy2 = y2;

    glBegin( GL_QUADS );
	    glColor3f( 1.0, 0.2, 0.0 );
	    glVertex2f( posx, posy);
	    glVertex2f( posx + xsize, posy);
	    glVertex2f( posx + xsize, posy + ysize);
	    glVertex2f( posx, posy + ysize);
    glEnd();
    glBegin(GL_QUADS );
	    glColor3f( 0.0, 0.2, 1.0 );
	    glVertex2f( posx2, posy2);
	    glVertex2f( posx2 + x2size, posy2);
	    glVertex2f( posx2 + x2size, posy2 + y2size);
	    glVertex2f( posx2, posy2 + y2size);
    glEnd();

    glFlush();
}

void reshape (int x, int y) {
    WINDOW_WIDTH = x;
    WINDOW_HEIGHT = y;
}

void run (){
    usleep(1000);
    if (x + xsize >= 1 || x <= -1){
        vx = -vx;
    }
    if (y + ysize >= 1 || y <= -1){
        vy = - vy;
    }

    if (x2 + x2size >= 1 || x2 <= -1){
        vx2 = -vx2;
    }
    if (y2 + y2size >= 1 || y2 <= -1){
        vy2 = - vy2;
    }

    float midx = x + xsize/2;
    float midy = y + ysize/2;
    float midx2 = x2 + x2size/2;
    float midy2 = y2 + y2size/2;
    float distx = x2size/2 + xsize/2;
    float disty = y2size/2 + ysize/2;

    if ((fabs(midx - midx2) <= distx)){
        if ((fabs(midy - midy2) <= disty)){
            if (fabs(midx - midx2) > fabs(midy - midy2)) {
                vx = -vx;
                vx2 = -vx2;
            }else {
                vy = -vy;
                vy2 = -vy2;
            }
        }
    }



    x += vx;
    y += vy;
    x2 += vx2;
    y2 += vy2;
    glutPostRedisplay();
}

int main(int argc, char** argv) {

	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-WINDOW_WIDTH)/2,(glutGet(GLUT_SCREEN_HEIGHT)-WINDOW_HEIGHT)/2);
    glutCreateWindow("Colider");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutIdleFunc(run);

    glutMainLoop(  );
    
    return 0;
}
