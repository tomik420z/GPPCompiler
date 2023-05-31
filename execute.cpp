#include "analyzer.h"
#include "syntax.h"
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
        if (programm1.flagAnalyzer) {
            cout << "SET_CONST = ";
            print_set(set_const.begin(), set_const.end());
            cout << "SET_VARIABLE = ";
            print_set(set_var.begin(), set_var.end());
            cout << "ANALYZER: accept" << endl;
            Syntax syntax2;   
            std::cout << "++++++\n";
            syntax2.StartSyntax(); 
            std::cout << "syntax: " << syntax2.flagSyntax << std::endl;
            std::ofstream buff("test.txt");
            auto li_atom = syntax2.get_atoms();
            for(auto it = li_atom.begin(); it != li_atom.end(); ++it) {
                buff << *it << std::endl;    
            }
        }
        else {
            PrintErrors();
            cout << "Analyzer: acception error" << endl;
            
            return -1;
        }
    } catch(exception e) {
        std::cerr <<  e.what() << std::endl;
    } catch (const char* e) {
        std::cerr << e << std::endl;
    }



    
    return 0;
}