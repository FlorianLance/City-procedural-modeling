#ifndef __Maison__
#define __Maison__

#include <iostream>

#include "Batiment.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"

class Batiment;

class Maison : public Batiment
{
	public:
		Maison(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax);
		Maison(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax);
		Maison(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax);
		~Maison(void);

		static void choixBatiment(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax);
		static void choixBatiment(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax);
		static void choixBatiment(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax);

		virtual void batir(const Triangle& t) =0;
		virtual void batir(const Quadrangle& q) =0;
		virtual void batir(const Pentangle& p) =0;

	protected :

		bool garage;

		void setMaisonInfos();

		virtual void batirEtages(const Triangle& t) =0;
		virtual void batirEtages(const Quadrangle& q) =0;
		virtual void batirEtages(const Pentangle& p) =0;

};

#endif
