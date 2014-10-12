// Changelog 14.02.2001

#ifndef __City__ 
#define __City__

#include <iostream>
#include <vector>

#include "vector.h"
#include "geometry.h"
#include "shape.h"

#include "exporte.h"

#include "mobilierUrbain.h"

#include "quartier.h"


#define UNITE 1/3 //soit 1 mètre, on pourra la modifier plus tard

enum TypeCentre { VILLE = 0, RESIDENCE = 1, INDUSTRIEL = 2};

class Centre {

	public:

		Centre(const Centre& _centre);
		Centre(const Vector &,const TypeCentre);

		double getDistance (const Quadrangle &_q) const;
		double getDistance (const Vector &, const Vector &, const Vector &) const;
		double getDistance (const Vector &, const Vector &, const Vector &, const Vector &) const;
		double getDistance(const Vector &, const Vector &, const Vector &, const Vector &, const Vector &) const;
		double getHauteur(const double &) const;
		TypeCentre getType() const;

	private:

		Vector positionCentre;
		TypeCentre type;
};


inline int Intersect(const Vector& ,const Vector& ,const Vector& ,const Vector& ){}


class BlockTriangle:public Triangle {
	protected:
	public:
	  BlockTriangle(const Vector&,const Vector&,const Vector&, const std::vector<Centre> &);
	  void Subdivide();
	  std::vector<Centre> centres;
};

class LandTriangle:public Triangle {
	protected:
	public:
	  LandTriangle(const Vector&,const Vector&,const Vector&,const std::vector<Centre> &);
	  void Subdivide();
	  std::vector<Centre> centres;
};


class BlockQuad:public Quadrangle {
	protected:
	public:
	  BlockQuad(const Vector&,const Vector&,const Vector&,const Vector&, const std::vector<Centre>&);
	  void Subdivide();
	  std::vector<Centre> centres;
};


class LandQuad:public Quadrangle{
	protected:
	public:
		LandQuad(const Vector&,const Vector&,const Vector&,const Vector&, const std::vector<Centre>&);
	  void Subdivide();
	  void creationQuartier();
	  //void Subdivise();
	  void Delimite();
	  std::vector<Centre> centres;
};

class LandPent:public Pentangle{
	protected:
	public:
	  LandPent(const Vector&,const Vector&,const Vector&,const Vector&, const Vector&, const std::vector<Centre> &);
	  void Subdivide();
	  std::vector<Centre> centres;
};


class City {

	public:
		City();
		void Generate();
};


#else
class Centre; //laisser cette ligne -> pour la 3ème partie
#endif