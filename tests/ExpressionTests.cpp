//
// Created by lap on 9/26/20.
//

#include "gtest/gtest.h"
#include "include/Expression.h"

#define SUITE_NAME ExpressionTests

struct TestData {
    std::string exprString;
    double expectedResult;
};

struct SUITE_NAME : ::testing::Test {
protected:
    void SetUp() override {
        PrepareTestData();
    }

    std::list<TestData> testData;

private:
    void PrepareTestData() {
        testData = {
                {"1 + 2 + 3", (1 + 2 + 3)},
                {"20.6 * 12 - 40", (20.6 * 12 - 40)},
                {"208.999 / 88 * 20", (208.999 / 88 * 20)},
                {"50 + 5 * 2", (50 + 5 * 2)},
                {"(50 + 5) * 2", ((50 + 5) * 2)},
                {"(200 - 49.9) / 2 + 10", ((200 - 49.9) / 2 + 10)},
                {"(200 - 49.9) / (2 + 10)", ((200 - 49.9) / (2 + 10))},
                {"1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5))", (1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5)))}
        };
    }
};

TEST_F(SUITE_NAME, SimpleExpressionsTest) {
    double result;
    size_t cnt = 0;

    for (auto data : testData) {
        Expression expression(data.exprString);
        expression.parseExpression();
        result = expression.getResult();

        EXPECT_EQ(data.expectedResult, result) << "Test iteration: " << cnt;
        ++cnt;
    }
}
