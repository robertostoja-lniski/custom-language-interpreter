
#tool for generating unit tests
input_file=config
file=/home/robert/CLionProjects/TKOM/Boost_tests/ScannerTest.cpp

cat << EOF > $file
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../include/Scanner.h"
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

    Scanner scanner("tmp.txt");
    Token expectedToken("$outputVal", ${outputType});
    scanner.getNextToken();
    auto receivedToken = scanner.getTokenValue();
    BOOST_CHECK_EQUAL(expectedToken, receivedToken);
}
EOF
((counter++))
done < "$input_file"

