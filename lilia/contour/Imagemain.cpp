#include "Image.hpp"

int main()
{
    // Création d'un objet Image à partir d'un fichier image
    Image img("image.jpg");

    // Affichage de l'image originale
    //img.afficherImage("Image originale");

    // Application de la détection de contours
    img.detectionContours();

    // Affichage du résultat
    img.afficherContours();

    return 0;
}

