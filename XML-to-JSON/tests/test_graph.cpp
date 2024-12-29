#include <gtest/gtest.h>
#include "Tree.h"
#include "graph.h"
#include <string>

class GraphTest : public ::testing::Test {
protected:
    Tree tr;
    Graph* g;
    
    GraphTest() {
        tr;    
    }

    void SetUp() override {
        std::string str = tr.fileToString("sample.xml");
        tr.Read_XML(str);
        g = tr.convert_to_graph();   
    }

    void TearDown() override {
        delete g;
    }
};

TEST_F(GraphTest, TestImage) {
    g->dotFile("d.dot");
    g->graphImage("d.dot","image.jpg");
}

TEST_F(GraphTest, TestIsEmpty) {
    EXPECT_FALSE(g->isEmpty());
}

TEST_F(GraphTest, TestMostActive) {
    int id;
    std::string name;
    int count;
    g->mostActive(id, name, count);
    EXPECT_GT(id, 0);
    EXPECT_FALSE(name.empty());
    EXPECT_GT(count, 0);
}

TEST_F(GraphTest, TestMostInfluencer) {
    User* influencer = g->MostInfluencer();
    EXPECT_NE(influencer, nullptr);
}

TEST_F(GraphTest, TestSearchPosts) {
    std::string topic = "programming";
    std::vector<Post*> posts = g->searchPosts(topic);
    EXPECT_FALSE(posts.empty());
}

TEST_F(GraphTest, TestWordSearch) {
    std::string word = "test";
    std::vector<std::string> matches = g->wordSearch(word);
    EXPECT_NO_THROW(g->wordSearch(word));
}

TEST_F(GraphTest, TestSuggestFollowers) {
    int testUserId = 1;
    std::vector<User*> suggestions = g->suggestFollowers(testUserId);
    EXPECT_NO_THROW(g->suggestFollowers(testUserId));
}

TEST_F(GraphTest, TestFindMutualFollowers) {
    std::vector<int> userIds = {1, 2};
    std::vector<int> mutual = g->findMutualFollowers(userIds);
    EXPECT_NO_THROW(g->findMutualFollowers(userIds));
}

TEST_F(GraphTest, TestUserIndex) {
    int validId = 1;
    int invalidId = -1;
    EXPECT_GE(g->userIndex(validId), 0);
    EXPECT_EQ(g->userIndex(invalidId), -1);
}

TEST_F(GraphTest, TestClearMarks) {
    EXPECT_NO_THROW(g->clearMarks());
}