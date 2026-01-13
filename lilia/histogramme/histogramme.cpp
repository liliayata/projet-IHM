#include "histogramme.hpp"
#include <opencv2/imgproc.hpp>  // Pour line
#include <opencv2/highgui.hpp>  // Pour imshow
#include <iostream>
#include <algorithm>            // Pour max_element

using namespace std;
using namespace cv;

// HISTOGRAMME GRIS 

// Fonction pour calculer l'histogramme d'une image niveaux de gris

void calculHistogrammeGris(const Mat& image, int hist[256], set<uchar>& val_uniques)
{
    // Vectoriser l'image (transformer en colonne)
    //Conserver le nombre de canal 0
    // Total= Ligne*Colone
    Mat image_vec = image.reshape(0, image.total());

    // Parcourir tous les pixels
    for(int i = 0; i < image_vec.rows; i++){
        uchar val = image_vec.at<uchar>(i);  // Accéder à la valeur du pixel
        val_uniques.insert(val);            // Ajouter la valeur au set (valeurs uniques)
        hist[val]++;                    // Incrémenter le compteur pour cette intensité
    }
}

// Fonction pour afficher l'histogramme d'une image niveaux de gris

void afficherHistogrammeGris(const int hist[256], const set<uchar>& val_uniques,int largeur, int hauteur)
{
    // Créer une image vide pour l'histogramme
    
    Mat histImage(hauteur, largeur, CV_8UC1, Scalar(0));

    // Trouver la valeur maximale pour normaliser les hauteurs
    int max_val = 0;
    for(auto v : val_uniques)
        max_val = max(max_val, hist[v]);

    int bin_w = largeur / val_uniques.size(); // Largeur d'une barre
    
    int i = 0;

    // Tracer chaque barre de l'histogramme
    
    for(auto v : val_uniques){
        int h = (hist[v] * hauteur) / max_val;  // Hauteur proportionnelle

        line(histImage,
             Point(i * bin_w, hauteur),      // Bas de la barre
             Point(i * bin_w, hauteur - h),  // Sommet de la barre
             Scalar(255), 2);               // Couleur blanche et épaisseur 2
        i++;
    }

    // Afficher l'histogramme
    imshow("Histogramme Gris", histImage);
}

//  HISTOGRAMME COULEUR 

// Fonction pour calculer l'histogramme d'une image couleur

void calculHistogrammeCouleur(const Mat& image,int histB[256], int histG[256], int histR[256]){
    
    // Parcourir tous les pixels
    
    for(int i = 0; i < image.rows; i++){
        for(int j = 0; j < image.cols; j++){
            Vec3b pixel_Canal = image.at<Vec3b>(i, j); // Accéder au pixel BGR
            histB[pixel_Canal[0]]++; // Bleu
            histG[pixel_Canal[1]]++; // Vert
            histR[pixel_Canal[2]]++; // Rouge
        }
    }
}

// Fonction pour afficher les histogrammes couleur en subplot vertical

void afficherHistogrammeCouleur(const int histB[256], const int histG[256], const int histR[256],int largeur, int hauteur)
{
    // Créer trois images séparées pour chaque canal
    Mat histogramme_canal_B(hauteur, largeur, CV_8UC3, Scalar(0,0,0));
    Mat histogramme_canal_G(hauteur, largeur, CV_8UC3, Scalar(0,0,0));
    Mat histogramme_canal_R(hauteur, largeur, CV_8UC3, Scalar(0,0,0));

    // Trouver la valeur maximale pour normaliser les hauteurs
    int maxB = *max_element(histB, histB + 256);
    int maxG = *max_element(histG, histG + 256);
    int maxR = *max_element(histR, histR + 256);

    int largeur_barre = largeur / 256; // Largeur d'une barre

    // Tracer chaque canal
    for(int i = 0; i < 256; i++){
        int h_b = (histB[i] * hauteur) / maxB; // hauteur normalisée
        int h_g = (histG[i] * hauteur) / maxG;
        int h_r = (histR[i] * hauteur) / maxR;

        line(histogramme_canal_B, Point(i*largeur_barre, hauteur), Point(i*largeur_barre, hauteur - h_b), Scalar(255,0,0), 1); // Bleu
        line(histogramme_canal_G, Point(i*largeur_barre, hauteur), Point(i*largeur_barre, hauteur - h_g), Scalar(0,255,0), 1); // Vert
        line(histogramme_canal_R, Point(i*largeur_barre, hauteur), Point(i*largeur_barre, hauteur- h_r), Scalar(0,0,255), 1); // Rouge
    }

    // Combiner verticalement (subplot) : B en haut, G milieu, R bas
    Mat histTotal;
    vconcat(histogramme_canal_B, histogramme_canal_G, histTotal);
    vconcat(histTotal, histogramme_canal_R, histTotal);

    // Afficher l'image finale
    imshow("Histogramme Couleur (B/G/R Vertical)", histTotal);
}

