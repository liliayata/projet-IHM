#include "histogramme.hpp"         
#include <opencv2/highgui.hpp>      
#include <opencv2/imgproc.hpp>      
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // Charger l'image depuis mon  fichier projet_infos
    
    Mat image = imread("lesly.jpg");
    
    // Afficher l'image originale
    imshow("Mon image", image);

    // Vérifier si l'image est en niveaux de gris ou en couleur
    
    if(image.channels() == 1){
        //  Niveau de gris 
        int hist[256] = {0};       // Tableau pour stocker l'histogramme
        set<uchar> val_uniques;        // Ensemble pour stocker les valeurs uniques présentes

        calculHistogrammeGris(image, hist, val_uniques);         // Calculer l'histogramme
        afficherHistogrammeGris(hist, val_uniques, image.rows, image.cols);    // Afficher l'histogramme 
    }
    else{
        // Image couleur 
        int histB[256] = {0};  // Histogramme canal Bleu
        int histG[256] = {0};  // Histogramme canal Vert
        int histR[256] = {0};  // Histogramme canal Rouge

        calculHistogrammeCouleur(image, histB, histG, histR);          // Calculer l'histogramme couleur
        afficherHistogrammeCouleur(histB, histG, histR, 512, 256);     // Afficher en subplot vertical, chaque canal 256 pixels de hauteur
    }

   
    
    return 0;
}

