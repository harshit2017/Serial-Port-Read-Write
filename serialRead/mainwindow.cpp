#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

QSerialPort *port;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    qDebug() << "Number of serial ports:" << QSerialPortInfo::availablePorts().count();

    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        port = new QSerialPort(info);

        qDebug()<<"Name: "<<info.portName();
        qDebug()<<"Description: "<<info.description();
        qDebug()<<"Manufactures: "<<info.manufacturer();



                if (port->open(QIODevice::ReadWrite)) {
                    qDebug() << "Baud rate:" << port->baudRate();
                    qDebug() << "Data bits:" << port->dataBits();
                    qDebug() << "Stop bits:" << port->stopBits();
                    qDebug() << "Parity:" << port->parity();
                    qDebug() << "Flow control:" << port->flowControl();
                    connect(port,SIGNAL(readyRead()),this,SLOT(receiveMsg()));


                } else {
                    qDebug() << "Unable to open port, error code" << port->error();
                }

    }

}

MainWindow::~MainWindow()
{
    delete ui;
    port->close();
}

void MainWindow::receiveMsg(){
   QByteArray msg = port->readAll();
    //do something
    ui->label->setText(msg);
    qDebug()<<msg;
}
