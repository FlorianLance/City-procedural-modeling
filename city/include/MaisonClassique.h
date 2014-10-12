#ifndef __MaisonClassique__
#define __MaisonClassique__

#include <iostream>

#include "Maison.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"

class Maison;

class MaisonClassique : public Maison
{
	public:
		MaisonClassique(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax);
		MaisonClassique(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax);
		MaisonClassique(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax);
		~MaisonClassique(void);

		virtual void batir(const Triangle& t);
		virtual void batir(const Quadrangle& q);
		virtual void batir(const Pentangle& p);

	protected :

		void setMaisonClassiqueInfos();

		virtual void batirEtages(const Triangle& t);
		virtual void batirEtages(const Quadrangle& q);
		virtual void batirEtages(const Pentangle& p);

};


#endif
