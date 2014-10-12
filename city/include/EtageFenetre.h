#ifndef __EtageFenetre__
#define __EtageFenetre__

#include <iostream>

#include "Batiment.h"
#include "city.h"
#include "geometry.h"
#include "shape.h"


/**
@class Permet principalement de créer un étage avec des fenêtres
*/
class EtageFenetre
{
	public:

		EtageFenetre();
		EtageFenetre(const double _tailleFenetre,
					 const double _tailleCoin,
					 const double _tailleInterFenetre,
					 const double _hauteurBordSup,
					 const double _hauteurBordInf);

		~EtageFenetre(void){}

		void creerEtagesVitres(std::vector<Vector>& listePoints,
							   const double& hauteurEtage,
							   const unsigned int& nbEtages,
							   const unsigned int& etageActu,
							   const unsigned int& nbEtagesRdc,
							   const unsigned int& nbEtagesMax);

		void setBoolCreerFenetre(double airMin);
		bool isCreerFenetre();

		void setTailleFenetre(const double _tailleFenetre);
		void setTailleCoin(const double _tailleCoin);
		void setTailleInterFenetre(const double _tailleInterFenetre);
		void setHauteurBordSup(const double _hauteurBordSup);
		void setHauteurBordInf(const double _hauteurBordInf);


	private:

		bool creerFenetre; /** true si on peut créer des fenêtres, false sinon */
		double tailleFenetre; /** largeur */
		double tailleCoin; /** taille minimal d'un rectangle dans chaque coin de l'étage */
		double tailleInterFenetre; /** mur entre deux fenêtres */
		double hauteurBordSup; /** mur au dessus de la fenêtres */
		double hauteurBordInf; /** mur en dessous de la fenêtres */
};

#else if
class EtageFenetre;
#endif
