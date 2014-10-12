#include "MaisonClassique.h"

MaisonClassique::MaisonClassique(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax): Maison(t, typeCentre, hauteurMax){setMaisonClassiqueInfos();}
MaisonClassique::MaisonClassique(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax): Maison(q, typeCentre, hauteurMax){setMaisonClassiqueInfos();}
MaisonClassique::MaisonClassique(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax): Maison(p, typeCentre, hauteurMax){setMaisonClassiqueInfos();}
MaisonClassique::~MaisonClassique(void){}


void MaisonClassique::batir(const Triangle& t){}

void MaisonClassique::batir(const Quadrangle& q)
{
	batirEtages(q);
	creerToitPrisme();
}

void MaisonClassique::batir(const Pentangle& p){}


void MaisonClassique::batirEtages(const Triangle& t){}

void MaisonClassique::batirEtages(const Quadrangle& q)
{
	Vector plusUnEtage(0,0, hauteurEtage);

	PrismQuad(q, nbEtagesMax*hauteurEtage).Render();
	for(unsigned int vect = 0; vect < 4; vect++) listePoints[vect] += (plusUnEtage*nbEtagesMax);

	//double unite = (double) UNITE;

	//for(unsigned int i = 1; i < nbEtagesMax; i++)
	//{
		//creerEtagesSimples(nbEtagesMax);

		//double nbFenetres = 2;
		//double tailleDesFenetres = unite;
		//double tailleDesCoins = unite;

		//double plusPetitCote = Norm(listePoints[3]-listePoints[0]);
		//if(plusPetitCote > Norm(listePoints[1]-listePoints[0])) plusPetitCote = Norm(listePoints[1]-listePoints[0]);	

		//double tailleDesInterFenetre = plusPetitCote - tailleDesFenetres * nbFenetres - tailleDesCoins*2;
		//tailleDesInterFenetre -= 0.5;

		//etageFenetre->setHauteurBordInf(hauteurEtage*0.1);
		//etageFenetre->setHauteurBordSup(hauteurEtage*0.1);
		//etageFenetre->setTailleInterFenetre(tailleDesInterFenetre);
		//etageFenetre->setTailleFenetre(tailleDesFenetres);
		//etageFenetre->setTailleCoin(tailleDesCoins);
		//etageFenetre->creerEtageVitre(listePoints, hauteurEtage);
	//}
}

void MaisonClassique::batirEtages(const Pentangle& p){}


void MaisonClassique::setMaisonClassiqueInfos()
{
	nbEtagesMax = rand()%2 + 2;
}