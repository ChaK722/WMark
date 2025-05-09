#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_selectButton_clicked();
    void on_applyButton_clicked();
    void on_saveButton_clicked();

private:
    QString filename;
    QPixmap fiximage;
    QPixmap currentPixmap; // 保存原始图片
    QString Model;
    QString Make;
    QString Date;
    QString ExTime;
    int FNum;
    int ISO;
    int FLent;
    QString logoPath;
    void logoSet(QString brand);

    QPixmap drawInfo(const QPixmap &src,const QString &text, int align);
    void updateImageDisplay();
    void readExifInfo(const QString &imagePath);
    QString text1();
    QString text2();
    QString text3();

protected:
    void resizeEvent(QResizeEvent *event) override; // 监听窗口尺寸变化

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
