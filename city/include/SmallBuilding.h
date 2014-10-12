#ifndef __SmallBuilding__
#define __SmallBuilding__

#include <iostream>
#include "Building.h"
#include "SmallBuilding.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"

class Building;

/**
* @class Ce sont les petits building de 3 à 10 étages
*/
class SmallBuilding : public Building
{
	public:
		SmallBuilding(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax);
		SmallBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax);
		SmallBuilding(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax);
		~SmallBuilding(void);

		void batir(const Triangle& t);
		void batir(const Quadrangle& q);
		void batir(const Pentangle& p);

	protected :

		void batirEtages(const Triangle& t);
		void batirEtages(const Quadrangle& q);
		void batirEtages(const Pentangle& p);

		void setSmallBuildingInfos();

};

#endif
