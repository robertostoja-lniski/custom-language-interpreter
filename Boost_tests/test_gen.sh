
input_file_single_token=config
input_file_mult_token=config_double
file=ScannerTest.cpp

cat << EOF > $file
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../include/Scanner.h"
#include "../include/Configuration.h"
#include "../src/Scanner.cpp"
EOF

# echo " " > $file
counter=0
while read -r input outputVal outputType
do

cat << EOF >> $file
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_$counter)
{
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "$input" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken("$outputVal", ${outputType});
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue();
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
EOF
((counter++))
done < "$input_file_single_token"

counter=0
while read -r input outputVal1 outputType1 outputVal2 outputType2
do

cat << EOF >> $file
BOOST_AUTO_TEST_CASE(AUTO_GENERATED_TEST_MULTI_NON_UNIT_$counter)
{
    // not a typical unit test, two things are chcked
    std::ofstream outfile;
    outfile.open("tmp.txt", std::ofstream::out | std::ofstream::trunc);
    outfile << "$input" << "$";
    outfile.close();

    Configuration configuration;
    configuration.inputPath = "tmp.txt";
    Scanner scanner(configuration);
    Token expectedToken1("$outputVal1", ${outputType1});
    Token expectedToken2("$outputVal2", ${outputType2});
    scanner.getNextToken();
    auto receivedToken1 = scanner.getTokenValue();
    scanner.getNextToken();
    auto receivedToken2 = scanner.getTokenValue();
    BOOST_CHECK_EQUAL(expectedToken1, receivedToken1);
    BOOST_CHECK_EQUAL(expectedToken2, receivedToken2);
}
EOF
((counter++))
done < "$input_file_mult_token"
