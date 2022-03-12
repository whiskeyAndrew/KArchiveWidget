#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <KCompressionDevice>
#include <KZip>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>


QString fileName; //директория файла

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void compressToZip(){ //Сжималка
    QFileInfo localFile(fileName); //берем информацию о файле, ниже в переменную запишем её имя, пока нам этого достаточно будет
    QString name = localFile.fileName();//имя файла, передадим в archive.addLocalFile

    KZip archive(QStringLiteral("test.zip")); //Создаем пустой архив

    if (archive.open(QIODevice::WriteOnly)) { //Открываем архив
        archive.addLocalFile(name,name); //Создаем файл внутри архива, метод переносит данные из исходного файла и его имя
        archive.close(); //Закрываем архив
    }
}

void uncompressFromZip(){ //Разжималка
    QString localFile(fileName); //берем файл, его название передадим в переменную archive
    KZip archive(localFile);

    if(!archive.open(QIODevice::ReadOnly)){ //Открываем архив
        qWarning("Can't open");
        exit(1);
    }

    const KArchiveDirectory *root = archive.directory(); //Новый файл из архива будет создан в корне приложения
    QString destination = QDir::currentPath();
    bool recursive = true;
    root->copyTo(destination,recursive);

    archive.close(); //Не забываем закрыть архив
}

void MainWindow::on_pushButton_3_clicked()
{
    fileName = QFileDialog::getOpenFileName(); //Верхняя кнопка, открывает диалоговое окно для выбора файла
    ui->label->setText(fileName); //Перенесем в лейбл, чтобы пользователь видел какой файл он открыл
}

void MainWindow::on_pushButton_clicked()
{    
    compressToZip(); //Кнопка сжать
}


void MainWindow::on_pushButton_2_clicked()
{    
    uncompressFromZip(); //Кнопка разжать
}




