#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zhuwin.h"
#include "qpainter.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pixmap(":/new/jpg/C:/Users/刘子乐/Pictures/test.bmp");
        QPalette palette;
        palette.setBrush(backgroundRole(), QBrush(pixmap));
        setPalette(palette);
    QPainter painter(this);
    QRect rec;
    rec.setTopLeft(QPoint(0,0));
    rec.setBottomRight(QPoint(this->width(),this->height()));
    QPixmap pix;
    pix.load(":/new/jpg/C:/Users/刘子乐/Pictures/test.bmp");
    painter.drawPixmap(rec,pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    zhuwin *lzl=new zhuwin(2);
    lzl->setWindowTitle("欢乐连连看");
    lzl->show();
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    zhuwin *lzl=new zhuwin(1);
    lzl->setWindowTitle("欢乐连连看");
    lzl->show();
    this->hide();
}

void MainWindow::on_pushButton_3_clicked()
{
    zhuwin *lzl=new zhuwin(1);
    lzl->setWindowTitle("欢乐连连看");
    lzl->show();
    this->hide();
}

void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::information(this,"帮助","点击左侧三个按钮开始游戏");
}

void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox::information(this,"关于","本程序由刘子乐开发，部分资源来源于网络");
}
