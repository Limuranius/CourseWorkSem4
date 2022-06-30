#include "planetaddwindow.h"
#include "ui_planetaddwindow.h"
#include <string>

PlanetAddWindow::PlanetAddWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlanetAddWindow)
{
    ui->setupUi(this);
}

PlanetAddWindow::~PlanetAddWindow()
{
    delete ui;
}

void PlanetAddWindow::on_buttonBox_accepted()
{
    std::string planet_name = ui->lineEdit->text().toStdString();
    double distance = ui->lineEdit_2->text().toDouble();
    int price = ui->lineEdit_3->text().toInt();
    emit send_data(planet_name, distance, price);
}

