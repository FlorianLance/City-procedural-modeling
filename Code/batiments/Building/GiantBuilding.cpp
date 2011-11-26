#include "GiantBuilding.h"

GiantBuilding::GiantBuilding(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax): Building(t, typeCentre, hauteurMax){setGiantBuildingInfos();}
GiantBuilding::GiantBuilding(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax): Building(q, typeCentre, hauteurMax){setGiantBuildingInfos();}
GiantBuilding::GiantBuilding(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax): Building(p, typeCentre, hauteurMax){setGiantBuildingInfos();}
GiantBuilding::~GiantBuilding(void){}

void GiantBuilding::batir(const Triangle& t){}

void GiantBuilding::batir(const Quadrangle& q)
{
	setBuildingInfos();
	creerRdc();
	batirEtages(q);

	const unsigned int score = rand()%100;
	if(score > 30) creerBordureToit(); 
	else if(score > 10 && score <= 30) creerToitPyramideCoupe();
	else creerToitPyramide();
}

void GiantBuilding::batir(const Pentangle& p){}



//----------------------------------------------------------------->
//--------------------------CONSTRUCTION----------------------------
//-----------------------------------------------------------------<


void GiantBuilding::batirEtages(const Triangle& t){}

void GiantBuilding::batirEtages(const Quadrangle& q)
{

	Quadrangle newQ(q);

	Vector a,b,c,d; //ils seront remplis plus bas (donnés-résultats)

	//Données pour les inter-étages
	double hauteurIntEtg = 0;
	if(rand()%100 > 20) hauteurIntEtg = 0.2;

	if(colonnesCoins && !palier) creerColonnesCoins();

	if(palierActif)
	{
		for(unsigned int i = nbEtageRDC; i < nbEtagesMax; i+=palier)
		{
			//*************************************
			//*** RETRECISSEMENT ET INTER-ETAGE ***
			//*************************************

			//nécéssaire pour vérifier l'air du quad
			newQ = Quadrangle(listePoints[0],listePoints[1],listePoints[2],listePoints[3]);

			if(newQ.Area() > airMin)
			{
				if(i != nbEtageRDC)
				{
					if(retrecissement > 0) //rétrécissement de l'étage
					{
						scale(a,b,c,d);
						listePoints.clear();
						listePoints.push_back(a);
						listePoints.push_back(b);
						listePoints.push_back(c);
						listePoints.push_back(d);
					}
					else if(hauteurIntEtg > 0 && (nbEtagesMax - i - 1) > 3) //ajout d'un inter-étage
					{
						RebordIntEtgQuad(hauteurIntEtg);
					}
				}

				if(colonnesCoins) creerColonnesCoins(i);
				
				
				//************************************
				//************** ETAGE ***************
				//************************************

				//vérification avant de créer les étages
				double nbEtageACreer;
				if( (i + palier) >= nbEtagesMax)
					nbEtageACreer = nbEtagesMax - i;
				else if(i != nbEtagesMax)
					nbEtageACreer = palier;

				creerEtages(nbEtageACreer, i);

				majLoiPalier();
				
			}

		}
	}
	else
	{
		creerEtages(nbEtagesMax - nbEtageRDC, 0);
	}

}

void GiantBuilding::batirEtages(const Pentangle& p){}


void GiantBuilding::RebordIntEtgQuad(const double& hauteurIntEtg)
{
	Vector centre(0,0,0); //C -> centre

	for(unsigned int i = 0; i < listePoints.size(); i++)
		centre += listePoints[i];
	centre /= listePoints.size();

	double largeurRebord = (double) UNITE;

	std::vector<Vector> nouvPoints; //pour se déplacer sur Ca, Cb, Cc, ...
	for(unsigned int i = 0; i < listePoints.size(); i++)
	{
		double pas = Norm(listePoints[i] - centre)/largeurRebord;
		nouvPoints.push_back( listePoints[i] + ( (listePoints[i] - centre)/pas ) );
	}
	
	PrismQuad(nouvPoints[0],nouvPoints[1],nouvPoints[2],nouvPoints[3], hauteurIntEtg).Render(); //on affiche l'inter-étage

	//mise à jour des hauteurs (newQ = listePoints en terme de Vectors)
	for(unsigned int vect = 0; vect < listePoints.size(); vect++) listePoints[vect] += Vector(0,0, hauteurIntEtg);
}

void GiantBuilding::scale(Vector& a, Vector& b, Vector& c, Vector& d, double val, bool retCentre) 
{
	a = listePoints[0];
	b = listePoints[1];
	c = listePoints[2];
	d = listePoints[3];

	if(centreRetrecissement == 0 || retCentre) //Centre
	{
		Vector centre = (a + b + c + d)/4;
		std::vector<Vector> variants;
		variants.push_back(a);
		variants.push_back(b);
		variants.push_back(c);
		variants.push_back(d);

		if(!retCentre) scaleXY(retrecissement, centre, variants);
		else scaleXY(val, centre, variants);

		a = variants[0];
		b = variants[1];
		c = variants[2];
		d = variants[3];

	}
	else if(centreRetrecissement == 1) //Nord
	{
		scaleXY(retrecissement, d, a);
		scaleXY(retrecissement, c, b);
	}
	else if(centreRetrecissement == 2) // Sud
	{
		scaleXY(retrecissement, b, c);
		scaleXY(retrecissement, a, d);
	}
	else if(centreRetrecissement == 3) //Est
	{
		scaleXY(retrecissement, b, a);
		scaleXY(retrecissement, c, d);
	}
	else //Ouest
	{
		scaleXY(retrecissement, a, b);
		scaleXY(retrecissement, d, c);
	}
}


void GiantBuilding::setGiantBuildingInfos()
{
	double unite = (double) UNITE;

	//les étages ne font pas plus de 2,7 mètres
	int choixTaille = rand()%2;
	if(choixTaille == 0) hauteurEtage = unite*2.5;
	else if(choixTaille == 1) hauteurEtage = unite*2.7;

	//Les fenêtres sont en général assez petites
	double largeurF = unite * ( ( ((double)(rand()%50))/100 ) + 1);
	etageFenetre->setTailleFenetre(largeurF);

	double bordureSup = hauteurEtage*0.3;
	double bordureInf = hauteurEtage*0.3;

	//double bordureSup = hauteurEtage*(rand()%30)/100;
	//double bordureInf = hauteurEtage*(rand()%30)/100;

	//if(bordureSup < 0.05) bordureSup = hauteurEtage*0.3;
	//if(bordureInf < 0.05) bordureInf = hauteurEtage*0.3;

	etageFenetre->setHauteurBordSup(bordureSup);
	etageFenetre->setHauteurBordInf(bordureInf);

	double interFenetre = (rand()%100)/100 + unite;
	etageFenetre->setTailleInterFenetre(interFenetre);
}