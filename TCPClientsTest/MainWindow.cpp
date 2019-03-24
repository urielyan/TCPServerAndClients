#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "TCPClients.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TCPClients *client = new TCPClients(this);
    //client.
}

MainWindow::~MainWindow()
{
    delete ui;
}
