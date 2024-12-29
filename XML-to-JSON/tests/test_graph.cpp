#include <gtest/gtest.h>
#include "Tree.h"
#include "graph.h"
#include <string>
#include <filesystem>

class GraphTest : public ::testing::Test {
protected:
    Tree tr;
    Graph* g;
    
    GraphTest() {
        tr;    
    }

    void SetUp() override {
        std::string str = tr.fileToString("sample_graph.xml");
        tr.Read_XML(str);
        g = tr.convert_to_graph();
    }

    void TearDown() override {
        delete g;
    }
};

TEST_F(GraphTest, TestIsEmpty) {
    EXPECT_FALSE(g->isEmpty());
}

TEST_F(GraphTest, TestSearchTopicsEconomy) {
    std::string topic = "economy";
    std::vector<Post*> posts = g->searchTopics(topic);
    EXPECT_FALSE(posts.empty());
    for (Post* post : posts) {
        bool found = false;
        for (const std::string& postTopic : post->topics) {
            if (postTopic == topic) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found);
    }
}

TEST_F(GraphTest, TestSearchTopicsSolarEnergy) {
    std::string topic = "solar_energy";
    std::vector<Post*> posts = g->searchTopics(topic);
    EXPECT_FALSE(posts.empty());
    for (Post* post : posts) {
        bool found = false;
        for (const std::string& postTopic : post->topics) {
            if (postTopic == topic) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found);
    }
}

TEST_F(GraphTest, TestUserConversion) {
    // Assuming the XML has a user with id 1 and name "Ahmed Ali"
    User* user = nullptr;
    for (User* u : g->vertices) {
        if (u->id == 1) {
            user = u;
            break;
        }
    }
    ASSERT_NE(user, nullptr);
    EXPECT_EQ(user->name, "Ahmed Ali");
    EXPECT_FALSE(user->marked);
}

