#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <Z21LanProtocol.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void SerialNumber(quint32 serial, const QString& str);
    void SystemState(const Z21SystemState& ss);

private:
    Ui::Dialog *ui;
    Z21LanProtocol z21;
};

#endif // DIALOG_H
