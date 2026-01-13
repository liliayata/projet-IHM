#include "rehaussement.hpp"
#include <iostream>

int main() {
    cv::Mat image = cv::imread("image_test.jpg");  // Charge AUTRE image
    
    if (image.empty()) {
        std::cerr << "Erreur de chargement." << std::endl;
        return -1;
    }
    
    Rehaussement rehaussement;
    cv::Mat imageRehaussee = rehaussement.appliquer(image);  // MÊME appel
    
    // Affiche
    cv::imshow("Originale", image);
    cv::imshow("Rehaussee", imageRehaussee);
    cv::waitKey(0);
    
    // Sauvegarde
    cv::imwrite("test_rehaussee.jpg", imageRehaussee);
    
    std::cout << "Terminé !" << std::endl;
    return 0;
}
