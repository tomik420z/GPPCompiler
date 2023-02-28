#include "analyzer.h"

using namespace std;

int main(int argc, char *argv[])
{
    //setlocale(LC_ALL, "Russian");

    if (argc != 2) {
        std::cout << "incorrent format\n\nformat: ./execute.exe -file";
        return 1;
    }
    try {
        StateM programm1;
        programm1.StartDKA(argv[1]);
        PrintVec(vecToken);
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