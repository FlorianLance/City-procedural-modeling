// Vector  
// Changelog 02.02.07

#ifndef __Vector__
#define __Vector__

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <math.h>
#include <stdlib.h>

#include <iostream>
//! \class Vector vector.h
//! \brief Cette classe définit des vecteurs et des sommets dans l'espace.

#define COL_DEF1 150
#define COL_DEF2 150
#define COL_DEF3 150

#define COL_FOND1 0
#define COL_FOND2 0
#define COL_FOND3 0

#define COL_LAMP1 100
#define COL_LAMP2 100
#define COL_LAMP3 100

#define COL_ROUTE1 55
#define COL_ROUTE2 55
#define COL_ROUTE3 55

#define COL_FEN1 20
#define COL_FEN2 65
#define COL_FEN3 250

#define COL_TROTT1 105
#define COL_TROTT2 105
#define COL_TROTT3 105

#define COL_HERBE1 0
#define COL_HERBE2 128
#define COL_HERBE3 0


class Vector
{

protected:
  double x,y,z; //!< Coordinates

public:

  static int col1,col2,col3;
  static int getCol(const unsigned int _num){
	 if(_num == 1)return col1;
	 else if(_num == 2) return col2;
	 else return col3;}

  static void setCol(const unsigned int _col1, const unsigned int _col2, const unsigned int _col3){
	  col1 = _col1; col2 = _col2; col3 = _col3;
  }

  static void setColDefaut(){
	  col1 = COL_DEF1; col2 = COL_DEF2; col3 = COL_DEF3;
  }

  Vector() { x=0; y=0; z=0;  } //! Empty
  Vector(const double& a, const double& b, const double& c) { x=a; y=b; z=c; }

  Vector getDiffxy(const Vector& _a, const Vector& _b, const double _longueur);
  void setDiffxy(const Vector& _a, const Vector& _b, const double _longueur);

	void afficher(std::ostream &flux) const
	{
		flux << "x: " << x << " y: " << y << " z: " << z << std::endl;
	}

  // Functions to a2ccess Vector class components
  double& operator[] (int i) {
    if (i == 0)    return x;
    else if (i == 1) return y;
    else	     return z;
  }

  const double operator[] (int i) const {
    if (i == 0)    return x;
    else if (i == 1) return y;
    else	     return z;
  }

  // Unary operators
  Vector operator+ () const;
  Vector operator- () const;

  // Assignment operators
  Vector& operator+= (const Vector&);
  Vector& operator-= (const Vector&);
  Vector& operator*= (const Vector&);
  Vector& operator/= (const Vector&);
  Vector& operator*= (double);
  Vector& operator/= (double);

  // Binary operators
  friend Vector operator+ (const Vector&, const Vector&);
  friend Vector operator- (const Vector&, const Vector&);

  friend double operator* (const Vector&, const Vector&);

  friend Vector operator* (const Vector&, double);
  friend Vector operator* (double, const Vector&);
  friend Vector operator/ (const Vector&, double);

  friend Vector operator/ (const Vector&, const Vector&);

  // Boolean functions
  friend int operator==(const Vector&,const Vector&);
  friend int operator!=(const Vector&,const Vector&);
  friend int operator<(const Vector&,const Vector&);
  friend int operator>(const Vector&,const Vector&);
  //  friend Vector min(const Vector&,const Vector&);
  //  friend Vector max(const Vector&,const Vector&);

  friend Vector Orthogonal(const Vector&);

  // Norm
  friend double Norm(const Vector&);
  friend Vector Normalized(const Vector&);

  friend Vector Random();
};

//! Generates a random vector with precision 1e-3 within [0,1] interval
inline Vector Random()
{
  double x=rand()%1001/1000.0;
  double y=rand()%1001/1000.0;
  double z=rand()%1001/1000.0;
  return Vector(x,y,z);
}
// Unary operators
inline Vector Vector::operator+ () const
{
  return *this;
}

inline Vector Vector::operator- () const
{
  return Vector(-x,-y,-z);
}

