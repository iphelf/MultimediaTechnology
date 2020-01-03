#ifndef CONVERTOR_H
#define CONVERTOR_H
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QDebug>

QImage cvtMat2QImage(const cv::Mat& mat);

enum GrayscaleMethod {
    Mean=0,Max,Min,Weighed
};

cv::Mat toGrayscale(const cv::Mat& src,int method,double weight[3]=nullptr);

cv::Mat changeBC(const cv::Mat& src,double b,double c);

cv::Mat transit(const cv::Mat& src,const cv::Mat& dst,double percent);

#endif // CONVERTOR_H
