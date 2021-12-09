#include "window.h"
#include <QFileDialog>
#include <string>

//下拉框多个模型选择问题，删除选择模型
//评价指标放上来（大的代码工程啊）


window::window(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    detector->init(string("./model/CT-MR.xml"));
}

window::~window() {

}

void window::on_comboBox_currentIndexChanged(QString index) {
    index = ui.comboBox->currentText();
    //qDebug() << "Text:" << index;
    QString path = QString("./model/") + index + QString(".xml");
    detector->init(path.toLatin1().data());

}




void window::on_Button1_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.isEmpty()) {
        cout << "debug:打开文件失败" << endl;
    }
    else {
        img1 = imread(fileName.toLatin1().data(),-1);
        showimg(ui.label_img1, img1);
    }
}


void window::on_Button2_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.isEmpty()) {
        cout << "debug:打开文件失败" << endl;
    }
    else {
        img2 = imread(fileName.toLatin1().data(),-1);
        showimg(ui.label_img2, img2);
    }
}

//void window::on_Button3_clicked() {
//    QString model_name = QFileDialog::getOpenFileName(this, tr("Open Model"), ".", tr("(*.xml)"));
//    if (model_name.isEmpty()) {
//        cout << "debug:打开文件失败" << endl;
//    }
//    else {
//        detector->init(model_name.toLatin1().data());
//    }
//}

void window::on_Button4_clicked() {
    Mat osrc;
    Mat yuv;
    bool spect = false;
    Mat imgs[3];
    Mat img11 = img1.clone();
    Mat img22 = img2.clone();
    int h = img1.cols;
    int w = img2.rows;
    cv::resize(img1, img11, Size(256, 256));
    cv::resize(img2, img22, Size(256, 256));
    //彩图融合
    if (img22.channels() == 3) {
        spect = true;
        cvtColor(img22, yuv, CV_BGR2YUV);
        split(yuv, channels);
        imgs[0] = img11;
        imgs[1] = channels[0];
        imgs[2] = channels[0];
    }
    //img2是单通道
    else {
        imgs[0] = img11;
        imgs[1] = img22;
        imgs[2] = img22;
    }
    merge(imgs, 3, osrc);
    Mat imgf_1;
    detector->process_frame(osrc, imgf_1);
    
    if (spect == true) {
        Mat imgs[3] = { imgf_1, channels[1], channels[2] };
        merge(imgs, 3, yuv);
        cvtColor(yuv, osrc, CV_YUV2BGR);
        cv::resize(osrc,imgf, Size(h,w));
        
    }
    else {
        cv::resize(imgf_1, imgf, Size(h, w));
    }
    showimg(ui.label_imgf, imgf);


    ////auto start = chrono::high_resolution_clock::now();
    //detector->process_frame(osrc, imgf);
    ////auto end = chrono::high_resolution_clock::now();
    ////std::chrono::duration<double> diff = end - start;
    ////cout << "use " << diff.count() << " s" << endl;
    ////ui.label_imgf->clear();
  
    //showimg(ui.label_imgf, imgf);


}

void window::on_Button5_clicked() {

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png *.bmp *.jpg)")); //选择路径
    if (fileName.isEmpty()) {
        cout << "debug:打开文件失败" << endl;
    }
    else {
        string fileAsSave = fileName.toLatin1().data();
        imwrite(fileAsSave, imgf);
    }
}


void window::showimg(QLabel* label, cv::Mat& mat)
{
    cv::Mat Rgb;
    QImage Img;
    if (mat.channels() == 3)//RGB Img
    {
        cv::cvtColor(mat, Rgb, CV_BGR2RGB);//颜色空间转换
        //imshow("12345", Rgb);
        Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
    }
    else//Gray Img
    {
        Img = QImage((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols * mat.channels(), QImage::Format_Indexed8);
    }
    label->setPixmap(QPixmap::fromImage(Img));
}



