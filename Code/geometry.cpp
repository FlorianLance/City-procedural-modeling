#include <iostream>

#include "geometry.h"
#include "shape.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*!
\class Triangle geometry.h
\brief This class implements a simple triangle.
*/

/*!
\brief Constructor.
*/
Triangle::Triangle(const Vector& a,const Vector& b,const Vector& c)
{
  p[0]=a;
  p[1]=b;
  p[2]=c;
}

Vector Triangle::getVectors(const int i)
{
	return p[i];
}

 void Triangle::setCompVector(const int& i, const int& composante, const double& valeur)
{
	p[i][composante] = valeur;
}


Vector Intersection(const Vector& a, const Vector& b, const Vector& c, const Vector& d) 
{ 
  double e = (a[0] - b[0]) * (c[1] - d[1]) - (a[1] - b[1]) * (c[0] - d[0]); 

  double u = (a[0]*b[1] - a[1]*b[0]);
  double v = (c[0]*d[1] - c[1]*d[0]); 

  double x = ( u * (c[0] - d[0]) - (a[0] - b[0]) * v ) / e; 
  double y = ( u * (c[1] - d[1]) - (a[1] - b[1]) * v ) / e; 

  return Vector(x,y,0.0);
}

/*!
\brief Shrinks the triangle by a given orthogonal offset for every edge.
*/
Triangle Triangle::Shrink(const double& ab,const double& bc, const double& ca)
{
  Vector sa = p[0]-Normalized((p[1]-p[0])/Vector(0,0,1))*ab;
  Vector sb = p[1]-Normalized((p[2]-p[1])/Vector(0,0,1))*bc;
  Vector sc = p[2]-Normalized((p[0]-p[2])/Vector(0,0,1))*ca;

  return Triangle(
    Intersection(sa,sa+(p[1]-p[0]),sb,sb+(p[2]-p[1])),
    Intersection(sb,sb+(p[2]-p[1]),sc,sc+(p[0]-p[2])),
    Intersection(sc,sc+(p[0]-p[2]),sa,sa+(p[1]-p[0])));
}


/*!
\class Quadrangle geometry.h
\brief This class implements a simple quadrangle with several useful geometric functions.
*/

/*!
\brief Constructor.
*/
Quadrangle::Quadrangle(const Vector& a,const Vector& b,const Vector& c,const Vector& d)
{
  p[0]=a;
  p[1]=b;
  p[2]=c;
  p[3]=d;
}

Vector Quadrangle::getVectors(const int i)
{
	return p[i];
}

 void Quadrangle::setCompVector(const int& i, const int& composante, const double& valeur)
{
	p[i][composante] = valeur;
}


/*!
\brief Shrinks the quadrangle by a given orthogonal offset for every edge.
*/
Quadrangle Quadrangle::Shrink(const double& ab,const double& bc, const double& cd, const double& da)
{
  Vector sa = p[0]-Normalized((p[1]-p[0])/Vector(0,0,1))*ab;
  Vector sb = p[1]-Normalized((p[2]-p[1])/Vector(0,0,1))*bc;
  Vector sc = p[2]-Normalized((p[3]-p[2])/Vector(0,0,1))*cd;
  Vector sd = p[3]-Normalized((p[0]-p[3])/Vector(0,0,1))*da;

  return Quadrangle(
    Intersection(sa,sa+(p[1]-p[0]),sb,sb+(p[2]-p[1])),
    Intersection(sb,sb+(p[2]-p[1]),sc,sc+(p[3]-p[2])),
    Intersection(sc,sc+(p[3]-p[2]),sd,sd+(p[0]-p[3])),
    Intersection(sd,sd+(p[0]-p[3]),sa,sa+(p[1]-p[0])));
}



Pentangle::Pentangle(const Vector& a, const Vector& b, const Vector& c, const Vector&d, const Vector&e)
{
  p[0]=a;
  p[1]=b;
  p[2]=c;
  p[3]=d;
  p[4]=e;
}


Pentangle Pentangle::Shrink(const double& ab,const double& bc, const double& cd, const double& de, const double& ea)
{
  Vector sa = p[0]-Normalized((p[1]-p[0])/Vector(0,0,1))*ab;
  Vector sb = p[1]-Normalized((p[2]-p[1])/Vector(0,0,1))*bc;
  Vector sc = p[2]-Normalized((p[3]-p[2])/Vector(0,0,1))*cd;
  Vector sd = p[3]-Normalized((p[4]-p[3])/Vector(0,0,1))*de;
  Vector se = p[4]-Normalized((p[0]-p[4])/Vector(0,0,1))*ea;

  return Pentangle(
    Intersection(sa,sa+(p[1]-p[0]),sb,sb+(p[2]-p[1])),
    Intersection(sb,sb+(p[2]-p[1]),sc,sc+(p[3]-p[2])),
    Intersection(sc,sc+(p[3]-p[2]),sd,sd+(p[4]-p[3])),
    Intersection(sd,sd+(p[4]-p[3]),se,se+(p[0]-p[4])),
	Intersection(se,se+(p[0]-p[4]),sa,sa+(p[1]-p[0])));
}

Vector Pentangle::getVectors(const int i)
{
	return p[i];
}

 void Pentangle::setCompVector(const int& i, const int& composante, const double& valeur)
{
	p[i][composante] = valeur;
}




Cercle::Cercle(const Vector& _centre, const double& _rayon) : centre(_centre), rayon(_rayon){}
const Vector& Cercle::getCentre() const {return centre;}
const double& Cercle::getRayon() const{return rayon;}
double Cercle::Area() const{return M_PI*rayon*rayon;}