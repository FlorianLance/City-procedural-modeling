#include <iostream>
#include "city.h"

//########################################################################################################### TRIANGLE

/*!
\brief Create a triangular block.
\param a,b,c End vertices of the block.
*/
BlockTriangle::BlockTriangle(const Vector& _a,const Vector& _b,const Vector& _c, const std::vector<Centre>&_centres): Triangle(_a,_b,_c)
{
	Quartier::choixQuartier(Triangle(_a,_b,_c),_centres);
}

/*!
\brief Create a triangular parcel of land.
\param a,b,c End vertices of the parcel.
*/
LandTriangle::LandTriangle(const Vector& _a,const Vector& _b,const Vector& _c,const std::vector<Centre> &_centres):Triangle(_a,_b,_c)
{
	centres = _centres;
}

/*
\brief Subdivide a triangular land parcel. 
*/
void LandTriangle::Subdivide()
{
  // Area
  double area=Area();

  // Check if minimal area : in this case stop 
  // land use subdivision and start base building generation
  if (area<20)  // Taille maximale d'un block de type Triangle
  {
	// ZONE DE TRAVAIL: FLORIAN

    Triangle t = Triangle(p[0],p[1],p[2]).Shrink(0.25,0.25,0.25);
	BlockTriangle(t.getVectors(0), t.getVectors(1), t.getVectors(2), centres);
  }

// ZONE DE TRAVAIL: ARMAND

  // Subdivide land use
  else
  {
    // Compute index of smallest edge
    double ab=Norm(p[1]-p[0]);
    double bc=Norm(p[2]-p[1]);
    double ca=Norm(p[0]-p[2]);

    if ((ab<ca)&&(ab<bc))
    {
      LandTriangle(p[2],(p[2]+p[0])/2.0,(p[1]+p[2])/2.0,centres).Subdivide();;
      LandQuad((p[2]+p[0])/2.0,p[0],p[1],(p[1]+p[2])/2.0,centres).Subdivide();;
    }
    else if ((bc<ab)&&(bc<ca))
    {
      LandTriangle(p[0],(p[0]+p[1])/2.0,(p[0]+p[2])/2.0,centres).Subdivide();;
      LandQuad((p[0]+p[1])/2.0,p[1],p[2],(p[0]+p[2])/2.0,centres).Subdivide();;
    }
    else
    {
      LandTriangle(p[1],(p[1]+p[2])/2.0,(p[0]+p[1])/2.0,centres).Subdivide();;
      LandQuad((p[1]+p[2])/2.0,p[2],p[0],(p[0]+p[1])/2.0,centres).Subdivide();;
    }
  }
}

//########################################################################################################### QUADRANGLE

/*!
\brief Create a quadrangular block.
\param a,b,c,d End vertices of the parcel.
*/
BlockQuad::BlockQuad(const Vector& _a,const Vector& _b,const Vector& _c,const Vector& _d,const std::vector<Centre>&_centres): Quadrangle(_a,_b,_c,_d)
{
	// hauteur de 10 mètres pour le lampadaire (5 unités)

	Mobilier(7*UNITE,50*UNITE,0.3*UNITE).creerLampadaires(Quadrangle(_a,_b,_c,_d)); // d a 10 pour le moment mais il faudra le mettre à 25 (cad tous les 50m) une fois les vrais quartiers définis

	// création du trottoir
	Vector::setCol(COL_TROTT1,COL_TROTT2,COL_TROTT3);
	PrismQuad(Quadrangle(_a,_b,_c,_d),0.30*UNITE).Render(); // hauteur de 20 cm
	Vector::setColDefaut();
	double tShrink = 4* UNITE; // 4 m
    Quadrangle q=Quadrangle(_a,_b,_c,_d).Shrink(tShrink,tShrink,tShrink,tShrink);
	Quartier::choixQuartier(q,_centres);
}

/*!
\brief Create a quadrangular parcel of land.
\2param a,b,c,d End vertices of the parcel.
*/
LandQuad::LandQuad(const Vector& _a,const Vector& _b,const Vector& _c,const Vector& _d, const std::vector<Centre> &_centres):Quadrangle(_a,_b,_c,_d)
{
	centres = _centres;
}

void LandQuad::creationQuartier()
{
	Vector::setCol(COL_ROUTE1,COL_ROUTE2,COL_ROUTE3);
	PrismQuad(Quadrangle(p[0],p[1],p[2],p[3]),0.10*UNITE).Render();
	Vector::setColDefaut();

	double tShrink = 7.5*UNITE; // largeur de 15m (au total, donc 7.5m de chaque côté depuis le milieu de la route)
	Quadrangle q=Quadrangle(p[0],p[1],p[2],p[3]).Shrink(tShrink,tShrink,tShrink,tShrink);
	
	BlockQuad(q.getVectors(0), q.getVectors(1), q.getVectors(2), q.getVectors(3),centres);
}

