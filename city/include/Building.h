#ifndef __Building__
#define __Building__

#include "Batiment.h"
#include "city.h"
#include "geometry.h"

class Batiment;

class Building : public Batiment
{
	public:

		Building(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax);
		Building(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax);
		Building(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax);
		~Building(void);

		static void choixBatiment(const Triangle& t, const unsigned int& typeCentre, const double& hauteurMax);
		static void choixBatiment(const Quadrangle& q, const unsigned int& typeCentre, const double& hauteurMax);
		static void choixBatiment(const Pentangle& p, const unsigned int& typeCentre, const double& hauteurMax);

		virtual void batir(const Triangle& t) =0;
		virtual void batir(const Quadrangle& q) =0;
		virtual void batir(const Pentangle& p) =0;

	protected :

		double retrecissement; /**  pourcentage de rétrecissement = 0% Ou 20-30% */
		int centreRetrecissement; /** on rétrécie la batiment selon un côté/point fixe : 0 = Centré, 1 = Nord, 2 = Sud, 3 = Est, 4 = Ouest  */

		bool palierActif; /** si vrai alors les paliers sont pris en compte, faux sinon */
		int palier; /** rétrécissement tous les N étages, avec N >= 4 */
		int loiPalier;  /** 0 = le nombe de paliers reste constant, 1 = augmente. Cette loi n'est pas modifiées pendant la construction */ 

		bool colonnesCoins; /** si vrai alors on met une colonne carré dans chaque coin, faux sinon */

		bool separation; /** si vrai, il y a séparation, false sinon (pas plus d'une fois par batiment) - TODO */
		unsigned int numEtageSeparation; /** l'étage à  partir duquel un batiment se scinde en 2 ou 3 parties (pas plus)*/

		/** @brief Initilise tous les attributs du building (à faire une seule fois) */
		void setBuildingInfos();

		/** @brief met à jour la valeur loiPalier */
		void majLoiPalier();

		/**
		*	@brief crée une colonne carré dans chaque coin du Quadrangle 
		*	@param etageActu il est à 1000 par défaut, de cette façon, si
		*	aucune valeur n'est donnée && palier = true, alors aucune colonne n'est crée (si nbEtageMax < 100000).
		*/
		void creerColonnesCoins(const unsigned int etageActu = 100000);
		void creerRdc();

		virtual void batirEtages(const Triangle& t) =0;
		virtual void batirEtages(const Quadrangle& q) =0;
		virtual void batirEtages(const Pentangle& p) =0;

};


#endif
