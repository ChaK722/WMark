#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>
#include <QResizeEvent>
#include <exiv2/exiv2.hpp>
#include <QPainter>
#include <numeric>
#include <QMessageBox>
#include <libraw/libraw.h>
#include <QImage>
#include <opencv2/opencv.hpp>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::logoSet(QString brand){
    brand = brand.toLower();
    if (brand.contains("canon"))      logoPath = ":/logos/Canon.png";
    else if (brand.contains("nikon")) logoPath = ":/logos/Nikon.png";
    else if (brand.contains("sony"))  logoPath = ":/logos/Sony.png";
    else if (brand.contains("fujifilm")) logoPath = ":/logos/Fujifilm.png";
    else if (brand.contains("leica")) logoPath = ":/logos/Leica.png";
    else if (brand.contains("lumix")) logoPath = ":/logos/Lumix.png";
    // else logoPath = ":/logos/default.png"; // 可选默认图标

}

QImage loadRawToQImage(const QString &filename) {
    LibRaw rawProcessor;
    if (rawProcessor.open_file(filename.toStdString().c_str()) != LIBRAW_SUCCESS)
        throw std::runtime_error("无法打开 RAW 文件");
    rawProcessor.imgdata.params.use_camera_wb = 1;     // 使用相机白平衡
    rawProcessor.imgdata.params.output_color = 1;      // sRGB
    rawProcessor.imgdata.params.use_auto_wb = 0;       // 不使用自动白平衡
    rawProcessor.imgdata.params.no_auto_bright = 0;    // 不自动亮度增强

    rawProcessor.unpack();
    rawProcessor.dcraw_process();
    libraw_processed_image_t *image = rawProcessor.dcraw_make_mem_image();

    if (!image || image->type != LIBRAW_IMAGE_BITMAP) {
        rawProcessor.recycle(); // 确保释放 LibRaw 本体资源
        throw std::runtime_error("RAW 解码失败或格式不支持");
    }

    QImage result(image->width, image->height, QImage::Format_RGB888);
    memcpy(result.bits(), image->data, image->height * image->width * 3);

    // 释放 libraw 的图像缓存和内部资源
    LibRaw::dcraw_clear_mem(image);
    rawProcessor.recycle();

    return result;
}


QPixmap rotated(const QPixmap src, QString orientation){
    QPixmap rotate = src;
    QTransform transform;
    if (orientation == "3"){
        transform.rotate(180);
    }else if (orientation == "6"){
        transform.rotate(90);
    }else if (orientation == "8"){
        transform.rotate(270);
    }
    rotate = src.transformed(transform, Qt::SmoothTransformation);

    return rotate;
}
// 点击按钮选择图像
void MainWindow::on_selectButton_clicked()
{
    filename = QFileDialog::getOpenFileName(
        this,
        "选择图片",
        "",
        "Images (*.png *.jpg *.jpeg *.bmp *.NEF *.CR3 *.ARW *.dng)"
        );

    if (filename.isEmpty()) return;

    QPixmap pixmap;
    QString ext = QFileInfo(filename).suffix().toLower();

    try {
        auto image = Exiv2::ImageFactory::open(filename.toStdString());
        image->readMetadata();
        auto &exifData = image->exifData();

        // 相机信息
        Make = QString::fromStdString(exifData["Exif.Image.Make"].toString());
        Model = QString::fromStdString(exifData["Exif.Image.Model"].toString());

        // 快门时间处理（简化）
        QString shutter = QString::fromStdString(exifData["Exif.Photo.ExposureTime"].toString());
        QStringList parts = shutter.split('/');
        if (parts.size() == 2) {
            bool ok1, ok2;
            int n = parts[0].toInt(&ok1);
            int d = parts[1].toInt(&ok2);
            if (ok1 && ok2 && d != 0) {
                int gcd = std::gcd(n, d);
                n /= gcd;
                d /= gcd;
                ExTime = QString("%1/%2").arg(n).arg(d);
            } else {
                ExTime = shutter;
            }
        } else {
            ExTime = shutter;
        }

        // 光圈、焦距、ISO
        FLent = exifData["Exif.Photo.FocalLength"].toFloat();
        ISO = exifData["Exif.Photo.ISOSpeedRatings"].toInt64();
        FNum = exifData["Exif.Photo.FNumber"].toFloat();

        // 方向自动旋转
        QString orientation = QString::fromStdString(exifData["Exif.Image.Orientation"].toString());
        qDebug() << "orientation:" << orientation;
        qDebug() << "Camera:" << Make << Model;
        qDebug() << "Shutter:" << ExTime;
        qDebug() << "FNumber:" << FNum << "ISO:" << ISO << "FL:" << FLent;

        if (ext == "cr3" || ext == "nef" || ext == "arw" || ext == "dng") {
            QImage rawImage;
            bool rawSuccess = false;
            try {
                rawImage = loadRawToQImage(filename);
                rawSuccess = true;
            } catch (const std::exception &e) {
                qDebug() << "RAW 解码失败:" << e.what();
                QMessageBox::warning(this, "RAW 解码失败", e.what());
            }
            if (rawSuccess) {
                pixmap = QPixmap::fromImage(rawImage);
            } else {
                return; // 加载失败则中止
            }
        } else {
            pixmap = rotated(QPixmap(filename),orientation);
        }

    } catch (const Exiv2::Error &e) {
        qDebug() << "EXIF 读取错误:" << e.what();
    }
    logoSet(Make);
    currentPixmap = pixmap;
    //currentPixmap = rotated;
    fiximage = currentPixmap;
    updateImageDisplay();
}

