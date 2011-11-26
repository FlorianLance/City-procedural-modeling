// Box
// Changelog 05.01.24

// Self include
#include "box.h"


/*!
\brief Create a box given a center point and the half side length.
\param c Center. 
\param r Half side length.
*/
Box::Box(const Vector& c,const double& r)
{
  a=c-Vector(r,r,r);
  b=c+Vector(r,r,r);
}

/*!
\brief Create a box given two opposite corners. Note that this
constructor does not check the coordinates of the two vectors.
\param a,b End vertices.
*/
Box::Box(const Vector& a,const Vector& b)
{
  Box::a=a;
  Box::b=b;
}

/*!
\brief Create an empty box given one vertex.
*/
Box::Box(const Vector& a)
{
  Box::b=Box::a=a;
}


/*!
\brief Create a box embedding two boxes.
*/
Box::Box(const Box& x,const Box& y)
{
  a=min(x.a,y.a);
  b=max(x.b,y.b);
}







/*!
\brief Checks if two boxes in space intersect.
*/
int operator&&(const Box& x,const Box& y)
{
  if (((x.a[0]>=y.b[0])||(x.a[1]>=y.b[1])||(x.a[2]>=y.b[2])||
    (x.b[0]<=y.a[0])||(x.b[1]<=y.a[1])||(x.b[2]<=y.a[2])))
    return 0;
  else
    return 1;
}



/*!
\brief Checks if a box is inside the instance.
*/
int Box::Inside(const Box& box) const
{
  return ((a<box.a) && (b>box.b));
}

/*!
\brief Checks if a point is inside the box.
*/
int Box::Inside(const Vector& u) const
{
  return ((a<u) && (b>u));
}


