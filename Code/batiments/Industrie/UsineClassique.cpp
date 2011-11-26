#include "UsineClassique.h"

std::vector<double> UsineClassique::ToitUsine;

UsineClassique::UsineClassique(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax): Usine(t, typeCentre, hauteurMax){setUsineClassiqueInfos();}
UsineClassique::UsineClassique(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax): Usine(q, typeCentre, hauteurMax){setUsineClassiqueInfos();}
UsineClassique::UsineClassique(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax): Usine(p, typeCentre, hauteurMax){setUsineClassiqueInfos();}
UsineClassique::~UsineClassique(void){}


void UsineClassique::batir(const Triangle& t){}

void UsineClassique::batir(const Quadrangle& q)
{
	batirEtages(q);
}

void UsineClassique::batir(const Pentangle& p){}


void UsineClassique::batirEtages(const Triangle& t){}

void UsineClassique::batirEtages(const Quadrangle& q)
{

	//PrismQuad(q, ((double) UNITE) *2).Render();
	
	int score = rand()%100;
	if(score > 30)
		typeEntrepot();
	else
		typeOld();
}


void UsineClassique::typeOld()
{
	/* On a deux versions, une pour le cas ou ab > ad et une seconde pour ab < ad

	 d_____f___h_______c
	 | 	   |  |		   |
	 | 	   |  |	...	   |	Si ab > ad : grandCote = 1
	 | 	   |  |		   |	avec aefd = Entrepôt, eghf et ... = chaîne, 
	 |_____|__|________|
	 a	   e  g		   b

	 
		d_______c
		|	    |
	   g|_______|h
		|	    |
		e_______f    Sinon ad > ab : grandCote = 3
		|	    |
		|	    |
		|	    |
		a_______b

	*/

	unsigned int grandCote = 3; //d
	if(Norm(listePoints[1]-listePoints[0]) > Norm(listePoints[3]-listePoints[0]))//ab > ad ?
		grandCote = 1;//b
	
	Vector vectGrandCote = listePoints[grandCote] - listePoints[0];
	double longueurGrandCote = Norm(vectGrandCote);


	if(longueurGrandCote > longueurGrandsEntr)
	{

		double petitCote = (grandCote+2)%4;
		Vector deplacementLargeur = listePoints[petitCote]-listePoints[0]; //ne change pas

		//------Création de l'entrepôt ---------------------->

		double pasEntr = longueurGrandCote/longueurGrandsEntr;
		Vector deplacementEntr = vectGrandCote/pasEntr;
		
		Vector e = listePoints[0] + deplacementEntr;
		Vector f = e + deplacementLargeur;

		//on doit choisir les points dans l'ordre inverse des aiguilles d'une montre (pour le rendu 3D, abcd != adcb : bizard)
		if(grandCote == 1)
			PrismQuad(listePoints[0], e, f, listePoints[3], hauteurGrandsEntr).Render(); //aefd
		else
			PrismQuad(listePoints[0], listePoints[1], f, e, hauteurGrandsEntr).Render(); //abfe

		//------Création des chaînes ---------------------->

		double longueurDispo = floor(longueurGrandCote - longueurGrandsEntr);
		unsigned int nbChaines = floor(longueurDispo/longMinBatChaine);
		Vector deplacementChaine = (listePoints[grandCote]-e)/nbChaines;
		

		/* 
			f___h_____
			|   |
			|   |	...   grandCote = 1
			|   |
			|___|_____    eg = deplacementChaine
			e  g


			  |	 ...  |
			 g|_______|h  grandCote = 3
			  |		  |
			  e_______f	  fh = deplacementChaine
		*/


		//on va partir de ef
		listePoints.clear();

		if(grandCote == 1) //eghf (voir schéma ci-dessus)
		{
			listePoints.push_back(e);
			listePoints.push_back(e + deplacementChaine);
			listePoints.push_back(f + deplacementChaine);
			listePoints.push_back(f);
		}
		else //efhg (ne pas regarder le schéma, il ne correspond pas à cette version)
		{
			listePoints.push_back(e);
			listePoints.push_back(f);
			listePoints.push_back(f + deplacementChaine);
			listePoints.push_back(e + deplacementChaine);

		}

		GLUquadric* params;
		params = gluNewQuadric();
		gluQuadricTexture(params, true);

		int j;

		Vector plusUnEtage(0,0, hauteurBatChaine);
		for(unsigned int i = 0; i < nbChaines; i++)
		{

			//std::cout<< i << std::endl;

			PrismQuad(listePoints[0], listePoints[1], listePoints[2], listePoints[3], hauteurBatChaine).Render();

			//on monte sur le bâtimenet pour créer la toîture
			for(unsigned int vect = 0; vect < 4; vect++) listePoints[vect] += plusUnEtage;

			//------------------ Prisme coupé ----------------------->

			Vector gZ = listePoints[0] + Vector(0,0,hauteurGrandsEntr - hauteurBatChaine);
			Vector hZ = listePoints[3] + Vector(0,0,hauteurGrandsEntr - hauteurBatChaine);


			glBegin(GL_QUADS); // Face de coupe
				Vector n= (gZ-listePoints[0])/(listePoints[3]-listePoints[0]);
				n/=Norm(n);
				glNormal3f(n[0],n[1],n[2]);
				glVertex3f(listePoints[0][0], listePoints[0][1], listePoints[0][2]);
				glVertex3f(gZ[0], gZ[1], gZ[2]);
				glVertex3f(hZ[0], hZ[1], hZ[2]);
				glVertex3f(listePoints[3][0], listePoints[3][1], listePoints[3][2]);

				for(j=0;j<=2;j++)
					ToitUsine.push_back(listePoints[0][j]);
				for(j=0;j<=2;j++)
					ToitUsine.push_back(gZ[j]);
				for(j=0;j<=2;j++)
					ToitUsine.push_back(hZ[j]);
				for(j=0;j<=2;j++)
					ToitUsine.push_back(listePoints[3][j]);


			glEnd();

			glBegin(GL_QUADS); //face inclinée
				n= (listePoints[2]-listePoints[1])/(hZ-listePoints[2]);
				n/=Norm(n);
				glNormal3f(n[0],n[1],n[2]);
				glVertex3f(listePoints[1][0], listePoints[1][1], listePoints[1][2]);
				glVertex3f(listePoints[2][0], listePoints[2][1], listePoints[2][2]);
				glVertex3f(hZ[0], hZ[1], hZ[2]);
				glVertex3f(gZ[0], gZ[1], gZ[2]);

				for(j=0;j<=2;j++)
					ToitUsine.push_back(listePoints[1][j]);
				for(j=0;j<=2;j++)
					ToitUsine.push_back(listePoints[2][j]);
				for(j=0;j<=2;j++)
					ToitUsine.push_back(hZ[j]);
				for(j=0;j<=2;j++)
					ToitUsine.push_back(gZ[j]);
				

			glEnd();

			glBegin(GL_TRIANGLES); // Triangle 1
				n= (gZ-listePoints[0])/(gZ-listePoints[1]);
				n/=Norm(n);
				glNormal3f(n[0],n[1],n[2]);
				glVertex3f(listePoints[0][0], listePoints[0][1], listePoints[0][2]);
				glVertex3f(listePoints[1][0], listePoints[1][1], listePoints[1][2]);
				glVertex3f(gZ[0], gZ[1], gZ[2]);

				for(j=0;j<=2;j++)
					ToitUsine.push_back(listePoints[0][j]);
				for(j=0;j<=2;j++)
					ToitUsine.push_back(listePoints[1][j]);
				for(j=0;j<=2;j++)
					ToitUsine.push_back(gZ[j]);

			glEnd();

			glBegin(GL_TRIANGLES); // Triangle 2
				n= (hZ-listePoints[2])/(hZ-listePoints[3]);
				n/=Norm(n);
				glNormal3f(n[0],n[1],n[2]);
				glVertex3f(listePoints[2][0], listePoints[2][1], listePoints[2][2]);
				glVertex3f(listePoints[3][0], listePoints[3][1], listePoints[3][2]);
				glVertex3f(hZ[0], hZ[1], hZ[2]);

				for(j=0;j<=2;j++)
					ToitUsine.push_back(listePoints[2][j]);
				for(j=0;j<=2;j++)
					ToitUsine.push_back(listePoints[3][j]);
				for(j=0;j<=2;j++)
					ToitUsine.push_back(hZ[j]);

			glEnd();

			//----------------------------------------------------------------->

			Vector centre = (listePoints[0] + listePoints[1] + listePoints[2] + listePoints[3])/4;
			glPushMatrix();
				glTranslatef(centre[0], centre[1], centre[2]);
				gluCylinder(params, ((double) UNITE)*1.7, (double) UNITE, ((double) UNITE)*6, 12, 1);
			glPopMatrix();

			//on redescend et on passe à l'entrepôt suivant
			for(unsigned int vect = 0; vect < 4; vect++) listePoints[vect] += - plusUnEtage + deplacementChaine;
		}

		gluDeleteQuadric(params);

		if(grandCote == 3) glPopMatrix();


	}
}


