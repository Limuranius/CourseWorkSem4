#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

QString MainWindow::ask_file_path_read() {
    QString path = QFileDialog::getOpenFileName(this, "Open File");
    return path;
}

QString MainWindow::ask_file_path_write() {
    QString path = QFileDialog::getSaveFileName(this, "Write to File");
    return path;
}

void MainWindow::on_action_files_page_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_action_planets_page_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_action_attributes_page_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_action_search_page_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_action_errors_page_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}

