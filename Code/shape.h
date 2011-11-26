// Changelog 14.02.2001

#ifndef __Shape__ 
#define __Shape__

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include <iostream>

#include "geometry.h"

void Shade(GLfloat,GLfloat,GLfloat);

class Cube {
protected:
  Vector a;
  Vector b;
public:
  Cube(const Vector&,const Vector&);
  virtual void Render();
};



class PrismTriangle:public Triangle {
protected:
  double h;
public:
  PrismTriangle(const Vector&,const Vector&,const Vector&,const double&);
  PrismTriangle(const Triangle&,const double&);
  virtual void Render();
};

class PrismQuad:public Quadrangle {
protected:
  double h;
public:
  PrismQuad(const Vector&,const Vector&,const Vector&,const Vector&,const double&);
  PrismQuad(const Quadrangle&,const double&);
  virtual void Render();

  static std::vector <double> face1;
  static std::vector <double> faces;


  static unsigned int nbQuad;
};

class PrismPent:public Pentangle {
protected:
  double h;
public:
  PrismPent(const Vector&,const Vector&,const Vector&,const Vector&, const Vector&,const double&);
  PrismPent(const Pentangle&,const double&);
  virtual void Render();
};


// Permet de definir une matiere a partir d'une couleur
inline void GlutShade(GLfloat r,GLfloat v,GLfloat b)
{
  // Couleur sans lumieres
  glColor3f(0.2,0.7,0.6);

  // Couleur avec lumieres
  GLfloat color[4];

  // La couleur diffuse sera egale a 87,5% de la couleur
  color[0]=0.875f*r;
  color[1]=0.875f*v;
  color[2]=0.875f*b;
  color[3]=1.0;

  glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

  // La couleur ambiante sera egale a 12,5% de la couleur
  color[0]=0.125f*r;
  color[1]=0.125f*v;
  color[2]=0.125f*b;
  color[3]=1.0;

  glMaterialfv(GL_FRONT, GL_AMBIENT, color); // GL_AMBIENT_AND_DIFFUSE

  color[0]=1.0f;
  color[1]=0.0f;
  color[2]=0.0f;
  color[3]=1.0;

  glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, color);
}



#endif
