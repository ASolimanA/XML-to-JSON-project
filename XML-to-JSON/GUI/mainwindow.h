#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adapter.h"
#include "Tree.h"

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
    void on_fix_clicked();
    void convert_to_json();
    void save_output();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QtAdapter adapter;
    OutputType outputType;
    Validator validator;
    Tree main_tree;
    Graph* main_graph;
    bool converted_to_tree;
    bool converted_to_graph;

    void clearOutput();
    void save_XML();
    void save_JSON();
    void prettify_XML();
    void open_graph_window();
};
#endif // MAINWINDOW_H
