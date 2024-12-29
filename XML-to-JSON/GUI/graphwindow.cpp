#include "graphwindow.h"
#include "ui_graphwindow.h"
#include <vector>
#include <QDesktopServices>
#include <qfiledialog.h>

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
    QString word = ui->lineEdit->text();
    if (word.isEmpty()) return;
    std::vector<Post*> matchedPosts = main_graph->postBodySearch(word.toStdString());
    QString output;
    for (int i = 1; i <= matchedPosts.size(); i++) {
        output += QString("Post " + QString::number(i) + ":\n");
        output += "Body: " + QString::fromStdString(matchedPosts[i-1]->body) + "\n";
        output+= QString("Topics: ");
        for (const std::string& topic : matchedPosts[i-1]->topics) {
            output+= QString::fromStdString(topic + ", ");
        }
        output+= "\n\n";
    }
    if (matchedPosts.empty()) {
        output = "No posts found with the word: " + word;
    }
    ui->textBrowser->setText(output);
}


void GraphWindow::on_mutual_followers_clicked()
{

}


void GraphWindow::on_suggest_users_clicked()
{
    QString id = ui->lineEdit->text();
    if (id.isEmpty()) return;
    std::vector<User*> suggestions = main_graph->suggestFollowers(id.toInt());
    QString output;
    for (User* user : suggestions) {
        output += "User ID: " + QString::number(user->id) + "\n";
        output += "User Name: " + QString::fromStdString(user->name) + "\n\n";
    }
    if (suggestions.empty()) {
        output = "No suggestions found for user with ID: " + id;
    }
    ui->textBrowser->setText(output);
}


void GraphWindow::on_most_active_clicked()
{

}


void GraphWindow::on_most_influncer_clicked()
{
    User * mostInfluencer = main_graph->MostInfluencer();
    QString output;
    output += "Most Influencer Name: " + QString::fromStdString(mostInfluencer->name) + "\n";
    output += "Most Influencer ID: " + QString::number(mostInfluencer->id) + "\n";
    ui->textBrowser->setText(output);
}


void GraphWindow::on_draw_graph_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Graph Image", "", "JPG (*.jpg)");
    main_graph->dotFile("sample_graph.dot");
    ui->textBrowser->setText("Saving Graph image...");
    main_graph->graphImage("sample_graph.dot", filePath.toStdString());
    ui->textBrowser->setText("Graph image saved successfully.");
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}