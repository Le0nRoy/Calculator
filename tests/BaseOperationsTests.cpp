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
    // TODO add multiple datasets
    void SetUp() override {
        data = {257, 845};

        expression.addNumber(data.left);
        expression.addNumber(data.right);
    }

    TestData data;
    BinaryOperation expression;
};

TEST_F(SUITE_NAME, SimplePlusTest) {
    expression.addOperator(Operators::PLUS);
    double expected = data.left + data.right;

    double result = expression.evaluate();

    ASSERT_EQ(result, expected);
}

TEST_F(SUITE_NAME, SimpleMinusTest) {
    expression.addOperator(Operators::MINUS);
    double expected = data.left - data.right;

    double result = expression.evaluate();

    ASSERT_EQ(result, expected);
}

TEST_F(SUITE_NAME, SimpleMulTest) {
    expression.addOperator(Operators::MUL);
    double expected = data.left * data.right;

    double result = expression.evaluate();

    ASSERT_EQ(result, expected);
}

TEST_F(SUITE_NAME, SimpleDivTest) {
    expression.addOperator(Operators::DIV);
    double expected = data.left / data.right;

    double result = expression.evaluate();

    ASSERT_EQ(result, expected);
}

TEST_F(SUITE_NAME, NoOperatorExceptionTest) {
    ASSERT_THROW(expression.evaluate(), BinaryOperationException);
}

TEST_F(SUITE_NAME, SecondOperatorExceptionTest) {
    expression.addOperator(Operators::DIV);
    ASSERT_THROW(expression.addOperator(Operators::MUL), BinaryOperationException);
}

TEST_F(SUITE_NAME, ThirdNumberExceptionTest) {
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
}
