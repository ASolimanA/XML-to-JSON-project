#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "validation.h"
#include "ErrorHighlighter.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    adapter = QtAdapter();
    ui->setupUi(this);
    connect(ui->Read, &QPushButton::clicked, this, &MainWindow::print_XML);
    connect(ui->getPath, &QPushButton::clicked, this, &MainWindow::get_file_path);
    connect(ui->verify, &QPushButton::clicked, this, &MainWindow::on_verify_clicked);
    ui->comboBox->addItem("Input text");
    ui->comboBox->addItem("File");
}

void MainWindow::get_file_path() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open XML File", "", "XML files (*.xml)");
    ui->textEdit->setText(filePath);
}

void MainWindow::print_XML() {
    ui->input_XML->clear();
    ui->textBrowser->clear();
    if(ui->comboBox->currentText() == "File") {
        QString filePath = ui->textEdit->toPlainText();
        if (!filePath.isEmpty()) {
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString content = in.readAll();
                ui->input_XML->setPlainText(content);
                ui->Message->setText("");
                file.close();
            }
            else {
                QMessageBox::warning(this, "Error", "Could not open the file for reading.");
            }
        }
        else {
            ui->Message->setText("No file Path");
            ui->Message->setStyleSheet("QLabel { color: red; }");
        }
    }
    else if(ui->comboBox->currentText() == "Input text") {
        QString content = ui->input_XML->toPlainText();
        ui->textBrowser->setText(content);
        ui->Message->setText("");
    }
}
void MainWindow::on_verify_clicked() {
    ui->textBrowser->clear();
    QString content = ui->input_XML->toPlainText();
    Validator validator;
    
    adapter.setVerifyContent(content, &validator);
    if (validator.validate()) {
        ui->Message->setText("XML is valid.");
        ui->Message->setStyleSheet("QLabel { color: green; }");
    }
    else {
        ui->Message->setText("XML is invalid.");
        ui->Message->setStyleSheet("QLabel { color: red; }");
        ErrorHighlighter* errorHighlighter = new ErrorHighlighter(ui->input_XML->document(), &validator);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
