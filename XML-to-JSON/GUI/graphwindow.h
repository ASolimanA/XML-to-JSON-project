#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QString>
#include "Graph.h"

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr, Graph *main_graph = nullptr);
    ~GraphWindow();

private slots:
    void on_search_topic_clicked();

    void on_search_word_clicked();

    void on_mutual_followers_clicked();

    void on_suggest_users_clicked();

    void on_most_active_clicked();

    void on_most_influncer_clicked();

    void on_draw_graph_clicked();

private:
    Ui::GraphWindow *ui;
    Graph* main_graph;
};

#endif // GRAPHWINDOW_H
