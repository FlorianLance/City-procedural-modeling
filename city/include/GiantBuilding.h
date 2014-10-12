#ifndef __GiantBuilding__
#define __GiantBuilding__

#include <iostream>

#include "Building.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"

class Building;

class GiantBuilding : public Building
{
	public:
		GiantBuilding(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax);
		GiantBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax);
		GiantBuilding(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax);
		~GiantBuilding(void);

		void batir(const Triangle& t);
		void batir(const Quadrangle& q);
		void batir(const Pentangle& p);

	protected :

		void batirEtages(const Triangle& t);
		void batirEtages(const Quadrangle& q);
		void batirEtages(const Pentangle& p);

		/** @brief rétrécissement selon un côté du (Nord, Sud, Est, Ouest) ou le centre du quad
		*   @param quad le quad à rétrécir
		*   @param abcd des se sont des données-résultats, il sont remplis pendant la méthode et contiennent les nouveaux points
		*	@param val la valeur de rétrécissement (uniquement utilisé si retCentre = true)
		*   @param retCentre true, alors on rétrécie le quad par le centre, false sinon
		*/
		void scale(Vector& a, Vector& b, Vector& c, Vector& d, double val = 1, bool retCentre = false);

		/** @brief Crée un inter-étage avec un rebord */
		void RebordIntEtgQuad(const double& hauteurIntEtg);

		void setGiantBuildingInfos();
};

#endif
