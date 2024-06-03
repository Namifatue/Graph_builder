#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "poland2.h"
#include <algorithm>
#include <string>
#include <QPainterPath>
#include <QPainter>
#include <cmath>
#include <QPen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    button = new QPushButton(this);
    button -> setGeometry(width()-200, 5, 100, 30);
    button -> setText("Build");
    connect(button, SIGNAL(clicked()), this, SLOT(MyClicked()));

    ui->label_2->setGeometry(width()-200, button->height()+10, 150, 20);
    ui->label_2->setStyleSheet("color: rgb(64, 64, 64)");
    ui->label_2->setText("<font size = 3><b>ВВЕДИТЕ ФУНКЦИЮ: <\b></font>");

    ui->lineEdit->setGeometry(width()-200, button->height()+10 + ui->label_2->height()+5, 140, 20);

    ui->label_3->setGeometry(width()-200, button->height()+10 + ui->label_2->height()+5 + ui->lineEdit->height()+10, 200, 20);
    ui->label_3->setStyleSheet("color: rgb(64, 64, 64)");
    ui->label_3->setText("<font size = 2><b>ВВЕДИТЕ ЛЕВУЮ ГРАНИЦУ: <\b></font>");

    ui->lineEdit_2->setGeometry(width()-200, button->height()+10 + ui->label_2->height()+5 + ui->lineEdit->height()+10 + ui->label_3->height()+5, 70, 20);

    ui->label_4->setGeometry(width()-200, button->height()+10 + ui->label_2->height()+5 + ui->lineEdit->height()+10 + ui->label_3->height()+5 + ui->lineEdit_2->height()+10, 200, 20);
    ui->label_4->setStyleSheet("color: rgb(64, 64, 64)");
    ui->label_4->setText("<font size = 2><b>ВВЕДИТЕ ПРАВУЮ ГРАНИЦУ: <\b></font>");

    ui->lineEdit_3->setGeometry(width()-200, button->height()+10 + ui->label_2->height()+5 + ui->lineEdit->height()+10 + ui->label_3->height()+5 + ui->lineEdit_2->height()+10 + ui->label_4->height()+5, 70, 20);

    ui->label_5->setGeometry(width()-200, button->height()+10 + ui->label_2->height()+5 + ui->lineEdit->height()+10 + ui->label_3->height()+5 + ui->lineEdit_2->height()+10 + ui->label_4->height()+5 + ui->lineEdit_3->height()+10, 200, 20);
    ui->label_5->setStyleSheet("color: rgb(64, 64, 64)");
    ui->label_5->setText("<font size = 2><b>ВВЕДИТЕ НИЖНЮЮ ГРАНИЦУ: <\b></font>");

    ui->lineEdit_4->setGeometry(width()-200, button->height()+10 + ui->label_2->height()+5 + ui->lineEdit->height()+10 + ui->label_3->height()+5 + ui->lineEdit_2->height()+10 + ui->label_4->height()+5 + ui->lineEdit_3->height()+10 + ui->label_5->height()+5, 70, 20);

    ui->label_6->setGeometry(width()-200, button->height()+10 + ui->label_2->height()+5 + ui->lineEdit->height()+10 + ui->label_3->height()+5 + ui->lineEdit_2->height()+10 + ui->label_4->height()+5 + ui->lineEdit_3->height()+10 + ui->label_5->height()+5 + ui->lineEdit_4->height()+10, 200, 20);
    ui->label_6->setStyleSheet("color: rgb(64, 64, 64)");
    ui->label_6->setText("<font size = 2><b>ВВЕДИТЕ ВЕРХНЮЮ ГРАНИЦУ: <\b></font>");

    ui->lineEdit_5->setGeometry(width()-200, button->height()+10 + ui->label_2->height()+5 + ui->lineEdit->height()+10 + ui->label_3->height()+5 + ui->lineEdit_2->height()+10 + ui->label_4->height()+5 + ui->lineEdit_3->height()+10 + ui->label_5->height()+5 + ui->lineEdit_4->height()+10 + ui->label_6->height()+5, 70, 20);

}


void MainWindow::MyClicked() {
    QString s = ui->lineEdit->text();
    QString s1;
    ui->label->setGeometry(5, 5, width()-210, height()-5-5);
    QPixmap pm(ui->label->width(), ui->label->height());
    pm.fill(Qt::white);

    QPainterPath path;
    QPainter painter;

    QPen pen;
    pen.setColor(QColor (64, 96, 192));
    pen.setWidth(2);

    QPen pen2;
    pen2.setColor(QColor (0, 0, 0));
    pen2.setWidth(1);

    double pi = 3.1415926;
    double xmin = (ui->lineEdit_2->text()).toDouble();
    double xmax = (ui->lineEdit_3->text()).toDouble();
    double ymin = (ui->lineEdit_4->text()).toDouble();
    double ymax = (ui->lineEdit_5->text()).toDouble();

    int xgmin = 0;
    int xgmax = pm.width();
    int ygmin = 0;
    int ygmax = pm.height();

    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (ygmin - ygmax) / (ymax - ymin);
    double step = ((xmax - xmin) / pm.height())/100;

    double x = xmin;
    s1 = s;
    s1.replace("x",  "(" + QString::number(x) + ")");
    double y;
    calculate(s1.toStdString(), y);

    int xg;
    int yg;
    int ygprev;

    xg = xgmin + kx * (x - xmin);
    yg = ygmin + ky * (y - ymax);
    path.moveTo(xg, yg);

    painter.begin(&pm);
    painter.setPen(pen);

    painter.drawLine(QPoint(xgmin, ygmin - ky * ymax), QPoint(xgmax, ygmin - ky * ymax));
    painter.drawLine(QPoint(xgmin - kx * xmin, ygmin), QPoint(xgmin - kx * xmin, ygmax));

    painter.setPen(pen2);
    for (double x = xmin; x < xmax; x += step) {
        s1 = s;
        s1.replace("x",  "(" + QString::number(x) + ")");
        calculate(s1.toStdString(), y);
        xg = xgmin + kx * (x - xmin);
        yg = ygmin + ky * (y - ymax);
        if (yg > ygmax) path.moveTo(xg, ygmax);
        if (yg < ygmin) path.moveTo(xg, ygmin);
        ygprev = yg;
        path.lineTo(xg, yg);
    }
    painter.drawPath(path);
    ui->label->setPixmap(pm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
