#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphwindow.h"
#include "compress-decompress.h"
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    adapter = QtAdapter();
    main_tree = Tree();
    outputType = none;
    converted_to_tree = false;
    converted_to_graph = false;
    ui->setupUi(this);
    setConnections();
    errorHighlighter = new ErrorHighlighter(ui->textBrowser->document());
}

void MainWindow::setConnections() {
    connect(ui->Read, &QPushButton::clicked, this, &MainWindow::Read_File);
    connect(ui->getPath, &QPushButton::clicked, this, &MainWindow::get_file_path);
    connect(ui->verify, &QPushButton::clicked, this, &MainWindow::on_verify_clicked);
    connect(ui->fix, &QPushButton::clicked, this, &MainWindow::on_fix_clicked);
    connect(ui->Save_File, &QPushButton::clicked, this, &MainWindow::save_output);
    connect(ui->convert, &QPushButton::clicked, this, &MainWindow::convert_to_json);
    connect(ui->graph_analysis, &QPushButton::clicked, this, &MainWindow::open_graph_window);
    connect(ui->pretty, &QPushButton::clicked, this, &MainWindow::prettify_XML);
    connect(ui->compress, &QPushButton::clicked, this, &MainWindow::compress_XML);
    connect(ui->decompress, &QPushButton::clicked, this, &MainWindow::decompress_XML);
    connect(ui->minify, &QPushButton::clicked, this, &MainWindow::on_minify_clicked);
}

void MainWindow::get_file_path() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open XML File", "", "XML files (*.xml)");
    ui->lineEdit->setText(filePath);
}

void MainWindow::Read_File() {
    ui->input_XML->clear();
    clearOutput();
    QString filePath = ui->lineEdit->text();
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
void MainWindow::on_verify_clicked() {
    clearOutput(); // Clear the output before verifying
    QString content = ui->input_XML->toPlainText();
    if (content.isEmpty())
        return;
    ui->textBrowser->setText(content);
    adapter.setVerifyContent(content, &validator);
    if (validator.validate()) {
        ui->Message->setText("XML is valid.");
        ui->Message->setStyleSheet("QLabel { color: green; }");
        outputType = xml;
        errorHighlighter->setHighlights(&validator);
    }
    else {
        ui->Message->setText("XML is invalid.");
        ui->Message->setStyleSheet("QLabel { color: red; }");
        outputType = containError;
        errorHighlighter->setHighlights(&validator);
    }
}

void MainWindow::on_fix_clicked()
{
    if(outputType == containError) {
        validator.fix();
        clearOutput();
        ui->textBrowser->setText(adapter.getfilecontent(&validator));
        validator.validate();
        errorHighlighter->setHighlights(&validator);
        outputType = xml;
        ui->Message->setText("Fixed Successfully.");
        ui->Message->setStyleSheet("QLabel { color: green; }");
    }
}

void MainWindow::prettify_XML() {
    if(outputType == xml) { // Only prettify if the output is XML

        if (!converted_to_tree) { // Convert the XML to a tree if not already done
            main_tree.Read_XML(adapter.to_string(ui->textBrowser->toPlainText()));
            converted_to_tree = true;
        }

        // Prettify the tree and display it in the text browser
        string prettified = main_tree.prettierFunction();
        ui->textBrowser->setText(adapter.to_qstring(prettified));
        ui->Message->setText("Prettified Successfully.");
        ui->Message->setStyleSheet("QLabel { color: green; }");

    } else if (outputType == none) { // If there is no output to prettify
        ui->Message->setText("You need to verify an XML file first.");
        ui->Message->setStyleSheet("QLabel { color: red; }");
    }

    else if (outputType == containError) { // If the output contains errors
        QMessageBox::warning(this, "Error", "Cannot prettify the output as it contains errors.");
    }
}

void MainWindow::convert_to_json() {
    if(outputType == xml) {
        if(!converted_to_tree) {
            main_tree.Read_XML(adapter.to_string(ui->textBrowser->toPlainText()));
            converted_to_tree = true;
        }
        ui->textBrowser->setText(adapter.to_qstring(main_tree.to_json()));
        ui->Message->setText("Converted Successfully.");
        ui->Message->setStyleSheet("QLabel { color: green; }");
        outputType = json;
    }
}

void MainWindow::save_output() {
    if (outputType == none) {
        QMessageBox::warning(this, "Error", "No output to save.");
    }
    else if (outputType == containError) {
        QMessageBox::warning(this, "Error", "Cannot save the output as it contains errors.");
    }
    else if (outputType == xml) {
        save_XML();
    }
    else if (outputType == json) {
        save_JSON();
    }
}

void MainWindow::save_XML() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save XML File", "", "XML files (*.xml)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textBrowser->toPlainText();
            file.close();
            QMessageBox::information(this, "Success", "XML file saved successfully.");
        }
        else {
            QMessageBox::warning(this, "Error", "Could not write the file.");
        }
    }
    else {
        QMessageBox::warning(this, "Error", "No file path provided.");
    }
}

