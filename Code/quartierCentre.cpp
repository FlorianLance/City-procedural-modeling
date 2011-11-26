#include "quartierCentre.h"

using namespace std;

ostream& operator<<( ostream &flux, const Vector& u)
{
    u.afficher(flux);
	return flux;
}

// CONSTRUCTEURS / DESTRUCTEURS

QuartierCentre::QuartierCentre(const Vector& _a, const Vector& _b, const Vector& _c,  const Centre& _centre) : Quartier(_a,_b,_c), centre(Centre(_centre))
{}

QuartierCentre::QuartierCentre(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d,  const Centre& _centre) : Quartier(_a,_b,_c,_d), centre(Centre(_centre))
{}

void QuartierCentre::choixQuartier(const Triangle& _t,const Centre& _centre)
{
	QuartierCentre qcentre(_t[0],_t[1],_t[2],Centre(_centre));

	float distance = qcentre.centre.getDistance(qcentre.a,qcentre.b,qcentre.c);
	float tailleImmeuble = qcentre.centre.getHauteur(distance);
    PrismTriangle(_t,tailleImmeuble).Render();
}

void QuartierCentre::choixQuartier(const Quadrangle& _q, const Centre& _centre)
{
	QuartierCentre qc(_q[0], _q[1], _q[2], _q[3], Centre(_centre));


	//cout << qc.centre.getDistance(qc.a,qc.b,qc.c,qc.d) << endl;

	if (qc.centre.getDistance(qc.a,qc.b,qc.c,qc.d) < 300*UNITE + rand()%20 *UNITE )
	{
		qc.centreGratteciel();
	}
	else
	{
		if(((qc.ab < 2 *qc.bc/3 +20*UNITE)&&(qc.ab > 2 *qc.bc/3 - 20*UNITE) || ((qc.bc < 2 *qc.ab/3 + 20*UNITE) && (qc.bc > 2 *qc.ab/3 + 20*UNITE))) && (qc.ab < 70*UNITE && qc.bc < 70*UNITE) && (qc.ab > 35*UNITE && qc.bc > 35*UNITE)) // centreCour
		{
			qc.centreCour();
			//cout << "cour " << qc.ab << " " << qc.bc << endl;
		}
		else if((qc.ab > 3 * qc.bc - 20*UNITE || qc.ab > 3 * qc.bc + 20*UNITE)  && min(qc.ab,qc.bc) > 12*UNITE ) // centre1Rangee
		{
			
			qc.centre1Rangee();
			//cout << "rangee1 " << qc.ab << " " << qc.bc << endl;
		}
		else if((qc.ab > 2 * qc.bc - 10*UNITE || qc.ab > 2 * qc.bc + 10*UNITE) && min(qc.ab,qc.bc) > 20*UNITE) // centre2Rangee
		{
			qc.centre2Rangee();
			//cout << "rangee2 " << qc.ab << " " << qc.bc << endl;
		}
		else if(qc.ab < qc.bc + 20*UNITE && qc.ab > qc.bc -20*UNITE  ) // centreCarre
		{
			qc.centreCarre();
			//cout << "carre " << qc.ab << " " << qc.bc << endl;
		}
		else if(qc.ab > 15*UNITE && qc.da > 15*UNITE)
		{
			//qc.centreRajout();
			//cout << "--------  autre : " << qc.ab << "  " << qc.da << endl;
			Batiment::choixBatiment(Quadrangle(qc.a,qc.b,qc.c,qc.d),qc.centre.getType(), qc.centre.getHauteur(qc.centre.getDistance(Quadrangle(qc.a,qc.b,qc.c,qc.d))));
			
		}
		else
		{
			//cout << "herbe "<< endl;
			Vector::setCol(COL_HERBE1,COL_HERBE2,COL_HERBE3); // a défaut on fout de l'herbe
			PrismQuad(Quadrangle(qc.a,qc.b,qc.c,qc.d),3*UNITE).Render();
			Vector::setColDefaut();
		}

	}

	//cout << "nbQuad: " << PrismQuad::nbQuad << endl;
}


