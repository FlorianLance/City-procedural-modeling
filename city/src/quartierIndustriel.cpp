#include "quartierIndustriel.h"
using namespace std;

// CONSTRUCTEURS / DESTRUCTEURS

QuartierIndustriel::QuartierIndustriel(const Vector& _a, const Vector& _b, const Vector& _c, const Centre& _centre) : Quartier(_a,_b,_c), centre(Centre(_centre))
{}

QuartierIndustriel::QuartierIndustriel(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d, const Centre& _centre) : Quartier(_a,_b,_c,_d), centre(Centre(_centre))
{}

void QuartierIndustriel::choixQuartier(const Triangle& _t, const Centre& _centre)
{
	QuartierIndustriel qindustriel(_t[0],_t[1],_t[2],Centre(_centre));

	float distance = qindustriel.centre.getDistance(qindustriel.a,qindustriel.b,qindustriel.c);
	float tailleImmeuble = qindustriel.centre.getHauteur(distance);
    PrismTriangle(_t,tailleImmeuble).Render();
}

void QuartierIndustriel::choixQuartier(const Quadrangle& _q, const Centre& _centre)
{
	QuartierIndustriel qi(_q[0],_q[1], _q[2], _q[3], Centre(_centre));

	if((qi.ab > 2 * qi.da || qi.da > 2 * qi.ab)) qi.industrie1Rangee(); 
	else Batiment::choixBatiment(_q, _centre.getType(), 12 + rand()%5);

}



void QuartierIndustriel::industrie1Rangee()
{

	// nb aléatoire d'immeubles sur une rangée
	// Marche pour tout quadrangle ( ab > 3 * ad)
	// d o---------o c
	//   |         |
	// a o---------o b

	int nbBatiments = 2*(int) (double)(max(ab,bc)/20) ; if(nbBatiments == 0) nbBatiments =1;
	//cout << " nbBatiments " << nbBatiments <<" "  << 2*max(ab,bc)/10 << endl;
	//cout << nbBatiments << endl;
	double l_immeubleRajoute = 0;
	Vector v1, v2;
	Vector v[4];

	if(ab >da)
	{
		double labBatiment = ab/nbBatiments; if(labBatiment == 0) labBatiment =1;
		double ldcBatiment = cd/nbBatiments; if(ldcBatiment == 0) ldcBatiment =1;

		double abrestant = labBatiment;
		double dcrestant = ldcBatiment;
		

		for ( int i = 0 ; i < nbBatiments; i ++)
		{
			if ( i != 0) {v[0] = v[1]; v[3] = v[2];}
			else {v[0] = a; v[3] = d;}
			
			v[1].setDiffxy(a,b,abrestant);
			v[2].setDiffxy(d,c,dcrestant);

			if (i < nbBatiments - 1) {abrestant += labBatiment; dcrestant += ldcBatiment;}
			else {abrestant =  Norm(b-a); dcrestant = Norm(d-c);} 

			if(rand()%2 == 0)Batiment::choixBatiment(Quadrangle(v[0],v[1],v[2],v[3]), centre.getType(),12 + rand()%2);
			else Batiment::choixBatiment(Quadrangle(v[1],v[2],v[3],v[0]), centre.getType(), 12 + rand()%5);
		}
	}
	else {

		double ldaBatiment = da/nbBatiments; if(ldaBatiment == 0) ldaBatiment =1;
		double lbcBatiment = bc/nbBatiments; if(lbcBatiment == 0) lbcBatiment =1;

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

			if(rand()%2 == 0)Batiment::choixBatiment(Quadrangle(v[0],v[3],v[2],v[1]), centre.getType(),12 + rand()%2 );
			else Batiment::choixBatiment(Quadrangle(v[3],v[2],v[1],v[0]), centre.getType(), 12 + rand()%5 );
		}
	}
}