/*
\brief Subdivide a quadrangular land parcel. 
*/
void LandQuad::Subdivide()
{
  // Area
  double area=Area();

    // Compute index of smallest edge
    double ab=Norm(p[1]-p[0]);
    double bc=Norm(p[2]-p[1]);
    double cd=Norm(p[3]-p[2]);
    double da=Norm(p[0]-p[3]);

	double random = ((double)(rand()%3 + 3) / 10); // rapport de division du côté

	//std::cout << "ab = " << ab << std::endl;
	//std::cout << "bc = " << bc << std::endl << std::endl;

	int partage = rand()%2;
	// première subdivision large

	if( ab > 150*UNITE && da > 150*UNITE)
	{
		if(partage)
		{
			Vector v1(0,0,0); v1.setDiffxy(p[0],p[1],random * ab);
			Vector v2(0,0,0); v2.setDiffxy(p[3],p[2],random * cd);
			LandQuad(p[0],v1,v2,p[3],centres).Subdivide();
			LandQuad(v1,p[1],p[2],v2,centres).Subdivide();

		}
		else 
		{
			Vector v1(0,0,0); v1.setDiffxy(p[0],p[3],random * da);
			Vector v2(0,0,0); v2.setDiffxy(p[1],p[2],random * bc);
			LandQuad(v1,v2,p[2],p[3],centres).Subdivide();
			LandQuad(p[0],p[1],v2,v1,centres).Subdivide();
		}
	}
	else if(ab > 150*UNITE )//&& partage
	{

		Vector v1(0,0,0); v1.setDiffxy(p[0],p[1],random * ab);
		Vector v2(0,0,0); v2.setDiffxy(p[3],p[2],random * cd);
		LandQuad(p[0],v1,v2,p[3],centres).Subdivide();
		LandQuad(v1,p[1],p[2],v2,centres).Subdivide();

	}
	else if( da >  150*UNITE )//&& !partage
	{

		Vector v1(0,0,0); v1.setDiffxy(p[0],p[3],random * da);
		Vector v2(0,0,0); v2.setDiffxy(p[1],p[2],random * bc);
		LandQuad(v1,v2,p[2],p[3],centres).Subdivide();
		LandQuad(p[0],p[1],v2,v1,centres).Subdivide();

	}
	
	else if( (ab > 90*UNITE && ab < 160*UNITE  && bc > 2*ab && bc < 320*UNITE && bc > 180*UNITE )|| (bc > 90*UNITE && bc < 160*UNITE  && ab > 2*bc && ab < 320*UNITE && ab > 180*UNITE) || // très grands quartiers rectangulaires
			 (ab > 150*UNITE && ab < 200*UNITE  && bc > 1.5*ab && bc < 300*UNITE && bc >225*UNITE )|| (bc > 150*UNITE && bc < 200*UNITE  && ab > 1.5*bc && ab < 300*UNITE && ab > 225*UNITE) || // très grands quartiers semi rectangulaires
			 (ab > 80*UNITE && ab < 100*UNITE  && bc < 100*UNITE  && bc > 80*UNITE)) // grands quartiers carrés
	{
		
		creationQuartier();
		
	}
	else if( ab > 90*UNITE && da >  90*UNITE)
	{
		if(partage){
			Vector v1(0,0,0); v1.setDiffxy(p[0],p[1],random * ab);
			Vector v2(0,0,0); v2.setDiffxy(p[3],p[2],random * cd);
			LandQuad(p[0],v1,v2,p[3],centres).Subdivide();
			LandQuad(v1,p[1],p[2],v2,centres).Subdivide();

		}
		else{
			Vector v1(0,0,0); v1.setDiffxy(p[0],p[3],random * da);
			Vector v2(0,0,0); v2.setDiffxy(p[1],p[2],random * bc);
			LandQuad(v1,v2,p[2],p[3],centres).Subdivide();
			LandQuad(p[0],p[1],v2,v1,centres).Subdivide();

		}

	}
	// deuxième subdivision moyenne
	else if(ab > 90*UNITE ) // && partage
	{
		Vector v1(0,0,0); v1.setDiffxy(p[0],p[1],random * ab);
		Vector v2(0,0,0); v2.setDiffxy(p[3],p[2],random * cd);
		LandQuad(p[0],v1,v2,p[3],centres).Subdivide();
		LandQuad(v1,p[1],p[2],v2,centres).Subdivide();

	}
	else if( da >  90*UNITE  ) // && !partage
	{
		Vector v1(0,0,0); v1.setDiffxy(p[0],p[3],random * da);
		Vector v2(0,0,0); v2.setDiffxy(p[1],p[2],random * bc);
		LandQuad(v1,v2,p[2],p[3],centres).Subdivide();
		LandQuad(p[0],p[1],v2,v1,centres).Subdivide();

	}

	else if( (ab > 80*UNITE && ab < 100*UNITE  && bc > 2*ab && bc < 200*UNITE && bc > 180*UNITE  )|| (bc > 80*UNITE && bc < 100*UNITE  && ab > 2*bc && ab < 200*UNITE && ab >160*UNITE )||  //  quartiers rectangulaires moyens
			(ab > 50*UNITE && ab < 70*UNITE  && bc < 70*UNITE  && bc > 50*UNITE) || //  quartiers carrés moyens
			(ab > 50*UNITE && ab < 70*UNITE  && bc > 3*ab && bc < 210*UNITE && bc >150*UNITE )|| (bc> 50*UNITE && bc < 70*UNITE  && ab > 3*bc && ab < 210*UNITE && ab >150*UNITE ) ||  //  quartiers rectangulaires étalés moyens
			(ab > 50*UNITE && ab < 80*UNITE  && bc > 1.5*ab && bc < 120*UNITE && bc > 75*UNITE )|| (bc > 50*UNITE && bc < 80*UNITE  && ab > 1.5*bc && ab < 120*UNITE && ab > 75*UNITE )) //  quartiers semi rectangulaires moyens
	{
		creationQuartier();
	}

	// dernière subdivision 
	else if(ab > 120*UNITE && ab > 2 *bc)
	{
		Vector v1(0,0,0); v1.setDiffxy(p[0],p[1],random * ab);
		Vector v2(0,0,0); v2.setDiffxy(p[3],p[2],random * cd);
		LandQuad(p[0],v1,v2,p[3],centres).Subdivide();
		LandQuad(v1,p[1],p[2],v2,centres).Subdivide();



	}
	else if( da >  120*UNITE && da > 2 *ab)
	{
		Vector v1(0,0,0); v1.setDiffxy(p[0],p[3],random * da);
		Vector v2(0,0,0); v2.setDiffxy(p[1],p[2],random * bc);
		LandQuad(v1,v2,p[2],p[3],centres).Subdivide();
		LandQuad(p[0],p[1],v2,v1,centres).Subdivide();


	}
	else if(da > 30*UNITE && ab > 30*UNITE)
	{
		creationQuartier();
	}
	else
	{
		Vector::setCol(COL_ROUTE1,COL_ROUTE2,COL_ROUTE3);
		PrismQuad(Quadrangle(p[0],p[1],p[2],p[3]),0.10*UNITE).Render();

		double tShrink = 7.5*UNITE; // largeur de 15m (au total, donc 7.5m de chaque côté depuis le milieu de la route)
		Quadrangle q=Quadrangle(p[0],p[1],p[2],p[3]).Shrink(tShrink,tShrink,tShrink,tShrink);

		Mobilier(10*UNITE,50*UNITE,0.3*UNITE).creerLampadaires(Quadrangle(q[0],q[1],q[2],q[3])); // d a 10 pour le moment mais il faudra le mettre à 25 (cad tous les 50m) une fois les vrais quartiers définis

		 //création du trottoir
		Vector::setCol(COL_TROTT1,COL_TROTT2,COL_TROTT3);
		PrismQuad(Quadrangle(q[0],q[1],q[2],q[3]),0.30*UNITE).Render(); // hauteur de 20 cm
		Vector::setColDefaut();
		 tShrink = 4* UNITE; // 4 m
		Quadrangle q2=Quadrangle(q[0],q[1],q[2],q[3]).Shrink(tShrink,tShrink,tShrink,tShrink);

		Vector::setCol(COL_HERBE1,COL_HERBE2,COL_HERBE3);
		
		PrismQuad(Quadrangle(q2[0],q2[1],q2[2],q2[3]),0.40*UNITE).Render();
		//PrismQuad(Quadrangle(p[0],p[1],p[2],p[3]),0.40*UNITE).Render();
		
		Vector::setColDefaut();
	}



  
}


