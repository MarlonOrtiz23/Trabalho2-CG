#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#include <sstream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
GLfloat fAspect = 2, angle = 90;
int x_ini,y_ini,bot;

int movZ1 = -1000; // movimento em Z dos objetos (posição inicial em Z)
int movZ2 = -1500;
int movZ3 = -2000;
int movZ4 = -2500;
int movZ5 = -3000;
int ran1;          // RANDOM X NUMBERS
int ran2;
int ran3;
int ran4;
int ran5;
int tx,ty = 1; // transladação da spaceship
int life = 100;
int score = 0;
int level = 1;

GLfloat luzAmbiente[4]={0.5,0.5,0.5,1.0};
GLfloat luzDifusa[4]={0.5,0.5,0.5,1.0};		 // "cor"
GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
GLfloat posicaoLuz[4]={40,50,0,1.0};

#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	30.0

using namespace std;

void PosicionaObservador(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(-obsX,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	gluLookAt(0.0,40.0,100, 0.0,0.0,0.0, 0.0,1.0,0.0);
}

void drawPlane()
{
  glBegin(GL_POLYGON);
    glVertex3f(1,0,1);
    glVertex3f(1,0,-1);
    glVertex3f(-1,0,-1);
    glVertex3f(-1,0,1);
  glEnd();
}

void drawSpaceship()
{
  glBegin(GL_TRIANGLES);
    glVertex3f(0,0.5,-1);
    glVertex3f(-1,0,0);
    glVertex3f(1,0,0);
  glEnd();
}

void drawObstacles()
{
  glBegin(GL_QUADS);
    glVertex3f(-1,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
  glEnd();
}

void Objetos(void)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
  // DRAW PLANE
  glPushMatrix();
    glColor3f(0.133, 0.545, 0.133); //forestGreen
    glScalef(1000,1000,1000);
    drawPlane();
  glPopMatrix();

  // DRAW SPACESHIP
  glPushMatrix();
    glColor4f(0.9,0.1,0.1,1.0);
    //glTranslated(0,30,85);
    glTranslated(tx,ty+30,80);
    glScalef(3,3,1);
    drawSpaceship();
  glPopMatrix();

  // DRAW OBSTACLES SEQUENCE
  glPushMatrix(); //1
    glColor4f(0.0,0.0,0.0,1.0);
    glTranslated(ran1,-10,movZ1);
    glScalef(2,1000,1);
    drawObstacles();
  glPopMatrix();

  glPushMatrix(); //2
    glColor4f(0.0,0.0,0.0,1.0);
    glTranslated(ran2,-10,movZ2);
    glScalef(2,1000,1);
    drawObstacles();
  glPopMatrix();

  glPushMatrix(); //3
    glColor4f(0.0,0.0,0.0,1.0);
    glTranslated(ran3,-10,movZ3);
    glScalef(2,1000,1);
    drawObstacles();
  glPopMatrix();

  glPushMatrix(); //4
    glColor4f(0.0,0.0,0.0,1.0);
    glTranslated(ran4,-10,movZ4);
    glScalef(2,1000,1);
    drawObstacles();
  glPopMatrix();

  glPushMatrix(); //5
    glColor4f(0.0,0.0,0.0,1.0);
    glTranslated(ran5,-10,movZ5);
    glScalef(2,1000,1);
    drawObstacles();
  glPopMatrix();

  //glutSwapBuffers();
}

void levelStatus(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000/2, 1000/2, -600/2, 600/2, -1000.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(-450,220,0);
    glScalef(0.3,0.3,0.3);
    string levell;
    std::ostringstream oss;
    oss << level;
    levell = oss.str();
    string s = "LEVEL: "+levell;
    void *font = GLUT_STROKE_ROMAN;
    for (string::iterator i = s.begin(); i != s.end(); ++i)
    {
    char c = *i;
    glutStrokeCharacter(font, c);
    }
    glPopMatrix();
    //glutSwapBuffers();
}

void lifeStatus(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000/2, 1000/2, -600/2, 600/2, -1000.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(-450,-250,0);
    glScalef(0.3,0.3,0.3);
    string lifee;
    std::ostringstream oss;
    oss << life;
    lifee = oss.str();
    string s = "LIFE: "+lifee;
    void *font = GLUT_STROKE_ROMAN;
    for (string::iterator i = s.begin(); i != s.end(); ++i)
    {
    char c = *i;
    glutStrokeCharacter(font, c);
    }
    glPopMatrix();
    //glutSwapBuffers();
}

void scoreStatus(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000/2, 1000/2, -600/2, 600/2, -1000.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0,0,0);
    glPushMatrix();
    glTranslatef(250,-250,0);
    glScalef(0.3,0.3,0.3);
    string scoree;
    std::ostringstream oss;
    oss << score;
    scoree = oss.str();
    string s = "SCORE: "+scoree;
    void *font = GLUT_STROKE_ROMAN;
    for (string::iterator i = s.begin(); i != s.end(); ++i)
    {
    char c = *i;
    glutStrokeCharacter(font, c);
    }
    glPopMatrix();
    //glutSwapBuffers();
}

