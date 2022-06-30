#include "attributeaddwindow.h"
#include "ui_attributeaddwindow.h"

AttributeAddWindow::AttributeAddWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttributeAddWindow)
{
    ui->setupUi(this);
}

AttributeAddWindow::~AttributeAddWindow()
{
    delete ui;
}

void AttributeAddWindow::on_buttonBox_accepted()
{
    std::string planet_name = ui->lineEdit->text().toStdString();
    std::string climate = ui->lineEdit_2->text().toStdString();
    std::string attribute = ui->lineEdit_3->text().toStdString();
    emit send_data(planet_name, climate, attribute);
}