TEST_F(GraphTest, TestPostConversion) {
    // Find user with id 1
    User* user = nullptr;
    for (User* u : g->vertices) {
        if (u->id == 1) {
            user = u;
            break;
        }
    }
    ASSERT_NE(user, nullptr);
    // Check number of posts
    EXPECT_EQ(user->posts.size(), 2);
    
    // Check first post
    EXPECT_EQ(user->posts[0]->body.size(), 
              std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.").size());
    EXPECT_EQ(user->posts[0]->topics.size(), 2);
    EXPECT_EQ(user->posts[0]->topics[0], "economy");
    EXPECT_EQ(user->posts[0]->topics[1], "finance");
    
    // Check second post
    EXPECT_EQ(user->posts[1]->topics.size(), 1);
    EXPECT_EQ(user->posts[1]->topics[0], "solar_energy");
}

TEST_F(GraphTest, TestFollowerRelationships) {
    // Assuming user with id 1 has followers with ids 2 and 3
    std::vector<int> expectedFollowers = {2, 3};
    int index = g->userIndex(1);
    ASSERT_GE(index, 0);
    EXPECT_EQ(g->followers[index].size(), expectedFollowers.size());
    for (size_t i = 0; i < expectedFollowers.size(); ++i) {
        EXPECT_EQ(g->followers[index][i], expectedFollowers[i]);
    }
}

TEST_F(GraphTest, TestAddVertex) {
    User* newUser = new User();
    newUser->id = 10;
    newUser->name = "New User";
    g->addVertex(newUser);
    
    int index = g->userIndex(10);
    EXPECT_GE(index, 0);
    EXPECT_EQ(g->vertices[index]->name, "New User");
}

TEST_F(GraphTest, TestMarkAndClearMarks) {
    // Mark a user and verify
    int userId = 1;
    User* user = nullptr;
    for (User* u : g->vertices) {
        if (u->id == userId) {
            user = u;
            break;
        }
    }
    ASSERT_NE(user, nullptr);
    
    g->markVertex(user);
    EXPECT_TRUE(user->marked);
    
    g->clearMarks();
    EXPECT_FALSE(user->marked);
}


TEST_F(GraphTest, TestSearchTopicsHealth) {
    // Test searching for the "health" topic
    std::string topic = "health";
    std::vector<Post*> posts = g->searchTopics(topic);
    EXPECT_FALSE(posts.empty());
    for (Post* post : posts) {
        bool found = false;
        for (const std::string& postTopic : post->topics) {
            if (postTopic == topic) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found);
    }
}

TEST_F(GraphTest, TestSearchTopicsNonexistent) {
    // Test searching for a topic that doesn't exist
    std::string topic = "nonexistent_topic";
    std::vector<Post*> posts = g->searchTopics(topic);
    EXPECT_TRUE(posts.empty());
}

TEST_F(GraphTest, TestSuggestFollowers) {
    // Test suggesting followers for user with id 1
    std::vector<User*> suggestions = g->suggestFollowers(2);
    std::vector<int> suggestedIds;
    for (User* user : suggestions) {
        suggestedIds.push_back(user->id);
    }
    // Based on sample_graph.xml, expected suggestions might be user4 and user5
    std::vector<int> expectedSuggestions = {3};
    EXPECT_EQ(suggestedIds.size(), expectedSuggestions.size());
    for (int id : expectedSuggestions) {
        EXPECT_NE(std::find(suggestedIds.begin(), suggestedIds.end(), id), suggestedIds.end());
    }
}

TEST_F(GraphTest, TestMostActiveUser) {
    int mostActiveId;
    std::string mostActiveName;
    int followerCount;
    g->mostActive(mostActiveId, mostActiveName, followerCount);
    EXPECT_EQ(mostActiveId, 1);
    EXPECT_EQ(mostActiveName, "Ahmed Ali");
    EXPECT_EQ(followerCount, 2);
}

TEST_F(GraphTest, TestUser6NoFollowers) {
    // Test that user with id 6 has no followers
    int index = g->userIndex(6);
    ASSERT_GE(index, 0);
    EXPECT_TRUE(g->followers[index].empty());
}

TEST_F(GraphTest, TestAddPostToUser) {
    // Add a new post to user with id 2 and verify
    int userId = 2;
    int index = g->userIndex(userId);
    ASSERT_GE(index, 0);
    Post* newPost = new Post();
    newPost->body = "New educational content.";
    newPost->topics = {"education", "technology"};
    g->vertices[index]->posts.push_back(newPost);

    // Verify the post was added
    EXPECT_EQ(g->vertices[index]->posts.size(), 2);
    EXPECT_EQ(g->vertices[index]->posts.back()->body, "New educational content.");
    EXPECT_EQ(g->vertices[index]->posts.back()->topics.size(), 2);
    EXPECT_EQ(g->vertices[index]->posts.back()->topics[0], "education");
    EXPECT_EQ(g->vertices[index]->posts.back()->topics[1], "technology");
}

TEST_F(GraphTest, TestRemoveFollower) {
    // Remove follower with id 3 from user with id 1 and verify
    int userId = 1;
    int followerId = 3;
    int index = g->userIndex(userId);
    ASSERT_GE(index, 0);
    auto& followerList = g->followers[index];
    auto it = std::find(followerList.begin(), followerList.end(), followerId);
    ASSERT_NE(it, followerList.end());
    followerList.erase(it);

    // Verify the follower was removed
    EXPECT_EQ(std::count(followerList.begin(), followerList.end(), followerId), 0);
    EXPECT_EQ(followerList.size(), 1);
}

TEST_F(GraphTest, TestGraphImage) {
    // Generate a DOT file and convert it to an image
    std::string dotfile = "sample_graph.dot";
    std::string imagefile = "sample_graph.png";
    g->dotFile(dotfile);
    g->graphImage(dotfile, imagefile);
    EXPECT_TRUE(std::filesystem::exists(imagefile));
}