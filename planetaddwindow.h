#ifndef PLANETADDWINDOW_H
#define PLANETADDWINDOW_H

#include <QDialog>

namespace Ui {
class PlanetAddWindow;
}

class PlanetAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PlanetAddWindow(QWidget *parent = nullptr);
    ~PlanetAddWindow();

signals:
    void send_data(std::string planet_name, double distance, int price);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PlanetAddWindow *ui;
};

#endif // PLANETADDWINDOW_H