//########################################################################################################### PENTANGLE

/*!
\brief Create a pentagular parcel of land.
\param a,b,c,d,e End vertices of the parcel.
*/
LandPent::LandPent(const Vector& _a,const Vector& _b,const Vector& _c,const Vector& _d,const Vector& _e, const std::vector<Centre> &_centres):Pentangle(_a,_b,_c,_d,_e)
{
	centres = _centres;
}


/*
\brief Subdivide a pentagular land parcel. 
*/
void LandPent::Subdivide()
{
  // Area
	double area=Area();
	Vector pointCentral(0,0,0);
  // Check if minimal area : in this case4 stop 
  // land use subdivision and start base building generation

	double ab = Norm(p[1] - p[0]);
	double bc = Norm(p[2] - p[1]);
	double cd = Norm(p[3] - p[2]);
	double de = Norm(p[4] - p[3]);
	double ea = Norm(p[0] - p[4]);
	double longueur = 0;


		Vector v0(0,0,0),v1(0,0,0),v2(0,0,0),v3(0,0,0),v4(0,0,0);

		longueur = (rand()%7 + 3)*ab/10;
		v0.setDiffxy(p[0],p[1],longueur);

		longueur = (rand()%7 + 3)*bc/10;
		v1.setDiffxy(p[1],p[2],longueur);

		longueur = (rand()%7 + 3)*cd/10;
		v2.setDiffxy(p[2],p[3],longueur);

		longueur = (rand()%7 + 3)*de/10;
		v3.setDiffxy(p[3],p[4],longueur);

		longueur = (rand()%7 + 3)*ea/10;
		v4.setDiffxy(p[4],p[0],longueur);

		LandQuad(v0,p[1],v1,pointCentral,centres).Subdivide();
		LandQuad(v1,p[2],v2,pointCentral,centres).Subdivide();
		LandQuad(v2,p[3],v3,pointCentral,centres).Subdivide();
		LandQuad(v3,p[4],v4,pointCentral,centres).Subdivide();
		LandQuad(v4,p[0],v0,pointCentral,centres).Subdivide();
  
}

