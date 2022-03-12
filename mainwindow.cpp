#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <KCompressionDevice>
#include <KZip>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QDir>


QString fileName;

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

void compressToZip(){
    QFileInfo localFile(fileName);
    QString name = localFile.fileName();

    KZip archive(QStringLiteral("test.zip"));

    // Open our archive for writing
    if (archive.open(QIODevice::WriteOnly)) {
        // The archive is open, we can now write data
        archive.addLocalFile(name,name);
        // Don't forget to close!
        archive.close();
    }
}

void uncompressFromZip(){
    QString file(fileName);
    KZip archive(file);

    if(!archive.open(QIODevice::ReadOnly)){
        qWarning("Can't open");
        exit(1);
    }

    const KArchiveDirectory *root = archive.directory();
    QString destination = QDir::currentPath();
    bool recursive = true;
    root->copyTo(destination,recursive);

    archive.close();
}





void MainWindow::on_pushButton_clicked()
{
    fileName = ui->plainTextEdit->toPlainText();
    compressToZip();
}


void MainWindow::on_pushButton_2_clicked()
{
    fileName = ui->plainTextEdit->toPlainText();
    uncompressFromZip();
}

