#ifndef _QCENTRE_
#define _QCENTRE_

#include <vector>
#include "quartier.h"


class Quartier;

class QuartierCentre : public Quartier
{

public:

	QuartierCentre(const Vector& _a, const Vector& _b, const Vector& _c,  const Centre&);
	QuartierCentre(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const Centre&);



	static void choixQuartier(const Triangle& _t,  const Centre &);
	static void choixQuartier(const Quadrangle& _t, const Centre &);

	//void immeublesCentre();

private:

	void centreGratteciel();
	void centreCour();
	void centre1Rangee();
	void centre2Rangee();
	void centreCarre();
	void centreRajout();
	void zoneRajoutee(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const double _taille);

	Centre centre;
	void creationPointsLongueur(const Vector& v1, const Vector& v2,const Vector& v3,const Vector& v4);
};

#endif