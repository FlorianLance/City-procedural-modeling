#include "shape.h"

using namespace std;
//#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>										
#include <GL/glu.h>


std::vector<double> PrismQuad::face1;
std::vector<double> PrismQuad::faces;

/*****************************************
************** TRIANGLE 3D ***************
******************************************/


/*!
\class PrismTriangle shape.h
This class imprements a prism based on a triangle base.
*/

/*!
\brief Creates a prism with a triangle base.
*/
PrismTriangle::PrismTriangle(const Vector& a,const Vector& b,const Vector& c,const double& h):Triangle(a,b,c)
{
  PrismTriangle::h=h;
}

/*!
\brief Creates a prism with a triangle base.
*/
PrismTriangle::PrismTriangle(const Triangle& t,const double& h)
{
  p[0]=t[0];
  p[1]=t[1];
  p[2]=t[2];
  PrismTriangle::h=h;
}
/*!
\brief Renders a triangular prism.
\note This function ommits the lower face of the prism.
*/
void PrismTriangle::Render()
{
  glBegin(GL_TRIANGLES);

  // Face z=+1
  glNormal3f( 0.0f, 0.0f,1.0f);
  glVertex3f(p[0][0],p[0][1],p[0][2]+h);
  glVertex3f(p[1][0],p[1][1],p[1][2]+h);
  glVertex3f(p[2][0],p[2][1],p[2][2]+h);

  glEnd();

  // Other faces
  glBegin(GL_QUADS);

  for (int i=0;i<3;i++)
  {
    int j=(i+1)%3;
    Vector n=(p[j]-p[i])/Vector(0,0,1);
    n/=Norm(n);
    glNormal3f(n[0],n[1],0.0f);
    glVertex3f(p[i][0],p[i][1],p[i][2]);
    glVertex3f(p[j][0],p[j][1],p[j][2]);
    glVertex3f(p[j][0],p[j][1],p[j][2]+h);
    glVertex3f(p[i][0],p[i][1],p[i][2]+h);
  }

  glEnd();
}



/*****************************************
************** QUADRANGLE 3D *************
******************************************/


/*!
\class PrismQuad shape.h
\brief This class Implements a prism based on a quadrangle.
*/

/*!
\brief Creates a prism with a quadrangle base.
*/
unsigned int PrismQuad::nbQuad = 0;

PrismQuad::PrismQuad(const Vector& a,const Vector& b,const Vector& c,const Vector& d,const double& h):Quadrangle(a,b,c,d)
{
  PrismQuad::h=h;
}

/*!
\brief Creates a prism with a quadrangle base.
*/
PrismQuad::PrismQuad(const Quadrangle& q,const double& h)
{
  p[0]=q[0];
  p[1]=q[1];
  p[2]=q[2];
  p[3]=q[3];
  PrismQuad::h=h;
}

/*!
\brief Renders a quadrilateral prism.
\note This function ommits the lower face of the prism.
*/
void PrismQuad::Render()
{
  glBegin(GL_QUADS);
  glColor3ub(Vector::col1,Vector::col2,Vector::col3);
  // Face z=+1
  glNormal3f( 0.0f, 0.0f,1.0f);
  glVertex3f(p[0][0],p[0][1],p[0][2]+h);
  glVertex3f(p[1][0],p[1][1],p[1][2]+h);
  glVertex3f(p[2][0],p[2][1],p[2][2]+h);
  glVertex3f(p[3][0],p[3][1],p[3][2]+h);


   int i,j;
/*
   for(unsigned int i=0; i<3; i++) row.push_back(1);
*/

    /*face1.push_back(0.0f);
	face1.push_back(0.0f);
	face1.push_back(1.0f);*/
	for(i=0;i<=3;i++)
	{
		for(j=0;j<=1;j++)
			face1.push_back(p[i][j]);
		if(j==2)
			face1.push_back(p[i][j]+h);
	}
  
  glEnd();

  // Other faces
  glBegin(GL_QUADS);
  glColor3ub(Vector::col1,Vector::col2,Vector::col3);
  
  for (int i=0;i<4;i++)
  {
    int j=(i+1)%4;
    Vector n=(p[j]-p[i])/Vector(0,0,1);
    n/=Norm(n);
    glNormal3f(n[0],n[1],0.0f);
    glVertex3f(p[i][0],p[i][1],p[i][2]);
    glVertex3f(p[j][0],p[j][1],p[j][2]);
    glVertex3f(p[j][0],p[j][1],p[j][2]+h);
    glVertex3f(p[i][0],p[i][1],p[i][2]+h);

  /*faces.push_back(n[0]);
  faces.push_back(n[1]);
  faces.push_back(0.0f);*/
  }

  //-------- EXPORT ------------->

  for (int i=0; i<=3 ;i++)
  {
	  for(j=0;j<=2;j++)
		  faces.push_back(p[i][j]);
	  for(j=0;j<=2;j++)
		  faces.push_back(p[(i+1)%4][j]);
	  for(j=0;j<=1;j++)
		  faces.push_back(p[(i+1)%4][j]);
	  if(j==2)
		  faces.push_back(p[(i+1)%4][j]+h);
	  for(j=0;j<=1;j++)
		  faces.push_back(p[i][j]);
	  if(j==2)
		  faces.push_back(p[i][j]+h);
  }

  glEnd();

  nbQuad++;
}


/*****************************************
************** PINTANGLE 3D **************
******************************************/

/*!
\class PrismPent shape.h
\brief This class Implements a prism based on a pentangle.
*/

/*!
\brief Creates a prism with a pentangle base.
*/
PrismPent::PrismPent(const Vector& a,const Vector& b,const Vector& c,const Vector& d, const Vector& e,const double& h):Pentangle(a,b,c,d,e)
{
  PrismPent::h=h;
}

/*!
\brief Creates a prism with a pentangle base.
//MODIFIER LES NORMALES
*/
PrismPent::PrismPent(const Pentangle& q,const double& h)
{
  p[0]=q[0];
  p[1]=q[1];
  p[2]=q[2];
  p[3]=q[3];
  p[4]=q[4];
  PrismPent::h=h;
}

/*!
\brief Renders a pentrilateral prism.
\note This function ommits the lower face of the prism.
*/
void PrismPent::Render()
{
  glBegin(GL_QUADS);

  // Face z=+1
  glNormal3f( 0.0f, 0.0f,1.0f);
  glVertex3f(p[0][0],p[0][1],p[0][2]+h);
  glVertex3f(p[1][0],p[1][1],p[1][2]+h);
  glVertex3f(p[2][0],p[2][1],p[2][2]+h);
  glVertex3f(p[3][0],p[3][1],p[3][2]+h);

  glEnd();

  glBegin(GL_TRIANGLES);

  glNormal3f( 0.0f, 0.0f,1.0f);
  glVertex3f(p[0][0],p[0][1],p[0][2]+h);
  glVertex3f(p[3][0],p[3][1],p[3][2]+h);
  glVertex3f(p[4][0],p[4][1],p[4][2]+h);


  glEnd();

  // Other faces
  glBegin(GL_QUADS);

  for (int i=0;i<5;i++)
  {
    int j=(i+1)%5;
    Vector n=(p[j]-p[i])/Vector(0,0,1);
    n/=Norm(n);
    glNormal3f(n[0],n[1],0.0f);
    glVertex3f(p[i][0],p[i][1],p[i][2]);
    glVertex3f(p[j][0],p[j][1],p[j][2]);
    glVertex3f(p[j][0],p[j][1],p[j][2]+h);
    glVertex3f(p[i][0],p[i][1],p[i][2]+h);
  }

  glEnd();
}
