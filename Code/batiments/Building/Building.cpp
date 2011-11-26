#include "Building.h"

#include "GiantBuilding.h" //le laisser ici
#include "SmallBuilding.h"

#include <iostream>

Building::Building(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax): Batiment(t, typeCentre, hauteurMax){setBuildingInfos();}
Building::Building(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax): Batiment(q, typeCentre, hauteurMax){setBuildingInfos();}
Building::Building(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax): Batiment(p, typeCentre, hauteurMax){setBuildingInfos();}
Building::~Building(void){}



//STATIC--------------------------------------------------->


void Building::choixBatiment(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax)
{

}

void Building::choixBatiment(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax)
{
	double unEtageMoyen = 2.5*UNITE; //2.5 mèters

	if(hauteurMax > 20*unEtageMoyen) //20 étages * taille d'un étage moyen (50 mètres)
		GiantBuilding(q, typeCentre, hauteurMax).batir(q);
	else if (hauteurMax > 12*unEtageMoyen && hauteurMax <= 20*unEtageMoyen) //> 30 mètres && <= 50 mètres
		SmallBuilding(q, typeCentre, hauteurMax).batir(q); //A MODIFIER, CREER UN MEDIUMBUILDING
	else if(hauteurMax > 3*unEtageMoyen && hauteurMax <= 12*unEtageMoyen)
		SmallBuilding(q, typeCentre, hauteurMax).batir(q); //> 7.5 mètres && <= 30 mètres
}

void Building::choixBatiment(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax)
{
}


//--------------------------------------------------------->


void Building::setBuildingInfos()
{

	colonnesCoins = rand()%100 > 10 ? true:false;

	//************************************
	//***** PROPORTIONS DU BATIMENT *****
	//************************************

	//pas de rétrécissement sur des building dont les côtés ne respectent pas le ratio 2
	bool bonnesProportions = false;
	double ab = Norm(listePoints[1] - listePoints[0]);
	double bc = Norm(listePoints[2] - listePoints[1]);
	if(ab > bc) bonnesProportions = ab/bc <= 2;
	else bonnesProportions = bc/ab <= 2;

	if(rand()%100 > 30 && bonnesProportions)
	{	
		//% de rétrecissement tous les N étage
		retrecissement = (double) ((rand()%10) + 7) /100;

		//type de rétrécissement
		centreRetrecissement = rand()%5; // Centré | Nord | Sud | Est | Ouest -> 0 1 2 3 4
	}
	else
	{
		retrecissement = 0; 
		centreRetrecissement = 0;
		creerFenetre = false; //pour éviter que certains étages aient des fenêtre et les autres non (risque de surface trop petite)
	}

	colonnesCoins = rand()%2 == 1?true:false;

	//************************************
	//********* HAUTEUR DU RDC ***********
	//************************************

	//taille deu RDC en fonction du nombre d'étage max
	if(nbEtagesMax > 15)
		nbEtageRDC = rand()%3 + 1;
	else if (nbEtagesMax > 25)
		nbEtageRDC = rand()%4 + 1;
	else if (nbEtagesMax > 30)
		nbEtageRDC = rand()%5 + 1;

	//************************************
	//** CALCUL DU PALIER ET DE SA LOI ***
	//************************************

	palierActif = rand()%100 > 15? true:false;
	int tmpValMin = (double) nbEtagesMax*0.2;
	if(tmpValMin < 4) tmpValMin = 3;
	palier = rand()%(tmpValMin) + tmpValMin;
	
	if(retrecissement)
	{
		//loi d'évolution du palier
		unsigned int randLoiPalier = rand()%100;
		if(randLoiPalier > 40)
			loiPalier = 0; //constante
		else if(randLoiPalier > 10)
			loiPalier = 1; //augmente
		//else
		//	loiPalier = 2; //diminue
	}
	else loiPalier = 0; //plus joli

	if(nbEtageRDC == palier) majLoiPalier();

	//************************************
	//******* SCINDER LE BUILDING ********
	//************************************

	/*
	* Si l'immeuble est scindé, celà doit être fait vers les premiers étages,
	* et s'il a un Hall d'entré assez haut, alors on ne fait rien.
	*/
	if(rand()%100 < 7) separation = true; else separation = false;
	if(separation && nbEtageRDC < 5) numEtageSeparation = nbEtageRDC + rand()%4; //ajout du RDc + 4 étages au maximum
	else numEtageSeparation = -1;
	

}

//----------------------------------------------------------------->
//--------------------------CONSTRUCTION----------------------------
//-----------------------------------------------------------------<


void Building::creerColonnesCoins(const unsigned int etageActu)
{
	double coteColonne = (double) UNITE;
	coteColonne /= 2; //facteur de réduction

	//on doit tester si le prochain palier est supérieur au nombre d'étages restants
	double nbEtageColonne;
	if(!palier)
		nbEtageColonne = nbEtagesMax; //si les paliers ne sont pas activés
	else if( (etageActu + palier) >= nbEtagesMax)
		nbEtageColonne = nbEtagesMax - etageActu;
	else if(etageActu != nbEtagesMax)
		nbEtageColonne = palier;

	Vector ab = listePoints[1] - listePoints[0];
	Vector bc = listePoints[2] - listePoints[1];

	Vector vectDeplAb = ab/(Norm(ab)/coteColonne);
	Vector vectDeplBc = bc/(Norm(bc)/coteColonne);

	for(unsigned int i = 0; i < 4; i++)
	{
		Quadrangle q (listePoints[i] - vectDeplAb - vectDeplBc,
					  listePoints[i] + vectDeplAb - vectDeplBc,
					  listePoints[i] + vectDeplAb + vectDeplBc,
					  listePoints[i] - vectDeplAb + vectDeplBc);

		PrismQuad(q, hauteurEtage*nbEtageColonne).Render();

	}
}

void Building::creerRdc()
{
	if(colonnesCoins) creerColonnesCoins(0);
	PrismQuad(listePoints[0], listePoints[1], listePoints[2], listePoints[3], hauteurEtage*nbEtageRDC).Render();

	//on monte dirrectement à l'étage au dessus du Rdc
	for(unsigned int vect = 0; vect < 4; vect++) listePoints[vect] += Vector(0,0, hauteurEtage*nbEtageRDC);
}


//----------------------------------------------------------------->
//-------------------------AUTRES METHODES--------------------------
//-----------------------------------------------------------------<


void Building::majLoiPalier()
{
	int val = ceil((double) palier*20/100);
	if(loiPalier == 1) palier += val;
	//else if(palier-val > 1) palier -= val; //-> pas vraiment bien par rapport à se qui existe
}