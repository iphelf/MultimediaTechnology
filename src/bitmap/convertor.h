#ifndef CONVERTOR_H
#define CONVERTOR_H
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QDebug>

QImage cvtMat2QImage(const cv::Mat& mat) {
    int width = mat.cols;
    int height = mat.rows;
    int bytesPerLine = static_cast<int>(mat.step);
    cv::Mat cloned=mat.clone();
    switch (mat.type()) {
    // 8bit, ARGB
    case CV_8UC4: {
        QImage image(cloned.data, width, height, bytesPerLine,
                     QImage::Format_ARGB32);
        return image.rgbSwapped();
    }
    // 8bit, BGR
    case CV_8UC3: {
        QImage image(cloned.data, width, height, bytesPerLine,
                     QImage::Format_RGB888);
        //swap blue and red channel
        return image.rgbSwapped();
    }
    // 8bit, Grayscale
    case CV_8UC1: {
        QImage image(cloned.data, width, height, bytesPerLine,
                     QImage::Format_Grayscale8);
        return image;
    }
    default: {
        // Unsupported format
        qWarning() << "Unsupported cv::Mat tpye: " << mat.type()
                   << ", Empty QImage will be returned!";
        return QImage();
    }
    }
}

enum GrayscaleMethod {
    Mean=0,Max,Min,Weighed
};

cv::Mat toGrayscale(const cv::Mat& src,int method,double weight[3]=nullptr) {
    cv::Mat dst;
    dst.create(src.size(),src.type());
    double w[3];
    if(weight!=nullptr) {
        w[0]=weight[2];
        w[1]=weight[1];
        w[2]=weight[0];
    } else {
        w[0]=0.11; //B
        w[1]=0.59; //G
        w[2]=0.30; //R
    }
    int r=src.rows,c=src.cols;
    for(int i=0; i<r; i++) {
        const cv::Vec3b *srci=src.ptr<cv::Vec3b>(i);
        cv::Vec3b *dsti=dst.ptr<cv::Vec3b>(i);
        for(int j=0; j<c; j++) {
            int v;
            switch (method) {
            case Mean:
                v=(srci[j][0]+srci[j][1]+srci[j][2])/3;
                break;
            case Max:
                v=std::max({srci[j][0],srci[j][1],srci[j][2]});
                break;
            case Min:
                v=std::min({srci[j][0],srci[j][1],srci[j][2]});
                break;
            case Weighed:
                v=std::min(255,int(srci[j][0]*w[0]+
                                   srci[j][1]*w[1]+
                                   srci[j][2]*w[2]));
                break;
            default:
                v=0;
            }
            dsti[j][0]=dsti[j][1]=dsti[j][2]=uchar(v);
        }
    }
    return dst;
}

cv::Mat changeBC(const cv::Mat& src,double b,double c) {
    cv::Mat dst;
    dst.create(src.size(),src.type());
    int nr=src.rows,nc=src.cols;
    double w[3]= {0.11,0.59,0.30};
    double avgB=0;
    for(int i=0; i<nr; i++) {
        const cv::Vec3b *srci=src.ptr<cv::Vec3b>(i);
        cv::Vec3b *dsti=dst.ptr<cv::Vec3b>(i);
        for(int j=0; j<nc; j++) {
            for(int k=0; k<3; k++) {
                dsti[j][k]=uchar(std::min(int(srci[j][k]*(1+b)),255));
                avgB+=dsti[j][k]*w[k];
            }
        }
    }
    avgB/=(nr*nc);
    for(int i=0; i<nr; i++) {
        cv::Vec3b *dsti=dst.ptr<cv::Vec3b>(i);
        for(int j=0; j<nc; j++) {
            double B=0;
            for(int k=0; k<3; k++) B+=dsti[j][k]*w[k];
            double ratio=(B+(B-avgB)*c)/B;
            for(int k=0; k<3; k++)
                dsti[j][k]=uchar(std::max(std::min(int(dsti[j][k]*ratio),
                                                   255),0));
        }
    }
    return dst;
}

#endif // CONVERTOR_H
