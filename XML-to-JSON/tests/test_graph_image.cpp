#include <gtest/gtest.h>
#include "Tree.h"
#include "graph.h"

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
        tr.Read_XML("sample.xml");
        g = tr.convert_to_graph();
        
    }
};

TEST_F(GraphTest, TestImage){
    g->dotFile("d.dot");
    g->graphImage("d.dot","image.jpg");
}