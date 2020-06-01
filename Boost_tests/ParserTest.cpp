#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../include/Scanner.h"
#include "../include/Configuration.h"
#include "../include/Parser.h"
#include "../include/Visitor.h"
// integration tests
BOOST_AUTO_TEST_CASE(manual_test_1)
{
    std::string expectedVarName = "f";
    std::string expectedSpecifier = "int";
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << expectedSpecifier << " " << expectedVarName << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    auto scanner = std::make_shared<Scanner>(configuration);
    auto parser = std::make_unique<Parser>(scanner);
    parser->parse();
    auto file = parser->getProgramTree();
    BOOST_CHECK_EQUAL(file->roots.size(), 1);
    auto node = file->roots.front()->expr;
    auto declaration = std::dynamic_pointer_cast<TypeSpecifierExpression>(node);
    auto varName = declaration->name;
    auto specifier = declaration->specifier;
    BOOST_CHECK_EQUAL(varName, expectedVarName);
    BOOST_CHECK_EQUAL(specifier, expectedSpecifier);
}
BOOST_AUTO_TEST_CASE(manual_test_2)
{
    std::string expectedVarName = "f";
    std::string expectedSpecifier = "float";
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << expectedSpecifier << " " << expectedVarName << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    auto scanner = std::make_shared<Scanner>(configuration);
    auto parser = std::make_unique<Parser>(scanner);
    parser->parse();
    auto file = parser->getProgramTree();
    BOOST_CHECK_EQUAL(file->roots.size(), 1);
    auto node = file->roots.front()->expr;
    auto declaration = std::dynamic_pointer_cast<TypeSpecifierExpression>(node);
    auto varName = declaration->name;
    auto specifier = declaration->specifier;
    BOOST_CHECK_EQUAL(varName, expectedVarName);
    BOOST_CHECK_EQUAL(specifier, expectedSpecifier);
}
BOOST_AUTO_TEST_CASE(manual_test_3)
{
    std::string expectedVarName = "f";
    std::string expectedSpecifier = "int";
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << expectedSpecifier << " " << expectedVarName << "()" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    auto scanner = std::make_shared<Scanner>(configuration);
    auto parser = std::make_unique<Parser>(scanner);
    parser->parse();
    auto file = parser->getProgramTree();
    BOOST_CHECK_EQUAL(file->roots.size(), 1);
    auto node = file->roots.front()->expr;
    auto declaration = std::dynamic_pointer_cast<FunctionExpression>(node);
    auto varName = declaration->name;
    auto specifier = declaration->specifier;
    BOOST_CHECK_EQUAL(varName, expectedVarName);
    BOOST_CHECK_EQUAL(specifier, expectedSpecifier);
}
BOOST_AUTO_TEST_CASE(manual_test_4)
{
    std::string expectedVarName = "f";
    std::string expectedSpecifier = "system_handler";
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << expectedSpecifier << " " << expectedVarName << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    auto scanner = std::make_shared<Scanner>(configuration);
    auto parser = std::make_unique<Parser>(scanner);
    parser->parse();
    auto file = parser->getProgramTree();
    BOOST_CHECK_EQUAL(file->roots.size(), 1);
    auto node = file->roots.front()->expr;
    auto declaration = std::dynamic_pointer_cast<SystemHandlerDeclExpression>(node);
    auto varName = declaration->name;
    BOOST_CHECK_EQUAL(varName, expectedVarName);
}
BOOST_AUTO_TEST_CASE(manual_test_5)
{
    std::string expectedFuncName = "f";
    std::string expectedSpecifier = "int";
    std::string expectedArgSpecifier1 = "int";
    std::string expectedArgName1 = "a";
    std::string expectedArgSpecifier2 = "float";
    std::string expectedArgName2 = "b";
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << expectedSpecifier << " " << expectedFuncName << "(";
    outfile << expectedArgSpecifier1 << " " << expectedArgName1 << ", ";
    outfile << expectedArgSpecifier2 << " " << expectedArgName2 << ", ";
    outfile << ")$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    auto scanner = std::make_shared<Scanner>(configuration);
    auto parser = std::make_unique<Parser>(scanner);
    parser->parse();
    auto file = parser->getProgramTree();
    BOOST_CHECK_EQUAL(file->roots.size(), 1);
    auto node = file->roots.front()->expr;
    auto declaration = std::dynamic_pointer_cast<FunctionExpression>(node);
    auto funcName = declaration->name;
    BOOST_CHECK_EQUAL(funcName, expectedFuncName);
    auto funcSpecifier = declaration->specifier;
    BOOST_CHECK_EQUAL(funcSpecifier, expectedSpecifier);

    auto args = std::move(declaration->arguments);
    BOOST_CHECK_EQUAL(args->statements.size(), 2);
    auto arg1 = std::dynamic_pointer_cast<TypeSpecifierExpression>(args->statements[0]);
    auto arg2 = std::dynamic_pointer_cast<TypeSpecifierExpression>(args->statements[1]);

    BOOST_CHECK_EQUAL(arg1->specifier, expectedArgSpecifier1);
    BOOST_CHECK_EQUAL(arg1->name, expectedArgName1);
    BOOST_CHECK_EQUAL(arg2->specifier, expectedArgSpecifier2);
    BOOST_CHECK_EQUAL(arg2->name, expectedArgName2);
}
BOOST_AUTO_TEST_CASE(manual_test_6)
{
    std::string expectedFuncName = "f";
    std::string expectedSpecifier = "int";
    std::string expectedArgSpecifier1 = "int";
    std::string expectedArgName1 = "a";
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << expectedSpecifier << " " << expectedFuncName << "(";
    outfile << expectedArgSpecifier1 << " " << expectedArgName1 << ", ";
    outfile << ")$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    auto scanner = std::make_shared<Scanner>(configuration);
    auto parser = std::make_unique<Parser>(scanner);
    parser->parse();
    auto file = parser->getProgramTree();
    BOOST_CHECK_EQUAL(file->roots.size(), 1);
    auto node = file->roots.front()->expr;
    auto declaration = std::dynamic_pointer_cast<FunctionExpression>(node);
    auto funcName = declaration->name;
    BOOST_CHECK_EQUAL(funcName, expectedFuncName);
    auto funcSpecifier = declaration->specifier;
    BOOST_CHECK_EQUAL(funcSpecifier, expectedSpecifier);

    auto args = std::move(declaration->arguments);
    BOOST_CHECK_EQUAL(args->statements.size(), 1);
    auto arg1 = std::dynamic_pointer_cast<TypeSpecifierExpression>(args->statements[0]);

    BOOST_CHECK_EQUAL(arg1->specifier, expectedArgSpecifier1);
    BOOST_CHECK_EQUAL(arg1->name, expectedArgName1);
}

BOOST_AUTO_TEST_CASE(manual_test_7)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "int a$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    auto scanner = std::make_shared<Scanner>(configuration);
    auto parser = std::make_unique<Parser>(scanner);
    parser->parse();
    auto root = parser->getProgramTree();
    EvaluationVisitor evaluationVisitor;
    evaluationVisitor.visit(root.get());
}