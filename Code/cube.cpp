
#include <GL/glew.h>
#include <GL/glut.h>									
#include <GL/glu.h>
#include <GL/gl.h>	

#include "shape.h"

Cube::Cube(const Vector& a,const Vector& b)
{
  Cube::a=a;
  Cube::b=b;
}

void Cube::Render()
{
  glBegin(GL_QUADS);

  // Face z=-1
  glNormal3f( 0.0f, 0.0f,-1.0f);
  glVertex3f(a[0],a[1],a[2]);
  glVertex3f(a[0],b[1],a[2]);
  glVertex3f(b[0],b[1],a[2]);
  glVertex3f(b[0],a[1],a[2]);

  // Face z=+1
  glNormal3f( 0.0f, 0.0f,1.0f);
  glVertex3f(a[0],a[1],b[2]);
  glVertex3f(b[0],a[1],b[2]);
  glVertex3f(b[0],b[1],b[2]);
  glVertex3f(a[0],b[1],b[2]);

  // Face x=-1
  glNormal3f(-1.0f,0.0f,0.0f);
  glVertex3f(a[0],a[1],a[2]);
  glVertex3f(a[0],b[1],a[2]);
  glVertex3f(a[0],b[1],b[2]);
  glVertex3f(a[0],a[1],b[2]);

  // Face x=+1
  glNormal3f(1.0f, 0.0f, 0.0f);
  glVertex3f(b[0],a[1],a[2]);
  glVertex3f(b[0],b[1],a[2]);
  glVertex3f(b[0],b[1],b[2]);
  glVertex3f(b[0],a[1],b[2]);

  // Face y=-1
  glNormal3f( 0.0f,-1.0f, 0.0f);
  glVertex3f(a[0],a[1],a[2]);
  glVertex3f(b[0],a[1],a[2]);
  glVertex3f(b[0],a[1],b[2]);
  glVertex3f(a[0],a[1],b[2]);

  // Face y=+1
  glNormal3f( 0.0f,1.0f, 0.0f);
  glVertex3f(a[0],b[1],a[2]);
  glVertex3f(a[0],b[1],b[2]);
  glVertex3f(b[0],b[1],b[2]);
  glVertex3f(b[0],b[1],a[2]);

  glEnd();
}
