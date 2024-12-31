#include <gtest/gtest.h>
#include "Tree.h"
#include <fstream>
class TreeTest : public ::testing::Test{
    protected:
        Tree t;

    TreeTest (){
        t;
    }
    void SetUp (){
        std::string str = t.fileToString("validSample.xml");
        t.Read_XML(str);
        
    }
};

// TEST_F(TreeTest,minify_function){
//     t.minify();
//     EXPECT_TRUE(t.minify());
// }
TEST_F(TreeTest, minify_function) {
    std::string minifiedOutput = t.minify();

    std::ofstream outFile("testingtheminify.txt");
    ASSERT_TRUE(outFile.is_open()) << "Failed to open testingtheminify.txt";
    outFile << minifiedOutput;
    outFile.close();

    EXPECT_FALSE(minifiedOutput.empty()); // or any other relevant check
}