#ifndef _QRESIDENTIEL_
#define _QRESIDENTIEL_

#include <vector>
#include "quartier.h"

class QuartierResidentiel : public Quartier
{
	public:

		QuartierResidentiel(const Vector& _a, const Vector& _b, const Vector& _c,  const Centre&);
		QuartierResidentiel(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const Centre&);

		static void choixQuartier(const Triangle& _t, const Centre&);
		static void choixQuartier(const Quadrangle& _t, const Centre&);

		
	private:

		//void residenceSimple();
		void residence1Rangee();
		void residenceRangee1Jardin();
		Centre centre;
};

#endif