#include "quartierResidentiel.h"
using namespace std;

// CONSTRUCTEURS / DESTRUCTEURS

QuartierResidentiel::QuartierResidentiel(const Vector& _a, const Vector& _b, const Vector& _c,  const Centre& _centre) : Quartier(_a,_b,_c), centre(Centre(_centre))
{}

QuartierResidentiel::QuartierResidentiel(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d,  const Centre& _centre) : Quartier(_a,_b,_c,_d), centre(Centre(_centre))
{}

void QuartierResidentiel::choixQuartier(const Triangle& _t, const Centre& _centre)
{
	QuartierResidentiel qresidentiel(_t[0],_t[1],_t[2],Centre(_centre));

	float distance = qresidentiel.centre.getDistance(qresidentiel.a,qresidentiel.b,qresidentiel.c);
	float tailleImmeuble = qresidentiel.centre.getHauteur(distance);
    PrismTriangle(_t,tailleImmeuble).Render();
}

void QuartierResidentiel::choixQuartier(const Quadrangle& _q, const Centre& _centre)
{
	QuartierResidentiel qr(_q[0],_q[1], _q[2], _q[3], Centre(_centre));



	if((qr.ab > 2 * qr.da || qr.da > 2 * qr.ab)) qr.residence1Rangee(); //  && qr.ab < 20*UNITE && qr.da < 20*UNITE
	else if(min(qr.ab,qr.da) > 20*UNITE) qr.residenceRangee1Jardin();
	else Batiment::choixBatiment(_q,_centre.getType(), 7 + rand()%2);


}


//void QuartierResidentiel::residenceSimple()
//{
//
//}


void QuartierResidentiel::residence1Rangee()
{
	// nb aléatoire d'immeubles sur une rangée
	// Marche pour tout quadrangle ( ab > 3 * ad)
	// d o---------o c
	//   |         |
	// a o---------o b

	int nbBatiments = 2*(int) (double)(max(ab,bc)/10) ; if(nbBatiments == 0) nbBatiments =1;
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

			if(rand()%2 == 0)Batiment::choixBatiment(Quadrangle(v[0],v[1],v[2],v[3]), centre.getType(),7 + rand()%2);
			else Batiment::choixBatiment(Quadrangle(v[1],v[2],v[3],v[0]), centre.getType(), 7 + rand()%2);
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

			if(rand()%2 == 0)Batiment::choixBatiment(Quadrangle(v[0],v[3],v[2],v[1]), centre.getType(), 7 + rand()%2 );
			else Batiment::choixBatiment(Quadrangle(v[3],v[2],v[1],v[0]), centre.getType(), 7 + rand()%2 );
		}
	}
}

