#include <gtest/gtest.h>
#include "validation.h"

class ValidatorTest : public ::testing::Test {
protected:
    Validator validator;

    ValidatorTest() : validator("sample.xml") {}

    void SetUp() override {
        validator.readFile();
        validator.validate();
    }
};

TEST_F(ValidatorTest, TestFilePath) {
    EXPECT_TRUE(validator.filePath_valid());
}

TEST_F(ValidatorTest, TestValidationResult) {
    // Assuming sample.xml contains errors
    EXPECT_FALSE(validator.validate());
}

TEST_F(ValidatorTest, TestErrorTypes) {
    // Types of expected errors
    std::vector<char> expected_error_types = {'c','o','o','c'};
    EXPECT_EQ(validator.get_error_types(), expected_error_types);
}

TEST_F(ValidatorTest, TestErrorPositions) {
    // Positions of expected errors
    std::vector<std::array<int,2>> expected_vec = {{6,7},{6,14},{17,24},{36,22}};
    EXPECT_EQ(validator.get_error_places(), expected_vec);
}
TEST_F(ValidatorTest, TestErrorList) {
    // Expected error list
    std::vector<std::pair<std::string, std::array<int,2>>> expected_error_list = {
        {"/name", {6,7}},
        {"body", {6,14}},
        {"post", {17,24}},
        {"/follower", {36,22}}
    };
    EXPECT_EQ(validator.get_error_list(), expected_error_list);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
