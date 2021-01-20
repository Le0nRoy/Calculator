//
// Created by lap on 9/26/20.
//

#include "Test.h"

#include "include/Expression.h"
#include <memory>
#include <utility>

#define SUITE_NAME ExpressionTests

struct TestData {
    TestData(std::string str, double expectedResult) :
            expectedResult(expectedResult),
            exprString(std::move(str)) {
    };

//    ~TestData() {
//        try {
//            exprString.erase();
//        } catch (std::exception &e) {
//            std::cout << "Exception in destructor" << std::endl
//                      << e.what() << std::endl;
//        }
//    }

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
protected:
    void SetUp() override {
        PrepareTestData();
    }

    std::vector<TestData> testData;

private:
    void PrepareTestData() {
        testData = {
                TestData("1 + 2 + 3", (1 + 2 + 3)),
                TestData("50 + 5 * 2", (50 + 5 * 2)),
                TestData("20.6 * 12 - 40", (20.6 * 12 - 40)),
                TestData("208.999 / 88 * 20", (208.999 / 88 * 20)),
                TestData("208.999 / 88 + 20", (208.999 / 88 + 20)),
                TestData("(50 + 5) * 2", ((50 + 5) * 2)),
                TestData("(200 - 49.9) / 2 + 10", ((200 - 49.9) / 2 + 10)),
                TestData("(200 - 49.9) / (2 + 10)", ((200 - 49.9) / (2 + 10))),
                TestData("123 * (50 + 80) / 22", (123. * (50 + 80) / 22)),
                TestData("1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5))",
                         (1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5)))
                ),
                TestData("1 + 5 * (421 - 905) / ((390.87 + 60.8) * 9333)",
                         (1 + 5 * (421 - 905) / ((390.87 + 60.8) * 9333))
                )
        };
    }
};

TEST_F(SUITE_NAME, SimpleExpressionsTest) {
    double result;
    size_t cnt = 0;
    std::string s1;
    std::shared_ptr<Expression> expression;

    for (auto data : testData) {
        try {
            expression = std::make_shared<Expression>(data.getExprString());
            EXPECT_NO_THROW(expression->parseExpression())
                                << "On test iteration: " << cnt << std::endl;
            result = expression->getResult();

            EXPECT_EQ(data.getExpectedResult(), result) << "Test iteration: " << cnt;
        } catch (ExpressionException &e) {
            std::cout << "Test data:" << std::endl
                      << data.getExprString() << std::endl;
        } catch (std::exception &e) {
            std::cout << "Unexpected exception was caught in test body on iteration: " << cnt << std::endl
                      << e.what() << std::endl
                      << "Test data:" << std::endl
                      << data.getExprString() << std::endl;
        }
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
