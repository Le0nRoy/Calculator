//
// Created by cerbe on 13.01.2021.
//

#include "Test.h"
#include "include/Expression.h"

#define SUITE_NAME AnyTests

struct TestData {
    TestData(double left, double right) :
    left(left), right(right) {}

    double getLeft() const {
        return left;
    }

    double getRight() const {
        return right;
    }

private:
    double left;
    double right;
};

struct SUITE_NAME : ::testing::Test {
protected:
    void PrepareTestData() {
        testData = {
                std::make_shared<TestData>(257,       845),
                std::make_shared<TestData>(0,         1),
                std::make_shared<TestData>(1,         0),
                std::make_shared<TestData>(124.9878,  89),
                std::make_shared<TestData>(9090.9090, 8080.8080),
                std::make_shared<TestData>(0,         0)
        };
    }

    void SetUp() override {
        PrepareTestData();
    }

    std::vector<std::shared_ptr<TestData>> testData;
};

TEST_F(SUITE_NAME, SimplePlusTest) {
    for (auto data : testData) {
        BinaryOperation expression(Number(data->getLeft()), Number(data->getRight()), '+');
        double expected = data->getLeft() + data->getRight();

        double result = expression.evaluate();

        EXPECT_EQ(result, expected);
    }
}

TEST_F(SUITE_NAME, SimpleMinusTest) {
    for (auto data : testData) {
        BinaryOperation expression(Number(data->getLeft()), Number(data->getRight()), '-');
        double expected = data->getLeft() - data->getRight();

        double result = expression.evaluate();

        EXPECT_EQ(result, expected);
    }
}

TEST_F(SUITE_NAME, SimpleMulTest) {
    for (auto data : testData) {
        BinaryOperation expression(Number(data->getLeft()), Number(data->getRight()), '*');
        double expected = data->getLeft() * data->getRight();

        double result = expression.evaluate();

        EXPECT_EQ(result, expected);
    }
}

TEST_F(SUITE_NAME, SimpleDivTest) {
    for (auto data : testData) {
        BinaryOperation expression(Number(data->getLeft()), Number(data->getRight()), '/');
        if (data->getRight() == 0) {
            ASSERT_THROW(expression.evaluate(), BinaryOperationException);
        } else {
            double expected = data->getLeft() / data->getRight();

            double result = expression.evaluate();

            EXPECT_EQ(result, expected);
        }
    }
}

TEST(PPCAT(Special, SUITE_NAME), WrongOperatorExceptionTest) {
    ASSERT_THROW(BinaryOperation expression(Number(1), Number(2), '_'),
                 BinaryOperationException);
}
