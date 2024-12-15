#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Read, &QPushButton::clicked, this, &MainWindow::LoadFile);
    connect(ui->getPath, &QPushButton::clicked, this, &MainWindow::get_file_path);
}

void MainWindow::get_file_path() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open Text File", "", "All Files (*)");
    ui->textEdit->setText(filePath);
}

void MainWindow::LoadFile() {
    QString filePath = ui->textEdit->toPlainText();
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();
            ui->textBrowser->setText(content);
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Could not open the file for reading.");
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
