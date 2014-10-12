#include "Batiment.h"
#include "Building.h"
#include "Maison.h"
#include "Usine.h"

#include <iostream>

std::vector<double> Batiment::ToitPyramideCoupe;
std::vector<double> Batiment::ToitPyramide;
std::vector<double> Batiment::ToitPrisme;

Batiment::Batiment(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax)
{
	listePoints.push_back(t[0]);
	listePoints.push_back(t[1]);
	listePoints.push_back(t[2]);
	airMin = t.Area()*0.3;
	setBatimentInfos(typeCentre, hauteurMax);
}

Batiment::Batiment(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax)
{
	listePoints.push_back(q[0]);
	listePoints.push_back(q[1]);
	listePoints.push_back(q[2]);
	listePoints.push_back(q[3]);
	airMin = q.Area()*0.3;
	setBatimentInfos(typeCentre, hauteurMax);
}

Batiment::Batiment(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax)
{
	listePoints.push_back(p[0]);
	listePoints.push_back(p[1]);
	listePoints.push_back(p[2]);
	listePoints.push_back(p[3]);
	listePoints.push_back(p[4]);
	airMin = p.Area()*0.3;
	setBatimentInfos(typeCentre, hauteurMax);
}

Batiment::~Batiment(void)
{
	delete etageFenetre;
}


//STATIC--------------------------------------------------->


void Batiment::choixBatiment(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax)
{
}

void Batiment::choixBatiment(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax)
{
	
	if(typeCentre != -1)
	{
		if(typeCentre == VILLE)
			Building::choixBatiment(q, typeCentre, hauteurMax);
		else if(typeCentre == RESIDENCE)
			Maison::choixBatiment(q, typeCentre, hauteurMax);
		else if (typeCentre == INDUSTRIEL)
			Usine::choixBatiment(q, typeCentre, hauteurMax);
	}
	else //aucun centre-ville à proximité, on fait des maisons
	{
		Maison::choixBatiment(q, typeCentre, hauteurMax);
	}

}

void Batiment::choixBatiment(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax)
{
}

//--------------------------------------------------------->


//----------------------------------------------------------------->
//--------------------------CONSTRUCTION----------------------------
//-----------------------------------------------------------------<



//----------------------------------------------------------------->
//------------------------------RDC--------------------------------
//-----------------------------------------------------------------<


void Batiment::creerRdc(const unsigned int& _nbEtages)
{
	PrismQuad(listePoints[0], listePoints[1], listePoints[2], listePoints[3], hauteurEtage*_nbEtages).Render();
	//on monte dirrectement à l'étage au dessus du Rdc
	for(unsigned int vect = 0; vect < 4; vect++) listePoints[vect] += Vector(0,0, hauteurEtage*_nbEtages);
}


//----------------------------------------------------------------->
//-----------------------------ETAGE-------------------------------
//-----------------------------------------------------------------<

void Batiment::creerEtages(const unsigned int& _nbEtages, const unsigned int& etageActu)
{
	if(etageFenetre->isCreerFenetre())
		etageFenetre->creerEtagesVitres(listePoints, hauteurEtage, _nbEtages, etageActu, nbEtageRDC, nbEtagesMax);
	else
		creerEtagesSimples(_nbEtages);
}

void Batiment::creerEtagesSimples(const unsigned int& _nbEtages)
{
	//étage normal
	PrismQuad(listePoints[0],listePoints[1],listePoints[2],listePoints[3], _nbEtages*hauteurEtage).Render();
	for(unsigned int vect = 0; vect < 4; vect++) listePoints[vect] += Vector(0,0,_nbEtages*hauteurEtage);
}

//----------------------------------------------------------------->
//------------------------------TOIT--------------------------------
//-----------------------------------------------------------------<