void QuartierCentre::centreGratteciel()
{
	Vector c1(0,0,0),c2(0,0,0),c3(0,0,0),c4(0,0,0);
	Vector c5(0,0,0),c6(0,0,0),c7(0,0,0),c8(0,0,0);


	if((ab > 3* bc   - 20*UNITE || ab > 3*bc + 10*UNITE) && min(ab,bc) > 20*UNITE && max(ab,bc)>30*UNITE)
	{
		//cout << " ab > 3 * bc " << ab << " " << bc << endl;
		c1.setDiffxy(a,b, ab/3 - 5*UNITE); c2.setDiffxy(a,b, ab/3 + 5*UNITE); c3.setDiffxy(a,b, 2*ab/3 - 5*UNITE); c4.setDiffxy(a,b, 2*ab/3 + 5*UNITE);
		c5.setDiffxy(d,c, cd/3 - 5*UNITE); c6.setDiffxy(d,c, cd/3 + 5*UNITE); c7.setDiffxy(d,c, 2*cd/3 - 5*UNITE); c8.setDiffxy(d,c, 2*cd/3 + 5*UNITE);

		Batiment::choixBatiment(Quadrangle(a,c1,c5,d),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
		Batiment::choixBatiment(Quadrangle(c2,c3,c7,c6),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
		Batiment::choixBatiment(Quadrangle(c4,b,c,c8),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));

	}
	else if ((bc > 3 * ab - 20*UNITE || bc > 3 * ab + 10*UNITE)&& min(ab,bc) > 20*UNITE && max(ab,bc)>30*UNITE)
	{
		//cout << " bc > 3 * ab " << endl;
		c1.setDiffxy(a,d, da/3 - 5*UNITE); c2.setDiffxy(a,d, da/3 + 5*UNITE); c3.setDiffxy(a,d, 2*da/3 - 5*UNITE); c4.setDiffxy(a,d, 2*da/3 + 5*UNITE);
		c5.setDiffxy(b,c, bc/3 - 5*UNITE); c6.setDiffxy(b,c, bc/3 + 5*UNITE); c7.setDiffxy(b,c, 2*bc/3 - 5*UNITE); c8.setDiffxy(b,c, 2*bc/3 + 5*UNITE);

		Batiment::choixBatiment(Quadrangle(a,b,c5,c1),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
		Batiment::choixBatiment(Quadrangle(c2,c6,c7,c3),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
		Batiment::choixBatiment(Quadrangle(c4,c8,c,d),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
	}
	else if(ab > 45*UNITE && bc > 45*UNITE) // pas de gratteciels carrés plus larges que 60 m
	{
		//cout << " ab > 50*UNITE && bc > 50*UNITE " << endl;
		c1.setDiffxy(a,b, ab/2 - 5 * UNITE); c2.setDiffxy(a,b, ab/2 + 5 *UNITE); c3.setDiffxy(a,d,da/2 - 5*UNITE); c6.setDiffxy(b,c,bc/2 - 5*UNITE);
		c4.setDiffxy(c3,c6, ab/2 - 5 *UNITE); c5.setDiffxy(c3,c6, ab/2 + 5 * UNITE);
		Batiment::choixBatiment(Quadrangle(a,c1,c4,c3),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
		Batiment::choixBatiment(Quadrangle(c2,b,c6,c5),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));

		c1.setDiffxy(a,d, da/2 + 5* UNITE); c4.setDiffxy(b,c, bc/2 + 5 *UNITE); c2.setDiffxy(c1,c4,ab/2 - 5*UNITE); c3.setDiffxy(c1,c4,ab/2 + 5*UNITE);
		c5.setDiffxy(d,c, cd/2 - 5 *UNITE); c6.setDiffxy(d,c, cd/2 + 5 * UNITE);
		Batiment::choixBatiment(Quadrangle(c1,c2,c5,d),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
		Batiment::choixBatiment(Quadrangle(c3,c4,c,c6),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));

	}
	else if((ab > 2* bc - 10*UNITE || ab > 2* bc + 10*UNITE) && min(ab,bc) > 20*UNITE && max(ab,bc)>30*UNITE)
	{
		//cout << " ab > 2* bc " << ab<< " " << bc << endl;
		c1.setDiffxy(a,b, ab/2 - 5*UNITE); c2.setDiffxy(a,b, ab/2 + 5*UNITE);
		c3.setDiffxy(d,c, cd/2 - 5*UNITE); c4.setDiffxy(d,c, cd/2 + 5*UNITE);

		Batiment::choixBatiment(Quadrangle(c2,b,c,c4),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
		Batiment::choixBatiment(Quadrangle(a,c1,c3,d),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
	}
	else if((bc > 2 * ab - 10*UNITE || bc > 2 * ab + 10*UNITE)  && min(ab,bc) > 20*UNITE && max(ab,bc)>30*UNITE)
	{
		//cout << " bc > 2 * ab " << bc << " " << ab <<  endl;
		c1.setDiffxy(a,d, da/2 - 5*UNITE); c2.setDiffxy(a,d, da/2 + 5*UNITE);
		c3.setDiffxy(b,c, bc/2 - 5*UNITE); c4.setDiffxy(b,c, bc/2 + 5*UNITE);

		Batiment::choixBatiment(Quadrangle(a,b,c3,c1),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
		Batiment::choixBatiment(Quadrangle(c2,c4,c,d),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
	}

	else if((ab < 1.5 * bc  || bc < 1.5* ab)&& min(ab,bc) > 15*UNITE && max(ab,bc)>25*UNITE)
	{
		if(ab >= bc)
		{
			//cout << "ab < 2 * bc  && bc < 2* ab && ab >= bc" <<  endl;
			c1.setDiffxy(a,b, (ab-da)/2);
			c2.setDiffxy(a,b, ab - (ab-da)/2);
			c3.setDiffxy(d,c, (cd-da)/2);
			c4.setDiffxy(d,c, cd - (cd-da)/2);
			Batiment::choixBatiment(Quadrangle(c1,c2,c4,c3),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));
		}
		else
		{
			//cout << "ab < 2 * bc  && bc < 2* ab && ab < bc" <<  endl;
			c1.setDiffxy(a,d, (da-ab)/2);
			c2.setDiffxy(a,d, da - (da-ab)/2);
			c3.setDiffxy(b,c, (bc-ab)/2);
			c4.setDiffxy(b,c, bc - (bc-ab)/2);
			Batiment::choixBatiment(Quadrangle(c1,c3,c4,c2),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));			
		}

	}
	else
	{
		Batiment::choixBatiment(Quadrangle(a,b,c,d),centre.getType(), centre.getHauteur(centre.getDistance(Quadrangle(a,b,c,d))));	
		//cout << "GratteCiel non gere " << endl;
	}

}


void QuartierCentre::centreCour() 
{	
	// nb d'immeubles aléatoire sur tous les côté + cours intétieure
	// Marche pour pour rectangles et losanges ( rapport 2/3)
	// d o---------o c
	//   |         |
	// a o---------o b

	Vector p2[4];
	double l = 2 + rand()%2;
	
	creationPointsLongueur(a,b,c,d);
	creationPointsLongueur(c,d,a,b);

	// création des 2 côtés restants
	Vector x1,x2,x3,x4;
	x1.setDiffxy(a,b,0.1); x2.setDiffxy(d,c,0.1); x3.setDiffxy(b,a,0.1); x4.setDiffxy(c,d,0.1); // décallage pour éviter le chevauchement

	p2[0].setDiffxy(x1,x2,l);//p2[0].setDiffxy(a,d,l);
	p2[1].setDiffxy(x3,x4,l);//p2[1].setDiffxy(b,c,l);
	p2[2].setDiffxy(x4,x3,l);//p2[2].setDiffxy(c,b,l);
	p2[3].setDiffxy(x2,x1,l);//p2[3].setDiffxy(d,a,l);

	creationPointsLongueur(p2[3],p2[0],p2[1],p2[2]);
	creationPointsLongueur(p2[1],p2[2],p2[3],p2[0]);
}

void QuartierCentre::centre1Rangee()
{
	// nb aléatoire d'immeubles sur une rangée
	// Marche pour tout quadrangle ( ab > 3 * ad)
	// d o---------o c
	//   |         |
	// a o---------o b

	int nbBatiments = 2*(int) (double)(max(ab,bc)/10); if (nbBatiments == 0) nbBatiments = 1;
	//cout << " nbBatiments " << nbBatiments <<" "  << 2*max(ab,bc)/10 << endl;
	//cout << nbBatiments << endl;
	double l_immeubleRajoute = 0;
	Vector v1, v2;

	if(rand()%10 == 0 &&  nbBatiments > 1)
	{
		l_immeubleRajoute = min(ab,da)/2 - (rand()%2)*UNITE; 
		
		if(rand()%2 == 0)
		{
			v1.setDiffxy(a,b,l_immeubleRajoute);
			v2.setDiffxy(d,c,l_immeubleRajoute);
			zoneRajoutee(a,v1,v2,d,7 + rand()%3);
			a = v1; d = v2;
			ab = Norm(b-a); cd = Norm(d-c);
		}

		else 
		{
			
			v1.setDiffxy(b,a,l_immeubleRajoute);
			v2.setDiffxy(c,d,l_immeubleRajoute);
			zoneRajoutee(v1,b,c,v2,7 + rand()%3);
			b = v1; c = v2;
			ab = Norm(b-a); cd = Norm(d-c);

		}
		nbBatiments--;
	}


	double labBatiment = ab/nbBatiments; if (labBatiment == 0) labBatiment = 1;
	double ldcBatiment = cd/nbBatiments; if (ldcBatiment == 0) labBatiment = 1;

	double abrestant = labBatiment;
	double dcrestant = ldcBatiment;
	Vector v[4];
	
	if(ab >da)
	{
		for ( int i = 0 ; i < nbBatiments; i ++)
		{
			if ( i != 0) {v[0] = v[1]; v[3] = v[2];}
			else {v[0] = a; v[3] = d;}
			
			v[1].setDiffxy(a,b,abrestant);
			v[2].setDiffxy(d,c,dcrestant);

			if (i < nbBatiments - 1) {abrestant += labBatiment; dcrestant += ldcBatiment;}
			else {abrestant =  ab; dcrestant = cd;} 

			//PrismQuad(Quadrangle(v[0],v[1],v[2],v[3]) ,rand()%2 + 5).Render(); // HAUTEUR A MODIFIER
			//std::cout <<  (int)(double)centre.getDistance(Quadrangle(a,b,c,d))/50 << std::endl;
			Batiment::choixBatiment(Quadrangle(v[0],v[1],v[2],v[3]), centre.getType(), 4);// 15 - (int)(double)centre.getDistance(Quadrangle(a,b,c,d))/50);
		}
	
	}
	else {
		
		double ldaBatiment = da/nbBatiments; if (ldaBatiment == 0) labBatiment = 1;
		double lbcBatiment = bc/nbBatiments; if (lbcBatiment == 0) labBatiment = 1;

		double darestant = ldaBatiment;
		double bcrestant = lbcBatiment;

		for ( int i = 0 ; i < nbBatiments; i ++)
		{
			if ( i != 0) {v[0] = v[1]; v[3] = v[2];}
			else {v[0] = a; v[3] = b;}
			
			v[1].setDiffxy(a,d,darestant);
			v[2].setDiffxy(b,c,bcrestant);

			if (i < nbBatiments - 1) {darestant += ldaBatiment; bcrestant += lbcBatiment;}
			else {darestant =  da; bcrestant = bc;} 

			//PrismQuad(Quadrangle(v[0],v[1],v[2],v[3]) ,rand()%2 + 5).Render(); // HAUTEUR A MODIFIER
			//std::cout <<  (int)(double)centre.getDistance(Quadrangle(a,b,c,d))/50 << std::endl;
			Batiment::choixBatiment(Quadrangle(v[0],v[3],v[2],v[1]), centre.getType(), 4);//15 - (int)(double)centre.getDistance(Quadrangle(a,b,c,d))/50);
		}
	}
}

void QuartierCentre::centre2Rangee()
{
	// nb d'immeubles aléatoire sur 2 rangées
	// Marche pour tout quadrangle  ( ab > 2 * ad)
	// d o----------o c
	//   |          |
	// x1|----------|x2
	//   |          |
	// a o----------o b

	double l_immeubleRajoute = 0;
	Vector v1, v2;
		
	if(rand()%4 == 0 && min(ab,da) >20)
	{
		l_immeubleRajoute = 5 + rand()%3;
		
		if(rand()%2 == 0)
		{
			v1 = a; v2 = d;
			a.setDiffxy(a,b,l_immeubleRajoute);
			d.setDiffxy(d,c,l_immeubleRajoute);
			zoneRajoutee(v1,a,d,v2,7 + rand()%3);
		}

		else 
		{
			v1 = b; v2 = c;
			b.setDiffxy(b,a,l_immeubleRajoute);
			c.setDiffxy(c,d,l_immeubleRajoute);
			zoneRajoutee(b,v1,v2,c,7 + rand()%3);
		}
	}

	Vector x1,x2, tempC,tempD;
	x1.setDiffxy(a,d,da/2);
	x2.setDiffxy(b,c,bc/2);

	tempC = c;
	tempD = d;

    c = x2;
	d = x1;
	bc = Norm(c-b);
	da = Norm(d-a);
	
	centre1Rangee();

	c = tempC;
	d = tempD;
	a = x1;
	b = x2;

	da = Norm(d-a);
	bc = Norm(c-b);

	centre1Rangee();
}

void QuartierCentre::centreCarre()
{

	// Marche pour tout quadrangle  ( ab == ad  ab > 5, ad > 5)
	// d o----x2----o c
	//   |         |
	// y1|----m----|y2
	//   |         |
	// a o----x1---o b

	double x_milieu = 0, y_milieu = 0;
	Vector x1,x2,y1,y2,m;

	if(rand()%2 == 0) x_milieu = ab/2 + rand()%4;
	else x_milieu = ab/2 - rand()%4;
	 
	if(rand()%2 == 0) y_milieu = da/2 + rand()%4;
	else y_milieu = da/2 - rand()%4;

	x1.setDiffxy(a,b,x_milieu);
	x2.setDiffxy(d,c,x_milieu);
	y1.setDiffxy(d,a,y_milieu);
	y2.setDiffxy(c,b,y_milieu);

	m.setDiffxy(y1,y2,x_milieu);

	int h = 15 - (int)(double)centre.getDistance(Quadrangle(a,b,c,d))/50;
	if(h<7)h = 7; 
	Batiment::choixBatiment(Quadrangle(a,x1,m,y1), centre.getType(), h);
	Batiment::choixBatiment(Quadrangle(x1,b,y2,m), centre.getType(), h); 
	Batiment::choixBatiment(Quadrangle(y1,m,x2,d), centre.getType(), h); 
	Batiment::choixBatiment(Quadrangle(m,y2,c,x2), centre.getType(), h); 

	//PrismQuad(Quadrangle(a,x1,m,y1) ,rand()%4 + 5).Render(); // HAUTEUR A MODIFIER
	//PrismQuad(Quadrangle(x1,b,y2,m) ,rand()%4 + 5).Render();
	//PrismQuad(Quadrangle(y1,m,x2,d) ,rand()%4 + 5).Render();
	//PrismQuad(Quadrangle(m,y2,c,x2) ,rand()%4 + 5).Render();

}

void QuartierCentre::centreRajout()
{
	// items rajoutés aléatoirements aux aux "centres" (immeuble individuel, cours cloisonnée)
	// Marche pour tout quadrangle ( 2ab > 3 * ad)
	// d o---------o c
	//   |         |
	//	 |         |
	// a o---------o b

	double l_immeubleRajoute = 0;
	Vector v1, v2;

	int cote = 0;

	if(rand()%4 == 0)
	{
		l_immeubleRajoute = 5 + rand()%3;
		
		if(rand()%2 == 0)
		{
			v1 = a; v2 = d;
			a.setDiffxy(a,b,l_immeubleRajoute);
			d.setDiffxy(d,c,l_immeubleRajoute);
			zoneRajoutee(v1,a,d,v2,15 + rand()%6);
			cote = 1;
			
		}

		else 
		{
			v1 = b; v2 = c;
			b.setDiffxy(b,a,l_immeubleRajoute);
			c.setDiffxy(c,d,l_immeubleRajoute);
			zoneRajoutee(b,v1,v2,c,15 + rand()%6);
			cote = 2;
		}
	}

	//if(cote != 1)
	//{
	//	Vector x1 = d,x2 = a;
	//	std::vector<Vector> tabVa,tabVb,tabVc,tabVd;
	//	double nbBatiments = rand()%3 + 4;
	//	double pronfondeur = rand()%3 + 4;
	//	double longueur = da/nbBatiments;
	//	double longueurEnCours = 0;

	//	//tabVa.push_back(d); tabVb.push_back(
	//	//for (unsigned int i = 0; i <  nbBatiments; i ++)
	//	//{
	//	//	

	//	//}
	//}

	//if(cote != 2)
	//{

	//}



}

void QuartierCentre::zoneRajoutee(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const double _taille)
{
	// d o---------o c
	//   |         |
	//	 |         |
	// a o---------o b
	int res = rand()%2;
	Vector a2,b2,c2,d2,a3,b3,c3,d3;
	int h = 15 - (int)(double)centre.getDistance(Quadrangle(a,b,c,d))/50;
	switch (res)
	{
		case 0:
			//PrismQuad(Quadrangle(_a,_b,_c,_d) ,_taille).Render();
			
			if(h<7)h = 7; 
			Batiment::choixBatiment(Quadrangle(_a,_b,_c,_d), centre.getType(), h);
		break;
		case 1:
			

			a2.setDiffxy(a,b,0.3);
			d2.setDiffxy(d,c,0.3);
			c2.setDiffxy(c,d,0.3);
			b2.setDiffxy(b,a,0.3);

			a3.setDiffxy(a2,d2,0.3);
			d3.setDiffxy(d2,a2,0.3);
			c3.setDiffxy(c2,b2,0.3);
			b3.setDiffxy(b2,c2,0.3);

			PrismQuad(Quadrangle(a,a2,d2,d) ,3*UNITE).Render();
			PrismQuad(Quadrangle(b2,b,c,c2) ,3*UNITE).Render();
			PrismQuad(Quadrangle(a2,b2,b3,a3) ,3*UNITE).Render();
			PrismQuad(Quadrangle(d3,c3,c2,d2) ,3*UNITE).Render();

		break;
		default:

		break;
	}
}




void QuartierCentre::creationPointsLongueur(const Vector& v1, const Vector& v2,const Vector& v3,const Vector& v4)
{
	double l = Norm(v2-v1);
	double h = Norm(v4-v3);
	bool nonTermine = true;

	double lrestante = l;
	double nbP = 1;
	if (l >= 100*UNITE) nbP = 6;
	else if(l >=80*UNITE) nbP = 4;
	else if(l >=40*UNITE) nbP = 2;
	else  nbP = 1;

	double tailleMoy = l / nbP; 

	double profondeur = 0;
	double tempL = 0;
	
	//cout << "tmoy = " << tailleMoy << "nbP = " << nbP<< endl;
	//cout << "l = " << l << endl;
	//
	vector<Vector> tabPx1;
	vector<Vector> tabPx2;
	vector<Vector> tabPx3;
	vector<Vector> tabPx4;


	int i = 0;
	while(nonTermine)
	{
	
		
		tempL = lrestante;

		if(i != 0 ){
			//if((int)tailleMoy == 0){lrestante -= 2;}

			lrestante -= tailleMoy-1 + rand()%2 ;

		}
		else lrestante -=3;


		if(i != 0 ){ profondeur = h/2 - rand()%3*UNITE -3*UNITE;
		//cout << profondeur << endl;
			//if((int)(h/2 -1) == 0){ profondeur = 2;}
			//else profondeur =  rand()%(int)(h/2 -1) + 2;
		}
		else profondeur = 10*UNITE;

		if (profondeur < 6 ) profondeur = 6;

		if(lrestante < tailleMoy -2 || lrestante < 0 )
		{
			lrestante = 0;
			profondeur = 4;
			
			nonTermine = false;
		}



		if(lrestante != 0)
		{
			tabPx2.push_back(Vector().getDiffxy(v1,v2,l - lrestante));
			Vector temp1 = temp1.getDiffxy(v4,v3,l - lrestante);
			tabPx3.push_back(Vector().getDiffxy(tabPx2[i],temp1, profondeur));
		}
		else 
		{
			tabPx3.push_back(Vector().getDiffxy(v2,v3,profondeur));
			tabPx2.push_back(v2);
		}



		if(i != 0) 
		{
			tabPx1.push_back(tabPx2[i-1]);
			Vector temp2 = temp2.getDiffxy(v4, v3, l - tempL);
			Vector temp3 = temp3.getDiffxy(tabPx2[i-1], temp2, profondeur);
			tabPx4.push_back(temp3);
		}
		else { tabPx1.push_back(v1); tabPx4.push_back(Vector().getDiffxy(v1,v4,profondeur));}

	
		
		//PrismQuad(Quadrangle(tabPx1[i],tabPx2[i],tabPx3[i],tabPx4[i]) ,rand()%2 + 5).Render();
	
		int h = 15 - (int)(double)centre.getDistance(Quadrangle(a,b,c,d))/50;
		if(h<7)h = 7; 
		Batiment::choixBatiment(Quadrangle(tabPx1[i],tabPx2[i],tabPx3[i],tabPx4[i]), centre.getType(), h);

		i++;

	}
}
