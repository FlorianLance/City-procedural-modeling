#ifndef __UsineClassique__
#define __UsineClassique__

#include <iostream>

#include "Usine.h"
#include "../../city.h"
#include "../../geometry.h"
#include "../../shape.h"

class Maison;

class UsineClassique : public Usine
{
	public:
		UsineClassique(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax);
		UsineClassique(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax);
		UsineClassique(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax);
		~UsineClassique(void);

		virtual void batir(const Triangle& t);
		virtual void batir(const Quadrangle& q);
		virtual void batir(const Pentangle& p);

		static std::vector <double> ToitUsine;

	protected :

		void setUsineClassiqueInfos();

		virtual void batirEtages(const Triangle& t);
		virtual void batirEtages(const Quadrangle& q);
		virtual void batirEtages(const Pentangle& p);

	private :
		void typeEntrepot();
		void typeOld();

};


#endif