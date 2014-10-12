#include "EtageFenetre.h"



EtageFenetre::EtageFenetre()
{
	creerFenetre = true;
}

EtageFenetre::EtageFenetre( const double _tailleFenetre,
							const double _tailleCoin,
							const double _tailleInterFenetre,
							const double _hauteurBordSup,
							const double _hauteurBordInf) :
							tailleFenetre(_tailleFenetre),
							tailleCoin(_tailleCoin),
							tailleInterFenetre(_tailleInterFenetre),
							hauteurBordSup(_hauteurBordSup),
							hauteurBordInf(_hauteurBordInf)
{
	creerFenetre = true;
}


void EtageFenetre::setBoolCreerFenetre(double airMin)
{
	double airMinPourCreation = ((tailleFenetre + 2*tailleCoin)*(tailleFenetre + 2*tailleCoin)) + 0.1; //+ 0.1 par sécurité
	creerFenetre = airMin > airMinPourCreation;
}

bool EtageFenetre::isCreerFenetre(){return creerFenetre;}
void EtageFenetre::setTailleFenetre(const double _tailleFenetre){tailleFenetre = _tailleFenetre;}
void EtageFenetre::setTailleCoin(const double _tailleCoin){tailleCoin = _tailleCoin;}
void EtageFenetre::setTailleInterFenetre(const double _tailleInterFenetre){tailleInterFenetre = _tailleInterFenetre;}
void EtageFenetre::setHauteurBordSup(const double _hauteurBordSup){hauteurBordSup = _hauteurBordSup;}
void EtageFenetre::setHauteurBordInf(const double _hauteurBordInf){hauteurBordInf = _hauteurBordInf;}


