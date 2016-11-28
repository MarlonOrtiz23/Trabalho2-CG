#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>

GLfloat angle = 0.0;	/*Rotationsvinkel*/

void createMenu(void);
void menu(int value);
void disp(void);

static int win;
static int menyid;
static int animeringsmeny;
static int springmeny;
static int val = 0;
static int fyrkantRoed = 1;
static int fyrkantGroen = 0;
static int fyrkantBla = 0;
static int trekantRoed = 1;
static int trekantGroen = 0;
static int trekantBla = 0;

int main(void){

	// normal initialisation
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(450,450);
	glutCreateWindow("Movimenta��o 3D");
    createMenu();
	glutMainLoop();

}
void createMenu(void){
	//////////
	// MENU //
	//////////

	// Create a submenu, this has to be done first.
	animeringsmeny = glutCreateMenu(menu);

	// Add sub menu entry
	glutAddMenuEntry("P�", 1);
	glutAddMenuEntry("Av", 2);

	springmeny = glutCreateMenu(menu);

	glutAddMenuEntry("G�", 3);
	glutAddMenuEntry("Galopp", 4);

	// Create the menu, this menu becomes the current menu
	menyid = glutCreateMenu(menu);

	// Create an entry
	glutAddSubMenu("Animering", animeringsmeny);
	glutAddSubMenu("L�pstil", springmeny);
	// Create an entry
	glutAddMenuEntry("Avluta", 0);

	// Let the menu respond on the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);


}

void disp(void){
	// Just clean the screen
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(fyrkantRoed, fyrkantGroen, fyrkantBla);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-0.75f, -1.0f);
    glVertex2f(-0.75f, -0.75f);
    glVertex2f (-1.0f, -0.75f);
    glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(trekantRoed, trekantGroen, trekantBla);
    glVertex2f(-0.6f, -1.0f);
    glVertex2f(-0.4f, -1.0f);
    glVertex2f(-0.6f, -0.6f);
    glEnd();

	// �ndra f�rg beroende p� menyval
	if(val == 1){
		trekantBla = 1;
		trekantRoed = 0;
		trekantGroen = 0;
	}
	else if(val == 2){
		trekantBla = 0;
		trekantRoed = 1;
		trekantGroen = 0;
	}
	else if(val == 3){
		fyrkantRoed = 0;
		fyrkantGroen = 0;
		fyrkantBla = 1;
	}
	else if(val == 4){
		fyrkantRoed = 1;
		fyrkantGroen = 0;
		fyrkantBla = 0;
	}
	glFlush();
}



void menu(int value){
	if(value == 0){
		glutDestroyWindow(win);
		exit(0);
	}else{
		val=value;
	}

	// you would want to redraw now
	glutPostRedisplay();
}