//########################################################################################################### CENTRE

Centre::Centre(const Centre& _centre) : type(_centre.type), positionCentre(_centre.positionCentre)
{}

Centre::Centre(const Vector &_a, const TypeCentre _type) : type(_type), positionCentre(_a)
{}

double Centre::getDistance (const Quadrangle &_q) const
{
	Vector centreQuadrangle((_q[0]+_q[1])/4 + (_q[3]+_q[2])/4);
	double distance = Norm(positionCentre - centreQuadrangle);
	return distance;
}

double Centre::getDistance(const Vector &_a, const Vector &_b, const Vector &_c)const
{
	Vector centreTriangle(((_a + _b)/2 + _c)/3);
	double distance = Norm( positionCentre - centreTriangle);

	return distance;
}

double Centre::getDistance(const Vector &_a, const Vector &_b, const Vector &_c, const Vector &_d)const
{
	Vector centreQuadrangle((_a+_b)/4 + (_d+_c)/4);
	
	double distance = Norm(positionCentre - centreQuadrangle);
	//std::cout<< distance << std::endl;
	
	return distance;
}

double Centre::getDistance(const Vector &_a, const Vector &_b, const Vector &_c, const Vector &_d, const Vector &_e)const
{
	Vector centreQuadrangle((_a+_b+_d+_c+_e)/5);
	double distance = Norm(positionCentre - centreQuadrangle);

	return distance;
}

double Centre::getHauteur(const double &_distance) const
{
	//calculette grahique online : http://grapheur.cours-de-math.eu/
	double hauteur =  250*(exp(6/_distance) -1);

	if(hauteur > 40) {hauteur = rand()%15 + 40;}
	return hauteur;
}

TypeCentre Centre::getType() const{return type;}


//########################################################################################################### CITY

/*!
\brief Constructor of a city
*/
City::City() {}

/*!
\brief Generate a city from an initial land triangle.
*/
void City::Generate()
{
	double x = 30 * UNITE; // x = 10  ->  1km² // maximum 15 pour l'exportation sous maya (trop lourd après)
	
	std::vector<Centre> centres;

	TypeCentre type1 = VILLE, type2 = INDUSTRIEL, type3 = RESIDENCE;
	centres.push_back(Centre(Vector(0,0,0),type1));
	centres.push_back(Centre(Vector(-30*x,-30*x,0),type2)); // ajout d'un centre industriel
	centres.push_back(Centre(Vector(-30*x,-30*x,0),type3)); // ajout d'un centre résidentiel
	centres.push_back(Centre(Vector(-30*x, 30*x,0),type3)); // ajout d'un centre résidentiel
	//centres.push_back(Centre(Vector(20*x,0,0),type1)); // ajout d'un centre ville

	Vector v[4];
	v[0] = Vector(-50*x,-50*x,0);
	v[1] = Vector(50*x, -50*x,0);
	v[2] = Vector(50*x, 50*x,0);
	v[3] = Vector(-50*x,50*x,0);

	Vector::setCol(COL_FOND1,COL_FOND2,COL_FOND3);
	PrismQuad(v[0],v[1],v[2],v[3], 0.000001); // coloration du fond de la zone de la ville
	Vector::setColDefaut();
	
	LandQuad(v[0],v[1],v[2],v[3], centres).Subdivide();
	std::cout << "Nombre de quads: " << PrismQuad::nbQuad << std::endl;

	// fonction d'exportation en obj
	//exporte::exporteMaya();
}


