//
// Created by cerbe on 13.01.2021.
//

#include "gtest/gtest.h"
#include "include/Expression.h"

#define SUITE_NAME AnyTests

struct TestData {
    double left;
    double right;
};

struct SUITE_NAME : ::testing::Test {
protected:
    void PrepareTestData() {
        testData = {
                {257,       845},
                {0,         1},
                {1,         0},
                {124.9878,  89},
                {9090.9090, 8080.8080},
                {0,         0}
        };
    }

    void SetUp() override {
        PrepareTestData();
    }

    std::vector<TestData> testData;
};

TEST_F(SUITE_NAME, SimplePlusTest) {
    for (auto data : testData) {
        BinaryOperation expression;
        expression.addNumber(data.left);
        expression.addNumber(data.right);
        expression.addOperator(Operators::PLUS);
        double expected = data.left + data.right;

        double result = expression.evaluate();

        EXPECT_EQ(result, expected);
    }
}

TEST_F(SUITE_NAME, SimpleMinusTest) {
    for (auto data : testData) {
        BinaryOperation expression;
        expression.addNumber(data.left);
        expression.addNumber(data.right);
        expression.addOperator(Operators::MINUS);
        double expected = data.left - data.right;

        double result = expression.evaluate();

        EXPECT_EQ(result, expected);
    }
}

TEST_F(SUITE_NAME, SimpleMulTest) {
    for (auto data : testData) {
        BinaryOperation expression;
        expression.addNumber(data.left);
        expression.addNumber(data.right);
        expression.addOperator(Operators::MUL);
        double expected = data.left * data.right;

        double result = expression.evaluate();

        EXPECT_EQ(result, expected);
    }
}

TEST_F(SUITE_NAME, SimpleDivTest) {
    for (auto data : testData) {
        BinaryOperation expression;
        expression.addNumber(data.left);
        expression.addNumber(data.right);
        expression.addOperator(Operators::DIV);
        if (data.right == 0) {
            ASSERT_THROW(expression.evaluate(), BinaryOperationException);
        } else {
            double expected = data.left / data.right;

            double result = expression.evaluate();

            EXPECT_EQ(result, expected);
        }
    }
}

TEST_F(SUITE_NAME, NoOperatorExceptionTest) {
    BinaryOperation expression;
    ASSERT_THROW(expression.evaluate(), BinaryOperationException);
}

TEST_F(SUITE_NAME, SecondOperatorExceptionTest) {
    BinaryOperation expression;
    expression.addOperator(Operators::DIV);
    ASSERT_THROW(expression.addOperator(Operators::MUL), BinaryOperationException);
}

TEST_F(SUITE_NAME, ThirdNumberExceptionTest) {
    BinaryOperation expression;
    expression.addNumber(testData.cbegin()->left);
    expression.addNumber(testData.cbegin()->right);
    expression.addOperator(Operators::PLUS);
    ASSERT_THROW(expression.addNumber(12), BinaryOperationException);
}

/* FIXME
    All tests in the same test suite must use the same test fixture
    class, so mixing TEST_F and TEST in the same test suite is
    illegal.  In test suite AnyTests,
    test SimplePlusTest is defined using TEST_F but
    test NotEnoughNumbersExceptionTest is defined using TEST.  You probably
    want to change the TEST to TEST_F or move it to another test
    case.

    Current solution not best I suppose
 */
TEST_F(SUITE_NAME, NotEnoughNumbersExceptionTest) {
    BinaryOperation expr;
    expr.addOperator(Operators::DIV);
    ASSERT_THROW(expr.evaluate(), BinaryOperationException);
    expr.addNumber(1);
    ASSERT_THROW(expr.evaluate(), BinaryOperationException);
    expr.addNumber(1);
    ASSERT_NO_THROW(expr.evaluate());
}
