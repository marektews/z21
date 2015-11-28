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
    connect(&z21, &Z21LanProtocol::lan_HardwareInfo, this, &Dialog::HardwareInfo);
    connect(&z21, &Z21LanProtocol::xbus_Version, this, &Dialog::XBus_Version);
    connect(&z21, &Z21LanProtocol::xbus_FirmwareVersion, this, &Dialog::XBus_FirmwareVersion);
}

Dialog::~Dialog()
{
    z21.Send_Logoff();
    delete ui;
}

/**
 * @brief Dialog::on_pushButton_clicked
 */
void Dialog::on_pushButton_clicked()
{
    ui->pushButton->setDisabled(true);
    z21.Configure(QHostAddress(ui->host->text()), ui->port->text().toInt());
    z21.Send_SetBroadcastFlags(0x100, 0x100);
    z21.Send_GetSerialNumber();
    z21.Send_GetHardwareInfo();
    z21.Send_XBus_GetVersion();
    z21.Send_XBus_GetFirmwareVersion();
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
    ui->mainCurrent->setText(ss.MainCurrent.toString(true));
    ui->progCurrent->setText(ss.ProgCurrent.toString(true));
    ui->filteredMainCurrent->setText(ss.FilteredMainCurrent.toString(true));
    ui->temperature->setText(ss.Temperature.toString(true));
    ui->supplyVoltage->setText(ss.SupplyVoltage.toString(true));
    ui->vccVoltage->setText(ss.VCCVoltage.toString(true));
    ui->centralState->setText(ss.CentralState.toString());
}

/**
 * @brief Dialog::HardwareInfo
 * @param hardwareType
 * @param firmwareVersion
 */
void Dialog::HardwareInfo(quint32 hardwareType, quint32 firmwareVersion)
{
    QString hwType;
    switch(hardwareType)
    {
    case 0x0200:    hwType = "Z21 (Variant from 2012)"; break;
    case 0x0201:    hwType = "Z21 (Variant from 2013)"; break;
    case 0x0202:    hwType = "SmartRail (from 2012)"; break;
    case 0x0203:    hwType = "Z21 Startset (Variant from 2012)"; break;
    }

    ui->hw_type->setText(hwType);
    ui->fw_version->setText(QString().sprintf("%x.%x", firmwareVersion>>8, firmwareVersion&0xFF));
}

/**
 * @brief Dialog::XBus_Version
 * @param version
 * @param centralID
 */
void Dialog::XBus_Version(quint8 version, quint8 centralID)
{
    QString central;
    switch(centralID)
    {
    default: central.sprintf("%x", centralID); break;
    case 0x12: central = "Z21"; break;
    }
    ui->xbus_version->setText(QString::asprintf("%x.%x", version>>4, version&0x0F) + " (" + central + ')');
}

/**
 * @brief Dialog::XBus_FirmwareVersion
 * @param msb
 * @param lsb
 * @param fv
 */
void Dialog::XBus_FirmwareVersion(quint8 msb, quint8 lsb, const QString &fv)
{
    Q_UNUSED(msb); Q_UNUSED(lsb);
    ui->xbus_fv->setText(fv);
}
