#ifndef __Usine__
#define __Usine__

#include <iostream>
#include <vector>

#include "Batiment.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"

class Usine;

class Usine : public Batiment
{
	public:
		Usine(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax);
		Usine(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax);
		Usine(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax);
		~Usine(void);

		static void choixBatiment(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax);
		static void choixBatiment(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax);
		static void choixBatiment(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax);

		virtual void batir(const Triangle& t) =0;
		virtual void batir(const Quadrangle& q) =0;
		virtual void batir(const Pentangle& p) =0;

	protected :

		/** la où l'on stocke et on va expédier les produits */
		double hauteurGrandsEntr; /** hauteur des grands entrepôts (entre 5 et 10 mètres) */
		double longueurGrandsEntr;

		/** Plusieurs chaines = un produit */
		double hauteurBatChaine; /** hauteur des batîments de chaine (plus petits que les entrepôts de stockage) */
		double longMinBatChaine; /** longueur des batîments de chaine */

		void setUsineInfos();

		virtual void batirEtages(const Triangle& t) =0;
		virtual void batirEtages(const Quadrangle& q) =0;
		virtual void batirEtages(const Pentangle& p) =0;

};

#endif
