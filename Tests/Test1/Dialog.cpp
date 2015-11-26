#include "Dialog.h"
#include "ui_Dialog.h"
#include <QHostAddress>

/**
 * @brief Dialog::Dialog
 * @param parent
 */
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&z21, &Z21LanProtocol::lan_SerialNumber, this, &Dialog::SerialNumber);
    connect(&z21, &Z21LanProtocol::lan_SystemState, this, &Dialog::SystemState);
}

Dialog::~Dialog()
{
    z21.Logoff();
    delete ui;
}

/**
 * @brief Dialog::on_pushButton_clicked
 */
void Dialog::on_pushButton_clicked()
{
    z21.Configure(QHostAddress(ui->host->text()), ui->port->text().toInt());
    z21.SetBroadcastFlags(0x100, 0x100);
    z21.GetSerialNumber();
}

/**
 * @brief Dialog::SerialNumber
 * @param serial
 * @param str
 */
void Dialog::SerialNumber(quint32 serial, const QString &str)
{
    Q_UNUSED(serial);
    ui->serial->setText(str);
}

/**
 * @brief Dialog::SystemState
 * @param ss
 */
void Dialog::SystemState(const Z21SystemState &ss)
{
    ui->mainCurrent->setText(ss.MainCurrent.toString());
    ui->progCurrent->setText(ss.ProgCurrent.toString());
    ui->filteredMainCurrent->setText(ss.FilteredMainCurrent.toString());
    ui->temperature->setText(ss.Temperature.toString());
    ui->supplyVoltage->setText(ss.SupplyVoltage.toString());
    ui->vccVoltage->setText(ss.VCCVoltage.toString());
    ui->centralState->setText(QVariant(ss.CentralState).toString());
    ui->centralStateEx->setText(QVariant(ss.CentralStateEx).toString());
}