void UsineClassique::typeEntrepot()
{
	double unite = (double) UNITE;

	unsigned int grandCote = 3; //d
	if(Norm(listePoints[1]-listePoints[0]) > Norm(listePoints[3]-listePoints[0]))//ab > ad ?
		grandCote = 1;//b
	
	Vector vectGrandCote = listePoints[grandCote] - listePoints[0];
	double longueurGrandCote = Norm(vectGrandCote);

	if(longueurGrandCote > longueurGrandsEntr)
	{
		double petitCote = (grandCote+2)%4;
		Vector deplacementLargeur = listePoints[petitCote]-listePoints[0]; //ne change pas

		//------Création de l'entrepôt ---------------------->

		double pasEntr = longueurGrandCote/longueurGrandsEntr;
		Vector deplacementEntr = vectGrandCote/pasEntr;
		
		Vector e = listePoints[0] + deplacementEntr;
		Vector f = e + deplacementLargeur;

		
		if(grandCote == 1)
		{

			/*
				d____f___________c
				|    |  		 |
				|    |  	...	 |	Si ab > ad : grandCote = 1
				|    |  		 |	avec aefd = Entrepôt
				|____|___________|
				a	  e  		   b
			*/

			PrismQuad(listePoints[0], e, f, listePoints[3], hauteurGrandsEntr).Render(); //aefd

			//---------------- Volets métalique ----->
			double largeurPorteEntr = ((double) UNITE)*4;

			Vector ef = f - e;
			double longueurEf = Norm(ef);
			double occupationMax = longueurEf*0.6;
			unsigned int nbPorte = floor(occupationMax/largeurPorteEntr);
			Vector deplacPorte = (ef*0.6)/nbPorte;

			double longueurInterPorte = (longueurEf - (nbPorte*largeurPorteEntr)) / (nbPorte+1);
			double pasInterPorte = longueurEf/longueurInterPorte;
			Vector deplacInterPorte = ef/pasInterPorte;

			Vector ab = listePoints[1] - listePoints[0];
			double pasLargeurPorte = Norm(ab)/(unite*0.2);
			Vector deplacLargeur = (ab) / pasLargeurPorte;

			Vector eDroite = e + deplacLargeur + deplacInterPorte;
			Vector ePrim = e + deplacInterPorte;

			Vector::setCol(112,112,112);
			for(unsigned int i = 0; i < nbPorte-1 && nbPorte; i++)
			{
				eDroite += deplacInterPorte;
				ePrim += deplacInterPorte;

				PrismQuad(ePrim, eDroite, eDroite + deplacPorte, ePrim + deplacPorte, hauteurGrandsEntr*0.7).Render();

				eDroite += deplacPorte;
				ePrim += deplacPorte;
			}
			Vector::setColDefaut();

			//----------------Muret + portail----------->

			/*				depAbPortail
								-->
	 deplLargeurMuret		       c
			^	------------------x
			|	-------------d'x--x c'
							   |__|
							   |  | -->P   R   A   L
							   |__| -->  O   T   I
							   |  |
				-------------a'x--x b'
				------------------x
							       b
			*/

			double largeurMuret = unite*0.5;

			Vector deplLargeurMuret = ef / ( Norm(ef) / largeurMuret );
			PrismQuad(e, listePoints[1], listePoints[1]+ deplLargeurMuret,e + deplLargeurMuret, unite*3).Render();
			PrismQuad(f - deplLargeurMuret, listePoints[2] - deplLargeurMuret, listePoints[2], f, unite*3).Render();

			Vector depAbPortail = ab / ( Norm(ab) / largeurMuret );
			Vector aPrim = listePoints[1] - depAbPortail + deplLargeurMuret;
			Vector bPrim = listePoints[1] + deplLargeurMuret;
			Vector cPrim = listePoints[2] - deplLargeurMuret;
			Vector dPrim = listePoints[2] - depAbPortail - deplLargeurMuret;

			double largeurPortail = unite*3;
			Vector cPrimbPrim = cPrim-bPrim;
			double pasCotePortail = (Norm(cPrimbPrim) - largeurPortail)/2; //pour les murets chaque côté du portail
			Vector depLargeurCotePortail = (cPrimbPrim)/pasCotePortail;

			//quad du bas
			PrismQuad(aPrim,
					  bPrim,
					  bPrim + depLargeurCotePortail,
					  aPrim + depLargeurCotePortail,
					  unite*3).Render();

			Vector::setCol(112,112,112);
			//portail
			PrismQuad(aPrim + depLargeurCotePortail,
					  bPrim + depLargeurCotePortail,
					  cPrim - depLargeurCotePortail,
					  dPrim - depLargeurCotePortail,
					  unite*2.5).Render();
			Vector::setColDefaut();

			//quad du haut
			PrismQuad(dPrim - depLargeurCotePortail,
					  cPrim - depLargeurCotePortail,
					  cPrim,
					  dPrim,
					  unite*3).Render();

		}
		else
		{
			/*
				d_______c
				|       |
				|	    |-> portail
				| volet |
				e__---__f    Sinon ad > ab : grandCote = 3
				|	    |
				|	    |-> volet métalique
				a_______b
			*/


			PrismQuad(listePoints[0], listePoints[1], f, e, hauteurGrandsEntr).Render(); //abfe


			////Ajoute d'un volet entre b et f
			//Vector bf = f - listePoints[1];
			Vector ef = f - e;
			//double longueurPorteEntr = unite*5; //volet métallique sur le côté de l'entrepôt
			//double pasCotePorteBf = Norm(bf)/((longueurGrandsEntr - longueurPorteEntr)/2);
			//Vector depPorteCoteLong = bf/pasCotePorteBf;
			//Vector depPorteCoteLarg = ef/(Norm(ef)/(unite*0.2));
			//Vector::setCol(112,112,112);
			//PrismQuad(listePoints[1] + depPorteCoteLong,
			//		  listePoints[1] + depPorteCoteLong + depPorteCoteLarg,
			//		  f - depPorteCoteLong + depPorteCoteLarg,
			//		  f - depPorteCoteLong,
			//		  hauteurGrandsEntr*0.7).Render();
			//Vector::setColDefaut();


			//---------------- Volets métalique ----->
			double largeurPorteEntr = unite*6; //côté cours intérieur

			
			double longueurEf = Norm(ef);
			double occupationMax = longueurEf*0.7;
			unsigned int nbPorte = floor(occupationMax/largeurPorteEntr);
			Vector deplacPorte = (ef*0.7)/nbPorte;

			double longueurInterPorte = (longueurEf - (nbPorte*largeurPorteEntr)) / (nbPorte+1);
			double pasInterPorte = longueurEf/longueurInterPorte;
			Vector deplacInterPorte = ef/pasInterPorte;

			Vector ad = listePoints[2] - listePoints[0];
			double pasLargeurPorte = Norm(ad)/(unite*0.2);
			Vector deplacLargeur = (ad) / pasLargeurPorte;

			Vector eTop = e + deplacLargeur + deplacInterPorte;
			Vector ePrim = e + deplacInterPorte;

			Vector::setCol(112,112,112);
			for(unsigned int i = 0; i < nbPorte-1  && nbPorte; i++)
			{
				eTop += deplacInterPorte;
				ePrim += deplacInterPorte;

				PrismQuad(ePrim, ePrim + deplacPorte, eTop + deplacPorte, eTop, hauteurGrandsEntr*0.8).Render();

				eTop += deplacPorte;
				ePrim += deplacPorte;
			}
			Vector::setColDefaut();
		}


	}
	
}


void UsineClassique::batirEtages(const Pentangle& p){

}


void UsineClassique::setUsineClassiqueInfos()
{
	double unite = (double) UNITE;

	longueurGrandsEntr = unite*(rand()%4 + 12); //de 12 à 15m
	hauteurGrandsEntr = unite*(rand()%3+8); //de 8 à 10m

	longMinBatChaine = unite*(rand()%3 + 8); //de 8 à 10mètres;
	hauteurBatChaine = hauteurGrandsEntr - 1.5*unite; 

}