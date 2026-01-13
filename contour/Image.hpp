#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class Image
{
private:
    // Image originale en niveaux de gris
    cv::Mat image;

    // Image résultant de la détection de contours
    cv::Mat imageContours;

public:
    // Constructeur : charge l'image depuis un fichier
    Image(const string& nomFichier);

    // Affiche l'image originale
    void afficherImage(const string& titre);

    // Détection de contours par filtre dérivatif (Sobel)
    void detectionContours();

    // Affiche l'image des contours
    void afficherContours();
};

#endif

