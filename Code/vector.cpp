#include "vector.h"

int Vector::col1 = 150;
int Vector::col2 = 150;
int Vector::col3 = 150;

Vector Vector::getDiffxy(const Vector& _a, const Vector& _b, const double _longueur)
{
	
	Vector _c(_a[0], _b[1], 0);

	double ab,ac,bc,diffX,diffY;

	if(_a[0] == _b[0] && _a[1] == _b[1])
	{
		return _a;
	}
	if(_a[0] == _b[0] )
		 {diffX = 0; diffY = _longueur;
	}
	else if(_a[1] == _b[1] )
	{
		diffX = _longueur; diffY = 0;
	}
	else {
		ab = Norm(_b-_a);
		ac = Norm(_c-_a);
		bc = Norm(_b-_c);

		diffX = _longueur * bc / ab;
		diffY = _longueur * ac / ab;

	}
	if(_a[0] > _b[0]) diffX = - diffX;
	if(_a[1] > _b[1]) diffY = - diffY;

	return Vector(_a[0] + diffX, _a[1] + diffY, 0);

}

void Vector::setDiffxy(const Vector& _a, const Vector& _b, const double _longueur)
{
	Vector v = getDiffxy(_a,_b,_longueur);
	x = v[0];
	y = v[1];
	z = v[2];
}