void Batiment::creerBordureToit(const bool& toitParDefaut)
{
	double largeurBord = (double) UNITE*0.2;
	double hauteurBord = (double) UNITE;
	hauteurBord *= toitParDefaut?0.5:0.2;

	double air = Quadrangle(listePoints[0],listePoints[1],listePoints[2],listePoints[3]).Area();

	bool airMini = air > 8*(largeurBord*largeurBord); //2*le minimum

	if(airMini)
	{
		for(unsigned int i = 0; i < 4 && airMin; i++)
		{
			Vector a(listePoints[i%4]);
			Vector b(listePoints[(i+1)%4]);
			Vector pt1, pt2, pt3, pt4;

			Vector ab = Vector(b-a);

			double angle = ( atan2(ab[1],ab[0]) + (M_PI/2) )* (180/M_PI);
			double plusX = largeurBord*cos(angle*M_PI/180);
			double plusY = largeurBord*sin(angle*M_PI/180);

			pt1 = Vector(a[0], a[1], a[2]);
			pt2 = Vector(b[0], b[1], b[2]);
			pt3 = Vector(b[0] + plusX, b[1] + plusY, b[2]);
			pt4 = Vector(a[0] + plusX, a[1] + plusY, a[2]);

			Vector::setCol(125,125,125);
			PrismQuad(pt1, pt2, pt3, pt4, hauteurBord).Render();
			Vector::setColDefaut();
		}
	}
}


void Batiment::creerToitPyramideCoupe()
{
	double largeurBord = (double) UNITE*0.2;
	double hauteurBord = (double) UNITE*0.2;
	double air = Quadrangle(listePoints[0],listePoints[1],listePoints[2],listePoints[3]).Area();
	bool airMini = air > 8*(largeurBord*largeurBord);

	if(airMini)
	{
		float zTriangle = listePoints[0][2] + (float) hauteurEtage*2;
		Vector centre(0,0,0);

		for(unsigned int i = 0; i < listePoints.size(); i++) centre += listePoints[i];
		centre /= listePoints.size();
		double& z = centre[2]; 
		z = zTriangle; // mise à jour de Z

		//-------------------------Quadrangle supérieur --------------------------------------------------->
		std::vector<Vector> quadrangleIn; //la liste des points du quadrangle supérieur

		double onConserve = (double)(rand()%15)/100;
		for(unsigned int i = 0; i < listePoints.size(); i++)
		{
			Vector in = listePoints[i] + (centre - listePoints[i])*(onConserve + 0.5);
			double& z = in[2];
			z = zTriangle;
			quadrangleIn.push_back(in);
		}

		glBegin(GL_QUADS);
			glNormal3d(0,0,1.0f);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			glVertex3f(quadrangleIn[0][0], quadrangleIn[0][1], quadrangleIn[0][2]);
			glVertex3f(quadrangleIn[1][0], quadrangleIn[1][1], quadrangleIn[1][2]);
			glVertex3f(quadrangleIn[2][0], quadrangleIn[2][1], quadrangleIn[2][2]);
			glVertex3f(quadrangleIn[3][0], quadrangleIn[3][1], quadrangleIn[3][2]);

			for(int i=0; i<4;i++)
			{
				for(int j =0;j<3;j++)
				{
					ToitPyramideCoupe.push_back(quadrangleIn[i][j]);
				}
			}
			
		glEnd(); 
		//--------------------------------------------------------------------------------------------------<


		//----------------------------Faces de la "pyramide coupée"-----------------------------------------<  
		glBegin(GL_QUADS);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			for(unsigned int i = 0; i < 4; i++)
			{	
				glVertex3f(quadrangleIn[i%4][0], quadrangleIn[i%4][1], quadrangleIn[i%4][2]); // point Haut-Gauche
				glVertex3f(listePoints[i%4][0], listePoints[i%4][1], listePoints[i%4][2]); // point Bas-Gauche
				glVertex3f(listePoints[(i+1)%4][0], listePoints[(i+1)%4][1], listePoints[(i+1)%4][2]); //point Bas-Droite
				glVertex3f(quadrangleIn[(i+1)%4][0], quadrangleIn[(i+1)%4][1], quadrangleIn[(i+1)%4][2]); //point Haut-Droite
			}

			int j;
			for (int i=0; i<=3 ;i++)
			{
				for(j=0;j<=2;j++)
					ToitPyramideCoupe.push_back(quadrangleIn[i%4][j]);
				for(j=0;j<=2;j++)
			   	    ToitPyramideCoupe.push_back(listePoints[i%4][j]);
			    for(j=0;j<=2;j++)
				    ToitPyramideCoupe.push_back(listePoints[(i+1)%4][j]);
			    for(j=0;j<=2;j++)
			        ToitPyramideCoupe.push_back(quadrangleIn[(i+1)%4][j]);
			}


		glEnd();
		//--------------------------------------------------------------------------------------------------<

		listePoints.clear();
		for(unsigned int i = 0; i < quadrangleIn.size(); i++) listePoints.push_back(quadrangleIn[i]);

		if(rand()%101 > 30) creerBordureToit(false);
		else PrismQuad(quadrangleIn[0],quadrangleIn[1],quadrangleIn[2],quadrangleIn[3], ((double) UNITE)*0.2).Render();
	}
	
}