void EtageFenetre::creerEtagesVitres(std::vector<Vector>& listePoints,
									 const double& hauteurEtage,
									 const unsigned int& nbEtages,
									 const unsigned int& etageActu,
									 const unsigned int& nbEtagesRdc,
									 const unsigned int& nbEtagesMax)
{

	//--------------------- Création des rectangles dans chaque coin de l'étage, des fenêtres et des inter-fenêtres ---------------------->

	const unsigned int nbPoints = listePoints.size();
	double tailleDeBaseCoin = tailleCoin;

	//on fait le calcul une seul fois pour les nbEtage, car les côtés opposées sont egaux

	//----------------------------Taille des rectangles dans les coins--------------------------->

	std::vector<double> tailleRect; //contient la largeur et la longeur du rectangle présents dans les coins
	std::vector<unsigned int> nbInterEtFene; //contient le nombre de "un inter-mur + une fenêtre" pour chaque côtés

	//comme c'est un rectangle, on parcours seulement 2 côtés
	for(unsigned int cherche = 0; cherche < 2; cherche++)
	{
		//taille du segement sur lequel seront "placées" les fenêtres
		double tailleTotSansCoin = Norm(listePoints[(cherche+1)%nbPoints] - listePoints[cherche]) - 2*tailleCoin;

		//nbInterEtFene est le nombre de fois que l'on peut poser "un inter-mur et une fenêtre"
		double nbInterEtFeneTmp = tailleTotSansCoin/(tailleFenetre + tailleInterFenetre);

		//"-1" car on aura déjà une fenêtre et un coin : Coin Fenêtre Inter-Mur
		double valeur = floor(nbInterEtFeneTmp) - 1;
		if(valeur <= 0) valeur = 0;
		nbInterEtFene.push_back(valeur);

		/*
			Au minimum on aura : nbInterEtFene - floor(nbInterEtFene) = 0.
			On ajoute tailleInterFenetre aux déchets car le premier élément posé sera une fenêtre.
			Exemple (dans l'ordre) : Coin Fenêtre Mur Fenêtre Mur Fenêtre Coin
			Exemple : on a 2,8 "mur + fenetre", on fait 2.8 - 2 + 1 = 1,8 -> soit 0.9 pour chaque coin.
		*/
		double dechets = nbInterEtFeneTmp - floor(nbInterEtFeneTmp) + tailleInterFenetre;
			
		//on réutilise ces dechets en les ajoutants à la taille du rectangle qui forme le coin (divise par 2 car il y a 2 coins)
		tailleRect.push_back( tailleDeBaseCoin + (dechets/2) ); //la valeur minimal sera : tailleDeBaseCoin + (tailleInterFenetre/2)
	}


	//Si aucun des côté n'a de fenêtre, on crée les nbEtage et on sort de la fonction
	for(unsigned int i = 0; i < nbInterEtFene.size(); i++) creerFenetre |= nbInterEtFene[i] > 0 ?true:false;
	if(!creerFenetre)
	{
		PrismQuad(listePoints[0], listePoints[1], listePoints[2], listePoints[3], hauteurEtage*nbEtages);
		return;
	}

	//---------------------- Création des bordures inférieurs et supérieurs aux fenêtres (juste deux quadrangle ABCD) ---------->	


	//On va créer les bordures inf et sup pour chaque étage 
	for(unsigned int etage = 0; etage < nbEtages; etage++)
	{
		Quadrangle newQ;

		unsigned int nouvEtage = etageActu + etage;

		//Etage juste après le Rez de chaussez ou au début du palier
		if (nouvEtage == nbEtagesRdc || etage == 0)
		{
			newQ = Quadrangle(listePoints[0], listePoints[1], listePoints[2], listePoints[3]);
			PrismQuad(newQ, hauteurBordInf).Render(); //on crée la bordure inférieure
		}


		if(nouvEtage != nbEtagesMax-1 && etage != nbEtages-1)
		{
			newQ = Quadrangle(listePoints[0], listePoints[1], listePoints[2], listePoints[3]);
			//modifiacation en Z pour tracer la bordure supérieur + la prochaine bordure inférieure
			for(unsigned int vect = 0; vect < 4; vect++) newQ.setCompVector(vect, 3, newQ[vect][3] + hauteurEtage - hauteurBordSup);
			
			//bordure supérieur entre b' et a' jusqu'à l'autre bord + hauteurBordInf pour éviter de créer deux quad
			PrismQuad(newQ, hauteurBordSup + hauteurBordInf).Render();
		}
		else if (nouvEtage == nbEtagesMax-1 || etage == nbEtages-1) //dernier étage
		{
			newQ = Quadrangle(listePoints[0], listePoints[1], listePoints[2], listePoints[3]);
			for(unsigned int vect = 0; vect < 4; vect++) newQ.setCompVector(vect, 3, newQ[vect][3] + hauteurEtage - hauteurBordSup);
			PrismQuad(newQ, hauteurBordSup).Render();
		}

		//mise à jour des hauteurs (on passe à l'étage supérieur)
		for(unsigned int vect = 0; vect < 4; vect++) listePoints[vect] += Vector(0,0, hauteurEtage);
	}

	//on redescend
	for(unsigned int vect = 0; vect < 4; vect++) listePoints[vect] -= Vector(0,0, hauteurEtage*nbEtages);

	//------------------------------- Création d'un des 4 rectangle du coin ----------->
	
	std::vector<Vector> pointCoin;
	std::vector<Vector> faceDeplacement;

	//on récupère les points
	Vector aCoin = listePoints[0]; pointCoin.push_back(listePoints[0]);
	Vector bCoin = listePoints[1]; pointCoin.push_back(listePoints[1]);
	Vector cCoin = listePoints[2]; pointCoin.push_back(listePoints[2]);
	Vector dCoin = listePoints[3]; pointCoin.push_back(listePoints[3]);

	//on calcul les vecteurs
	Vector abCoin = bCoin - aCoin;
	Vector bcCoin = cCoin - bCoin;
	Vector dcCoin = cCoin - dCoin;
	Vector adCoin = dCoin - aCoin;

	//on divise le segement en N morceaux. On utilise (cote+1)%2 pour avoir les bons coef.
	double nbFoisAb = Norm(abCoin)/tailleRect[0];
	double nbFoisBc = Norm(bcCoin)/tailleRect[1];
	double nbFoisDc = Norm(dcCoin)/tailleRect[0];
	double nbFoisAd = Norm(adCoin)/tailleRect[1];

	//on crée les vecteurs de déplacement
	Vector abDeplace = abCoin/nbFoisAb; faceDeplacement.push_back(abDeplace);
	Vector bcDeplace = bcCoin/nbFoisBc; faceDeplacement.push_back(bcDeplace);
	Vector dcDeplace = dcCoin/nbFoisDc; faceDeplacement.push_back(dcDeplace);
	Vector adDeplace = adCoin/nbFoisAd; faceDeplacement.push_back(adDeplace);

	//pour chaque côté du bâtiments
	for(unsigned int cote = 0; cote < nbPoints; cote++)
	{

		/* 
			On fait pivoter l'ordre des lettres dans le sens anti-horaire.
			On cherche à créer le bord du côté du sommet A en premier.
			La vecteurs de déplacements sont dans la boucle car les rectangles et carrés ne sont pas parfait.
				D---C
				|	|
				A---B

			Exemple pour les deux bord en A et B :

				|			   |
				d'--c'	   d''-c''
				|   |      |   |
				A---b'-----a'--B


			Avec Ab' = d'c' = d''c'' = a'B = tailleRect[0]
			Et Ad' = bc' = a'd'' = Bc'' = tailleRect[1]
			(pareil pour les deux coins qui partent de D et C)

		*/

		Vector deplacementAbOubA = cote < 2 ? faceDeplacement[cote]:-faceDeplacement[cote];
		Vector deplacementBcOucB = (cote+1)%nbPoints < 2 ? faceDeplacement[(cote+1)%nbPoints]:-faceDeplacement[(cote+1)%nbPoints];

		//Coordonées du rectangle
		Vector bPrim = pointCoin[cote] + deplacementAbOubA;
		Vector cPrim = bPrim + deplacementBcOucB;
		Vector dPrim = pointCoin[cote] + deplacementBcOucB;

		//juste une fois, et sa fait pour les nbEtages
		 PrismQuad(pointCoin[cote], bPrim, cPrim, dPrim, hauteurEtage*nbEtages).Render();

		//----------------------- Création des Inter-Fenetres ------------------------------->

		//on le fait uniquement pour les 2 premier côté AB BC
 		if(cote < 2 && nbInterEtFene[cote%2] > 0)
		{
			/*
				On se déplace sur AB et DC, on part de A et D.
				Un mur inter-fenêtre fait toute la longeur/largeur du batiment,
				de cette façon on divise par 4 le nombre de PrismQuad à créer.

				Mur inter-fenêtre :
				D---... H - G
						|	|
						|	|
				A---... E - F
			*/
			
			//les vecteurs de déplacement sont dans le même sens
			Vector e = pointCoin[cote] + faceDeplacement[cote%nbPoints];
			Vector f = e; //on ajoutera HG plus bas
			Vector h = pointCoin[(cote+3)%nbPoints] + faceDeplacement[(cote+2)%nbPoints];
			Vector g = h; //on ajoutera EF plus bas

			//-----Nouvelles valeurs de déplacement (pour chaque côté car le rectangle n'est pas parfait) ------->

			Vector aCoinBCoin = pointCoin[(cote+1)%nbPoints] - pointCoin[cote];
			Vector dCoinCCoin = pointCoin[(cote+2)%nbPoints] - pointCoin[(cote+3)%nbPoints];

			//on se déplace de fenêtre en fenêtre
			double nbFoisAb2 = Norm(aCoinBCoin)/tailleFenetre;
			double nbFoisDc2 = Norm(dCoinCCoin)/tailleFenetre;
			Vector abDeplaceFen = (aCoinBCoin)/nbFoisAb2;
			Vector dcDeplaceFen = (dCoinCCoin)/nbFoisDc2;

			//on se déplace de mur inter-fenêtre en mur inter-fenêtre
			nbFoisAb2 = Norm(aCoinBCoin)/tailleInterFenetre;
			nbFoisDc2 = Norm(dCoinCCoin)/tailleInterFenetre;
			Vector abDeplaceItM = (aCoinBCoin)/nbFoisAb2;
			Vector dcDeplaceItM = (dCoinCCoin)/nbFoisDc2;

			//Ajout de EF et HG, on le fait pour définir la largeur de l'inter-mur.
			e += abDeplaceFen;
			f += abDeplaceFen + abDeplaceItM; //abDeplaceItM = EF
			g += dcDeplaceFen + dcDeplaceItM; //dcDeplaceItM = HG
			h += dcDeplaceFen;

			for(unsigned int fen = 0; fen < nbInterEtFene[cote%2]; fen++)
			{
				//Création de l'inter-etage
				PrismQuad(e,f,g,h, hauteurEtage*nbEtages).Render();
					
				//on se déplace d'une fenêtre et d'un inter-mur
				e += abDeplaceFen + abDeplaceItM;
				f += abDeplaceFen + abDeplaceItM;
				g += dcDeplaceFen + dcDeplaceItM;
				h += dcDeplaceFen + dcDeplaceItM;
			}

		}
		//si à l'étage 0 il n'y a pas de fenêtre sur cette façade, il n'y en aura jamais pour tous les étages
		else if (cote < 2)
		{
			/* Il n'y a pas de fenêtre sur cette façade, on doit boucher le trou.
			Il y a forcément des fenêtres sur l'autre façade, sinon on serai
			déjà sortie de la fonction (à cause du : if(!pasDeFenetre) ..., plus haut)

				|			   |
				d'--c'	   d''-c''
				|   |      |   |  //on veut tracer le quad b'a'd''c''
				A---b'-----a'--B

			*/


			//on a déjà bPrim et cPrim, on cherche a' et d''
			Vector bPrimAPrim = (pointCoin[(cote+1)%nbPoints] - pointCoin[cote]) - 2*deplacementAbOubA; // = AB - (Ab' + a'B), avec Ab' = a'B
			Vector aPrim = bPrim + bPrimAPrim;
			Vector dPrimPrim = cPrim + bPrimAPrim;

			PrismQuad(bPrim, aPrim, dPrimPrim, cPrim, hauteurEtage*nbEtages).Render();

		} //fin du si (cote < 2 && nbInterEtFene[cote%2] > 0)

	}//find de la boucle de parcours des faces du quad


	//------------------ Création des fenêtres ------------------------------->

	//Si un côté n'a pas de fenêtre sa ne pose pas de problème vu qu'un quad bouche la vue

	Vector centre = (listePoints[0] + listePoints[1] + listePoints[2] + listePoints[3])/4;
	double largeurRebord = ((double) UNITE) * 0.2;

	double coef = 0.1;

	Vector::setCol(COL_FEN1, COL_FEN2, COL_FEN3);
	PrismQuad(listePoints[0] + faceDeplacement[0]*coef + faceDeplacement[1]*coef,
			  listePoints[1] + faceDeplacement[1]*coef - faceDeplacement[2]*coef,
			  listePoints[2] - faceDeplacement[2]*coef - faceDeplacement[3]*coef,
			  listePoints[3] - faceDeplacement[3]*coef + faceDeplacement[0]*coef,
			  hauteurEtage*nbEtages - hauteurBordSup).Render();
	Vector::setColDefaut();

	//------------------------------------------------------------------------>

	//mise à jour des hauteurs (on passe à l'étage supérieur)
	for(unsigned int vect = 0; vect < 4; vect++) listePoints[vect] += Vector(0,0, hauteurEtage*nbEtages);
}

