#include "Maison.h"

#include "MaisonClassique.h"

Maison::Maison(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax): Batiment(t, typeCentre, hauteurMax){setMaisonInfos();}
Maison::Maison(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax): Batiment(q, typeCentre, hauteurMax){setMaisonInfos();}
Maison::Maison(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax): Batiment(p, typeCentre, hauteurMax){setMaisonInfos();}
Maison::~Maison(void){}


//STATIC --------------------------------------------------->

void Maison::choixBatiment(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax)
{
	MaisonClassique(q, typeCentre, hauteurMax).batir(q);
}

//--------------------------------------------------------->

void Maison::setMaisonInfos()
{

}