void MainWindow::save_JSON() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save JSON File", "", "JSON files (*.json)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textBrowser->toPlainText();
            file.close();
            QMessageBox::information(this, "Success", "JSON file saved successfully.");
        }
        else {
            QMessageBox::warning(this, "Error", "Could not write the file.");
        }
    }
    else {
        QMessageBox::warning(this, "Error", "No file path provided.");
    }
}

void MainWindow::open_graph_window() {
    if(outputType == xml) {
        if(!converted_to_graph) {
            if(!converted_to_tree) {
                main_tree.Read_XML(adapter.to_string(ui->textBrowser->toPlainText()));
                converted_to_tree = true;
            }
            main_graph = main_tree.convert_to_graph();
            converted_to_graph = true;
        }
        GraphWindow* g = new GraphWindow(this, main_graph);
        g->show();
    } else {
        ui->Message->setText("Cannot open the graph window as the XML is not yet verified.");
        ui->Message->setStyleSheet("QLabel { color: red; }");
    }
}

// void MainWindow::on_minify_clicked() {
//     if(outputType == xml) {
//         string minified_xml = minify(adapter.to_string(ui->textBrowser->toPlainText()));
//         ui->textBrowser->setText(adapter.to_qstring(minified_xml));
//         ui->Message->setText("Minified Successfully.");
//         ui->Message->setStyleSheet("QLabel { color: green; }");
//     }
//     else if (outputType == none) { // If there is no output to prettify
//         ui->Message->setText("You need to verify an XML file first.");
//         ui->Message->setStyleSheet("QLabel { color: red; }");
//     }
//     else if (outputType == containError) { // If the output contains errors
//         QMessageBox::warning(this, "Error", "Cannot Minify the output as it contains errors.");
//     }
// }

void MainWindow::compress_XML() {
    // Check if the output is a valid XML
    if (outputType == xml) {
        // Get the file path to save the compressed file
        QString compressFilePath = QFileDialog::getSaveFileName(this, "Save Compressed File", "", "Compressed File (*.comp)");
        
        // Compress the XML content and save it to the file
        compress(adapter.to_string(ui->textBrowser->toPlainText()), adapter.to_string(compressFilePath));
        
        // Display a success message
        ui->Message->setText("Compressed Successfully.");
        ui->Message->setStyleSheet("QLabel { color: green; }");
    } else {
        // Display an error message if the output is not a valid XML
        ui->Message->setText("Cannot compress the output as it is not a valid XML.");
        ui->Message->setStyleSheet("QLabel { color: red; }");
    }
}

void  MainWindow::decompress_XML() {
    QString decompressFilePath = QFileDialog::getOpenFileName(this, "Open Compressed File", "", "Compressed File (*.comp)");
    
    // Check if the file path is not empty
    if (!decompressFilePath.isEmpty()) {
    
        // Decompress the file
        string decompressed = decompress(adapter.to_string(decompressFilePath));

        // Display the decompressed content
        main_tree.Read_XML(decompressed);
        converted_to_tree = true;
        // Use prettier function before displaying
        QString qdecompressed = adapter.to_qstring(main_tree.prettierFunction());
        ui->textBrowser->setText(qdecompressed);
        ui->input_XML->setPlainText(qdecompressed);

        // Display a success message
        ui->Message->setText("Decompressed Successfully.");
        ui->Message->setStyleSheet("QLabel { color: green; }");
    } else {
        // Display an error message if the file path is empty
        ui->Message->setText("No file path provided.");
        ui->Message->setStyleSheet("QLabel { color: red; }");
    }
}

void MainWindow::clearOutput() {
    ui->textBrowser->clear();
    converted_to_tree = false;
    converted_to_graph = false;
    outputType = none;
    ui->Message->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}



