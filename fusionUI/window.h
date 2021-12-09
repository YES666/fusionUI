#pragma once

#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>
#include "ui_window.h"
#include "opencv2/imgproc/types_c.h"
#include "detector.h"
using namespace cv;
class window : public QMainWindow
{
    Q_OBJECT

public:
    window(QWidget *parent = Q_NULLPTR);
    ~window();
    

private :
    Ui::windowClass ui;
private slots:
    void showimg(QLabel* label, Mat& mat);
    void on_Button1_clicked();
    void on_Button2_clicked();
    //void on_Button3_clicked();
    void on_Button4_clicked();
    void on_Button5_clicked();

    void on_comboBox_currentIndexChanged(QString index);

private:
    Mat img1, img2, imgf;
    Mat channels[3];
    Detector* detector = new Detector;

};
