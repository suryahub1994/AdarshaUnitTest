#include "../src/adarsha_test.hpp"
#include <iostream>
#include <set>
#include <string>

int main(int argc, char** argv) {
    if (argc > 1) {
        std::string argumentOne = argv[1];

        if (argumentOne == "--help" || argumentOne == "-h") {
            std::cout << "AdarshaUnitTest - Minimal C++ Test Framework\n\n";
            std::cout << "Usage:\n";
            std::cout << "  " << argv[0] << "            Run all tests\n";
            std::cout << "  " << argv[0] << " <filter>  Run only tests whose names contain <filter>\n";
            std::cout << "  " << argv[0] << " --name=a,b[,c...]  Run only listed tests\n";
            std::cout << "  " << argv[0] << " -n a b [c ...]     Run only listed tests (space-separated)\n";
            std::cout << "  " << argv[0] << " --help    Show this help message\n\n";
            std::cout << "Examples:\n";
            std::cout << "  " << argv[0] << "           # run all registered tests\n";
            std::cout << "  " << argv[0] << " math      # run only tests with 'math' in their name\n";
            return 0;
        }
        else if (argumentOne.rfind("--name=", 0) == 0 || argumentOne == "-n") {
            std::set<std::string> names;
            if (argumentOne.rfind("--name=", 0) == 0) {
                std::string actualList = argumentOne.substr(7);
                actualList += ' ';
                std::string word;

                for (int i = 0; i < static_cast<int>(actualList.size()); ++i) {
                    char c = actualList[i];
                    if (c == ',' || c == ' ') {
                        if (!word.empty()) {
                            names.insert(word);
                            word.clear();
                        }
                    } else {
                        word.push_back(c);
                    }
                }
            }
            else {
                for (int i = 2; i < argc; ++i) {
                    names.insert(argv[i]);
                }
            }

            return Adarsha::TestRepository::runAll(names);
        }
    }

    return Adarsha::TestRepository::runAll();
}
