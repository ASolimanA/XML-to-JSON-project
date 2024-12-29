#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GraphWindow)
{
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

