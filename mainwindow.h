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
    void on_get_add_planet_info(std::string planet_name, double distance, int price);
    void on_get_add_attribute_info(std::string planet_name, std::string climate, std::string attribute);

    void add_planet_to_treewidget(Planet planet);
    void add_attribute_to_treewidget(Attribute attribute);

    void update();
    void update_planets();
    void update_attributes();

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

    void on_button_import_default_databases_clicked();

    void on_button_export_default_databases_clicked();

    void on_button_export_default_search_clicked();

    void on_pushButton_log_planets_table_clicked();

    void on_pushButton_log_planets_dist_tree_clicked();

    void on_pushButton_log_planets_price_tree_clicked();

    void on_pushButton_log_attrs_planet_tree_clicked();

    void on_pushButton_log_attrs_climate_tree_clicked();

    void on_pushButton_log_attrs_attr_tree_clicked();

    void on_pushButton_planets_search_planet_clicked();

    void on_pushButton_planets_search_max_distance_clicked();

    void on_pushButton_planets_search_max_price_clicked();

    void on_pushButton_planets_search_clear_clicked();

    void on_pushButton_attrs_search_planet_clicked();

    void on_pushButton_attrs_search_climate_clicked();

    void on_pushButton_attrs_search_attribute_clicked();

    void on_pushButton_attrs_search_clear_clicked();

private:
    Ui::MainWindow *ui;

    Database database;

    QString ask_file_path_read();

    QString ask_file_path_write();

    void log(std::string message);
    void success_message(QString message);
    void error_message(QString message);

    // Пути по умолчанию
    std::string default_import_planets_path = "./planets.txt";
    std::string default_import_attrs_path = "./attributes.txt";
    std::string default_export_planets_path = "./planets.txt";
    std::string default_export_attrs_path = "./attributes.txt";
    std::string default_export_search_path = "./report.txt";

    // Названия файлов. Любые другие названия не будут приниматься
    std::string planets_filename = "planets.txt";
    std::string attributes_filename = "attributes.txt";
    std::string report_filename = "report.txt";

    bool check_planets_path(std::string path);
    bool check_attributes_path(std::string path);
    bool check_report_path(std::string path);
};
#endif // MAINWINDOW_H
