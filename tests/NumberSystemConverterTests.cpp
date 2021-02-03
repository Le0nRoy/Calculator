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

struct SUITE_NAME : ::testing::Test {
protected:
    virtual void prepareTestData() = 0;

    void SetUp() override {
        prepareTestData();
    }

    size_t testIteration = 0;
};

struct SUITE_NAME_STR_PARSE : SUITE_NAME {
protected:
    /*
     * testString
     * value in D2
     * value in D10
     */
    class TestDTO {
        bool negativeTest;
        double valD10;
        std::string testStr;

    public:
        TestDTO(bool negativeTest, std::string testStr, double valD10)
                : negativeTest(negativeTest),
                  testStr(std::move(testStr)),
                  valD10(valD10) {}

        bool isNegativeTest() const {
            return negativeTest;
        }

        const std::string &getTestStr() const {
            return testStr;
        }

        double getValD10() const {
            return valD10;
        }
    };

    void prepareTestData() {
        testData = {
                TestDTO(false, "198 D10", 198),
                TestDTO(false, "600 D7", 294),
                TestDTO(false, "adab D16", 44459),
                TestDTO(false, "12345 D8", 5349),
                TestDTO(false, "zaz D36", 45755),
                TestDTO(false, "1011010101 D2", 725),
                TestDTO(false, "131 D4", 29),
                TestDTO(false, "13a1 d16", 5025),
                // FIXME no check in algorithm ('g' is D17)
                // FIXME test framework doesn't handle absence of exception
                TestDTO(true, "13g1 d16", 0)
        };
    }

    std::vector<TestDTO> testData;
};

/**
 * a b c d e f g
 * h i j k l m n
 * o p q r s t u
 * v w x y z
 */
TEST_F(SUITE_NAME_STR_PARSE, ConstructorFromStringTest) {
    std::shared_ptr<NumberSystemConverter> converter;

    for (const auto &data : testData) {
        try {
            converter = std::make_shared<NumberSystemConverter>(data.getTestStr());
            EXPECT_EQ(data.getValD10(), converter->getValueD10())
                                << "Test iteration: " << testIteration << std::endl;
        } catch (std::exception &e) {
            if (data.isNegativeTest()) {
                EXPECT_THROW(throw e, NumberSystemConverterException)
                                    << "Got unexpected exception." << std::endl
                                    << "---" << e.what() << std::endl
                                    << "Test iteration: " << testIteration << std::endl;
            } else {
                EXPECT_NO_THROW(throw e)
                                    << "Got unexpected exception." << std::endl
                                    << "---" << e.what() << std::endl
                                    << "Test iteration: " << testIteration << std::endl;
            }
        }
        ++testIteration;
    }
}

// FIXME this test and test above make in one function which gets pointer to function and sends there test string
TEST_F(SUITE_NAME_STR_PARSE, ParseStringTest) {
    NumberSystemConverter converter;

    for (const auto &data : testData) {
        try {
            converter.parseString(data.getTestStr());
            EXPECT_EQ(data.getValD10(), converter.getValueD10())
                                << "Test iteration: " << testIteration;
        } catch (std::exception &e) {
            if (data.isNegativeTest()) {
                EXPECT_THROW(throw e, NumberSystemConverterException)
                                    << "Got unexpected exception." << std::endl
                                    << e.what() << std::endl
                                    << "Test iteration: " << testIteration << std::endl;
            } else {
                EXPECT_NO_THROW(throw e)
                                    << "Got unexpected exception." << std::endl
                                    << e.what() << std::endl
                                    << "Test iteration: " << testIteration << std::endl;
            }
        }
        ++testIteration;
    }
}

struct SUITE_NAME_CONVERSION : SUITE_NAME {
protected:
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
                TestDTO("10 D10", 16, "A")
        };
    }

    std::vector<TestDTO> testData;
};

TEST_F(SUITE_NAME_CONVERSION, ConversionTest) {}

class SUITE_NAME_ARITHMETIC_OPERATIONS : public SUITE_NAME {
protected:
    enum class Operations {
        PLUS,
        MINUS,
        MUL,
        DIV,
        INCREMENT,
        DECREMENT,
    };

    class TestDTO {
        std::string left;
        std::string right;
        Operations operation;
        std::string result;
    };

    void prepareTestData() override {
        testData = {};
    }

    std::vector<TestDTO> testData;
};

TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, PlusTest) {}

TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, MinusTest) {}

TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, MulTest) {}

TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, DivTest) {}

TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, IncrementTest) {}

TEST_F(SUITE_NAME_ARITHMETIC_OPERATIONS, DecrementTest) {}

class SUITE_NAME_RELATIONAL_OPERATIONS : public SUITE_NAME {
protected:
    enum class Operations {
        BIGGER,
        BIGGER_EQ,
        SMALLER,
        SMALLER_EQ,
        EQ,
        NOT_EQ
    };

    class TestDTO {
        std::string left;
        std::string right;
        Operations operation;
        bool result;
    };

    void prepareTestData() override {
        testData = {};
    }

    std::vector<TestDTO> testData;
};

TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, BiggerTest) {}

TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, BiggerEqTest) {}

TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, SmallerTest) {}

TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, SmallerEqTest) {}

TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, EqTest) {}

TEST_F(SUITE_NAME_RELATIONAL_OPERATIONS, NotEqTest) {}