void QuartierResidentiel::residenceRangee1Jardin()
{
	double tempAB = ab, tempBC = bc, tempCD = cd, tempDA = da;
	Vector tempA = a, tempB = b, tempC = c, tempD = d;

	if (ab > da)
	{
		double diff = 0;
		if (rand()%2 == 0 && ab> 25*UNITE) diff = ab/6; else diff =  0;
		Vector v1,v2,v3,v4;

		if(rand()%2 == 0)
		{
			
			v1.setDiffxy(a,b, ab/2 + diff);
			v2.setDiffxy(d,c, ab/2 + diff);

			a = v1; d = v2;
			ab = Norm(b-a); cd = Norm(c-d);
			residence1Rangee();
			a = tempA; d = tempD; ab = tempAB; cd = tempCD;
			
			if(rand()%3 != 0)
			{
				v3.setDiffxy(d,a,0.2*UNITE);
				v4.setDiffxy(v2,v1,0.2*UNITE);
				PrismQuad(v3,v4,v2,d,5*UNITE).Render();
				v3.setDiffxy(a,b,0.2*UNITE);
				v4.setDiffxy(d,c,0.2*UNITE);
				PrismQuad(a,v3,v4,d,5*UNITE).Render();
				v3.setDiffxy(a,d,0.2*UNITE);
				v4.setDiffxy(v1,v2,0.2*UNITE);
				PrismQuad(a,v1,v4,v3,5*UNITE).Render();

				Vector::setCol(COL_HERBE1,COL_HERBE2, COL_HERBE3);
				PrismQuad(a,v1,v2,d,0.2).Render();
				Vector::setColDefaut();
			}
			else
			{
				b = v1; c = v2;
				ab = Norm(b-a); cd = Norm(d-c);
				residence1Rangee();
			}	
		}
		else
		{

				v1.setDiffxy(a,b, ab/2 - diff);
				v2.setDiffxy(d,c, ab/2 - diff);

				b = v1; c = v2;
				ab = Norm(b-a); cd = Norm(c-d);
				residence1Rangee();
				b = tempB; c = tempC; ab = tempAB; cd = tempCD;
		
			if(rand()%3 != 0)
			{
				v3.setDiffxy(v2,v1,0.2*UNITE);
				v4.setDiffxy(c,d,0.2*UNITE);
				PrismQuad(v3,v4,c,v2,5*UNITE).Render();
				v3.setDiffxy(b,a,0.2*UNITE);
				v4.setDiffxy(c,d,0.2*UNITE);
				PrismQuad(v3,b,c,v4,5*UNITE).Render();
				v3.setDiffxy(v1,v2,0.2*UNITE);
				v4.setDiffxy(b,c,0.2*UNITE);
				PrismQuad(v1,b,v4,v3,5*UNITE).Render();

				Vector::setCol(COL_HERBE1,COL_HERBE2, COL_HERBE3);
				PrismQuad(v1,b,c,v2,0.2).Render();
				Vector::setColDefaut();
			}
			else
			{
				a = v1; d = v2;
				ab = Norm(b-a); cd = Norm(d-c);
				residence1Rangee();
			}	
		
		}
	}
	else
	{

		double diff = 0;
		if (rand()%2 == 0 && da> 25*UNITE) diff = da/6; else diff =  0;
		Vector v1,v2,v3,v4;

		if(rand()%2 == 0)
		{
			
			v1.setDiffxy(a,d, da/2 + diff);
			v2.setDiffxy(b,c, da/2 + diff);

			a = v1; b = v2;
			da = Norm(a-d); bc = Norm(c-b);
			residence1Rangee();
			a = tempA; b = tempB; da = tempDA; bc = tempBC;
			


			if(rand()%3 != 0)
			{
				v3.setDiffxy(v1,v2,0.2*UNITE);
				v4.setDiffxy(a,b,0.2*UNITE);
				PrismQuad(a,v4,v3,v1,5*UNITE).Render();
				v3.setDiffxy(a,d,0.2*UNITE);
				v4.setDiffxy(b,c,0.2*UNITE);
				PrismQuad(a,b,v4,v3,5*UNITE).Render();
				v3.setDiffxy(b,a,0.2*UNITE);
				v4.setDiffxy(v2,v1,0.2*UNITE);
				PrismQuad(v3,b,v2,v4,5*UNITE).Render();
				Vector::setCol(COL_HERBE1,COL_HERBE2, COL_HERBE3);
				PrismQuad(a,b,v2,v1,0.2).Render();
				Vector::setColDefaut();
			}
			else
			{
				c = v2; d = v1;
				bc = Norm(c-b); da = Norm(a-d);
				residence1Rangee();
			}	
		}
		else
		{

			v1.setDiffxy(d,a, ab/2 + diff);
			v2.setDiffxy(c,b, ab/2 + diff);

			d = v1; c = v2;
			da = Norm(a-d); bc = Norm(c-b);
			residence1Rangee();
			d = tempD; c = tempC; da = tempDA; bc = tempBC;
	

			if(rand()%3 != 0)
			{
				v3.setDiffxy(v1,v2,0.2*UNITE);
				v4.setDiffxy(d,c,0.2*UNITE);
				PrismQuad(v1,v3,v4,d,5*UNITE).Render();
				v3.setDiffxy(d,a,0.2*UNITE);
				v4.setDiffxy(c,b,0.2*UNITE);
				PrismQuad(v3,v4,c,d,5*UNITE).Render();
				v3.setDiffxy(c,d,0.2*UNITE);
				v4.setDiffxy(v2,v1,0.2*UNITE);
				PrismQuad(v4,v2,c,v3,5*UNITE).Render();
				Vector::setCol(COL_HERBE1,COL_HERBE2, COL_HERBE3);
				PrismQuad(v1,v2,c,d,0.2).Render();
				Vector::setColDefaut();
			}
			else
			{
				a = v1; b = v2;
				da = Norm(a-d); bc = Norm(c-b);
				residence1Rangee();
			}	
		}
	}


}