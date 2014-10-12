// Box
// Changelog 05.01.24

#ifndef __Box__
#define __Box__

// Include Vector class
#include "vector.h"

class Box
{ 
protected:
  Vector a,b; //!< End vertices of the box.
public:
  //! Creates a generic box (empty).
  Box() {}
  Box(const Vector&);
  Box(const Vector&,const Vector&);
  Box(const Vector&,const double&);

  Box(const Box&,const Box&);

  //! Destroy a box, empty.
  ~Box() {}

  // Access vertexes
  Vector& operator[] (int);
  Vector operator[] (int) const;

  Vector Center() const;
  Vector Diagonal() const;
  double Radius() const;
  Vector Vertex(int) const;

  int Intersect(const Box&) const;

  int Inside(const Box&) const;
  int Inside(const Vector&) const;

  // Boolean
  friend int operator&&(const Box&,const Box&);

  double Volume() const;
  double Area() const;
public:
  static const double epsilon;
};

//! Returns either end vertex of the box.
inline Vector& Box::operator[] (int i) 
{
  if (i==0) return a;
  else return b;
}

//! Overloaded.
inline Vector Box::operator[] (int i) const 
{
  if (i==0) return a;
  else return b;
}

//! Returns the center of the box.
inline Vector Box::Center() const { return 0.5*(a+b); }

//! Returns the half diagonal of the box.
inline Vector Box::Diagonal() const { return 0.5*(b-a); }

//! Returns the radius of the box, i.e. the length of the half diagonal of the box.
inline double Box::Radius() const { return 0.5*Norm(b-a); }

//! Returns the k<SUP>th</SUP> vertex of the box.
inline Vector Box::Vertex(int k) const { return Vector ((k&1)?b[0]:a[0],(k&2)?b[1]:a[1],(k&4)?b[2]:a[2]); }

//! Compute the volume of a box.
inline double Box::Volume() const
{
  Vector side=b-a;
  return side[0]*side[1]*side[2];
}

//! Compute the surface area of a box.
inline double Box::Area() const
{
  Vector side=b-a;
  return 2.0*(side[0]*side[1]+side[0]*side[2]+side[1]*side[2]);
}

//! Check if two box intersect.
inline int Box::Intersect(const Box& box) const
{
  return (*this)&&box;
}
#endif

