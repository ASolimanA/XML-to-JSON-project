#include <gtest/gtest.h>
#include "Tree.h"
#include "graph.h"
#include <string>

class GraphTest : public ::testing::Test {
protected:
    
//read from tree 
//convert to graph
    Tree tr;
    Graph* g;
    GraphTest(){
        tr;    
    }

    void SetUp() override {
        std::string str = tr.fileToString("sample.xml");
        tr.Read_XML(str);
        g = tr.convert_to_graph();   
    }
};

TEST_F(GraphTest, TestImage){
    g->dotFile("d.dot");
    g->graphImage("d.dot","image.jpg");
}