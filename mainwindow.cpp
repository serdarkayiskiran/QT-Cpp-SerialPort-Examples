#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtSerialPort/QSerialPort>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QMessageBox>


QSerialPort *serialPort;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    baglantiAcik=false;
    baglantiKapali=false;


    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }

    ui->portComboBox->addItems(stringPorts);

    QList<qint32> baudRates = QSerialPortInfo::standardBaudRates();
    QList<QString> stringBaudRates;
    for(int i = 0 ; i < baudRates.size() ; i++){
        stringBaudRates.append(QString::number(baudRates.at(i)));
    }
    ui->baudeRateComboBox->addItems(stringBaudRates);

}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::serialPortAc()
{
    serialPort=new QSerialPort;
    serialPort->setPortName(ui->portComboBox->currentText());
    serialPort->setBaudRate(ui->baudeRateComboBox->currentText().toInt());
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    serialPort->open(QIODevice::ReadWrite);
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(veriOku()));

    if(!serialPort->isOpen())
    {
        serialPort->open(QIODevice::ReadWrite);
        ui->durumLabel->setText(serialPort->errorString());
    }

    else
    {
        baglantiAcik=true;
        baglantiKapali=false;
        ui->durumLabel->setText("Bağlantı Kuruldu");
    }
}


void MainWindow::serialPortKapat()
{
    serialPort->close();
    ui->durumLabel->setText("Bağlantı Kesildi");
    baglantiAcik=false;
    baglantiKapali=true;
}


void MainWindow::veriGonder(const QByteArray &veri)
{
    serialPort->write(veri);
    QThread::msleep(100);
}


void MainWindow::veriOku()
{
    const QByteArray veri = serialPort->readAll();
    ui->terminalEkrani->append(veri);
     ui->terminalEkrani->setStyleSheet("color:green");

    if(veri=="1")
    {
        i++;
        ui->gelenVeriADC1->setText(QString::number(i));
    }
    if(veri=="2")
    {
        i++;
        ui->gelenVeriADC2->setText(QString::number(i));
    }
    if(veri=="3")
    {
        i++;
        ui->gelenVeriADC3->setText(QString::number(i));
    }
    if(veri=="4")
    {
        i++;
        ui->gelenVeriADC4->setText(QString::number(i));
    }

}


void MainWindow::on_seriPortAcButon_clicked()
{


    if((baglantiAcik & !baglantiKapali))
    {
        return;
    }

    QPixmap pix(":/ikonlar/ikonlar/baglantiVar.png");
    ui->label_5->setAlignment(Qt::AlignCenter);
    ui->label_5->setPixmap(pix.scaled(ui->label_5->size(),Qt::KeepAspectRatio));

    ui->veriGonderTextBox->clear();
    ui->veriGonderTextBox->setPlaceholderText("Veri giriniz...");
    serialPortAc();
}


void MainWindow::on_seriPortKapatButon_clicked()
{
    if((!baglantiAcik & baglantiKapali))
    {
        return;
    }
    QPixmap pix(":/ikonlar/ikonlar/baglantiYok.png");
    ui->label_5->setAlignment(Qt::AlignCenter);
    ui->label_5->setPixmap(pix.scaled(ui->label_5->size(),Qt::KeepAspectRatio));

    ui->veriGonderTextBox->clear();
    ui->veriGonderTextBox->setPlaceholderText("Bağlantı Yok");
    serialPortKapat();
}


void MainWindow::on_veriGonderButon_clicked()
{
    if(!baglantiAcik)
    {
        ui->veriGonderTextBox->clear();
        ui->veriGonderTextBox->setPlaceholderText("Bağlantı Yok");
        ui->terminalEkrani->append("Bağlantı Yok");
        ui->terminalEkrani->setStyleSheet("color:red");
        return;
    }

    QString veri = ui->veriGonderTextBox->text();
    QByteArray data =veri.toUtf8();
    veriGonder(data);
}


void MainWindow::on_terminalEkranitTemizle_clicked()
{
    ui->terminalEkrani->clear();
}

