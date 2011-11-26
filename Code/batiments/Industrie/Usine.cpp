#include "Usine.h"

#include "UsineClassique.h"

Usine::Usine(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax): Batiment(t, typeCentre, hauteurMax){setUsineInfos();}
Usine::Usine(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax): Batiment(q, typeCentre, hauteurMax){setUsineInfos();}
Usine::Usine(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax): Batiment(p, typeCentre, hauteurMax){setUsineInfos();}
Usine::~Usine(void){}


//STATIC --------------------------------------------------->

void Usine::choixBatiment(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax)
{
	UsineClassique(q, typeCentre, hauteurMax).batir(q);
}

//--------------------------------------------------------->

void Usine::setUsineInfos()
{

}