void Batiment::creerToitPyramide()
{
	double largeurBord = (double) UNITE*0.2;
	double hauteurBord = (double) UNITE*0.2;
	double air = Quadrangle(listePoints[0],listePoints[1],listePoints[2],listePoints[3]).Area();
	bool airMini = air > 8*(largeurBord*largeurBord);
	int j;

	if(airMini)
	{
		double hauteurPyramide = hauteurEtage*2;
		Vector monterEnZ(0,0,hauteurPyramide);
		Vector centre(0,0,0);

		for(unsigned int i = 0; i < listePoints.size(); i++) centre += listePoints[i];
		centre /= listePoints.size();
		centre += monterEnZ;// mise à jour de Z


		glBegin(GL_TRIANGLES); // Debut du dessin de la pyramide
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			for(unsigned int i = 0; i < 4; i++)
			{
				glNormal3d(0,0,1.0f);
				glVertex3f(centre[0], centre[1], centre[2]); // Haut du triangle de face
				glVertex3f(listePoints[i%4][0], listePoints[i%4][1], listePoints[i%4][3]); // Bas gauche du triangle de face
				glVertex3f(listePoints[(i+1)%4][0], listePoints[(i+1)%4][1], listePoints[(i+1)%4][3]); // Bas droit du triangle de face

				for(j=0;j<=2;j++)
			   	    ToitPyramide.push_back(centre[j]);
			    for(j=0;j<=1;j++)
				    ToitPyramide.push_back(listePoints[i%4][j]);
				if(j==2)
					ToitPyramide.push_back(listePoints[i%4][j+1]);
			    for(j=0;j<=1;j++)
			        ToitPyramide.push_back(listePoints[(i+1)%4][j]);
				if(j==2)
					ToitPyramide.push_back(listePoints[(i+1)%4][j+1]);

			}
		glEnd(); // Fin du dessin de la pyramide

		//ajout d'une antenne
		if(rand()%100 > 30)
		{
			//"0.9*" pour enterrer l'antenne dans la pyramide
			Vector enterrer(0,0, -0.15*hauteurPyramide);

			std::vector<Vector> quadrangleIn;

			// la base de l'antenne
			for(unsigned int i = 0; i < listePoints.size(); i++)
			{
				Vector in = (listePoints[i] + monterEnZ) + (centre - (listePoints[i] + monterEnZ))*0.97 + enterrer;
				quadrangleIn.push_back(in);
			}
			
			PrismQuad(quadrangleIn[0], quadrangleIn[1], quadrangleIn[2], quadrangleIn[3], hauteurEtage).Render();


			// l'antenne
			for(unsigned int i = 0; i < listePoints.size(); i++)
				quadrangleIn[i] = quadrangleIn[i] + (centre - quadrangleIn[i])*0.5;
			
			PrismQuad(quadrangleIn[0], quadrangleIn[1], quadrangleIn[2], quadrangleIn[3], hauteurPyramide*1.5).Render();
		}

	}
}


