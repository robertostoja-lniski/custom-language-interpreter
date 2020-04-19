#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../include/Scanner.h"
#include "../include/Configuration.h"
#include "../src/Scanner.cpp"
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_0)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("dasdasdasd", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_1)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "a__" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("a__", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_2)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "adadsa312321" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("adadsa312321", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_3)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("dasdasdasd", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_4)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd&" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("dasdasdasd", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_5)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd|" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("dasdasdasd", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_6)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd$" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("dasdasdasd", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_7)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd:" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("dasdasdasd", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_8)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "inta" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("inta", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_9)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "unsigned_inta" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("unsigned_inta", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_10)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "floata" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("floata", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_11)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "stringa" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("stringa", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_12)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "system_handlera" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("system_handlera", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_13)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "while()" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("while", T_WHILE);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_14)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "while" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("while", T_WHILE);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_15)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "while*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("while", T_WHILE);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_16)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "while|" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("while", T_WHILE);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_17)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "if(" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("if", T_IF);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_18)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "if" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("if", T_IF);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_19)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "exit" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("exit", T_EXIT);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_20)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("123.3213", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_21)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "0.3213" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("0.3213", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_22)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.0003213" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("123.0003213", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_23)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "0.0" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("0.0", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_24)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213-" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("123.3213", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_25)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213+" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("123.3213", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_26)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("123.3213", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_27)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213/" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("123.3213", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_28)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213|" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("123.3213", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_29)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213&" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("123.3213", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_30)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("123.3213", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_31)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "3123" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("3123", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_32)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "3123-" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("3123", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_33)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "3123+" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("3123", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_34)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "3123*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("3123", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_35)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "3123:" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("3123", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_36)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "0" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("0", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_37)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "do" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("do", T_DO);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_38)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "done" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("done", T_DONE);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_39)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_40)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+_" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_41)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "++" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_42)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_43)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+==" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_44)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+>" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_45)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+<" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_46)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+123" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_47)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+int" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_48)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+0.0" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_49)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+.." << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_50)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_51)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-_" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_52)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-+" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_53)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_54)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-+==" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_55)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "->" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_56)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-<" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_57)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-123" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_58)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-int" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_59)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-0.0" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_60)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-.." << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_61)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*0.0" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_62)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_63)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*_" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_64)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*6" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_65)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*>" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_66)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*<" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_67)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/0.0" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("/", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_68)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("/", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_69)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/_" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("/", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_70)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/6" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("/", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_71)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/>" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("/", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_72)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/<" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("/", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_73)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "==" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("==", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_74)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ">=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(">=", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_75)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "<=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("<=", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_76)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "==a__" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("==", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_77)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "==eqweq" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("==", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_78)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ">=eqweq" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(">=", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_79)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "<=0.002" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("<=", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_80)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "==int" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("==", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_81)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "<=*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("<=", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_82)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ">=/" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(">=", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_83)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "==--" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("==", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_84)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "<==" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("<=", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_85)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "<=<=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("<=", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_86)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("=", T_ASSIGN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_87)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "=-" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("=", T_ASSIGN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_88)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "=+" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("=", T_ASSIGN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_89)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "=rre" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("=", T_ASSIGN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_90)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "=123.123" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("=", T_ASSIGN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_91)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "int" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("int", T_SPECIFIER);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_92)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "unsigned_int" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("unsigned_int", T_SPECIFIER);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_93)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "string" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("string", T_SPECIFIER);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_94)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "system_handler" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("system_handler", T_SPECIFIER);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_95)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "float" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("float", T_SPECIFIER);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_96)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("(", T_OPENING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_97)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("(", T_OPENING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_98)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "()" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("(", T_OPENING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_99)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("(", T_OPENING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_100)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("(", T_OPENING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_101)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(==" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("(", T_OPENING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_102)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(3123.33" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("(", T_OPENING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_103)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "($" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("(", T_OPENING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_104)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ")" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(")", T_CLOSING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_105)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ")a__" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(")", T_CLOSING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_106)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "))" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(")", T_CLOSING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_107)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "){}" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(")", T_CLOSING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_108)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ")eqwe" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(")", T_CLOSING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_109)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ")<=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(")", T_CLOSING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_110)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "," << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(",", T_SEMICON);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_111)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ".eqwe" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(".", T_SEMICON);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_112)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ".0003" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(".", T_SEMICON);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_113)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ":" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(":", T_CON);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_114)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ":eqwe" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(":", T_CON);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_115)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ":dd" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(":", T_CON);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_116)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ":ww" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(":", T_CON);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_117)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("{", T_OPENING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_118)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{do" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("{", T_OPENING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_119)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{done" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("{", T_OPENING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_120)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{." << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("{", T_OPENING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_121)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{qweqw" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("{", T_OPENING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_122)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{}" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("{", T_OPENING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_123)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("}", T_CLOSING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_124)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}eqwe" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("}", T_CLOSING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_125)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}22" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("}", T_CLOSING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_126)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}$" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("}", T_CLOSING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_127)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}$" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("}", T_CLOSING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_128)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}%" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("}", T_CLOSING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_129)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}&" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("}", T_CLOSING_BRACKET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_130)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "$" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("$", T_END);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_131)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "$$$" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("$", T_END);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_132)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "$afetrerer" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("$", T_END);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_133)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "$." << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("$", T_END);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_134)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "^" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("^", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_135)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "%" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("%", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_136)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "#" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("#", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_137)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "@" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("@", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_138)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "!" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("!", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_139)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "~" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("~", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_140)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "`" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("`", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_141)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("/", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_142)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ";" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken(";", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_0)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("dasdasdasd", T_USER_DEFINED_NAME);
    Token expectedToken2("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_1)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd&" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("dasdasdasd", T_USER_DEFINED_NAME);
    Token expectedToken2("&", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_2)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd|" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("dasdasdasd", T_USER_DEFINED_NAME);
    Token expectedToken2("|", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_3)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd$" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("dasdasdasd", T_USER_DEFINED_NAME);
    Token expectedToken2("$", T_END);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_4)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "dasdasdasd:" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("dasdasdasd", T_USER_DEFINED_NAME);
    Token expectedToken2(":", T_CON);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_5)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "while()" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("while", T_WHILE);
    Token expectedToken2("(", T_OPENING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_6)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "while*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("while", T_WHILE);
    Token expectedToken2("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_7)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "while|" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("while", T_WHILE);
    Token expectedToken2("|", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_8)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "if(" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("if", T_IF);
    Token expectedToken2("(", T_OPENING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_9)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213-" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("123.3213", T_REAL_NUM);
    Token expectedToken2("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_10)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213+" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("123.3213", T_REAL_NUM);
    Token expectedToken2("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_11)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("123.3213", T_REAL_NUM);
    Token expectedToken2("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_12)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213/" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("123.3213", T_REAL_NUM);
    Token expectedToken2("/", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_13)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213|" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("123.3213", T_REAL_NUM);
    Token expectedToken2("|", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_14)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "123.3213&" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("123.3213", T_REAL_NUM);
    Token expectedToken2("&", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_15)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "3123-" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("3123", T_INT_NUM);
    Token expectedToken2("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_16)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "3123+" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("3123", T_INT_NUM);
    Token expectedToken2("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_17)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "3123*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("3123", T_INT_NUM);
    Token expectedToken2("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_18)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "3123:" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("3123", T_INT_NUM);
    Token expectedToken2(":", T_CON);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_19)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2("a", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_20)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+_" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2("_", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_21)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "++" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_22)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2("=", T_ASSIGN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_23)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+==" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2("==", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_24)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+>" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2(">", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_25)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+<" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2("<", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_26)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+123" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2("123", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_27)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+int" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2("int", T_SPECIFIER);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_28)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+0.0" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2("0.0", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_29)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "+.." << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("+", T_ADD_OPERATOR);
    Token expectedToken2(".", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_30)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2("a", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_31)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-_" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2("_", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_32)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-+" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_33)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2("=", T_ASSIGN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_34)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-+==" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_35)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "->" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2(">", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_36)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-<" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2("<", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_37)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-123" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2("123", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_38)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-int" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2("int", T_SPECIFIER);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_39)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-0.0" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2("0.0", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_40)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "-.." << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("-", T_ADD_OPERATOR);
    Token expectedToken2(".", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_41)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*0.0" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("*", T_MULT_OPERATOR);
    Token expectedToken2("0.0", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_42)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("*", T_MULT_OPERATOR);
    Token expectedToken2("a", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_43)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*_" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("*", T_MULT_OPERATOR);
    Token expectedToken2("_", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_44)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*6" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("*", T_MULT_OPERATOR);
    Token expectedToken2("6", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_45)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*>" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("*", T_MULT_OPERATOR);
    Token expectedToken2(">", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_46)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "*<" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("*", T_MULT_OPERATOR);
    Token expectedToken2("<", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_47)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/0.0" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("/", T_MULT_OPERATOR);
    Token expectedToken2("0.0", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_48)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("/", T_MULT_OPERATOR);
    Token expectedToken2("a", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_49)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/_" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("/", T_MULT_OPERATOR);
    Token expectedToken2("_", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_50)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/6" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("/", T_MULT_OPERATOR);
    Token expectedToken2("6", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_51)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/>" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("/", T_MULT_OPERATOR);
    Token expectedToken2(">", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_52)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "/<" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("/", T_MULT_OPERATOR);
    Token expectedToken2("<", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_53)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "==a__" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("==", T_BOOLEAN_OPERATOR);
    Token expectedToken2("a__", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_54)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "==eqweq" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("==", T_BOOLEAN_OPERATOR);
    Token expectedToken2("eqweq", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_55)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ">=eqweq" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(">=", T_BOOLEAN_OPERATOR);
    Token expectedToken2("eqweq", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_56)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "<=0.002" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("<=", T_BOOLEAN_OPERATOR);
    Token expectedToken2("0.002", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_57)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "==int" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("==", T_BOOLEAN_OPERATOR);
    Token expectedToken2("int", T_SPECIFIER);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_58)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "<=*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("<=", T_BOOLEAN_OPERATOR);
    Token expectedToken2("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_59)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ">=/" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(">=", T_BOOLEAN_OPERATOR);
    Token expectedToken2("/", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_60)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "==--" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("==", T_BOOLEAN_OPERATOR);
    Token expectedToken2("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_61)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "<==" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("<=", T_BOOLEAN_OPERATOR);
    Token expectedToken2("=", T_ASSIGN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_62)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "<=<=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("<=", T_BOOLEAN_OPERATOR);
    Token expectedToken2("<=", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_63)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "=-" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("=", T_ASSIGN_OPERATOR);
    Token expectedToken2("-", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_64)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "=+" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("=", T_ASSIGN_OPERATOR);
    Token expectedToken2("+", T_ADD_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_65)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "=rre" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("=", T_ASSIGN_OPERATOR);
    Token expectedToken2("rre", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_66)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "=123.123" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("=", T_ASSIGN_OPERATOR);
    Token expectedToken2("123.123", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_67)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "unsigned_int*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("unsigned_int", T_SPECIFIER);
    Token expectedToken2("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_68)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "string&" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("string", T_SPECIFIER);
    Token expectedToken2("&", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_69)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "system_handler*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("system_handler", T_SPECIFIER);
    Token expectedToken2("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_70)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(a" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("(", T_OPENING_PARENTHESIS);
    Token expectedToken2("a", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_71)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "()" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("(", T_OPENING_PARENTHESIS);
    Token expectedToken2(")", T_CLOSING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_72)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("(", T_OPENING_PARENTHESIS);
    Token expectedToken2("=", T_ASSIGN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_73)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(*" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("(", T_OPENING_PARENTHESIS);
    Token expectedToken2("*", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_74)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(==" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("(", T_OPENING_PARENTHESIS);
    Token expectedToken2("==", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_75)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "(3123.33" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("(", T_OPENING_PARENTHESIS);
    Token expectedToken2("3123.33", T_REAL_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_76)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ")a__" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(")", T_CLOSING_PARENTHESIS);
    Token expectedToken2("a__", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_77)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "))" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(")", T_CLOSING_PARENTHESIS);
    Token expectedToken2(")", T_CLOSING_PARENTHESIS);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_78)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "){}" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(")", T_CLOSING_PARENTHESIS);
    Token expectedToken2("{", T_OPENING_BRACKET);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_79)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ")eqwe" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(")", T_CLOSING_PARENTHESIS);
    Token expectedToken2("eqwe", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_80)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ")<=" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(")", T_CLOSING_PARENTHESIS);
    Token expectedToken2("<=", T_BOOLEAN_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_81)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ".eqwe" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(".", T_SEMICON);
    Token expectedToken2("eqwe", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_82)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ".0003" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(".", T_SEMICON);
    Token expectedToken2("0", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_83)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ":eqwe" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(":", T_CON);
    Token expectedToken2("eqwe", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_84)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ":dd" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(":", T_CON);
    Token expectedToken2("dd", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_85)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << ":ww" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1(":", T_CON);
    Token expectedToken2("ww", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_86)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{do" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("{", T_OPENING_BRACKET);
    Token expectedToken2("do", T_DO);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_87)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{done" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("{", T_OPENING_BRACKET);
    Token expectedToken2("done", T_DONE);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_88)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{." << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("{", T_OPENING_BRACKET);
    Token expectedToken2(".", T_SEMICON);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_89)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{qweqw" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("{", T_OPENING_BRACKET);
    Token expectedToken2("qweqw", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_90)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "{}" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("{", T_OPENING_BRACKET);
    Token expectedToken2("}", T_CLOSING_BRACKET);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_91)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}eqwe" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("}", T_CLOSING_BRACKET);
    Token expectedToken2("eqwe", T_USER_DEFINED_NAME);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_92)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}22" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("}", T_CLOSING_BRACKET);
    Token expectedToken2("22", T_INT_NUM);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_93)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}%" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("}", T_CLOSING_BRACKET);
    Token expectedToken2("%", T_NOT_DEFINED_YET);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_94)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "}&" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("}", T_CLOSING_BRACKET);
    Token expectedToken2("&", T_MULT_OPERATOR);
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue(); 
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
