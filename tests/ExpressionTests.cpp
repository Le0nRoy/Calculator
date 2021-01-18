//
// Created by lap on 9/26/20.
//

#include "Test.h"

#include "include/Expression.h"
#include <memory>

#define SUITE_NAME ExpressionTests

struct TestData {
    TestData(std::string str, double expectedResult) :
            expectedResult(expectedResult),
            exprString(std::move(str)) {
    };

    const std::string &getExprString() const {
        return exprString;
    }

    double getExpectedResult() const {
        return expectedResult;
    }

private:
    std::string exprString;
    double expectedResult;
};

struct SUITE_NAME : ::testing::Test {
protected:
    void SetUp() override {
        PrepareTestData();
    }

    std::vector<std::shared_ptr<TestData>> testData;

private:
    void PrepareTestData() {
        testData = {
                std::make_shared<TestData>("1 + 2 + 3", (1 + 2 + 3)),
                std::make_shared<TestData>("20.6 * 12 - 40", (20.6 * 12 - 40)),
                std::make_shared<TestData>("208.999 / 88 * 20", (208.999 / 88 * 20)),
                std::make_shared<TestData>("50 + 5 * 2", (50 + 5 * 2)),
                std::make_shared<TestData>("(50 + 5) * 2", ((50 + 5) * 2)),
                std::make_shared<TestData>("(200 - 49.9) / 2 + 10", ((200 - 49.9) / 2 + 10)),
                std::make_shared<TestData>("(200 - 49.9) / (2 + 10)", ((200 - 49.9) / (2 + 10))),
                std::make_shared<TestData>("123 * (50 + 80) / 22", (123 * (50 + 80) / 22)),
                std::make_shared<TestData>("1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5))",
                                           (1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5)))
                )
        };
    }
};

TEST_F(SUITE_NAME, SimpleExpressionsTest) {
    double result;
    size_t cnt = 0;
    std::string s1;

    for (auto data : testData) {
        Expression expression(data->getExprString());
        expression.parseExpression();
        result = expression.getResult();

        EXPECT_EQ(data->getExpectedResult(), result) << "Test iteration: " << cnt;
        ++cnt;
    }
}

TEST(PPCAT(Comparator, SUITE_NAME), PriorityComparatorTest) {
    struct TestData {
        enum class Relations {
            EQUAL,
            VAL1_BIGGER,
            VAL1_SMALLER
        };

        size_t val1;
        size_t val2;
        Relations rel;
    } testData[] = {
            {1102, 1101, TestData::Relations::VAL1_SMALLER},
            {1202, 1302, TestData::Relations::VAL1_SMALLER},
            {101,  202,  TestData::Relations::VAL1_SMALLER},
            {2004, 1102, TestData::Relations::VAL1_BIGGER},
            {1,    2,    TestData::Relations::VAL1_BIGGER},
            {101,  102,  TestData::Relations::VAL1_BIGGER},
            {300,  300,  TestData::Relations::EQUAL},
            {2001, 2001, TestData::Relations::EQUAL},
            {1,    1,    TestData::Relations::EQUAL}
    };

    PriorityComparator comp;
    size_t testIteration = 0;

    for (auto data : testData) {
        switch (data.rel) {
            case TestData::Relations::VAL1_BIGGER:
                EXPECT_TRUE(comp(data.val1, data.val2))
                                    << "Test iteration: " << testIteration;
                EXPECT_FALSE(comp(data.val2, data.val1))
                                    << "Test iteration: " << testIteration;
                break;
            case TestData::Relations::VAL1_SMALLER:
                EXPECT_TRUE(comp(data.val2, data.val1))
                                    << "Test iteration: " << testIteration;
                EXPECT_FALSE(comp(data.val1, data.val2))
                                    << "Test iteration: " << testIteration;
                break;
            case TestData::Relations::EQUAL:
                EXPECT_FALSE(comp(data.val1, data.val2))
                                    << "Test iteration: " << testIteration;
                EXPECT_FALSE(comp(data.val2, data.val1))
                                    << "Test iteration: " << testIteration;
                break;
            default:
                EXPECT_TRUE(false)
                                    << "Test data is wrong on iteration: " << testIteration;
                break;
        }
        ++testIteration;
    }
}
