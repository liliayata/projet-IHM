#ifndef REHAUSSEMENT_HPP
#define REHAUSSEMENT_HPP

#include <opencv2/opencv.hpp>
#include <vector>

class Rehaussement {
public:
    Rehaussement();  // Constructeur
    cv::Mat appliquer(const cv::Mat& image);

private:
    cv::Mat noyau;  // DÉCLARATION du noyau
};

#endif
