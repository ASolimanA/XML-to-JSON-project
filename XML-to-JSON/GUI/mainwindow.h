#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adapter.h"

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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QtAdapter adapter;
};
#endif // MAINWINDOW_H
