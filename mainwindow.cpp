#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "planetaddwindow.h"
#include "attributeaddwindow.h"
#include <iostream>
#include "QTreeWidgetItem"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_import_planets_default_path->setText(QString::fromStdString("Путь по умолчанию: " + this->default_import_planets_path));
    ui->label_import_attrs_default_path->setText(QString::fromStdString("Путь по умолчанию: " + this->default_import_attrs_path));
    ui->label_export_planets_default_path->setText(QString::fromStdString("Путь по умолчанию: " + this->default_export_planets_path));
    ui->label_export_attrs_default_path->setText(QString::fromStdString("Путь по умолчанию: " + this->default_export_attrs_path));
    ui->label_search_export_default_path->setText(QString::fromStdString("Путь по умолчанию: " + this->default_export_search_path));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check_planets_path(std::string path) {
    std::string pattern = this->planets_filename;
    int patt_len = pattern.size();
    if (patt_len <= path.size()) {
        return path.substr(path.size() - patt_len, patt_len) == pattern;
    } else {
        return false;
    }
}

bool MainWindow::check_attributes_path(std::string path) {
    std::string pattern = this->attributes_filename;
    int patt_len = pattern.size();
    if (patt_len <= path.size()) {
        return path.substr(path.size() - patt_len, patt_len) == pattern;
    } else {
        return false;
    }
}

bool MainWindow::check_report_path(std::string path) {
    std::string pattern = this->report_filename;
    int patt_len = pattern.size();
    if (patt_len <= path.size()) {
        return path.substr(path.size() - patt_len, patt_len) == pattern;
    } else {
        return false;
    }
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

void MainWindow::on_button_import_planets_path_clicked()
{
    QString path = this->ask_file_path_read();
    ui->lineEdit_import_planets_path->setText(path);
}

void MainWindow::on_button_import_attrs_path_clicked()
{
    QString path = this->ask_file_path_read();
    ui->lineEdit_import_attrs_path->setText(path);
}

void MainWindow::on_button_export_planets_path_clicked()
{
    QString path = this->ask_file_path_write();
    ui->lineEdit_export_planets_path->setText(path);
}

void MainWindow::on_button_export_attrs_path_clicked()
{
    QString path = this->ask_file_path_write();
    ui->lineEdit_export_attrs_path->setText(path);
}

void MainWindow::on_button_export_search_path_clicked()
{
    QString path = this->ask_file_path_write();
    ui->lineEdit_export_search_path->setText(path);
}

void MainWindow::on_button_add_planet_clicked()
{
    PlanetAddWindow win;
    connect(&win, &PlanetAddWindow::send_data,
            this, &MainWindow::on_get_add_planet_info);
    win.setModal(true);
    win.exec();
}

void MainWindow::on_button_add_attr_clicked()
{
    AttributeAddWindow win;
    connect(&win, &AttributeAddWindow::send_data,
            this, &MainWindow::on_get_add_attribute_info);
    win.setModal(true);
    win.exec();
}

void MainWindow::on_get_add_planet_info(std::string planet_name, double distance, int price) {
    // Проверка валидности входных данных
    if (!(is_distance_correct(distance) && is_price_correct(price))) {
        this->error_message("Неверные данные");
        return;
    }

    AddResult result = this->database.add_planet(planet_name, distance, price);
    if (result == AddResult::SUCCESS) {
        this->success_message("Планета добавлена");
        this->update();
        return;
    } else if (result == AddResult::EXIST) {
        this->error_message("Планета уже существует в справочнике");
        return;
    }
}

void MainWindow::on_get_add_attribute_info(std::string planet_name, std::string climate, std::string attribute) {
    AddResult result = this->database.add_attribute(planet_name, climate, attribute);
    if (result == AddResult::SUCCESS) {
        this->success_message("Признак добавлен");
        this->update();
        return;
    } else if (result == AddResult::EXIST) {
        this->error_message("Признак уже существует в справочнике");
        return;
    } else if (result == AddResult::NO_LINKED_PLANET) {
        this->error_message("Для несуществующей планеты нельзя добавить признак");
        return;
    }
}

void MainWindow::log(std::string message) {
    QString new_text = ui->textEdit_log->toPlainText();
    new_text += QString::fromStdString(message + "\n");
    ui->textEdit_log->setText(new_text);
}


void MainWindow::on_button_import_databases_clicked()
{
    std::string planets_import_path = ui->lineEdit_import_planets_path->text().toStdString();
    std::string attributes_import_path = ui->lineEdit_import_attrs_path->text().toStdString();

    if (this->check_planets_path(planets_import_path) && this->check_attributes_path(attributes_import_path)) {  // Проверяем соответствие названия файлов заданным названиям
        this->database.read_planets_file(planets_import_path);
        this->database.read_attributes_file(attributes_import_path);
        this->update();
        this->success_message("Загрузка прошла успешно");
    } else {
        this->error_message("Неверный файл");
    }
}

void MainWindow::on_button_import_default_databases_clicked()
{
    if (this->check_planets_path(this->default_import_planets_path) && this->check_attributes_path(this->default_import_attrs_path)) {  // Проверяем соответствие названия файлов заданным названиям
        this->database.read_planets_file(this->default_import_planets_path);
        this->database.read_attributes_file(this->default_import_attrs_path);
        this->update();
        this->success_message("Загрузка прошла успешно");
    } else {
        this->error_message("Неверный файл");
    }
}


void MainWindow::on_button_export_databases_clicked()
{
    std::string planets_export_path = ui->lineEdit_export_planets_path->text().toStdString();
    std::string attributes_export_path = ui->lineEdit_export_attrs_path->text().toStdString();
    this->database.save_planets_to_file(planets_export_path);
    this->database.save_attributes_to_file(attributes_export_path);
    this->success_message("Справочники экспортированы");
}

void MainWindow::on_button_export_default_databases_clicked()
{
    this->database.save_planets_to_file(this->default_export_planets_path);
    this->database.save_attributes_to_file(this->default_export_attrs_path);
    this->success_message("Справочники экспортированы");
}

void MainWindow::update() {
    this->update_planets();
    this->update_attributes();
}

void MainWindow::update_planets() {
    ui->treeWidget_planets->clear();
    vector<Planet> planets = this->database.get_all_planets();
    for (Planet& planet: planets) {
        this->add_planet_to_treewidget(planet);
    }
}

void MainWindow::update_attributes() {
    ui->treeWidget_attrs->clear();
    vector<Attribute> attributes = this->database.get_all_attributes();
    for (Attribute& attribute: attributes) {
        this->add_attribute_to_treewidget(attribute);
    }
}


void MainWindow::on_treeWidget_planets_itemSelectionChanged()
{
    auto selected_items = ui->treeWidget_planets->selectedItems();
    ui->button_rem_planet->setEnabled(!(selected_items.size() == 0));
}

void MainWindow::on_button_rem_planet_clicked()
{
    auto selected_items = ui->treeWidget_planets->selectedItems();
    // В данной таблице всегда может быть выбран только один элемент
    QTreeWidgetItem* item = selected_items[0];
    std::string planet_name = item->text(0).toStdString();

    // Спрашиваем пользователя, хочет ли он удалить запись и зависящие от неё признаки
    vector<Attribute> attrs = this->database.get_attributes_by_planet(planet_name);
    std::string message_text = "Из справочника \"Признаки\" удалятся следующие зависимые признаки:\n";
    for (Attribute &attr: attrs) {
        message_text += attribute_to_string(attr) + "\n";
    }
    message_text += "Вы хотите всё это удалить?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Удаление", QString::fromStdString(message_text), QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->database.remove_planet(planet_name);
        this->update();
        this->success_message("Планета и зависимые признаки удалены");
    }
}

