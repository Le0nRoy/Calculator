//
// Created by cerbe on 26.01.2021.
//

#include "Test.h"

#include <utility>
#include "NumberSystemConverter.h"

#define SUITE_NAME NumberSystemConverterTests
#define SUITE_NAME_STR_PARSE PPCAT(SUITE_NAME, StringParsing)
#define SUITE_NAME_CONVERSION PPCAT(SUITE_NAME, Conversion)
#define SUITE_NAME_ARITHMETIC_OPERATIONS PPCAT(SUITE_NAME, ArithmeticOperations)
#define SUITE_NAME_RELATIONAL_OPERATIONS PPCAT(SUITE_NAME, RelationalOperations)

class SUITE_NAME : ::testing::Test {
protected:
    virtual void prepareTestData() = 0;

    void SetUp() override {
        prepareTestData();
    }

};

class SUITE_NAME_STR_PARSE : SUITE_NAME {
protected:
    class TestDTO {
        bool negativeTest;
        std::string testStr;
        std::string val;
        size_t sysOrig;
        size_t sysNew;

    public:
        TestDTO(bool negativeTest, std::string testStr, std::string val, size_t sysOrig, size_t sysNew)
                : negativeTest(negativeTest),
                  testStr(std::move(testStr)),
                  val(std::move(val)),
                  sysOrig(sysOrig),
                  sysNew(sysNew) {}

        bool isNegativeTest() const {
            return negativeTest;
        }

        const std::string &getTestStr() const {
            return testStr;
        }

        const std::string &getVal() const {
            return val;
        }

        size_t getSysOrig() const {
            return sysOrig;
        }

        size_t getSysNew() const {
            return sysNew;
        }
    };

    void prepareTestData() {
        testData = {
                TestDTO(false, "198 D10 D16", "198", 10, 16),
                TestDTO(false, "13a1 d16 d2", "13a1", 16, 2)
        };
    }

    std::vector<TestDTO> testData;
};

/*
 * TODO
 *  constructor from string test
 *  string parsing test
 *  conversion test
 *  operations tests
 *
 *  at least 3 different DTOs
*/

// TODO same test for string setter
TEST_F(SUITE_NAME_STR_PARSE, ConstructorFromStringTest) {
    size_t cnt;
    std::shared_ptr<NumberSystemConverter> converter;

    for (const auto &data : testData) {
        try {
            converter = std::make_shared<NumberSystemConverter>(data.getTestStr());
            EXPECT_STREQ(data.getVal().data(), converter->getValueStr().data());
            EXPECT_EQ(data.getSysOrig(), converter->getNumSysOrig());
            EXPECT_EQ(data.getSysNew(), converter->getNumSysNew());
        } catch (std::exception &e) {
            if (data.isNegativeTest()) {
                EXPECT_THROW(throw e, NumberSystemConverterException)
                                    << "Got unexpected exception." << std::endl
                                    << e.what() << std::endl
                                    << "Test iteration: " << cnt << std::endl;
            } else {
                EXPECT_NO_THROW(throw e)
                                    << "Got unexpected exception." << std::endl
                                    << e.what() << std::endl
                                    << "Test iteration: " << cnt << std::endl;
            }
        }
        ++cnt;
    }
}

class SUITE_NAME_CONVERSION : SUITE_NAME {
    class TestDTO {
        std::string testString;
        std::string expectedValue;

    public:
        TestDTO(std::string testString, std::string expectedValue) :
                testString(std::move(testString)),
                expectedValue(std::move(expectedValue)) {}

        const std::string &getTestString() const {
            return testString;
        }

        const std::string &getExpectedValue() const {
            return expectedValue;
        }
    };

    void prepareTestData() {
        testData = {
                TestDTO("10 D10 D16", "A")
        };
    }

protected:
    virtual void SetUp() {
        prepareTestData();
    }

    std::vector<TestDTO> testData;
};

TEST_F(SUITE_NAME_CONVERSION, ConversionTest) {}

// TODO same but with bool result for relational operations
class SUITE_NAME_ARITHMETIC_OPERATIONS : SUITE_NAME {
protected:  enum class Operations;
private:
    class TestDTO {
        std::string left;
        std::string right;
        Operations operation;
        std::string result;
    };

    void prepareTestData() override {
        testData = {};
    }

protected:
    std::vector<TestDTO> testData;

    enum class Operations {
        PLUS,
        MINUS,
        MUL,
        DIV,
        INCREMENT,
        DECREMENT,
    };
};

TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, PlusTest) {}
TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, MinusTest) {}
TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, MulTest) {}
TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, DivTest) {}
TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, IncrementTest) {}
TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, DecrementTest) {}

class SUITE_NAME_RELATIONAL_OPERATIONS : SUITE_NAME {
protected:  enum class Operations;
private:
    class TestDTO {
        std::string left;
        std::string right;
        Operations operation;
        bool result;
    };

    void prepareTestData() override {
        testData = {};
    }

protected:
    std::vector<TestDTO> testData;

    enum class Operations {
        BIGGER,
        BIGGER_EQ,
        SMALLER,
        SMALLER_EQ,
        EQ,
        NOT_EQ
    };
};

TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, BiggerTest){}
TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, BiggerEqTest){}
TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, SmallerTest){}
TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, SmallerEqTest){}
TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, EqTest){}
TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, NotEqTest){}
