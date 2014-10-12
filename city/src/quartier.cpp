#include "quartier.h"
#include "quartierCentre.h"
#include "quartierResidentiel.h"
#include "quartierIndustriel.h"

#include <iostream>

using namespace std;

int nombreQuad = 10;

// CONSTRUCTEURS / DESTRUCTEURS

Quartier::Quartier()
{}

Quartier::Quartier(const Vector& _a, const Vector& _b, const Vector& _c) : a(_a), b(_b), c(_c), 
																				 ab(Norm(b-a)), bc(Norm(c-b)), ca(Norm(a-c))
{}

Quartier::Quartier(const Vector& _a, const Vector& _b, const Vector& _c,  const vector<Centre> &_centres) : a(_a), b(_b), c(_c), 
																					centres(_centres), ab(Norm(b-a)), bc(Norm(c-b)), ca(Norm(a-c))
{}

Quartier::Quartier(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d) : a(_a), b(_b), c(_c), d(_d),
																					 ab(Norm(b-a)), bc(Norm(c-b)), cd(Norm(d-c)), da(Norm(a-d))
{}

Quartier::Quartier(const Vector& _a, const Vector& _b, const Vector& _c, const Vector& _d,  const vector<Centre> &_centres) : a(_a), b(_b), c(_c), d(_d),
																					centres(_centres), ab(Norm(b-a)), bc(Norm(c-b)), cd(Norm(d-c)), da(Norm(a-d))
{}


void Quartier::choixQuartier(const Triangle& _t, const vector< Centre>& _centres)
{
	//QuartierCentre::choixQuartier(_t,_centres);
}

void Quartier::choixQuartier(const Quadrangle& _q, const vector< Centre>& _centres)
{
	double totalDistance = 0, additionChance = 0, additionT = 0, minDistance = 10000000; int numCentreRetenu = 0, numMin =  0;
	vector<double> t;

		for(int i = 0; i != _centres.size(); i++) {double d = _centres[i].getDistance(_q); totalDistance += d; if(minDistance > d){ minDistance = d; numMin = i;}}
		for(int i = 0; i != _centres.size(); i++) {
			double multi;
			if(i == numMin) { multi = 20;}
			else multi = 1;
				t.push_back(multi*totalDistance/_centres[i].getDistance(_q)); 
				additionT += 10*t[i]; 
		
		}

		int chance = rand()%(int)additionT;

		for(int i = 0; i != _centres.size(); i++)
		{
			additionChance += 10*t[i];
			if(chance <= additionChance){numCentreRetenu = i; break;}
		}


		switch(_centres[numCentreRetenu].getType())
		{
		case VILLE:   QuartierCentre::choixQuartier(_q,_centres[numCentreRetenu]);
		break;
		case RESIDENCE: QuartierResidentiel::choixQuartier(_q,_centres[numCentreRetenu]); 
		break;
		case INDUSTRIEL: QuartierIndustriel::choixQuartier(_q,_centres[numCentreRetenu]);
		break;
		default: QuartierCentre::choixQuartier(_q,_centres[0]);
		break;
		}


}




