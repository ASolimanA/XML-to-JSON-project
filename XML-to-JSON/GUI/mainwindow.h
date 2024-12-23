#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adapter.h"

typedef enum {none, containError ,xml, json} OutputType;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void print_XML();
    void get_file_path();
    void on_verify_clicked();
    void save_output();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QtAdapter adapter;
    OutputType outputType;

    void clearOutput();
    void save_XML();
    void save_JSON();
    void prettify_XML();
};
#endif // MAINWINDOW_H
