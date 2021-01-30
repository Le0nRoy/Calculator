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

/**
 * Get number in any number system (e.g. "16a1 D16")
 * store it in D2 system in std::vector<bool> and std::string
 * return string with that number in needed number system
 * if D10 - return double
 * arithmetic and relational operations
 */

class SUITE_NAME : ::testing::Test {
protected:
    virtual void prepareTestData() = 0;

    void SetUp() override {
        prepareTestData();
    }

};

class SUITE_NAME_STR_PARSE : SUITE_NAME {
protected:
    /*
     * testString
     * value in D2
     * value in D10
     */
    class TestDTO {
        bool negativeTest;
        std::string testStr;
        std::string valD2;
        std::string valD10;

    public:
        TestDTO(bool negativeTest, std::string testStr, std::string valD2, std::string valD10)
                : negativeTest(negativeTest),
                  testStr(std::move(testStr)),
                  valD2(std::move(valD2)),
                  valD10(std::move(valD10)) {}

        bool isNegativeTest() const {
            return negativeTest;
        }

        const std::string &getTestStr() const {
            return testStr;
        }

        const std::string &getValD2() const {
            return valD2;
        }

        const std::string &getValD10() const {
            return valD10;
        }
    };

    void prepareTestData() {
        testData = {
                TestDTO(false, "198 D10", "11000110", std::to_string(198)),
                TestDTO(false, "13a1 d16", "1001110100001", std::to_string(5025))
        };
    }

    std::vector<TestDTO> testData;
};

TEST_F(SUITE_NAME_STR_PARSE, ConstructorFromStringTest) {
    size_t cnt;
    std::shared_ptr<NumberSystemConverter> converter;

    for (const auto &data : testData) {
        try {
            converter = std::make_shared<NumberSystemConverter>(data.getTestStr());
            // TODO check D2 value
            // TODO check D10 value
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

// FIXME this test and test above make in one function which gets pointer to function and sends there test string
TEST_F(SUITE_NAME_STR_PARSE, ParseStringTest) {
    size_t cnt;
    NumberSystemConverter converter;

    for (const auto &data : testData) {
        try {
            converter.parseString(data.getTestStr());
            // TODO check D2 value
            // TODO check D10 value
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
        size_t numberSystem;
        std::string expectedValue;

    public:
        TestDTO(std::string testString, size_t numberSystem, std::string expectedValue) :
                testString(std::move(testString)),
                numberSystem(numberSystem),
                expectedValue(std::move(expectedValue)) {}

        const std::string &getTestString() const {
            return testString;
        }

        size_t getNumberSystem() const {
            return numberSystem;
        }

        const std::string &getExpectedValue() const {
            return expectedValue;
        }
    };

    void prepareTestData() {
        testData = {
                TestDTO("10 D10",16 , "A")
        };
    }

protected:
    virtual void SetUp() {
        prepareTestData();
    }

    std::vector<TestDTO> testData;
};

TEST_F(SUITE_NAME_CONVERSION, ConversionTest) {}

class SUITE_NAME_ARITHMETIC_OPERATIONS : SUITE_NAME {
protected:
    enum class Operations;
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
protected:
    enum class Operations;
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

TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, BiggerTest) {}
TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, BiggerEqTest) {}
TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, SmallerTest) {}
TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, SmallerEqTest) {}
TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, EqTest) {}
TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, NotEqTest) {}
