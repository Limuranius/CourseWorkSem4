#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_files_page_triggered();

    void on_action_planets_page_triggered();

    void on_action_attributes_page_triggered();

    void on_action_search_page_triggered();

    void on_action_errors_page_triggered();

private:
    Ui::MainWindow *ui;

    QString ask_file_path_read();

    QString ask_file_path_write();
};
#endif // MAINWINDOW_H