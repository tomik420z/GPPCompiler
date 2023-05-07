#include "analyzer.h"

using namespace std;

int main(int argc, char *argv[])
{

    if (argc != 2) {
        std::cout << "incorrent form\at\n\nformat: ./execute.exe -file";
        return 1;
    }
    try {
        StateM programm1;
        programm1.StartDKA(argv[1]);
        PrintVec(vecToken);
        cout << "SET_CONST = ";
        print_set(set_const.begin(), set_const.end());
        cout << "SET_VARIABLE = ";
        print_set(set_var.begin(), set_var.end());
        PrintErrors();
    if (programm1.flagAnalyzer == true) {
        cout << "ANALYZER: accept" << endl;
    }
    else {
        cout << "Analyzer: acception error" << endl;
        
        return -1;
    }
    } catch(exception e) {
        std::cerr <<  e.what() << std::endl;
    }


    
    return 0;
}