void Batiment::creerToitPrisme(bool ajouterCheminer)
{

	/*
	 d_________________c
	 |				   |
	e|________g________|f --> arrête supérieure du prisme
	 | 				   |
	 |________h________|
	 a				   b
	*/

	double air = Quadrangle(listePoints[0],listePoints[1],listePoints[2],listePoints[3]).Area();

	if(air > airMin)
	{
		double hauteurPrisme = (double) UNITE * 3;
		Vector monterEnZ(0,0,hauteurPrisme);
		int j;

		Vector e = ( (listePoints[3] + listePoints[0]) /2 ) + monterEnZ;
		Vector f = ( (listePoints[2] + listePoints[1]) /2 ) + monterEnZ;

		glBegin(GL_TRIANGLES); // Face ade
			Vector n= (listePoints[3]-listePoints[0])/(e-listePoints[0]);
			n/=Norm(n);
			glNormal3f(n[0],n[1],n[2]);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			glVertex3f(listePoints[0][0], listePoints[0][1], listePoints[0][2]);
			glVertex3f(listePoints[3][0], listePoints[3][1], listePoints[3][2]);
			glVertex3f(e[0], e[1], e[2]);

			  
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(listePoints[0][j]);
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(listePoints[3][j]);
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(e[j]);			

		glEnd();

		glBegin(GL_QUADS); // Face abfe
			n= (listePoints[1]-listePoints[0])/(e-listePoints[0]);
			n/=Norm(n);
			glNormal3f(n[0],n[1],n[2]);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			glVertex3f(listePoints[0][0], listePoints[0][1], listePoints[0][2]);
			glVertex3f(listePoints[1][0], listePoints[1][1], listePoints[1][2]);
			glVertex3f(f[0], f[1], f[2]);
			glVertex3f(e[0], e[1], e[2]);

			for(j=0;j<=2;j++)
				ToitPrisme.push_back(listePoints[0][j]);
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(listePoints[1][j]);
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(f[j]);
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(e[j]);
			
		glEnd();

		glBegin(GL_QUADS); // Face cdef
			n= (listePoints[3]-listePoints[2])/(f-listePoints[2]);
			n/=Norm(n);
			glNormal3f(n[0],n[1],n[2]);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			glVertex3f(listePoints[2][0], listePoints[2][1], listePoints[2][2]);
			glVertex3f(listePoints[3][0], listePoints[3][1], listePoints[3][2]);
			glVertex3f(e[0], e[1], e[2]);
			glVertex3f(f[0], f[1], f[2]);

			for(j=0;j<=2;j++)
				ToitPrisme.push_back(listePoints[2][j]);
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(listePoints[3][j]);
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(e[j]);
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(f[j]);

		glEnd();

		glBegin(GL_TRIANGLES); // Face bcf
			n= (listePoints[2]-listePoints[1])/(f-listePoints[1]);
			n/=Norm(n);
			glNormal3f(n[0],n[1],n[2]);
			glColor3ub(Vector::col1,Vector::col2,Vector::col3);
			glVertex3f(listePoints[1][0], listePoints[1][1], listePoints[1][2]);
			glVertex3f(listePoints[2][0], listePoints[2][1], listePoints[2][2]);
			glVertex3f(f[0], f[1], f[2]);

			for(j=0;j<=2;j++)
				ToitPrisme.push_back(listePoints[1][j]);
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(listePoints[2][j]);
			for(j=0;j<=2;j++)
				ToitPrisme.push_back(f[j]);

		glEnd();


		//-------------------Cheminée----------------------------->

		if(ajouterCheminer)
		{
			Vector g = (e + f)/2;
			Vector h = (listePoints[0] + listePoints[1])/2;

			double largeurCheminee = (double) UNITE;

			std::vector<Vector> nouvPoints;
			nouvPoints.push_back(listePoints[0] + monterEnZ/3);
			nouvPoints.push_back(h + monterEnZ/3); //e - monterEnZ + (monterEnZ/3)
			nouvPoints.push_back(e - (monterEnZ*2/3)); //g - monterEnZ + (monterEnZ/3)
			nouvPoints.push_back(g - (monterEnZ*2/3));

			Vector tmp = (listePoints[0] + e + g + h)/4;
			Vector centerAEGH = Vector(tmp[0],tmp[1], nouvPoints[0][2]); //le centre de la cheminée

			double tailleAd = Norm(nouvPoints[3] - nouvPoints[0]);
			double tailleAb = Norm(nouvPoints[1] - nouvPoints[0]);
			double ratioAbEtDc,ratioAdEtBc;
			if(tailleAd > tailleAb)
			{
				ratioAbEtDc = tailleAd/tailleAb;
				ratioAdEtBc = 1;
			}
			else
			{
				ratioAbEtDc = 1;
				ratioAdEtBc = tailleAb/tailleAd;
			}
		
			for(unsigned int i = 0; i < nouvPoints.size(); i++)
			{
				double pas = Norm(nouvPoints[i] - centerAEGH)/largeurCheminee;
				nouvPoints[i] = centerAEGH + ( (nouvPoints[i] - centerAEGH)/pas );
			}

			//Les sommets de la cheminée
			Vector a,b,c,d;
			a = nouvPoints[0];
			b = nouvPoints[1];
			c = nouvPoints[3];
			d = nouvPoints[2];

			//comme on veut que tous les côtés soient égaux, on applique un ratio
			PrismQuad(
				a,
				a + (b - a)*ratioAbEtDc,
				d + (c - d)*ratioAbEtDc,
				a + (d - a)*ratioAdEtBc,
				((double)UNITE)*3).Render();
		}
	}

}