void MainWindow::on_treeWidget_attrs_itemSelectionChanged()
{
    auto selected_items = ui->treeWidget_attrs->selectedItems();
    if (selected_items.size() != 0)
        ui->button_rem_attr->setEnabled(selected_items[0]->childCount() == 0);
    else
        ui->button_rem_attr->setEnabled(false);
}

void MainWindow::on_button_rem_attr_clicked()
{
    auto selected_items = ui->treeWidget_attrs->selectedItems();
    // В данной таблице всегда может быть выбран только один элемент
    QTreeWidgetItem* item = selected_items[0];
    std::string planet_name = item->text(0).toStdString();
    std::string climate = item->text(1).toStdString();
    std::string attribute = item->text(2).toStdString();
    this->database.remove_attribute(planet_name, climate, attribute);
    this->update();
}



void MainWindow::on_button_search_clicked()
{
    std::string climate = ui->lineEdit_search_climate->text().toStdString();
    std::string attribute = ui->lineEdit_search_attr->text().toStdString();
    double distance = ui->lineEdit_search_dist->text().toDouble();
    int price = ui->lineEdit_search_cost->text().toInt();

    // Проверка валидности входных данных
    if (!(is_distance_correct(distance) && is_price_correct(price))) {
        this->error_message("Неверные данные");
        return;
    }

    QString result = QString::fromStdString(this->database.search_to_string(distance, price, climate, attribute));
    ui->textEdit_search->setText(result);
}


void MainWindow::on_button_export_search_clicked()
{
    std::string path = ui->lineEdit_export_search_path->text().toStdString();

    if (this->check_report_path(path)) {
        std::ofstream out(path);
        out << ui->textEdit_search->toPlainText().toStdString();
        out.close();
        this->success_message("Отчёт сохранён");
    } else {
        this->error_message("Неверный файл");
    }

}

