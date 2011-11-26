// Vector  
// Changelog 02.02.07

#ifndef __Geometry__
#define __Geometry__

#include <vector>
#include "vector.h"


class Figure
{

};

class Triangle: public Figure
{
	protected:
	  Vector p[3];
	public:
	  Triangle() {}
	  Triangle(const Vector&,const Vector&,const Vector&);
	  Triangle Shrink(const double&,const double&,const double&);
	  void setCompVector(const int& i, const int& composante, const double& valeur);
	  Vector getVectors(const int i);
	  double Area() const;
	  inline Vector operator[](int i) const { return p[i]; }
};

//! \brief Compute the area of a triangle
inline double Triangle::Area() const
{
  return Norm((p[1]-p[0])/(p[2]-p[0]))/2.0;
}

class Quadrangle: public Figure
{
	protected:
	  Vector p[4];
	public:
	  Quadrangle() {}
	  Quadrangle(const Vector&,const Vector&,const Vector&,const Vector&);
	  Quadrangle Shrink(const double&,const double&,const double&,const double&);
	  void setCompVector(const int& i, const int& composante, const double& valeur);
	  Vector getVectors(const int i);
	  double Area() const;
	  inline Vector operator[](int i) const { return p[i]; }

};

//! \brief Compute the area of a quadrangle
inline double Quadrangle::Area() const
{
  return Norm((p[1]-p[0])/(p[2]-p[0]))+Norm((p[2]-p[0])/(p[3]-p[0]));
}


class Pentangle: public Figure
{
	protected:
	  Vector p[5];
	public:
	  Pentangle() {}
	  Pentangle(const Vector&, const Vector&, const Vector&, const Vector&, const Vector&);
	  Pentangle Shrink(const double&,const double&,const double&,const double&,const double&);
	  void setCompVector(const int& i, const int& composante, const double& valeur);
	  Vector getVectors(const int i);
	  double Area() const;
	  inline Vector operator[](int i) const { return p[i]; }
};

//! \brief Compute the area of a pentangle
inline double Pentangle::Area() const
{
  return Norm((p[1]-p[0])/(p[2]-p[0]))+Norm((p[2]-p[0])/(p[3]-p[0]))+Norm((p[3]-p[0])/(p[4]-p[0]));
}


class Cercle : Figure
{
	protected:
		Vector centre;
		double rayon;

	public:
		Cercle(const Vector& centre, const double& rayon);
		const Vector& getCentre() const;
		const double& getRayon() const;
		const double operator[](int i) const {return centre[i];}
		double Area() const;
};

#endif