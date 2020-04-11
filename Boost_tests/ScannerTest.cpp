#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../include/Scanner.h"
#include "../src/Scanner.cpp"
std::string term = "$";

void tokenPrint(std::vector<Token> tokens) {

    for(auto token : tokens) {
        std::cout << token << std::endl;
    }
}

BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_IF)
{
    Scanner scanner;
    std::string input = "if" + term;
    Token expectedToken("if", T_IF);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WHILE)
{
    Scanner scanner;
    std::string input = "while" + term;
    Token expectedToken("while", T_WHILE);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_DO)
{
    Scanner scanner;
    std::string input = "do" + term;
    Token expectedToken("do", T_DO);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_DONE)
{
    Scanner scanner;
    std::string input = "done" + term;
    Token expectedToken("done", T_DONE);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_INT)
{
    Scanner scanner;
    std::string input = "int" + term;
    Token expectedToken("int", T_SPECIFIER);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_UNSIGNED_INT)
{
    Scanner scanner;
    std::string input = "unsigned_int" + term;
    Token expectedToken("unsigned_int", T_SPECIFIER);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_FLOAT)
{
    Scanner scanner;
    std::string input = "float" + term;
    Token expectedToken("float", T_SPECIFIER);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_STRING)
{
    Scanner scanner;
    std::string input = "string" + term;
    Token expectedToken("string", T_SPECIFIER);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_SYSTEM_HANDLER)
{
    Scanner scanner;
    std::string input = "system_handler" + term;
    Token expectedToken("system_handler", T_SPECIFIER);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WHITESPACE_REMOVING_1)
{
    Scanner scanner;
    std::string input = "system _ handler" + term;
    Token expectedToken("system", T_USER_DEFINED_NAME);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WHITESPACE_REMOVING_2)
{
    Scanner scanner;
    std::string input = "          system" + term;
    Token expectedToken("system", T_USER_DEFINED_NAME);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WHITESPACE_REMOVING_3)
{
    Scanner scanner;
    std::string input = "          s y s t e m" + term;
    Token expectedToken("s", T_USER_DEFINED_NAME);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WHITESPACE_REMOVING_4)
{
    Scanner scanner;
    std::string input = "system            " + term;
    Token expectedToken("system", T_USER_DEFINED_NAME);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_MULT)
{
    Scanner scanner;
    std::string input = "*" + term;
    Token expectedToken("*", T_MULT_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_DIV)
{
    Scanner scanner;
    std::string input = "/" + term;
    Token expectedToken("/", T_MULT_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_AND)
{
    Scanner scanner;
    std::string input = "+" + term;
    Token expectedToken("+", T_ADD_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_SUB)
{
    Scanner scanner;
    std::string input = "-" + term;
    Token expectedToken("-", T_ADD_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_OR)
{
    Scanner scanner;
    std::string input = "|" + term;
    Token expectedToken("|", T_ADD_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_BOOLEAN_1)
{
    Scanner scanner;
    std::string input = "<" + term;
    Token expectedToken("<", T_BOOLEAN_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_BOOLEAN_2)
{
    Scanner scanner;
    std::string input = "<=" + term;
    Token expectedToken("<=", T_BOOLEAN_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_BOOLEAN_3)
{
    Scanner scanner;
    std::string input = ">" + term;
    Token expectedToken(">", T_BOOLEAN_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_BOOLEAN_4)
{
    Scanner scanner;
    std::string input = ">=" + term;
    Token expectedToken(">=", T_BOOLEAN_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_BOOLEAN_5)
{
    Scanner scanner;
    std::string input = "==" + term;
    Token expectedToken("==", T_BOOLEAN_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_ASSIGN)
{
    Scanner scanner;
    std::string input = "=" + term;
    Token expectedToken("=", T_ASSIGN_OPERATOR);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_INT_NUM_1)
{
    Scanner scanner;
    std::string input = "0" + term;
    Token expectedToken("0", T_INT_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_INT_NUM_2)
{
    Scanner scanner;
    std::string input = "123124135&" + term;
    Token expectedToken("123124135", T_INT_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_INT_NUM_3)
{
    Scanner scanner;
    std::string input = "3232**" + term;
    Token expectedToken("3232", T_INT_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_INT_NUM_4)
{
    Scanner scanner;
    std::string input = "11111111111111111111111111111111" + term;
    Token expectedToken("11111111111111111111111111111111", T_INT_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_INT_NUM_5)
{
    Scanner scanner;
    std::string input = "111111111111111111 11111111111111" + term;
    Token expectedToken("111111111111111111", T_INT_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_INT_NUM_6)
{
    Scanner scanner;
    std::string input = "111111111111111111 abc" + term;
    Token expectedToken("111111111111111111", T_INT_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_INT_NUM_7)
{
    Scanner scanner;
    std::string input = "      9&&&&" + term;
    Token expectedToken("9", T_INT_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_INT_NUM_8)
{
    Scanner scanner;
    std::string input = "8 8 8 8 8 8 8" + term;
    Token expectedToken("8", T_INT_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_REAL_NUM_1)
{
    Scanner scanner;
    std::string input = "0.0" + term;
    Token expectedToken("0.0", T_REAL_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_REAL_NUM_2)
{
    Scanner scanner;
    std::string input = "0.00" + term;
    Token expectedToken("0.00", T_REAL_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_REAL_NUM_3)
{
    Scanner scanner;
    std::string input = "       0.01" + term;
    Token expectedToken("0.01", T_REAL_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_REAL_NUM_4)
{
    Scanner scanner;
    std::string input = "0.005" + term;
    Token expectedToken("0.005", T_REAL_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_REAL_NUM_5)
{
    Scanner scanner;
    std::string input = "123.123" + term;
    Token expectedToken("123.123", T_REAL_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_REAL_NUM_6)
{
    Scanner scanner;
    std::string input = "999999.999999 9999" + term;
    Token expectedToken("999999.999999", T_REAL_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_REAL_NUM_7)
{
    Scanner scanner;
    std::string input = "     999999.999999 9999" + term;
    Token expectedToken("999999.999999", T_REAL_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_REAL_NUM_8)
{
    Scanner scanner;
    std::string input = "     999999     .       999999 9999" + term;
    Token expectedToken("999999", T_INT_NUM);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_OPEN_PARENTHESIS)
{
    Scanner scanner;
    std::string input = "(" + term;
    Token expectedToken("(", T_OPENING_PARENTHESIS);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_CLOSE_PARENTHESIS)
{
    Scanner scanner;
    std::string input = ")" + term;
    Token expectedToken(")", T_CLOSING_PARENTHESIS);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_OPEN_BRACKET)
{
    Scanner scanner;
    std::string input = "{" + term;
    Token expectedToken("{", T_OPENING_BRACKET);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_CLOSE_BRACKET)
{
    Scanner scanner;
    std::string input = "}" + term;
    Token expectedToken("}", T_CLOSING_BRACKET);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_CON)
{
    Scanner scanner;
    std::string input = ":" + term;
    Token expectedToken(":", T_CON);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_SEMICON)
{
    Scanner scanner;
    std::string input = "," + term;
    Token expectedToken(",", T_SEMICON);
    Token receivedToken = scanner.getNextToken(input);
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_NAME_1)
{
    Scanner scanner;
    std::string input = "asdasd%" + term;
    std::string expectedMsg = "Error in reading name";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_NAME_2)
{
    Scanner scanner;
    std::string input = "asdasd#&" + term;
    std::string expectedMsg = "Error in reading name";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_1)
{
    Scanner scanner;
    std::string input = "10." + term;
    std::string expectedMsg = "No decimal part in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_2)
{
    Scanner scanner;
    std::string input = "10." + term;
    std::string expectedMsg = "No decimal part in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_3)
{
    Scanner scanner;
    std::string input = "0." + term;
    std::string expectedMsg = "No decimal part in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_4)
{
    Scanner scanner;
    std::string input = "0." + term;
    std::string expectedMsg = "No decimal part in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_5)
{
    Scanner scanner;
    std::string input = "10.00000#" + term;
    std::string expectedMsg = "Forbidden sign in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_6)
{
    Scanner scanner;
    std::string input = "1123.33@" + term;
    std::string expectedMsg = "Forbidden sign in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_7)
{
    Scanner scanner;
    std::string input = "9809.809!" + term;
    std::string expectedMsg = "Forbidden sign in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_8)
{
    Scanner scanner;
    std::string input = "99999.A" + term;
    std::string expectedMsg = "Forbidden sign in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_9)
{
    Scanner scanner;
    std::string input = "998888.Z" + term;
    std::string expectedMsg = "Forbidden sign in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_10)
{
    Scanner scanner;
    std::string input = "0.3123a" + term;
    std::string expectedMsg = "Forbidden sign in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_11)
{
    Scanner scanner;
    std::string input = "0.3123z" + term;
    std::string expectedMsg = "Forbidden sign in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_12)
{
    Scanner scanner;
    std::string input = "0.3123_" + term;
    std::string expectedMsg = "Forbidden sign in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_13)
{
    Scanner scanner;
    std::string input = "0.3123:" + term;
    std::string expectedMsg = "Forbidden sign in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_14)
{
    Scanner scanner;
    std::string input = "0.3123321312." + term;
    std::string expectedMsg = "Forbidden sign in real number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_15)
{
    Scanner scanner;
    std::string input = "000" + term;
    std::string expectedMsg = "Too many zeros in prefix";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_REAL_NUM_16)
{
    Scanner scanner;
    std::string input = "000." + term;
    std::string expectedMsg = "Too many zeros in prefix";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_INT_NUM_1)
{
    Scanner scanner;
    std::string input = "12a" + term;
    std::string expectedMsg = "Forbidden sign in integer number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_INT_NUM_2)
{
    Scanner scanner;
    std::string input = "12#" + term;
    std::string expectedMsg = "Forbidden sign in integer number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_INT_NUM_3)
{
    Scanner scanner;
    std::string input = "12312321321~" + term;
    std::string expectedMsg = "Forbidden sign in integer number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_INT_NUM_4)
{
    Scanner scanner;
    std::string input = "12[" + term;
    std::string expectedMsg = "Forbidden sign in integer number";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_OPERATOR_1)
{
    Scanner scanner;
    std::string input = ">*" + term;
    std::string expectedMsg = "Forbidden sign in reading operator";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_OPERATOR_2)
{
    Scanner scanner;
    std::string input = "<*" + term;
    std::string expectedMsg = "Forbidden sign in reading operator";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_OPERATOR_3)
{
    Scanner scanner;
    std::string input = "=*" + term;
    std::string expectedMsg = "Forbidden sign in reading operator";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_OPERATOR_4)
{
    Scanner scanner;
    std::string input = "<<" + term;
    std::string expectedMsg = "Forbidden sign in reading operator";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_OPERATOR_5)
{
    Scanner scanner;
    std::string input = ">>" + term;
    std::string expectedMsg = "Forbidden sign in reading operator";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_OPERATOR_6)
{
    Scanner scanner;
    std::string input = "<>" + term;
    std::string expectedMsg = "Forbidden sign in reading operator";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_OPERATOR_7)
{
    Scanner scanner;
    std::string input = "><" + term;
    std::string expectedMsg = "Forbidden sign in reading operator";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_OPERATOR_8)
{
    Scanner scanner;
    std::string input = "<>" + term;
    std::string expectedMsg = "Forbidden sign in reading operator";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_OPERATOR_9)
{
    Scanner scanner;
    std::string input = "=<" + term;
    std::string expectedMsg = "Forbidden sign in reading operator";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}
BOOST_AUTO_TEST_CASE(SINGLE_TOKEN_WRONG_OPERATOR_10)
{
    Scanner scanner;
    std::string input = "=>" + term;
    std::string expectedMsg = "Forbidden sign in reading operator";
    std::string actualMsg;

    try{
        scanner.getNextToken(input);
    } catch(std::exception& e) {
        actualMsg = e.what();
    }

    BOOST_CHECK_EQUAL(expectedMsg, actualMsg);
}

BOOST_AUTO_TEST_CASE(MANY_TOKENS_DECLARATION_1)
{
    Scanner scanner;
    std::string input = "int a";
    std::vector<Token> expectedTokens = {{"int", T_SPECIFIER}, {"a", T_USER_DEFINED_NAME}, {"$", T_END}};
    std::vector<Token> actualTokens = scanner.testScan(input);

    BOOST_CHECK_EQUAL_COLLECTIONS(expectedTokens.begin(), expectedTokens.end(), actualTokens.begin(), actualTokens.end());
}

BOOST_AUTO_TEST_CASE(MANY_TOKENS_DECLARATION_2) {
    Scanner scanner;
    std::string input = "system_handler a = 500";
    std::vector<Token> expectedTokens = {{"system_handler", T_SPECIFIER},
                                         {"a",              T_USER_DEFINED_NAME},
                                         {"=",              T_ASSIGN_OPERATOR},
                                         {"500",            T_INT_NUM},
                                         {"$",              T_END}};
    std::vector<Token> actualTokens = scanner.testScan(input);

    BOOST_CHECK_EQUAL_COLLECTIONS(expectedTokens.begin(), expectedTokens.end(), actualTokens.begin(),
                                  actualTokens.end());
}
BOOST_AUTO_TEST_CASE(MANY_TOKENS_DECLARATION_3)
{
    Scanner scanner;
    std::string input = "system_handler a = my_var";
    std::vector<Token> expectedTokens = {{"system_handler", T_SPECIFIER}, {"a", T_USER_DEFINED_NAME},
                                         {"=", T_ASSIGN_OPERATOR}, {"my_var", T_USER_DEFINED_NAME}, {"$", T_END}};
    std::vector<Token> actualTokens = scanner.testScan(input);

    BOOST_CHECK_EQUAL_COLLECTIONS(expectedTokens.begin(), expectedTokens.end(), actualTokens.begin(), actualTokens.end());
}
BOOST_AUTO_TEST_CASE(MANY_TOKENS_COMPLEX_EXPR_1)
{
    Scanner scanner;
    std::string input = "if(abc == 5        ) do w = 1.00005 done";
    std::vector<Token> expectedTokens = {{"if", T_IF}, {"(", T_OPENING_PARENTHESIS}, {"abc" , T_USER_DEFINED_NAME},
                                         {"==", T_BOOLEAN_OPERATOR}, {"5", T_INT_NUM}, {")", T_CLOSING_PARENTHESIS},
                                         {"do", T_DO}, {"w", T_USER_DEFINED_NAME}, {"=", T_ASSIGN_OPERATOR},
                                         {"1.00005", T_REAL_NUM}, {"done", T_DONE}, {"$", T_END}};
    std::vector<Token> actualTokens = scanner.testScan(input);

    BOOST_CHECK_EQUAL_COLLECTIONS(expectedTokens.begin(), expectedTokens.end(), actualTokens.begin(), actualTokens.end());
}
BOOST_AUTO_TEST_CASE(MANY_TOKENS_COMPLEX_EXPR_2)
{
    Scanner scanner;
    std::string input = "name * 5  & ( a + e22222 )*(12312 - 111.3333   * 123) | a";
    std::vector<Token> expectedTokens = {{"name", T_USER_DEFINED_NAME}, {"*", T_MULT_OPERATOR}, {"5", T_INT_NUM},
                                         {"&", T_MULT_OPERATOR},{"(", T_OPENING_PARENTHESIS}, {"a", T_USER_DEFINED_NAME},
                                         {"+", T_ADD_OPERATOR},{"e22222", T_USER_DEFINED_NAME}, {")", T_CLOSING_PARENTHESIS},
                                         {"*", T_MULT_OPERATOR},{"(", T_OPENING_PARENTHESIS}, {"12312", T_INT_NUM},
                                         {"-", T_ADD_OPERATOR},{"111.3333", T_REAL_NUM}, {"*", T_MULT_OPERATOR},
                                         {"123", T_INT_NUM},{")", T_CLOSING_PARENTHESIS},{"|", T_ADD_OPERATOR},
                                         {"a", T_USER_DEFINED_NAME}, {"$", T_END}};
    std::vector<Token> actualTokens = scanner.testScan(input);

    BOOST_CHECK_EQUAL_COLLECTIONS(expectedTokens.begin(), expectedTokens.end(), actualTokens.begin(), actualTokens.end());
}
