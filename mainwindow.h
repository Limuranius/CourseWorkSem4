#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <string>
#include "Database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void get_add_planet_info(std::string planet_name, double distance, int price);

    void get_add_attribute_info(std::string planet_name, std::string climate, std::string attribute);

private slots:
    void on_action_files_page_triggered();

    void on_action_planets_page_triggered();

    void on_action_attributes_page_triggered();

    void on_action_search_page_triggered();

    void on_action_errors_page_triggered();

    void on_button_import_planets_path_clicked();

    void on_button_import_attrs_path_clicked();

    void on_button_export_planets_path_clicked();

    void on_button_export_attrs_path_clicked();

    void on_button_export_search_path_clicked();

    void on_button_add_planet_clicked();

    void on_button_add_attr_clicked();

    void on_button_import_databases_clicked();

    void on_button_export_databases_clicked();

    void on_treeWidget_planets_itemSelectionChanged();

    void on_button_rem_attr_clicked();

    void on_button_rem_planet_clicked();

    void on_treeWidget_attrs_itemSelectionChanged();

    void on_button_search_clicked();

    void on_button_export_search_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_button_import_default_databases_clicked();

    void on_button_export_default_databases_clicked();

    void on_button_export_default_search_clicked();

private:
    Ui::MainWindow *ui;

    std::string default_import_planets_path = "./planets.txt";
    std::string default_import_attrs_path = "./attributes.txt";
    std::string default_export_planets_path = "./planets.txt";
    std::string default_export_attrs_path = "./attributes.txt";
    std::string default_export_search_path = "./report.txt";

    Database database;

    QString ask_file_path_read();

    QString ask_file_path_write();

    void log(std::string message);

    void update();

    void update_planets();

    void update_attributes();
};
#endif // MAINWINDOW_H
