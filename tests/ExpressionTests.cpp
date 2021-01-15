//
// Created by lap on 9/26/20.
//

#include "gtest/gtest.h"
#include "include/Expression.h"

#define SUITE_NAME ExpressionTests

// both PPCAT_NX(s, 1) and PPCAT(s, 1) produce the identifier s1,
// unless s is defined as a macro, in which case PPCAT(s, 1) produces <macro value of s>1.
#define PPCAT_NX(A, B) A ## B
#define PPCAT(A, B) PPCAT_NX(A, B)

struct TestData {
    std::string exprString;
    double expectedResult;
};

struct SUITE_NAME : ::testing::Test {
protected:
    void SetUp() override {
        PrepareTestData();
    }

    std::vector<TestData> testData;

private:
    void PrepareTestData() {
        testData = {
                {"1 + 2 + 3",                                                (1 + 2 + 3)},
                {"20.6 * 12 - 40",                                           (20.6 * 12 - 40)},
                {"208.999 / 88 * 20",                                        (208.999 / 88 * 20)},
                {"50 + 5 * 2",                                               (50 + 5 * 2)},
                {"(50 + 5) * 2",                                             ((50 + 5) * 2)},
                {"(200 - 49.9) / 2 + 10",                                    ((200 - 49.9) / 2 + 10)},
                {"(200 - 49.9) / (2 + 10)",                                  ((200 - 49.9) / (2 + 10))},
                {"1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5))", (1 + 5 * (421 - 905) /
                                                                                  ((390.87 + 60.8) * (9333 - 180.5)))}
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
            {1, 1, TestData::Relations::EQUAL}
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
