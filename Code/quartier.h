#ifndef _QUARTIER_
#define _QUARTIER_


#include "shape.h"
#include "geometry.h"
#include "city.h"
#include "batiments\Batiment.h"
#include <vector>

class Quartier {

public:

	Quartier();

	Quartier(const Vector&, const Vector&, const Vector&);
	Quartier(const Vector&, const Vector&, const Vector&, const std::vector<Centre> &);

	Quartier(const Vector&, const Vector&, const Vector&, const Vector&);
	Quartier(const Vector&, const Vector&, const Vector&, const Vector&, const std::vector<Centre> &);

	static void choixQuartier(const Triangle&, const std::vector<Centre>&);
	static void choixQuartier(const Quadrangle&, const std::vector<Centre>&);

protected:

	Vector a;
	Vector b;
	Vector c;
	Vector d;

	double ab,bc,cd,da,ca;

	std::vector<Centre> centres;

	
};

#endif