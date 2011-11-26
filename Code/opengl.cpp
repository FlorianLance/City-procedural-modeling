// Affichage OpenGL
// Changelog 06.02.2002

#include <time.h>

#include "vector.h"
#include "city.h"
#include "shape.h"

// Identifiant d'une cité
GLuint cut;


// Parametre global de temps
float t=0.0f;


#include "Camera.h"

Camera cam;

// Code ASCII
#define ESCAPE 27
#define PAGE_UP 73
#define PAGE_DOWN 81
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

void processMouseActiveMotion(int x, int y);
void processMousePassiveMotion(int x, int y);
void processMouse(int button, int state, int x, int y);
void specialKeyPressed(int key, int x, int y);




// Angle
float alpha=0.0f;

int Mousekey=0,Mousex,Mousey;

int light=1;
int rotate=1; 


// Identifiant de fenetre
int window;

GLuint GenerateCity()
{
  GLuint list=glGenLists(1);

  // Optimize list
  glNewList(list,GL_COMPILE);

  glEnable(GL_COLOR_MATERIAL);

  GlutShade(0.9,0.9,0.9);

  City city;
  city.Generate();

  // Fin de la liste
  glEndList();

  return list;
}


// Gestion du clavier.
void Keyboard(unsigned char key, int x, int y)
{
  // Si ESC
  if (key==27)
  {
    glutDestroyWindow(window); 
    exit(0);
  }
  // Gestion des lumieres
  if ((key=='l') || (key=='L'))
  {
    light = 1-light;
    if (!light) 
    {
      glDisable(GL_LIGHTING);
    } 
    else 
    {
      glEnable(GL_LIGHTING);
    }
  }
  if ((key=='r') || (key=='R'))
  {
    rotate = 1-rotate;
  }

  glutPostRedisplay();
}

void Resize(int width, int height)
{
  if (height==0)				
  {
    height=1;
  }
  // Set window
  glViewport (0, 0, width, height);

  // Define the projection matrix
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();  
  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,2.0f,500.0f);

  // Back to model space
  glMatrixMode(GL_MODELVIEW);
}


// Affichage
void GlutRendering()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();


  camSetGL(cam);


  gluLookAt(120.0, 120.0, 150, //position de la caméra
    0, 0, 0, //point visé par la caméra
    0, 0, 1); //rotaions

	//gluLookAt(50, 0, 200, //position de la caméra
 //   0, 0, 0, //point visé par la caméra
 //   0, 0, 1); //rotaions

  //if (rotate)
  //{
  //  alpha+=0.25/3;
  //}
  //glRotatef(alpha/2,0.0f,0.0f,1.0f);

  glCallList(cut);

  glutSwapBuffers();
}

void MouseMove(int x, int y)
{
  Mousex = x;
  Mousey = y;
}

void MousePush(int button, int state, int x, int y)
{

  Mousex = x;
  Mousey = y;
  Mousekey=button;
}

// Rafraichissement
void GlutIdle(void)
{
  // Augmentation du parametre de temps
  t+=1.0;
  GlutRendering();
}

