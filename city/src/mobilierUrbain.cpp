
#include "mobilierUrbain.h"

Mobilier::Mobilier(const double _hauteurLampadaire, const  double _distanceEspacement, const double _largeurLampadaire) : h(_hauteurLampadaire), d(_distanceEspacement), l(_largeurLampadaire)
{
}


void Mobilier::creerLampadaires(const Quadrangle &_q)
{
	nbLampRangee = Norm(_q[1] - _q[0])/d; if(nbLampRangee<1) nbLampRangee= 1;
	creerRangeeLampadaire(Vector().getDiffxy(_q[0],_q[3],1), Vector().getDiffxy(_q[1],_q[2],1),_q[0],_q[1]);
	nbLampRangee = Norm(_q[2] - _q[1])/d; if(nbLampRangee<1) nbLampRangee= 1;
	creerRangeeLampadaire(Vector().getDiffxy(_q[1],_q[0],1), Vector().getDiffxy(_q[2],_q[3],1),_q[1],_q[2]);
	nbLampRangee = Norm(_q[3] - _q[2])/d; if(nbLampRangee<1) nbLampRangee= 1;
	creerRangeeLampadaire(Vector().getDiffxy(_q[2],_q[1],1), Vector().getDiffxy(_q[3],_q[0],1),_q[2],_q[3]);
	nbLampRangee = Norm(_q[0] - _q[3])/d; if(nbLampRangee<1) nbLampRangee= 1;
	creerRangeeLampadaire(Vector().getDiffxy(_q[3],_q[2],1), Vector().getDiffxy(_q[0],_q[1],1),_q[3],_q[0]);
}

void Mobilier::creerRangeeLampadaire(const Vector &_v1, const Vector &_v2, const Vector &_q1, const Vector &_q2)
{
	double d = Norm(_v2-_v1);

	// on définit les emplacements des i lampadaires

		

	for (unsigned int i = 0; i < nbLampRangee; i++)
	{
		Vector l1 = l1.getDiffxy(_v1, _v2, d/(2*nbLampRangee) +i * d / nbLampRangee);
		Vector l2 = l2.getDiffxy(_v1, _v2, d/(2*nbLampRangee) +l+i * d / nbLampRangee);

		Vector x1 = x1.getDiffxy(_q1, _q2, d/(2*nbLampRangee) + i * d / nbLampRangee);
		Vector l3 = l2.getDiffxy(l1,x1, l);

		Vector x2 = x2.getDiffxy(_q1, _q2, d/(2*nbLampRangee) + l+i * d / nbLampRangee);
		Vector l4 = l4.getDiffxy(l2,x2, l);

		Vector::setCol(COL_LAMP1,COL_LAMP2,COL_LAMP3);
		PrismQuad(l3,l4,l2,l1,h).Render();
		Vector::setCol(150,150,150);

		Vector d1(0,0,h),d2(0,0,h),d3(0,0,h+0.5),d4(0,0,h+0.5); // dessus du lampadaire
		d1 += l1; d2 += l2;
		Vector x3 = x3.getDiffxy(l1,l3,1.5);
		Vector x4 = x4.getDiffxy(l2,l4,1.5);
		
		d3 += x3; d4 += x4;
		
		PrismQuad(d3,d4,d2,d1,0.2).Render();
		
	}

		
}