QImage blurImageWithOpenCV(const QImage &input, int radius) {
    if (radius % 2 == 0) radius += 1;
    if (radius < 3) radius = 3;

    QImage formatted = input.convertToFormat(QImage::Format_RGBA8888);

    // 深拷贝像素数据（避免依赖 Qt 管理内存）
    cv::Mat mat(formatted.height(), formatted.width(), CV_8UC4);
    memcpy(mat.data, formatted.bits(), formatted.sizeInBytes());

    // 执行高斯模糊
    cv::Mat blurred;
    cv::GaussianBlur(mat, blurred, cv::Size(radius, radius), 0);

    // 创建新 QImage，从 OpenCV 数据复制
    QImage result(blurred.cols, blurred.rows, QImage::Format_RGBA8888);
    memcpy(result.bits(), blurred.data, blurred.total() * blurred.elemSize());

    return result;
}



QPixmap mode1(const QPixmap src){
    QPixmap newPix(src.width(),src.height()*1.2);
    newPix.fill(Qt::white);

    QPainter painter(&newPix);
    painter.drawPixmap(0,0,src);
    return newPix;
}

QPixmap mode2(const QPixmap src){
    QPixmap newPix(src.width()*1.1,src.height()*1.3);
    newPix.fill(Qt::white);

    QPainter painter(&newPix);
    painter.drawPixmap(src.width()*0.05,src.height()*0.05,src);

    return newPix;
}

QPixmap mode3(const QPixmap src){
    QPixmap newPix(src.width()*1.1,src.height()*1.3);
    newPix.fill(Qt::white);

    QPainter painter(&newPix);
    QRect rect(0,0,newPix.width(),newPix.height());
    painter.drawPixmap(rect, QPixmap::fromImage(blurImageWithOpenCV(src.toImage(),500)));
    painter.drawPixmap(src.width()*0.05,src.height()*0.05,src);

    return newPix;
}

QString MainWindow::text1(){
    QString text = QString("%1 mm\nF%2\n%3s\nISO %4\n").arg(FLent).arg(FNum).arg(ExTime).arg(ISO);
    qDebug()<<text;
    return text;
}
QString MainWindow::text2(){
    QString text = QString("%1 mm | F%2 | %3s | ISO %4").arg(FLent).arg(FNum).arg(ExTime).arg(ISO);
    qDebug()<<text<<"text2";
    return text;
}
QMap<QString, QColor> colorMap = {
    {"Black", Qt::black},
    {"White", Qt::white},
    {"Red", Qt::red},
    {"Green", Qt::green},
    {"Blue", Qt::blue},
    {"Yellow", Qt::yellow},
    {"Cyan", Qt::cyan},
    {"Magenta", Qt::magenta},
    };

QPixmap MainWindow::drawInfo(const QPixmap &src, const QString &text, int align) {
    QPixmap result = src.copy();  // 创建副本以绘制
    QPainter painter(&result);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // 设置字体和颜色
    QFont font("Times New Roman");
    int size = result.height()*0.02;
    font.setPointSize(size);
    font.setBold(true);
    painter.setFont(font);
    QString colorStr = ui->colorBox->currentText();
    if (colorMap.contains(colorStr)) {
        painter.setPen(colorMap[colorStr]);
    } else {
        painter.setPen(Qt::black); // 默认颜色
    }

    // 居中画在底部
    QRect rect(result.width()*0.05, result.height()*0.85, result.width()*0.9, result.height()*0.15);  // 图片底部区域
    painter.drawText(rect, align, text);

    if (!logoPath.isEmpty()) {
        QPixmap logo(logoPath);
        if (!logo.isNull()) {
            int logoWidth = result.width() * 0.15;
            int logoHeight = logo.height() * logoWidth / logo.width();  // 保持比例
            QRect logoRect(result.width() * 0.5 - logoWidth*0.5, result.height() * 0.85, logoWidth, logoHeight);
            painter.drawPixmap(logoRect, logo);
            qDebug()<<"1";
        }
    }

    return result;
}

void MainWindow::on_applyButton_clicked(){
    currentPixmap = fiximage;    // 保存原始图像
    if(!currentPixmap.isNull()){
        QString mode = ui->modeBox->currentText();
        if(mode == "1"){
            currentPixmap = mode1(currentPixmap);
        }else if(mode == "2"){
            currentPixmap = mode2(currentPixmap);
        }else if(mode == "3"){
            currentPixmap = mode3(currentPixmap);
        }
        QString text = ui->textBox->currentText();
        if(text == "1"){
            currentPixmap = drawInfo(currentPixmap,text1(),2);

        }else if(text == "2"){
            currentPixmap = drawInfo(currentPixmap,text2(),132);
        }
        updateImageDisplay();

    }
}
void MainWindow::on_saveButton_clicked(){
    QString savePath = QFileDialog::getSaveFileName(
        this,
        "保存图片",
        "watermarked.jpg",
        "Images (*.png *.jpg *.bmp)"
        );

    if (!savePath.isEmpty()) {
        if (currentPixmap.save(savePath)) {
            QMessageBox::information(this, "保存成功", "图片已保存至:\n" + savePath);
        } else {
            QMessageBox::warning(this, "保存失败", "无法保存图片！");
        }
    }
}

// 窗口尺寸变化时重新缩放图片
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);  // 保留父类行为
    updateImageDisplay();             // 调整图像大小
}

// 缩放并显示图像，保持比例
void MainWindow::updateImageDisplay()
{
    if (!currentPixmap.isNull()) {
        QPixmap scaled = currentPixmap.scaled(
            ui->imageLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            );
        ui->imageLabel->setPixmap(scaled);
    }
}