//!Initialise OpenGL
void InitGlut(int width,int height)
{  
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);

  // Fenetre initiale
  glutInitWindowSize(800, 450);  
  glutInitWindowPosition(0, 0);  
  window=glutCreateWindow("City Generator");

  glutDisplayFunc(GlutRendering);
  //glutFullScreen();

  // Rafraichissement
  glutIdleFunc(&GlutIdle);

  // Changement de taille
  glutReshapeFunc(Resize);

  // Clavier
  glutKeyboardFunc(Keyboard);
  //glutSpecialFunc(&SpecialKeyboard);

  // Souris
  glutMouseFunc(MousePush);
  glutMotionFunc(MouseMove);

  // Initialise les parametres de rendu
  glClearColor (0.5f, 0.6f, 0.7f, 1.0);

  glClearDepth(1.0);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);	
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glShadeModel(GL_SMOOTH);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix


  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,2.0f,500.0f);

  // Placement des lumieres dans l'espace du modele
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();				// Reset The Projection Matrix

  GLfloat light_ambient1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  GLfloat light_diffuse1[] = { 0.7f, 0.7f, 0.6f, 1.0f };
  GLfloat light_position1[] = { -50.0,-50.0, 200.0,0.0 };

  GLfloat light_ambient2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  GLfloat light_diffuse2[] = { 0.6f, 0.6f, 0.7f, 1.0f };
  GLfloat light_position2[] = { 50.0,50.0, 200.0,0.0 };

  glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient1);
  glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
  glLightfv (GL_LIGHT1, GL_POSITION, light_position1);
  glEnable(GL_LIGHT1); 

  glLightfv (GL_LIGHT2, GL_AMBIENT, light_ambient2);
  glLightfv (GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
  glLightfv (GL_LIGHT2, GL_POSITION, light_position2);
  glEnable(GL_LIGHT2); 

  glEnable(GL_LIGHTING);

  // Elimination des facettes arriere
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);



  
	// quand une touche speciale est pressee
	glutSpecialFunc(&specialKeyPressed);

	// mouse
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutPassiveMotionFunc(processMousePassiveMotion);

	camSetGL(cam);

	

  cut=GenerateCity();
}

int main(int argc,char **argv)
{

  srand(time(NULL));

  glutInit(&argc, argv);

  InitGlut(512,512);
  glutMainLoop();
  return 0;
}







//The function called whenever a normal key is pressed.
void specialKeyPressed(int key, int x, int y)
{
    // avoid thrashing this procedure 
//    sleep(100);

    const float stepR=2;
    const int stepL=1;

    if (glutGetModifiers()==GLUT_ACTIVE_CTRL)
    {
        switch (key)
        {
        case GLUT_KEY_UP:
            camTurnUpDown( cam, -stepR);
            break;

        case GLUT_KEY_DOWN:
            camTurnUpDown( cam, stepR);
            break;

        case GLUT_KEY_LEFT:
            camTurnLeftRight( cam, -stepR);
            break;

        case GLUT_KEY_RIGHT:
            camTurnLeftRight( cam, stepR);
            break;
        }
    }
    else if (glutGetModifiers()!=GLUT_ACTIVE_ALT)
    {
        switch (key)
        {
        case GLUT_KEY_PAGE_UP:
            camTranslate( cam, UP);
            break;

        case GLUT_KEY_PAGE_DOWN:
            camTranslate( cam, DOWN);
            break;
        case GLUT_KEY_UP:
            camTranslate( cam, FRONT);
            break;

        case GLUT_KEY_DOWN:
            camTranslate( cam, BACK);
            break;

        case GLUT_KEY_LEFT:
            camTranslate( cam, LEFT);
            break;

        case GLUT_KEY_RIGHT:
            camTranslate( cam, RIGHT);
            break;
        default:
            //~ printf ("Special key %d pressed. No action there yet.\n", key);
            break;
        }
    }
}


void processMouse(int button, int state, int x, int y)
{
//    printf("processMouse\n");
    int specialKey;
    specialKey = glutGetModifiers();

    camStartMove( cam, CAMERA_STOP, x, y);

    if ((state == GLUT_DOWN)) // && (specialKey == GLUT_ACTIVE_ALT))
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            camStartMove( cam, CAMERA_ROTATION, x, y);
        }
        else if (button == GLUT_RIGHT_BUTTON)
        {
            camStartMove( cam, CAMERA_TRANSLATION, x, y);
        }
    }
}


void processMouseActiveMotion(int x, int y)
{
//    printf("processMouseActiveMotion\n");
    camMove( cam, x, y);
}

void processMousePassiveMotion(int x, int y)
{
    //printf("processMousePassiveMotion\n");
}