void EspecificaParametrosVisualizacao(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle,fAspect,0.1,1000);
    PosicionaObservador();
}

void DefineIluminacao()
{
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
	//Desabilita iluminacao para desenhar a esfera
	glDisable(GL_LIGHTING);
	//Desenha esfera na posição da fonte de luz
	glPushMatrix();
	glTranslatef(posicaoLuz[0], posicaoLuz[1], movZ1+25);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(5, 50, 50);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Inicializa (void)
{
	// Especifica que a cor de fundo da janela será preta
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	DefineIluminacao();
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
}

void Desenha(void)
{
	glClearColor(0.118, 0.565, 1.000, 1.0); //skyBlue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	EspecificaParametrosVisualizacao();
    Objetos();
    DefineIluminacao();
    lifeStatus();
    scoreStatus();
    levelStatus();
    glutSwapBuffers();
}

void Teclado (unsigned char key, int x, int y)
{
    printf("%d\n",key);
	if (key == 27)
		exit(0);
}

void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os parâmetros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

/*void GerenciaMovim(int x, int y)
{
	if(bot==GLUT_LEFT_BUTTON)
	{
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		int deltaz = y_ini - y;
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}

	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}*/

void moveNave(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
		tx-=1;
		int deltax = x_ini - tx;
        rotY = rotY_ini - deltax/SENS_ROT;
		if(tx<-10)
            tx = -10;
	}
	if(key == GLUT_KEY_RIGHT){
		tx+=1;
		int deltax = x_ini - tx;
        rotY = rotY_ini - deltax/SENS_ROT;
        if(tx>10)
            tx=10;
	}
	if(key == GLUT_KEY_DOWN){
		ty-=1;
		int deltay = y_ini - ty;
		rotX = rotX_ini - deltay/SENS_ROT;
		if(ty<-5)
            ty = -5;
	}
	if(key == GLUT_KEY_UP){
		ty+=1;
		int deltay = y_ini - ty;
		rotX = rotX_ini - deltay/SENS_ROT;
        if(ty>5)
            ty=5;
	}
	glutPostRedisplay();
}

void atualizaVariaveis(){
    movZ1 += level+7;  // movimento dos objetos
    if(movZ1 > 100){
            movZ1 = -2500;
            ran1 = rand() % 20 - 10;
            score += 10;
    }
    movZ2 += level+7;  // movimento dos objetos
    if(movZ2 > 100){
            movZ2 = -2500;
            ran2 = rand() % 20 - 10;
            score += 10;
    }
    movZ3 += level+7;  // movimento dos objetos
    if(movZ3 > 100){
            movZ3 = -2500;
            ran3 = rand() % 20 - 10;
            score += 10;
    }
    movZ4 += level+7;  // movimento dos objetos
    if(movZ4 > 100){
            movZ4 = -2500;
            ran4 = rand() % 20 - 10;
            score += 10;
    }
    movZ5 += level+7;  // movimento dos objetos
    if(movZ5 > 100){
            movZ5 = -2500;
            ran5 = rand() % 20 - 10;
            score += 10;
            level += 1;
    }

}

void gameover(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000/2, 1000/2, -600/2, 600/2, -1000.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(-250,0,0);
    glScalef(0.6,0.6,0.6);
    string s = "GAME OVER";
    void *font = GLUT_STROKE_ROMAN;
    for (string::iterator i = s.begin(); i != s.end(); ++i)
    {
    char c = *i;
    glutStrokeCharacter(font, c);
    }
    glPopMatrix();
    glutSwapBuffers();
    Sleep(5000);
    exit(0);
}

