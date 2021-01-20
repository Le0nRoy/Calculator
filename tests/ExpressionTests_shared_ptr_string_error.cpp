//
// Created by lap on 9/26/20.
//

#include "Test.h"

#include "include/Expression.h"
#include <memory>
#include <utility>

#define SUITE_NAME ExpressionTests

// TODO This file is for study purposes:
//  `std::shared_ptr<TestData> da = std::make_shared<TestData>("1 + 2 + 3", (1 + 2 + 3));`
//  string above is the reason of SIGTRAP on test finishing
//  By some reason destructor of TestData is not even used
//  What else may be checked:
//  1.

struct TestData {
    TestData(std::string str, double expectedResult) :
            expectedResult(expectedResult),
            exprString(std::move(str)) {
    };

    ~TestData() {
        try {
            exprString.erase();
        } catch (std::exception &e) {
            std::cout << "Exception in destructor" << std::endl
                      << e.what() << std::endl;
        }
    }

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

    std::vector<std::shared_ptr<TestData>> testData;

/*
Hello. Indeed, link does not exist any more...
 Anyway, the core answer was the following.
 When one declares and initiates a variable inside the body of main function it's memory allocated on the stack.
 Everything is okay until the FreeRTOS scheduler started. After vTaskStartScheduler(); called the stack pointer is rewinded to the very begining (sorry, to the very end of RAM).
 Scheduler begins it work actively using the stack and cheerfully overwriting already allocated local variables declared in main function body.
Thus the core of the problem is the stack pointer rewind to the end of RAM during launching the FreeRTOS scheduler.
 One can clearly see this asm code following this chain of function calls: vTaskStartScheduler() -> xPortStartScheduler() -> prvPortStartFirstTask().
 And there is that tricky instruction:
" msr msp, r0         \n" //Set the msp back to the start of the stack.
In conclusion I would like to say that this problem was not the only I've faced trying to combine mordern C++, HAL and FreeRTOS.
 I've gave up this idea and moved to pure C. In C one also can write construct program using OOP.
 Not as convinient as C++, but stable and predictable.

*** Doesn't seem as mine case - I'm using copy constructor for string
 */
private:
    void PrepareTestData() {
        testData = {
//                std::make_shared<TestData>("1 + 2 + 3", (1 + 2 + 3)),
//                std::make_shared<TestData>("20.6 * 12 - 40", (20.6 * 12 - 40)),
                std::make_shared<TestData>("208.999 / 88 * 20", (208.999 / 88 * 20)),
//                std::make_shared<TestData>("50 + 5 * 2", (50 + 5 * 2)),
//                std::make_shared<TestData>("(50 + 5) * 2", ((50 + 5) * 2)),
                std::make_shared<TestData>("(200 - 49.9) / 2 + 10", ((200 - 49.9) / 2 + 10)),
                std::make_shared<TestData>("(200 - 49.9) / (2 + 10)", ((200 - 49.9) / (2 + 10))),
                std::make_shared<TestData>("123 * (50 + 80) / 22", (123 * (50 + 80) / 22)),
                std::make_shared<TestData>("1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5))",
                                           (1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5)))
                )
        };
    }
};

TEST(SOME, test) {
    std::shared_ptr<TestData> da = std::make_shared<TestData>("1 + 2 + 3", (1 + 2 + 3));
//    std::shared_ptr<TestData> da = std::make_shared<TestData>("208.999 / 88 * 20",
//            (1 + 2 + 3));
//    std::cout << da.use_count() << std::endl;
    try {
        da.reset();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    EXPECT_TRUE(false);
}

TEST_F(SUITE_NAME, SimpleExpressionsTest) {
    double result;
    size_t cnt = 0;
    std::string s1;
    std::shared_ptr<Expression> expression;

    for (auto data : testData) {
        expression = std::make_shared<Expression>(data->getExprString());
        ASSERT_NO_THROW(expression->parseExpression())
                                    << "On test iteration: " << cnt << std::endl;
        result = expression->getResult();

        EXPECT_EQ(data->getExpectedResult(), result) << "Test iteration: " << cnt;
        ++cnt;
    }

    EXPECT_TRUE(false);
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