//----------------------------------------------------------------->
//-----------------------------AUTRES-------------------------------
//-----------------------------------------------------------------<


void Batiment::scaleXY(const double& facteur, const Vector& invariants, std::vector<Vector>& variants) const
{
	if(!variants.empty() && facteur != 0 && facteur != 1) //si il y a au moins un point invariant et un variant et facteur != 0
	{

		double nouvFacteur = 1 - facteur;
		if(facteur > 1) nouvFacteur = facteur;

		//Modification des vecteurs "variants" en x et y
		for(unsigned int i = 0; i < variants.size(); i++)
		{
			variants[i][0] = invariants[0] + (variants[i][0] - invariants[0])*nouvFacteur;
			variants[i][1] = invariants[1] + (variants[i][1] - invariants[1])*nouvFacteur;
		}

	}
}


void Batiment::scaleXY(const double& facteur, const Vector& invariants, Vector& variants) const
{
	if(facteur != 0 && facteur != 1) //si il y a au moins un point invariant et un variant et facteur != 0
	{
		double nouvFacteur = 1 - facteur;
		if(facteur > 1) nouvFacteur = facteur;

		variants[0] = invariants[0] + (variants[0] - invariants[0])*nouvFacteur;
		variants[1] = invariants[1] + (variants[1] - invariants[1])*nouvFacteur;
	}
}


void Batiment::setBatimentInfos(const unsigned int& typeCentre, const double& hauteurMax)
{
	nbEtageRDC = 1;

	hauteur = hauteurMax; 
	separation = false;

	if(typeCentre == 0) //Ville
	{
		//if(typeBat = 0) //si c'est un building
		separation = true;
	}

	hauteurEtage = (double) UNITE*2.5; //par défaut, voir dans les classes filles
	nbEtagesMax = floor(hauteur/hauteurEtage);
	
	//initialisation de la classe qui crée les étages vitrés
	double unite = (double) UNITE;
	double largeurF = unite * (((double) (rand()%100)/100) + 1);
	etageFenetre = new EtageFenetre(largeurF, unite/2, unite, unite*0.4, unite*0.75);
	etageFenetre->setBoolCreerFenetre(airMin);
}

double Batiment::getHauteurParDefaut(){return rand()%2 + 0.5;}
unsigned int Batiment::getNbEtagesMax(){return nbEtagesMax;}