void colisao(){ // spaceship: x = 0,-3,3; y= 0,0,0; z=0,3,3;
    int tzi = 80; // posição Z da spaceship  // tx = posição X
    if(tzi-5 < movZ1 && movZ1 < tzi+5){
            if(tx-5 < ran1 && ran1 < tx+5){
                    life -= 5;
                    PlaySound("crash.wav",NULL,SND_ASYNC|SND_FILENAME);
            }
    }
    if(tzi-5 < movZ2 && movZ2 < tzi+5){
            if(tx-5 < ran2 && ran2 < tx+5){
                    life -= 5;
                    PlaySound("crash.wav",NULL,SND_ASYNC|SND_FILENAME);
            }
    }
    if(tzi-5 < movZ3 && movZ3 < tzi+5){
            if(tx-5 < ran3 && ran3 < tx+5){
                    life -= 5;
                    PlaySound("crash.wav",NULL,SND_ASYNC|SND_FILENAME);
            }
    }
    if(tzi-5 < movZ4 && movZ4 < tzi+5){
            if(tx-5 < ran4 && ran4 < tx+5){
                    life -= 5;
                    PlaySound("crash.wav",NULL,SND_ASYNC|SND_FILENAME);
            }
    }
    if(tzi-5 < movZ5 && movZ5 < tzi+5){
            if(tx-5 < ran5 && ran5 < tx+5){
                    life -= 5;
                    PlaySound("crash.wav",NULL,SND_ASYNC|SND_FILENAME);
            }
    }
    if(life <= 0) gameover();
}

void TimerFunction( int value ){
    colisao();
    atualizaVariaveis();
    glutPostRedisplay();          //Atualiza a tela
    glutTimerFunc(33, TimerFunction, 1); //Faz a nova chamada para a função;
}
//MENU
/*
const int MENU_START = 1; // purely arbitrary values which
const int MENU_EXIT = 2; // will be used in a switch
const int MAIN_MENU = 3; // in the appropriate function.
const int MENU_CONTROLS = 4;
int MainMenuID;
int ControlsMenuID;
int GameID;

void MainMenu( int value )
{
  switch(value)
  {
  case MENU_START:
     glutSetMenu(GameID); // set the current menu
     break;
  case MENU_CONTROLS:
     glutSetMenu(ControlsMenuID); // set the current menu
     break;
  case MENU_EXIT:
     exit(1);
     break;
  }
}

void MainMenuCallback(int value)
{
  switch( value )
  {
  case MAIN_MENU:
     glutSetMenu(MainMenuID); // set the current menu
     break;
  }
}*/

int main(void)
{
    srand (time(NULL)); // initialize random seed
    ran1 = rand() % 20 - 10; // RANDOM NUMBERS [-10,10]
    ran2 = rand() % 20 - 10;
    ran3 = rand() % 20 - 10;
    ran4 = rand() % 20 - 10;
    ran5 = rand() % 20 - 10;
    PlaySound("sound.wav",NULL,SND_ASYNC|SND_FILENAME);
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(1000,600);
	glutCreateWindow("Spaceship Game");
    glutTimerFunc(33, TimerFunction, 1); // 33 ms
	glutDisplayFunc(Desenha);
	glutKeyboardFunc (Teclado);
	glutSpecialFunc(moveNave);
	Inicializa();
	//glutMotionFunc(GerenciaMovim);
	//glutMouseFunc(GerenciaMouse);

    //MENU
    /*
    MainMenuID = glutCreateMenu(MainMenu); // implicitely "current menu"
    glutAddMenuEntry("START",MENU_START);
    glutAddMenuEntry("EXIT",MENU_EXIT);
    ControlsMenuID = glutCreateMenu(MainMenuCallback); // implicitely "current menu"
    glutAddSubMenu("CONTROLS",MainMenuID);
    glutAddMenuEntry("BACK",MAIN_MENU);
    int WindowID = glutCreateWindow("MENU"); // // implicitely "current window"
    glutAttachMenu(GLUT_MIDDLE_BUTTON); // The middle button triggers the menu.
    */

	glutMainLoop();

	return 0;
}
