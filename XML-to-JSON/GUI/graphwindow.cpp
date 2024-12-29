#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent, Graph* main_graph)
    : QDialog(parent)
    , ui(new Ui::GraphWindow)
{
    this->main_graph = main_graph;
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}


void GraphWindow::on_search_topic_clicked()
{

}


void GraphWindow::on_search_word_clicked()
{

}


void GraphWindow::on_mutual_followers_clicked()
{

}


void GraphWindow::on_suggest_users_clicked()
{

}


void GraphWindow::on_most_active_clicked()
{

}


void GraphWindow::on_most_influncer_clicked()
{

}


void GraphWindow::on_draw_graph_clicked()
{

}