void MainWindow::on_button_export_default_search_clicked()
{
    if (this->check_report_path(this->default_export_search_path)) {
        std::ofstream out(this->default_export_search_path);
        out << ui->textEdit_search->toPlainText().toStdString();
        out.close();
        this->success_message("Отчёт сохранён");
        return;
    } else {
        this->error_message("Неверный файл");
        return;
    }
}

void MainWindow::success_message(QString message) {
    QMessageBox::information(this, "Успех", message);
}

void MainWindow::error_message(QString message) {
    QMessageBox::critical(this, "Ошибка", message);
}

void MainWindow::add_planet_to_treewidget(Planet planet) {
    QTreeWidgetItem* table_item = new QTreeWidgetItem(ui->treeWidget_planets);
    table_item->setText(0, QString::fromStdString(planet.planet_name));
    table_item->setText(1, QString::number(planet.distance));
    table_item->setText(2, QString::number(planet.price));
    ui->treeWidget_planets->addTopLevelItem(table_item);
}

void MainWindow::add_attribute_to_treewidget(Attribute attribute) {
    QTreeWidgetItem* table_item = new QTreeWidgetItem(ui->treeWidget_attrs);
    table_item->setText(0, QString::fromStdString(attribute.planet_name));
    table_item->setText(1, QString::fromStdString(attribute.climate));
    table_item->setText(2, QString::fromStdString(attribute.attribute));
    ui->treeWidget_attrs->addTopLevelItem(table_item);
}


void MainWindow::on_pushButton_log_planets_table_clicked()
{
    this->log(this->database.planets_to_string_planet_table());
}


void MainWindow::on_pushButton_log_planets_dist_tree_clicked()
{
    this->log(this->database.planets_to_string_distance_tree());
}


void MainWindow::on_pushButton_log_planets_price_tree_clicked()
{
    this->log(this->database.planets_to_string_price_tree());
}


void MainWindow::on_pushButton_log_attrs_planet_tree_clicked()
{
    this->log(this->database.attributes_to_string_planet_tree());
}


void MainWindow::on_pushButton_log_attrs_climate_tree_clicked()
{
    this->log(this->database.attributes_to_string_climate_tree());
}


void MainWindow::on_pushButton_log_attrs_attr_tree_clicked()
{
    this->log(this->database.attributes_to_string_attribute_tree());
}


void MainWindow::on_pushButton_planets_search_planet_clicked()
{
    std::string planet_name = ui->lineEdit_planets_search_planet->text().toStdString();

    ui->treeWidget_planets->clear();
    if (this->database.has_planet(planet_name)) {
        Planet planet = this->database.get_planet(planet_name);
        this->add_planet_to_treewidget(planet);
    }
}


void MainWindow::on_pushButton_planets_search_max_distance_clicked()
{
    double max_distance = ui->lineEdit_planets_search_max_distance->text().toDouble();

    if (!is_distance_correct(max_distance)) {
        this->error_message("Неверные данные");
        return;
    }

    ui->treeWidget_planets->clear();
    vector<Planet> search_result = this->database.get_planets_lower_distance(max_distance);
    for (Planet &planet: search_result) {
        this->add_planet_to_treewidget(planet);
    }
}


void MainWindow::on_pushButton_planets_search_max_price_clicked()
{
    int max_price = ui->lineEdit_planets_search_max_price->text().toInt();

    if (!is_price_correct(max_price)) {
        this->error_message("Неверные данные");
        return;
    }

    ui->treeWidget_planets->clear();
    vector<Planet> search_result = this->database.get_planets_lower_price(max_price);
    for (Planet &planet: search_result) {
        this->add_planet_to_treewidget(planet);
    }
}


void MainWindow::on_pushButton_planets_search_clear_clicked()
{
    this->update_planets();
}


void MainWindow::on_pushButton_attrs_search_planet_clicked()
{
    std::string planet_name = ui->lineEdit_attrs_search_planet->text().toStdString();

    ui->treeWidget_attrs->clear();
    vector<Attribute> attributes = this->database.get_attributes_by_planet(planet_name);
    for (Attribute &attr: attributes) {
        this->add_attribute_to_treewidget(attr);
    }
}


void MainWindow::on_pushButton_attrs_search_climate_clicked()
{
    std::string climate = ui->lineEdit_attrs_search_climate->text().toStdString();

    ui->treeWidget_attrs->clear();
    vector<Attribute> attributes = this->database.get_attributes_by_climate(climate);
    for (Attribute &attr: attributes) {
        this->add_attribute_to_treewidget(attr);
    }
}


void MainWindow::on_pushButton_attrs_search_attribute_clicked()
{
    std::string attribute = ui->lineEdit_attrs_search_attribute->text().toStdString();

    ui->treeWidget_attrs->clear();
    vector<Attribute> attributes = this->database.get_attributes_by_attribute(attribute);
    for (Attribute &attr: attributes) {
        this->add_attribute_to_treewidget(attr);
    }
}


void MainWindow::on_pushButton_attrs_search_clear_clicked()
{
    this->update_attributes();
}

