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
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::ask_file_path_read() {
    QString path = QFileDialog::getOpenFileName(this, "Open File", "C:/Users/Gleb/Documents/CourseWorkSem4");
    return path;
}

QString MainWindow::ask_file_path_write() {
    QString path = QFileDialog::getSaveFileName(this, "Write to File", "C:/Users/Gleb/Documents/CourseWorkSem4");
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


void MainWindow::on_button_export_log_path_clicked()
{
    QString path = this->ask_file_path_write();
    ui->lineEdit_export_log_path->setText(path);
}


void MainWindow::on_button_add_planet_clicked()
{
    PlanetAddWindow win;
    connect(&win, &PlanetAddWindow::send_data,
            this, &MainWindow::get_add_planet_info);
    win.setModal(true);
    win.exec();
}


void MainWindow::on_button_add_attr_clicked()
{
    AttributeAddWindow win;
    connect(&win, &AttributeAddWindow::send_data,
            this, &MainWindow::get_add_attribute_info);
    win.setModal(true);
    win.exec();
}

void MainWindow::get_add_planet_info(std::string planet_name, double distance, int price) {
    // Сюда вставить добавление планеты в БД (и проверку на дубликаты)
    if (this->database.has_planet(planet_name)) {
        QMessageBox::warning(this, "Ошибка", "Данная планета уже есть в справочнике.");
        return;
    }
    this->database.set_planet(planet_name, distance, price);
    this->update();
}

void MainWindow::get_add_attribute_info(std::string planet_name, std::string climate, std::string attribute) {
    // Сюда вставить добавление признака в БД (и проверку на дубликаты)
    if (this->database.has_attribute(planet_name, climate, attribute)) {
        QMessageBox::warning(this, "Ошибка", "Данный признак уже есть в справочнике.");
        return;
    }
    if (!this->database.has_planet(planet_name)) {
        QMessageBox::warning(this, "Ошибка", "Нельзя добавлять признаки для планеты, не описанной в справочнике \"Планеты\"");
        return;
    }
    this->database.add_attribute(planet_name, climate, attribute);
    this->update();
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
    this->database.read_planets_file(planets_import_path);
    this->database.read_attributes_file(attributes_import_path);
    this->update();
}


void MainWindow::on_button_export_databases_clicked()
{
    std::string planets_export_path = ui->lineEdit_export_planets_path->text().toStdString();
    std::string attributes_export_path = ui->lineEdit_export_attrs_path->text().toStdString();
    this->database.save_planets_to_file(planets_export_path);
    this->database.save_attributes_to_file(attributes_export_path);
}

void MainWindow::update() {
    this->update_planets();
    this->update_attributes();
}

void MainWindow::update_planets() {
    ui->treeWidget_planets->clear();
    auto planets = this->database.planets.to_vector();
    for (auto& planet: planets) {
        QTreeWidgetItem* table_item = new QTreeWidgetItem(ui->treeWidget_planets);
        table_item->setText(0, QString::fromStdString(planet.planet_name));
        table_item->setText(1, QString::number(planet.distance));
        table_item->setText(2, QString::number(planet.price));
        ui->treeWidget_planets->addTopLevelItem(table_item);
    }
}

void MainWindow::update_attributes() {
    ui->treeWidget_attrs->clear();
    auto climates_vector = this->database.attributes.DB.to_vector();  // Получаем все климаты
    for (auto &clim_data: climates_vector) {
        QTreeWidgetItem* climate_item = new QTreeWidgetItem(ui->treeWidget_attrs);
        climate_item->setText(0, QString::fromStdString(clim_data.climate));
        auto attrs_vector = clim_data.attrs_tree.to_vector();  // У каждого климата получаем все признаки
        for (auto &attr_data: attrs_vector) {
            QTreeWidgetItem* attr_item = new QTreeWidgetItem();
            attr_item->setText(0, QString::fromStdString(attr_data.attribute));
            auto planets_list = attr_data.planets_list;  // У каждого признака получаем список планет
            for (auto &planet_name: planets_list.to_vector()) {  // Проходимся по каждой планете
                QTreeWidgetItem* planet_item = new QTreeWidgetItem();
                planet_item->setText(0, QString::fromStdString(planet_name));
                attr_item->addChild(planet_item);
            }
            climate_item->addChild(attr_item);
        }
        ui->treeWidget_attrs->addTopLevelItem(climate_item);
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
    auto attrs = this->database.get_planet_attributes(planet_name);
    std::string message_text = "Из справочника \"Признаки\" удалятся следующие зависимые признаки:\n";
    for (auto attr: attrs) {
        message_text += attr.climate + ", " + attr.attribute + "\n";
    }
    message_text += "Вы хотите всё это удалить?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Удаление", QString::fromStdString(message_text), QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->database.remove_planet(planet_name);
        this->update();
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
    std::string attribute = item->parent()->text(0).toStdString();
    std::string climate = item->parent()->parent()->text(0).toStdString();
    this->database.remove_attribute(planet_name, climate, attribute);
    this->update();
}



void MainWindow::on_button_search_clicked()
{
    std::string climate = ui->lineEdit_search_climate->text().toStdString();
    std::string attribute = ui->lineEdit_search_attr->text().toStdString();
    double distance = ui->lineEdit_search_dist->text().toDouble();
    int price = ui->lineEdit_search_cost->text().toInt();

    QString result = QString::fromStdString(this->database.search_to_string(distance, price, climate, attribute));

    ui->textEdit_search->setText(result);
}


void MainWindow::on_button_export_search_clicked()
{
    std::string path = ui->lineEdit_export_search_path->text().toStdString();
    std::ofstream out(path);
    out << ui->textEdit_search->toPlainText().toStdString();
    out.close();
}


void MainWindow::on_pushButton_clicked()
{
    this->log(this->database.planets_to_string());
}


void MainWindow::on_pushButton_2_clicked()
{
    this->log(this->database.attributes_to_string());
}


void MainWindow::on_button_export_log_clicked()
{
    std::string path = ui->lineEdit_export_log_path->text().toStdString();
    std::ofstream out(path);
    out << ui->textEdit_log->toPlainText().toStdString();
    out.close();
}

