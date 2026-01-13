#ifndef IMAGEKMEANS_HPP
#define IMAGEKMEANS_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

/*
    Classe Images
    Elle regroupe les méthodes de traitement d’image
*/
class Images
{
private:
    cv::Mat image;          // Image originale
    cv::Mat imageSegmentee; // Image après K-means

public:
    // Constructeur
    Images(const string& nomFichier);

    // Appliquer la segmentation K-means
    void segmentationKMeans(int K);

    // Afficher les images
    void afficherImages() const;
};

#endif

