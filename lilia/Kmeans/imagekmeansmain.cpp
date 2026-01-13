#include "imagekmeans.hpp"

/*
    Constructeur
    Charge l’image depuis un fichier
*/
Images::Images(const string& nomFichier)
{
    // Chargement de l’image en couleur
    image = cv::imread(nomFichier, cv::IMREAD_COLOR);
}

/*
    Méthode de segmentation par K-means
*/
void Images::segmentationKMeans(int K)
{
    /*
        Étape 1 : reformater l’image
        Chaque pixel devient un vecteur (B, G, R)
    */
    cv::Mat data;
    image.convertTo(data, CV_32F);          // Conversion en float
    data = data.reshape(1, image.rows * image.cols);

    /*
        Étape 2 : paramètres de K-means
    */
    cv::Mat labels;     // Classe de chaque pixel
    cv::Mat centers;    // Centres des clusters

    cv::kmeans(
        data,               // Données d’entrée
        K,                  // Nombre de clusters
        labels,             // Résultat des labels
        cv::TermCriteria(
            cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER,
            10,              // Nombre max d’itérations
            1.0              // Précision
        ),
        3,                  // Nombre de tentatives
        cv::KMEANS_PP_CENTERS,
        centers
    );

    /*
        Étape 3 : reconstruction de l’image segmentée
    */
    imageSegmentee = cv::Mat(image.size(), image.type());

    for (int i = 0; i < image.rows * image.cols; i++)
    {
        int clusterIndex = labels.at<int>(i);

        imageSegmentee.at<cv::Vec3b>(i / image.cols, i % image.cols)[0] =
            static_cast<uchar>(centers.at<float>(clusterIndex, 0));

        imageSegmentee.at<cv::Vec3b>(i / image.cols, i % image.cols)[1] =
            static_cast<uchar>(centers.at<float>(clusterIndex, 1));

        imageSegmentee.at<cv::Vec3b>(i / image.cols, i % image.cols)[2] =
            static_cast<uchar>(centers.at<float>(clusterIndex, 2));
    }
}

/*
    Affichage des images
*/
void Images::afficherImages() const
{
    cv::imshow("Image originale", image);
    cv::imshow("Image segmentee - KMeans", imageSegmentee);

    cv::waitKey(0);
}

