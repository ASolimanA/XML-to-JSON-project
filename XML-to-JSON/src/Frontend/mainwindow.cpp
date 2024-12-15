#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Read, &QPushButton::clicked, this, &MainWindow::print_XML);
    connect(ui->getPath, &QPushButton::clicked, this, &MainWindow::get_file_path);
    ui->comboBox->addItem("Input text");
    ui->comboBox->addItem("File");
}

void MainWindow::get_file_path() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open XML File", "", "XML files (*.xml)");
    ui->textEdit->setText(filePath);
}

void MainWindow::print_XML() {
    if(ui->comboBox->currentText() == "File") {
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
    else if(ui->comboBox->currentText() == "Input text") {
        QString content = ui->input_XML->toPlainText();
        ui->textBrowser->setText(content);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
