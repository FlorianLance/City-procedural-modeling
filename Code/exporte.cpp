#include <iostream>
#include <string>
#include <fstream>

#include "exporte.h"
#include "batiments/Industrie/UsineClassique.h"
 
using namespace std;

void exporte::exporteMaya()
{
		
	//cout << PrismQuad::face1[15]<< PrismQuad::face1[16]<< PrismQuad::face1[17];
	//for(unsigned int i=0; i < PrismQuad::v.size(); i++) std::cout << PrismQuad::v[i] << std::endl;
	/*
	for(unsigned int i=0; i < PrismQuad::faces.size() ; i++) {
			std::cout << PrismQuad::faces[i] << " ";
		if((i+1)%3 == 0)
			cout<<endl;
	}
	

	for(unsigned int i=12; i < 20 ; i++) {
		std::cout << PrismQuad::faces[i] << " ";
		if((i+1)%3 == 0)
			cout<<endl;
	}
	*/
	
	ofstream fichier("exportmaya.obj", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
 
        if(fichier)
        {
			fichier << "# Fichier d'exporte maya"<<endl;
			unsigned int j =0;
			unsigned int i =0;
			int k=0;
			int l=0;
			int m=1;
			int n=0;
			int u=0;
			int v=0;

			cout<<"Taille de face1 : "<<PrismQuad::face1.size()<<endl;
			cout<<"Taille de faces : "<<PrismQuad::faces.size()<<endl;
			cout<<"Taille de Toitpyramide : "<<Batiment::ToitPyramide.size()<<endl;
			cout<<"Taille de Toitpyramidecoupe : "<<Batiment::ToitPyramideCoupe.size()<<endl;
			cout<<"Taille de toitprisme : "<<Batiment::ToitPrisme.size()<<endl;
			cout<<"Taille de toitUsine : "<<UsineClassique::ToitUsine.size()<<endl;


			while(l==0)
			{
				while(n==0)
				{
					fichier << endl << "g Quad"<<k<<endl<<endl;
					fichier<<"v ";
					while(i < PrismQuad::face1.size() && (i+1)%12 != 0)
					{
						fichier << PrismQuad::face1[i] << " ";
						if((i+1)%3 == 0)
						{
							fichier<<endl;
							fichier<<"v ";
						}
						i++;
					}
					if (i < PrismQuad::face1.size())
					{
						if((i+1)%12 !=0 || i!=PrismQuad::face1.size())
						{
							fichier <<PrismQuad::face1[i];
							i++;
						}
					}
					fichier << endl<<endl;
	
					fichier<<"v ";
					
					while(j < PrismQuad::faces.size() && (j+1)%48 != 0)
					{
						fichier <<PrismQuad::faces[j] <<" ";
						if((j+1)%3 == 0 && !((j+1)%12 == 0))
						{
							fichier<<endl;
							fichier<<"v ";
						}	
						if((j+1)%12 == 0)
						{	
							fichier<<endl<<endl;
							fichier<<"v ";
						}
						j++;
					}
					if (j < PrismQuad::faces.size())
					{
						if((j+1)%48 != 0 || j !=PrismQuad::faces.size())
						{
							fichier <<PrismQuad::faces[j];
							j++;
						}
					}

					fichier <<endl<<endl<< "f ";
				
					while(m%20 != 0)
					{
						fichier << m<<" ";
						if(m%4 == 0 && !((m)%20 == 0))
						{
							fichier<<endl;
							fichier<<"f ";
						}
						m++;
					}
					fichier << m<<endl;
					m++;

					//fichier << endl << endl << "#Quad " << k << " finis !"<< endl << endl;
					k++;
	

					if(i >= PrismQuad::face1.size() && j >= PrismQuad::faces.size())
					{
						cout<<"# i : "<<i<<"|| j : "<<j<<"|| n :"<<n<<endl;
						fichier <<endl<< "# faces finies"<<endl;
						n=1;
					}
				}
				i=0;
				k=0;
				if(Batiment::ToitPyramideCoupe.size() == 0)
					n=2;

				// Boucle sur les toits!
				while(n==1)
				{
					fichier << endl << "g ToitPyramideCoupe"<<k<<endl<<endl;
					fichier<<"v ";
					while(i < Batiment::ToitPyramideCoupe.size() && (i+1)% 60 != 0)
					{
						fichier << Batiment::ToitPyramideCoupe[i] << " ";
						if((i+1)%3 == 0 && (i+1)%12 != 0)
						{
							fichier<<endl;
							fichier<<"v ";
						}
						if((i+1)%12 == 0 )
						{	
							fichier<<endl<<endl;
							fichier<<"v ";
						}
						i++;
					}
					if (i < Batiment::ToitPyramideCoupe.size())
					{
						if((i+1)%12 !=0 || i!=Batiment::ToitPyramideCoupe.size())
						{
							fichier <<Batiment::ToitPyramideCoupe[i];
							i++;
						}
					}
					fichier << endl<<endl;
					
					fichier<<"f ";
					while(m%20 != 0)
					{
						fichier << m<<" ";
						if(m%4 == 0 && !((m)%20 == 0))
						{
							fichier<<endl;
							fichier<<"f ";
						}
						m++;
					}
					fichier << m<<endl;
					m++;

					k++;
	
					if(i >= Batiment::ToitPyramideCoupe.size())
					{
						cout<<"# i : "<<i<<endl;
						fichier << "# Toitpyramidecoupe finis";
						n=2;
						
					}
				}
				k=0;
				i=0;

				u=1;

				if(Batiment::ToitPyramide.size() == 0)
					n=3;

				while(n==2)
				{
					fichier << endl << "g ToitPyramide"<<k<<endl<<endl;
					fichier<<"v ";
					while(i < Batiment::ToitPyramide.size() && (i+1)% 36 != 0)
					{
						fichier << Batiment::ToitPyramide[i] << " ";
						if((i+1)%3 == 0 && (i+1)%9 != 0)
						{
							fichier<<endl;
							fichier<<"v ";
						}
						if((i+1)%9 == 0 )
						{	
							fichier<<endl<<endl;
							fichier<<"v ";
						}
						i++;
					}
					if (i < Batiment::ToitPyramide.size())
					{
						if((i+1)%12 !=0 || i!=Batiment::ToitPyramide.size())
						{
							fichier <<Batiment::ToitPyramide[i];
							i++;
						}
					}
					fichier << endl<<endl;
					
					fichier<<"f ";
					while((u)%12 != 0)
					{
						fichier << m<<" ";
						if((u)%3 == 0 && !((u)%12 == 0))
						{
							fichier<<endl;
							fichier<<"f ";
						}
						m++;
						u++;
					}
					fichier << m<<endl;
					m++;

					k++;
					u=1;
	
					if(i >= Batiment::ToitPyramide.size())
					{
						cout<<"# i : "<<i<<endl;
						fichier << "# C'est finis";
						n=3;						
					}
				}
				k=0;
				i=0;
				j=0;
				u=1;
				if(Batiment::ToitPrisme.size() == 0)
					n=4;

				while(n==3)
				{
					fichier << endl << "g ToitPrisme"<<k<<endl<<endl;
					fichier<<"v ";
					while(i < Batiment::ToitPrisme.size() && (i+1)% 42 != 0)
					{
						fichier << Batiment::ToitPrisme[i] << " ";
						j++;
						if((i+1)%3 == 0 && j!=9 && j!=21 && j!=33 && j!=42)
						{
							fichier<<endl;
							fichier<<"v ";
						}
						if(j==9 || j==21 || j==33)
						{	
							fichier<<endl<<endl;
							fichier<<"v ";
						}
						i++;
					}
					if (i < Batiment::ToitPrisme.size())
					{
						if((i+1)%12 !=0 || i!=Batiment::ToitPrisme.size())
						{
							fichier <<Batiment::ToitPrisme[i];
							i++;
						}
					}
					fichier << endl<<endl;


					j=0;
					fichier<<"f ";
					while((j+1)%14 != 0)
					{
						fichier << m<<" ";
						j++;
						if(j==3 || j==7 || j==11 || j==14)// && !((m)%14 == 0))
						{
							fichier<<endl;
							fichier<<"f ";
						}
						m++;
					}
					fichier << m<<endl;
					m++;

					k++;
					j=0;
	
					if(i >= Batiment::ToitPrisme.size())
					{
						cout<<"# i : "<<i<<endl;
						fichier << "# C'est finis";
						n=4;
					}
				}
				i=0;
				k=0;

				if(UsineClassique::ToitUsine.size() == 0)
				{
					n=-1;
					l=-1;
				}
				
				while(n==4)
				{
					fichier << endl << "g ToitUsine"<<k<<endl<<endl;
					fichier<<"v ";
					while(i < UsineClassique::ToitUsine.size() && (i+1)% 42 != 0)
					{
						fichier << UsineClassique::ToitUsine[i] << " ";
						j++;
						if((i+1)%3 == 0 && j!=12 && j!=24 && j!=33 && j!=42)
						{
							fichier<<endl;
							fichier<<"v ";
						}
						if(j==12 || j==24 || j==33)
						{	
							fichier<<endl<<endl;
							fichier<<"v ";
						}
						i++;
					}
					if (i < UsineClassique::ToitUsine.size())
					{
						if((i+1)%12 !=0 || i!=UsineClassique::ToitUsine.size())
						{
							fichier <<UsineClassique::ToitUsine[i];
							i++;
						}
					}
					fichier << endl<<endl;


					j=0;
					fichier<<"f ";
					while((j+1)%14 != 0)
					{
						fichier << m<<" ";
						j++;
						if(j==4 || j==8 || j==11 || j==14)
						{
							fichier<<endl;
							fichier<<"f ";
						}
						m++;
					}
					fichier << m<<endl;
					m++;

					k++;
					j=0;
	
					if(i >= UsineClassique::ToitUsine.size())
					{
						cout<<"# i : "<<i<<endl;
						fichier << "# C'est finis";
						n=-1;
						l=-1;
					}
				}
			}

 
			fichier.close();
		}
		else
			     cout << "Impossible d'ouvrir le fichier !" << endl;
}