#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshObjectListFromSM()));
    timer->start(5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshObjectListFromSM(){ //tutaj powinno być odświeżanie zawartości pamięci dzielonej (w pierwszej wersji, bez obsługi sygnałów do listowania zdarzeń)
    ui->comboBox->addItem("Something");
}
