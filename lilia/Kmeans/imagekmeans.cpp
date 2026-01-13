#include "imagekmeans.hpp"

using namespace std;

int main()
{
    // Création de l’objet Images
    Images img("image.jpg"); 

    // Application de la segmentation K-means
    img.segmentationKMeans(3); // K = nombre de régions

    // Affichage des résultats
    img.afficherImages();

    return 0;
}

