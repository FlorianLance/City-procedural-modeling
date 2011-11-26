#ifndef _QINDUSTRIEL_
#define _QINDUSTRIEL_

#include <vector>
#include "quartier.h"

class QuartierIndustriel : public Quartier
{
	public:

		QuartierIndustriel(const Vector& _a, const Vector& _b, const Vector& _c, const Centre&);
		QuartierIndustriel(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const Centre&);

		static void choixQuartier(const Triangle& _t, const Centre&);
		static void choixQuartier(const Quadrangle& _t, const Centre&);

	private:

		Centre centre;
		void industrie1Rangee();
};

#endif