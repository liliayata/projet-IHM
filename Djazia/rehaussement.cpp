#include "rehaussement.hpp"

// Constructeur : initialise le noyau
Rehaussement::Rehaussement() {
    noyau = (cv::Mat_<float>(3,3) <<
        0, -1,  0,
        -1,  5, -1,
        0, -1,  0
    );
}

// La méthode appliquer reste identique à celle au-dessus
cv::Mat Rehaussement::appliquer(const cv::Mat& image) {
    if (image.empty()) return cv::Mat();
   
    cv::Mat resultat;
   
    if (image.channels() == 3) {
        std::vector<cv::Mat> canaux;
        cv::split(image, canaux);
       
        for (int i = 0; i < 3; i++) {
            cv::Mat canalRehausse;
            cv::filter2D(canaux[i], canalRehausse, -1, noyau);  // Utilise le noyau
            canaux[i] = canalRehausse;
        }
       
        cv::merge(canaux, resultat);
    }
    else {
        cv::filter2D(image, resultat, -1, noyau);  // Utilise le noyau
    }
   
    return resultat;
}
