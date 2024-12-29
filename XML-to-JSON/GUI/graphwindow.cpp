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
    std::vector<Post*> posts = main_graph->searchTopics(ui->lineEdit->text().toStdString());
    ui->textBrowser->setText("Posts with topic: " + ui->lineEdit->text());
    for(int i = 0; i < posts.size(); i++) {
        ui->textBrowser->append("\n" + QString::fromStdString(posts[i]->body) + "\n");
    }
}


void GraphWindow::on_search_word_clicked()
{

}


void GraphWindow::on_mutual_followers_clicked()
{
    std::vector<int> users_id, mutual;
    QString input = ui->lineEdit->text();
    // Split the string by commas
    QStringList items = input.split(',');
    // Extract integers from input
    for (const QString &item : items) {
        bool valid_int;
        int number = item.toInt(&valid_int);
        // Check if the conversion to int was successful
        if (valid_int) {
            users_id.push_back(number);
        }
    }
    mutual = main_graph->findMutualFollowers(users_id);
    ui->textBrowser->setText("Mutual Followers: ");
    for(int i = 0; i < mutual.size(); i++) {
        ui->textBrowser->append("\nID: " + QString::number(mutual[i]) +
                                "\nName: " + QString::fromStdString(main_graph->getUser(mutual[i])->getName()));
    }
}


void GraphWindow::on_suggest_users_clicked()
{

}


void GraphWindow::on_most_active_clicked()
{
    User* most_active_user = main_graph->mostActive();
    ui->textBrowser->setText("Most Active User:\nID: " +
                             QString::number(most_active_user->getId()) +
                             "\nName: " +
                             QString::fromStdString(most_active_user->getName()));
}


void GraphWindow::on_most_influncer_clicked()
{

}


void GraphWindow::on_draw_graph_clicked()
{

}

