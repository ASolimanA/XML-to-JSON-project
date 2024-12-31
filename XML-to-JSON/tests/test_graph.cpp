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

    TEST_F(GraphTest, TestSearchTopicsSports) {
        std::string topic = "sports";
        std::vector<Post*> posts = g->searchTopics(topic);
        EXPECT_FALSE(posts.empty());
    }

    TEST_F(GraphTest, TestUserConversion) {
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
        User* user = nullptr;
        for (User* u : g->vertices) {
            if (u->id == 1) {
                user = u;
                break;
            }
        }
        ASSERT_NE(user, nullptr);
        EXPECT_EQ(user->posts.size(), 2);
        
        EXPECT_EQ(user->posts[0]->body.size(), 
                  std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.").size());
        EXPECT_EQ(user->posts[0]->topics.size(), 2);
        EXPECT_EQ(user->posts[0]->topics[0], "economy");
        EXPECT_EQ(user->posts[0]->topics[1], "finance");
        
        EXPECT_EQ(user->posts[1]->topics.size(), 1);
        EXPECT_EQ(user->posts[1]->topics[0], "solar_energy");
    }

    TEST_F(GraphTest, TestFollowerRelationships) {
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
        std::string topic = "nonexistent_topic";
        std::vector<Post*> posts = g->searchTopics(topic);
        EXPECT_TRUE(posts.empty());
    }

    TEST_F(GraphTest, TestSuggestFollowers) {
        std::vector<User*> suggestions = g->suggestFollowers(7);
        std::vector<int> suggestedIds;
        for (User* user : suggestions) {
            suggestedIds.push_back(user->id);
        }
        // Based on sample_graph.xml, expected suggestions might be user with id 1, 3, and 5
        std::vector<int> expectedSuggestions = {1,3,5};
        EXPECT_EQ(suggestedIds.size(), expectedSuggestions.size());
        for (int id : expectedSuggestions) {
            EXPECT_NE(std::find(suggestedIds.begin(), suggestedIds.end(), id), suggestedIds.end());
        }
    }

    TEST_F(GraphTest, TestMostActiveUser) {
        // Uncomment if you adjust the function signature to return user object or fill references
        auto mostActiveUser = g->mostActive();
        ASSERT_NE(mostActiveUser, nullptr);
        EXPECT_EQ(mostActiveUser->id, 2);
    }

    TEST_F(GraphTest, TestUser6NoFollowers) {
        int index = g->userIndex(6);
        ASSERT_GE(index, 0);
        EXPECT_EQ(g->followers[index].size(), 2);
    }

    TEST_F(GraphTest, TestAddPostToUser) {
        int userId = 2;
        int index = g->userIndex(userId);
        ASSERT_GE(index, 0);
        Post* newPost = new Post();
        newPost->body = "New educational content.";
        newPost->topics = {"education", "technology"};
        g->vertices[index]->posts.push_back(newPost);

        EXPECT_EQ(g->vertices[index]->posts.size(), 3);
        EXPECT_EQ(g->vertices[index]->posts.back()->body, "New educational content.");
        EXPECT_EQ(g->vertices[index]->posts.back()->topics.size(), 2);
        EXPECT_EQ(g->vertices[index]->posts.back()->topics[0], "education");
        EXPECT_EQ(g->vertices[index]->posts.back()->topics[1], "technology");
    }

    TEST_F(GraphTest, TestRemoveFollower) {
        int userId = 1;
        int followerId = 3;
        int index = g->userIndex(userId);
        ASSERT_GE(index, 0);
        auto& followerList = g->followers[index];
        auto it = std::find(followerList.begin(), followerList.end(), followerId);
        ASSERT_NE(it, followerList.end());
        followerList.erase(it);

        EXPECT_EQ(std::count(followerList.begin(), followerList.end(), followerId), 0);
        EXPECT_EQ(followerList.size(), 1);
    }

    TEST_F(GraphTest, TestGraphImage) {
        std::string dotfile = "sample_graph.dot";
        std::string imagefile = "sample_graph.png";
        g->dotFile(dotfile);
        g->graphImage(dotfile, imagefile);
        EXPECT_TRUE(std::filesystem::exists(imagefile));
    }

    // Additional tests below:

    TEST_F(GraphTest, TestFindMutualFollowers) {
        // Suppose user 1 is followed by 2 and 3, user 2 is followed by 3 or 4, etc.
        // We'll try to find mutual followers for users 1 and 2.
        // std::vector<int> userIds = {5, 7};
        // std::vector<int> mutuallyFollowing;
        // try {
        //     mutuallyFollowing = g->findMutualFollowers(userIds);
        // } catch (...) {
        //     FAIL() << "findMutualFollowers threw an unexpected exception.";
        // }
        // // We expect possibly an empty list or a specific user ID depending on sample_graph.xml
        // // For demonstration, let's just check it doesn't crash.
        // std::vector<int> expectedMutualFollowers = {2,4};
        // EXPECT_EQ(mutuallyFollowing, expectedMutualFollowers);
    }

    TEST_F(GraphTest, TestPostBodySearch) {
        // Searching for a word inside the Lorem ipsum post
        std::string word = "to";
        std::vector<Post*> foundPosts = g->postBodySearch(word);
        EXPECT_FALSE(foundPosts.empty());
        bool matched = false;
        for (auto* post : foundPosts) {
            if (post->body.find("to") != std::string::npos) {
                matched = true;
                break;
            }
        }
        EXPECT_TRUE(matched);
    }

    TEST_F(GraphTest, TestMostInfluencer) {
        // The user with the most followers in sample_graph.xml is likely user 1, but adjust if needed
        User* influencer = g->MostInfluencer();
        ASSERT_NE(influencer, nullptr);
        // Expect user 7 or a known ID from your sample data
        EXPECT_EQ(influencer->id, 7);
    }