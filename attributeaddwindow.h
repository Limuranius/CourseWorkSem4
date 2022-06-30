#ifndef ATTRIBUTEADDWINDOW_H
#define ATTRIBUTEADDWINDOW_H

#include <QDialog>
#include <string>

namespace Ui {
class AttributeAddWindow;
}

class AttributeAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AttributeAddWindow(QWidget *parent = nullptr);
    ~AttributeAddWindow();

signals:
    void send_data(std::string planet_name, std::string climate, std::string attribute);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AttributeAddWindow *ui;
};

#endif // ATTRIBUTEADDWINDOW_H
