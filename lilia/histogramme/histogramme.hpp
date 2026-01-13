#ifndef HISTOGRAMME_H   
#define HISTOGRAMME_H

#include <opencv2/core.hpp> 
#include <set>               

using namespace cv;         
using namespace std;        




// Déclaration de la fonction pour calculer l'histogramme d'une image niveaux de gris
// image : image d'entrée
// hist : tableau de 256 entiers pour stocker le nombre de pixels par intensité
// uniques : ensemble pour stocker les intensités présentes
void calculHistogrammeGris(const Mat& image, int hist[256], set<uchar>& uniques);




// Déclaration de la fonction pour calculer l'histogramme d'une image couleur
// histB, histG, histR : tableaux pour stocker le nombre de pixels par intensité pour chaque canal
void calculHistogrammeCouleur(const Mat& image,int histB[256], int histG[256], int histR[256]);




// Déclaration de la fonction pour afficher l'histogramme d'une image niveaux de gris
// hist : tableau des occurrences
// uniques : valeurs uniques présentes dans l'image
// width, height : dimensions de l'image d'affichage de l'histogramme
void afficherHistogrammeGris(const int hist[256], const set<uchar>& uniques,int width, int height);




// Déclaration de la fonction pour afficher l'histogramme d'une image couleur
// histB, histG, histR : tableaux des occurrences pour chaque canal
// width, height : dimensions de chaque canal de l'image d'affichage
void afficherHistogrammeCouleur(const int histB[256], const int histG[256], const int histR[256],int width, int height);

#endif  