// Assignment unary operators
inline Vector& Vector::operator+= (const Vector& u)
{
  x+=u.x; y+=u.y; z+=u.z;
  return *this;
}

inline Vector& Vector::operator-= (const Vector& u)
{
  x-=u.x; y-=u.y; z-=u.z;
  return *this;
}

inline Vector& Vector::operator*= (double a)
{
  x*=a; y*=a; z*=a;
  return *this;
}

inline Vector& Vector::operator/= (double a)
{
  x/=a; y/=a; z/=a;
  return *this;
}

inline Vector& Vector::operator*= (const Vector& u)
{
  x*=u.x; y*=u.y; z*=u.z;
  return *this;
}

inline Vector& Vector::operator/= (const Vector& u)
{
  x/=u.x; y/=u.y; z/=u.z;
  return *this;
}

// Binary operators
inline Vector operator+ (const Vector& u, const Vector& v)
{
  return Vector(u.x+v.x,u.y+v.y,u.z+v.z);
}

inline Vector operator- (const Vector& u, const Vector& v)
{
  return Vector(u.x-v.x,u.y-v.y,u.z-v.z);
}

// Scalar product
inline double operator* (const Vector& u, const Vector& v)
{
  return (u.x*v.x+u.y*v.y+u.z*v.z);
}

inline Vector operator* (const Vector& u,double a)
{
  return Vector(u.x*a,u.y*a,u.z*a);
}

inline Vector operator* (double a, const Vector& v)
{
  return v*a;
}

// Cross product
inline Vector operator/ (const Vector& u, const Vector& v)
{
  return Vector(u.y*v.z-u.z*v.y,u.z*v.x-u.x*v.z,u.x*v.y-u.y*v.x);
}

inline Vector operator/ (const Vector& u, double a)
{
  return Vector(u.x/a,u.y/a,u.z/a);
}

// Boolean functions
inline int operator== (const Vector& u,const Vector& v)
{
  return ((u.x==v.x)&&(u.y==v.y)&&(u.z==v.z));
}

inline int operator!= (const Vector& u,const Vector& v)
{
  return (!(u==v));
}




/*!
\brief Compute the Euclidean norm of a vector.
*/
inline double Norm(const Vector& u)
{
  return sqrt(u.x*u.x+u.y*u.y+u.z*u.z);
}
/*!
\brief Compute the normalized vector.
*/
inline Vector Normalized(const Vector& u)
{
  return u/Norm(u);
}

inline int operator<(const Vector& a,const Vector& b)
{
  return ((a.x<b.x)&&(a.y<b.y)&&(a.z<b.z));
}

inline int operator>(const Vector& a,const Vector& b)
{
  return ((a.x>b.x)&&(a.y>b.y)&&(a.z>b.z));
}




/*!
\brief Return a new vector with coordinates set to the minimum coordinates
of the two argument vectors.
*/
inline Vector min(const Vector& a,const Vector& b)
{
  return Vector(a[0]<b[0]?a[0]:b[0],a[1]<b[1]?a[1]:b[1],a[2]<b[2]?a[2]:b[2]);
}

/*!
\brief Return a new vector with coordinates set to the maximum coordinates
of the two argument vectors.
*/
inline Vector max(const Vector& a,const Vector& b)
{
  return Vector(a[0]>b[0]?a[0]:b[0],a[1]>b[1]?a[1]:b[1],a[2]>b[2]?a[2]:b[2]);
}

/*!
\brief Returns a new vector orthogonal to the argument vector.
*/
inline Vector Orthogonal(const Vector& u)
{  
  Vector a=Vector(fabs(u[0]),fabs(u[1]),fabs(u[2]));
  int i=0;
  int j=1;
  if (a[0]>a[1])
  {
    if (a[2]>a[1])
    {
      j=2;
    }
  }
  else
  {
    i=1;
    j=2;
    if (a[0]>a[2])
    {
      j=0;
    }
  }
  a=Vector(0.0,0.0,0.0);
  a[i]=u[j];
  a[j]=-u[i];
  return a;
}



#endif

