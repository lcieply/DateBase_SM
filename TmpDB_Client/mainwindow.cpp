#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "SMSystem.h"
#include <QDebug>
#include <QMessageBox>

using namespace sm;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    int work = 1;
    if(this->system.contains(ui->lineEdit_3->text().toLatin1())){
        QMessageBox msgBox;
        msgBox.setWindowTitle("SMSystem");
        msgBox.setText("Object with this key exist in SMSystem!");
        msgBox.setInformativeText("Do you want to replace it?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        //msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Save){
            work = 2;
        }else{
            work = 0;
        }
    }if(work){
        if(ui->comboBox_2->currentText() == "int"){
            SMType <int> element(ui->lineEdit->text().toInt());
                try{
                if(work==1)
                    this->system.insert(ui->lineEdit_3->text().toLatin1(), &element);
                else
                    this->system.update(ui->lineEdit_3->text().toLatin1(), &element);
                }catch(...){
                    qDebug() << "ERROR";
                }
                ui->lineEdit->clear();
                ui->lineEdit_3->clear();
        }else if(ui->comboBox_2->currentText() == "char"){
            SMType <char> element(ui->lineEdit->text().at(0).toLatin1());
                try{
                if(work==1)
                    this->system.insert(ui->lineEdit_3->text().toLatin1(), &element);
                else
                    this->system.update(ui->lineEdit_3->text().toLatin1(), &element);
                }catch(...){
                    qDebug() << "ERROR";
                }
                ui->lineEdit->clear();
                ui->lineEdit_3->clear();
        }else{
            SMType <float> element(ui->lineEdit->text().toFloat());
                try{
                if(work==1)
                    this->system.insert(ui->lineEdit_3->text().toLatin1(), &element);
                else
                    this->system.update(ui->lineEdit_3->text().toLatin1(), &element);
                }catch(...){
                    qDebug() << "ERROR";
                }
                ui->lineEdit->clear();
                ui->lineEdit_3->clear();
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    if(!this->system.contains(ui->lineEdit_3->text().toLatin1())){
        QMessageBox msgBox;
        msgBox.setWindowTitle("SMSystem");
        msgBox.setText("Object with this key doesn't exist!");
        msgBox.setInformativeText("Maybe you press wrong button?");
        //msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }else{
        if(ui->comboBox_2->currentText() == "int"){
            SMType <int> element;
                try{
                    this->system.fetch(ui->lineEdit_3->text().toLatin1(), element);
                    QString str = QString::number(element.val);
                    ui->listWidget_2->addItem(str);
                    ui->lineEdit_3->clear();
                   }catch(...){
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("SMSystem");
                        msgBox.setText("Wrong type");
                        msgBox.setInformativeText("Probably you choose wrong type of object");
                        msgBox.exec();
                }
        }else if(ui->comboBox_2->currentText() == "char"){
            SMType <char> element;
                try{
                    this->system.fetch(ui->lineEdit_3->text().toLatin1(), element);
                    QString str(element.val);
                    ui->listWidget_2->addItem(str);
                    ui->lineEdit_3->clear();
                   }catch(...){
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("SMSystem");
                        msgBox.setText("Wrong type");
                        msgBox.setInformativeText("Probably you choose wrong type of object");
                        msgBox.exec();
                }
        }else{
            SMType <float> element;
                try{
                    this->system.fetch(ui->lineEdit_3->text().toLatin1(), element);
                    QString str = QString::number(element.val);
                    ui->listWidget_2->addItem(str);
                    ui->lineEdit_3->clear();
                   }catch(...){
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("SMSystem");
                        msgBox.setText("Wrong type");
                        msgBox.setInformativeText("Probably you choose wrong type of object");
                        msgBox.exec();
                }
        }
    }
}
