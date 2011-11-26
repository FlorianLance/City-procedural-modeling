#ifndef __MobilierUrbain__
#define __MobilierUrbain__

#include "geometry.h"
#include <vector>
#include "shape.h"
#include "city.h"


class Mobilier {

public:

	Mobilier(const double _hauteurLampadaire, const double _distanceEspacement, const double _largeurLampadaire);

	void creerLampadaires(const Quadrangle &_q);
	void creerRangeeLampadaire(const Vector &_v1, const Vector &_v2, const Vector &_q1, const Vector &_q2);

private:
	
	double h; // hauteur du lampadaire
	double l; // largeur du lampadaire
	double d; // distance qui sépart 2 lampadaires

	unsigned int nbLampRangee; // nb de lampadaires dans une rangée


};


#endif