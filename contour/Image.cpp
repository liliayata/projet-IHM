#include "Image.hpp"
#include <iostream>
#include <cmath>

using namespace std;

// Constructeur de la classe Image
Image::Image(const string& nomFichier)
{
    // Chargement de l'image en niveaux de gris
    // IMREAD_GRAYSCALE force une image à un seul canal
    image = cv::imread(nomFichier, cv::IMREAD_GRAYSCALE);
}


// Affichage de l'image originale
void Image::afficherImage(const string& titre)
{
    // Affiche l'image originale dans une fenêtre OpenCV
    cv::imshow(titre, image);
}


// Détection de contours par filtre dérivatif (Sobel)
// ======================================================
void Image::detectionContours()
{
    // Création de l'image résultat
    // Même taille que l'image originale
    // CV_8UC1 : image en niveaux de gris (8 bits, 1 canal)
    imageContours = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);

    // Masque de Sobel pour le gradient horizontal (Gx)
    // Permet de détecter les contours verticaux
    int sobelX[3][3] = {
        {-1,  0,  1},
        {-2,  0,  2},
        {-1,  0,  1}
    };

    // Masque de Sobel pour le gradient vertical (Gy)
    // Permet de détecter les contours horizontaux
    int sobelY[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // Parcours de l'image pixel par pixel
    // On commence à 1 et on s'arrête à rows-1 / cols-1
    // pour éviter les débordements aux bords
    for (int i = 1; i < image.rows - 1; i++)
    {
        for (int j = 1; j < image.cols - 1; j++)
        {
            // Gradients selon x et y
            int gx = 0;
            int gy = 0;

            // Application des filtres de Sobel sur le voisinage 3x3
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // Valeur du pixel voisin
                    int pixel = image.at<uchar>(i + k, j + l);

                    // Accumulation pour le gradient horizontal
                    gx += pixel * sobelX[k + 1][l + 1];

                    // Accumulation pour le gradient vertical
                    gy += pixel * sobelY[k + 1][l + 1];
                }
            }

            // Calcul de la norme du gradient
            // Cette valeur représente l'intensité du contour
            int magnitude = static_cast<int>(sqrt(gx * gx + gy * gy));

            // Saturation pour rester dans l'intervalle [0, 255]
            if (magnitude > 255)
                magnitude = 255;
            if (magnitude < 0)
                magnitude = 0;

            // Stockage du résultat dans l'image de contours
            imageContours.at<uchar>(i, j) = static_cast<uchar>(magnitude);
        }
    }
}

// Affichage de l'image des contours
void Image::afficherContours()
{
    // Affiche l'image après détection de contours
    cv::imshow("Contours detectes", imageContours);

    // Attend une action de l'utilisateur
    cv::waitKey(0);
}

