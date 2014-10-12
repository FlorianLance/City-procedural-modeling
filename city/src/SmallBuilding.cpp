#include "SmallBuilding.h"

SmallBuilding::SmallBuilding(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax): Building(t, typeCentre, hauteurMax){setSmallBuildingInfos();}
SmallBuilding::SmallBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax): Building(q, typeCentre, hauteurMax){setSmallBuildingInfos();}
SmallBuilding::SmallBuilding(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax): Building(p, typeCentre, hauteurMax){setSmallBuildingInfos();}
SmallBuilding::~SmallBuilding(void){}

void SmallBuilding::batir(const Triangle& t){}

void SmallBuilding::batir(const Quadrangle& q)
{
	creerRdc();

	batirEtages(q);

	const unsigned int score = rand()%101;
	if(score > 7) creerBordureToit(); 
}

void SmallBuilding::batir(const Pentangle& p){}


//----------------------------------------------------------------->
//--------------------------CONSTRUCTION----------------------------
//-----------------------------------------------------------------<


void SmallBuilding::batirEtages(const Triangle& t){}


void SmallBuilding::batirEtages(const Quadrangle& q)
{
	Quadrangle newQ(q);
	creerEtages(nbEtagesMax - nbEtageRDC, 0);
}

void SmallBuilding::batirEtages(const Pentangle& p)
{
}

void SmallBuilding::setSmallBuildingInfos()
{
	palierActif = false;

	colonnesCoins = false;

	nbEtageRDC = rand()%2 + 1;

	double unite = (double) UNITE;

	//les étages ne font pas plus de 3 Unités
	int choixTaille = rand()%3;
	if(choixTaille == 0) hauteurEtage = unite*2.5;
	else if(choixTaille == 1) hauteurEtage = unite*2.7;
	else hauteurEtage = unite*3;

	//Les fenêtres sont en général hautes et +/- large
	double largeurF = unite * ( ( ((double) (rand()%70) ) /100 ) + 1);
	etageFenetre->setTailleFenetre(largeurF);
	etageFenetre->setHauteurBordSup(hauteurEtage*0.2);
	etageFenetre->setHauteurBordInf(hauteurEtage*0.2);
}