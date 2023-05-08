#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include <list>
#include <set>
#include <array>
#include "data_token.h"
#include <unordered_set>
#include "hash_set.h"

using namespace std;

enum SymbolToken
{
    LEX_DIGIT,
    LEX_CHARACTER,
    LEX_AR_OPERATION,
    LEX_RATIO,
    LEX_L_BRACKET,
    LEX_R_BRACKET,
    LEX_SPACE,
    LEX_LF,
    LEX_COMMA,
    LEX_SEMICOLON,
    LEX_ERR_SYMB,
    LEX_COLON,
    LEX_L_SQ_BRACKET,
    LEX_R_SQ_BRACKET,
    LEX_END_MARKET
};



enum TypeRatio
{
    LESS,
    MORE,
    LESS_EQUAL,
    MORE_EQUAL,
    EQUAL,
    INEQUAL
};

enum States
{
    s_A0,
    s_A1,
    s_B1,
    s_C1,
    s_D1,
    s_E1,
    s_F1,
    s_F2,
    s_J1,
    s_M1,
    s_M2,
    s_H1,
    s_H2,
    s_H3,
    s_H4,
    s_H5,
    s_W1,
    s_G1,
    s_G1a,
    s_T1,
    s_T1a,
    s_K1,
    s_K2,
    s_K3,
    s_R1,
    s_Z1,
    s_Z2,
    s_Z3, 
    s_Z4,
    s_P1,
    s_Error,
    s_Stop
};

struct PairToken
{
    SymbolToken SToken;
    char value;
};

list<data_token> vecToken;      
set<pair<string, bool>> SetVar; 
unordered_set<int> set_const;
unordered_set<string> set_var;
vector<string> vec_errors;

class StateM
{
protected:
    PairToken s;
    int discovery_register;
    int reg_const;
    string reg_name;
    int reg_num_str;

    int reg_str_comment;

    char register_ratio;
    int cur_state;
    TokenClass register_ar_operations;
    TokenClass reg_token;
    hash_set reg_hash;

    static constexpr int state_number = 32;
    static constexpr int class_number = 14;
    
    

public:
    typedef int (StateM::*function_pointer)();
protected:

    std::array<std::array<function_pointer, class_number>, state_number> table;                          
    int A0();    
    int A0a();

    int B1();
    int B1a();
    int B1c();
    int B1d();
    int B1g();
    int B1s();
    int B1h();
    int B1i();
    int C1k();
    int B1u();

    int C1a();
    int C1b();  
    int C1c();
    int C1d();
    int C1e();
    int C1f();
    int C1g();
    int C1h();
    int C1i();  
    int C1l();

    int D1();

    int G1();
    int G1e();
    int G1f();
    int G1g();
    int G1h();
    int G1y();
    int G1k();
    int G1l();
    int G1m();
    int G1n();
    int G1o();

    int F1();
    int F2();
    int F2a();
    int F2b();
    int F2c();
    int F2_add();

    int H1();
    int H1a();
    int H2();
    int H3();
    int H3a();
    int H4();
    int H5();
    int H5a();
    int H5b();
    int K1();

    int K2();
    int K2a();

    int K3b();
    int K4a();
    int K4b();
    int K4c();

    int J1();

    int G1d();
    int G1a();
    int G1b();
    int G1c();
    

    int M1();
    int M2();
    
    int R1();
    int R1a();

    int T1();
    int T1a();
    int T1b();
    int T2();
    int T2a();

    int S1a();
    int S1b();
    int S1c();

    int Z1(); // считать [
    int Z1a(); // считать пробелы 
    int Z1b();  // ]

    int Z2a();  // считать первую цифру 
    int Z2b();  // считать остальные цифры числа  
    int Z2c();  // пробел после цифры 
    int Z2d();  // считать ] 
    int Z2e();  // считать , 

    int Z3a(); // считатть остальные проблелы 
    int Z3d(); // считать ] 
    int Z3e(); // считать ,

    int Z4a(); // счиать пробелы 
    int Z4b(); // считать цифру 

    int Z5a();

    int E1(); //ошибка переменной
    int E1a();
    int E2(); //символы
    int E2a();
    int E3(); //операции
    int E3a();
    int E4(); //хэш
    int E4a();
    int E5(); //метки
    int E5a();
    int E6(); //raise
    int E6a();
    int E7(); //comment
    int E7a();
    int E8();
    int E9(); //end switch
    int E9a();
    int E10();

    int P1();

    int Q1();

    int Error1();
    void CreateVariable();
    void CreateConst();
    void CreateList();
    void CreateAttitude();

public:
    bool flagAnalyzer;
    set<int> SetConst; 
    
    void transliterator(char ch);                 
    void StartDKA(const char *NameFile);            
    void LineProcessing(const string &RegisterStr); 
    friend void PrintLableList(set<int> &obj);
    friend void PrintConst(set<int> &obj);

    StateM(const StateM&) = delete;
    StateM& operator=(const StateM&) = delete;

    StateM()
    {
        cur_state = s_A0;
        reg_num_str = 0;


        for (int i = 0; i < state_number; ++i)
            for (int j = 0; j < class_number; ++j)
                table[i][j] = &StateM::Error1;
        
        table[s_A0][LEX_SPACE] = &StateM::A0; //пропуск пробелов
        table[s_A0][LEX_LF] = &StateM::A0a; //перевод строки, регистр строки +1
        table[s_A0][LEX_SEMICOLON] = &StateM::D1; //создание лексемы ;
        table[s_A0][LEX_DIGIT] = &StateM::B1;   // создание числа
        table[s_A0][LEX_AR_OPERATION] = &StateM::G1;
        table[s_A0][LEX_RATIO] = &StateM::F1;
        table[s_A0][LEX_CHARACTER] = &StateM::C1a;
        table[s_A0][LEX_L_BRACKET] = &StateM::R1;
        table[s_A0][LEX_R_BRACKET] = &StateM::R1;
        table[s_A0][LEX_COLON] = &StateM::T1;
        table[s_A0][LEX_COMMA] =&StateM::S1a;
        table[s_A0][LEX_L_SQ_BRACKET] = &StateM::Z1;

        table[s_A0][LEX_R_SQ_BRACKET] = &StateM::E4;

        table[s_A0][LEX_ERR_SYMB] = &StateM::E2;

        table[s_W1][LEX_AR_OPERATION] =&StateM::E3;
    
        table[s_W1][LEX_SPACE] = &StateM::G1e; 
        table[s_W1][LEX_LF] = &StateM::G1f;
        table[s_W1][LEX_SEMICOLON] = &StateM::G1g;
        table[s_W1][LEX_DIGIT] = &StateM::G1h;
        table[s_W1][LEX_RATIO] = &StateM::G1y;
        table[s_W1][LEX_CHARACTER] = &StateM::G1k;
        table[s_W1][LEX_L_BRACKET] = &StateM::G1l;
        table[s_W1][LEX_R_BRACKET] = &StateM::G1l;
        table[s_W1][LEX_COLON] = &StateM::G1m;
        table[s_W1][LEX_COMMA] =&StateM::G1n;
        table[s_W1][LEX_L_SQ_BRACKET] = &StateM::G1o;
        table[s_W1][LEX_ERR_SYMB] = &StateM::E2;
        
        // parsing constant 
        table[s_B1][LEX_DIGIT] = &StateM::B1a;
        table[s_B1][LEX_SPACE] = &StateM::B1c;
        table[s_B1][LEX_SEMICOLON] = &StateM::B1d;
        table[s_B1][LEX_SPACE] = &StateM::B1s;
        table[s_B1][LEX_LF] = &StateM::B1g;
        table[s_B1][LEX_AR_OPERATION] = &StateM::B1h;
        table[s_B1][LEX_RATIO] = &StateM::B1i;
        table[s_B1][LEX_COMMA] = &StateM::S1b;  
        table[s_B1][LEX_L_BRACKET] = &StateM::B1u;
        table[s_B1][LEX_R_BRACKET] = &StateM::B1u;

        table[s_B1][LEX_CHARACTER] = &StateM::E1;

        table[s_B1][LEX_R_SQ_BRACKET] =&StateM::E4;

        // parsing variable 
        table[s_C1][LEX_CHARACTER] = &StateM::C1b;
        table[s_C1][LEX_DIGIT] = &StateM::C1c;
        table[s_C1][LEX_SPACE] = &StateM::C1d;
        table[s_C1][LEX_RATIO] = &StateM::C1e;
        table[s_C1][LEX_SEMICOLON] = &StateM::C1f;
        table[s_C1][LEX_LF] = &StateM::C1g;
        table[s_C1][LEX_L_BRACKET] = &StateM::C1k;
        table[s_C1][LEX_R_BRACKET] = &StateM::C1k;
        table[s_C1][LEX_AR_OPERATION] = &StateM::C1l;
        table[s_C1][LEX_COMMA] = &StateM::S1c;   

        table[s_C1][LEX_R_SQ_BRACKET] =&StateM::E4;
        table[s_C1][LEX_ERR_SYMB] = &StateM::E2;     

        table[s_F1][LEX_RATIO] = &StateM::F2; // двухсимвольный знак отношения 
        table[s_F1][LEX_DIGIT] = &StateM::F2a;
        table[s_F1][LEX_CHARACTER] = &StateM::F2b; 
        table[s_F1][LEX_SPACE] = &StateM::F2c;


        table[s_M1][LEX_CHARACTER] = &StateM::M1;
        table[s_M1][LEX_L_BRACKET] = &StateM::C1k;
        table[s_M1][LEX_R_BRACKET] = &StateM::C1k;
        table[s_M1][LEX_DIGIT] = &StateM::C1c;
        table[s_M1][LEX_SPACE] = &StateM::C1d;
        table[s_M1][LEX_LF] = &StateM::C1g;
        table[s_M1][LEX_COMMA] = &StateM::S1c;
        
        table[s_H1][LEX_CHARACTER] = &StateM::C1b;
        table[s_H1][LEX_DIGIT] = &StateM::C1b;
        table[s_H1][LEX_SPACE] = &StateM::H1;
        table[s_H1][LEX_SEMICOLON] = &StateM::H1a;
        table[s_H1][LEX_L_BRACKET] = &StateM::R1a;
        table[s_H1][LEX_R_BRACKET] = &StateM::R1a;
        table[s_H1][LEX_LF] = &StateM::Q1;

        table[s_H1][LEX_COMMA] = &StateM::E8;

        table[s_R1][LEX_CHARACTER] = &StateM::C1b;
        table[s_R1][LEX_DIGIT] = &StateM::C1b;
        table[s_R1][LEX_SPACE] = &StateM::P1;
        table[s_R1][LEX_SEMICOLON] = &StateM::H1a;

        table[s_P1][LEX_SPACE]= &StateM::P1;
        table[s_P1][LEX_SEMICOLON] = &StateM::H1a;
        
        table[s_P1][LEX_DIGIT] = &StateM::E6;
        table[s_P1][LEX_CHARACTER] = &StateM::E6;
        table[s_P1][LEX_L_BRACKET] = &StateM::E6;
        table[s_P1][LEX_R_BRACKET] = &StateM::E6;
        table[s_P1][LEX_AR_OPERATION] = &StateM::E6;
        table[s_P1][LEX_RATIO] = &StateM::E6;
        table[s_P1][LEX_COLON] = &StateM::E6;
        table[s_P1][LEX_ERR_SYMB] = &StateM::E2;
        table[s_P1][LEX_L_SQ_BRACKET] = &StateM::E6;
        table[s_P1][LEX_LF] = &StateM::E6a;
        table[s_P1][LEX_R_SQ_BRACKET] = &StateM::E6;

        table[s_R1][LEX_L_BRACKET] = &StateM::E6;
        table[s_R1][LEX_R_BRACKET] = &StateM::E6;
        table[s_R1][LEX_AR_OPERATION] = &StateM::E6;
        table[s_R1][LEX_RATIO] = &StateM::E6;
        table[s_R1][LEX_COLON] = &StateM::E6;
        table[s_R1][LEX_ERR_SYMB] = &StateM::E2;
        table[s_R1][LEX_L_SQ_BRACKET] = &StateM::E6;
        table[s_R1][LEX_LF] = &StateM::E6a;
        table[s_R1][LEX_R_SQ_BRACKET] = &StateM::E6;

        // end switch
        table[s_H2][LEX_SPACE] = &StateM::H3;
        table[s_H2][LEX_CHARACTER] =&StateM::C1b;

        table[s_H2][LEX_L_BRACKET] = &StateM::E9;
        table[s_H2][LEX_R_BRACKET] = &StateM::E9;
        table[s_H2][LEX_AR_OPERATION] = &StateM::E9;
        table[s_H2][LEX_RATIO] = &StateM::E9;
        table[s_H2][LEX_COLON] = &StateM::E9;
        table[s_H2][LEX_ERR_SYMB] = &StateM::E2;
        table[s_H2][LEX_L_SQ_BRACKET] = &StateM::E9;
        table[s_H2][LEX_LF] = &StateM::E9a;
        table[s_H2][LEX_R_SQ_BRACKET] = &StateM::E9;
        table[s_H2][LEX_COMMA] =&StateM::E9;
        table[s_H2][LEX_DIGIT] =&StateM::E9;
        table[s_H2][LEX_SEMICOLON] =&StateM::E9;

        table[s_H3][LEX_CHARACTER] = &StateM::H3a;
        table[s_H3][LEX_SPACE] = &StateM::H3;

        table[s_H3][LEX_L_BRACKET] = &StateM::E9;
        table[s_H3][LEX_R_BRACKET] = &StateM::E9;
        table[s_H3][LEX_AR_OPERATION] = &StateM::E9;
        table[s_H3][LEX_RATIO] = &StateM::E9;
        table[s_H3][LEX_COLON] = &StateM::E9;
        table[s_H3][LEX_ERR_SYMB] = &StateM::E2;
        table[s_H3][LEX_L_SQ_BRACKET] = &StateM::E9;
        table[s_H3][LEX_LF] = &StateM::E9a;
        table[s_H3][LEX_R_SQ_BRACKET] = &StateM::E9;
        table[s_H3][LEX_COMMA] =&StateM::E9;
        table[s_H3][LEX_DIGIT] =&StateM::E9;
        table[s_H3][LEX_SEMICOLON] =&StateM::E9;

        table[s_H4][LEX_CHARACTER] = &StateM::H4;

        table[s_H4][LEX_SPACE] = &StateM::E9;
        table[s_H4][LEX_L_BRACKET] = &StateM::E9;
        table[s_H4][LEX_R_BRACKET] = &StateM::E9;
        table[s_H4][LEX_AR_OPERATION] = &StateM::E9;
        table[s_H4][LEX_RATIO] = &StateM::E9;
        table[s_H4][LEX_COLON] = &StateM::E9;
        table[s_H4][LEX_ERR_SYMB] = &StateM::E2;
        table[s_H4][LEX_L_SQ_BRACKET] = &StateM::E9;
        table[s_H4][LEX_LF] = &StateM::E9a;
        table[s_H4][LEX_R_SQ_BRACKET] = &StateM::E9;
        table[s_H4][LEX_COMMA] =&StateM::E9;
        table[s_H4][LEX_DIGIT] =&StateM::E9;
        table[s_H4][LEX_SEMICOLON] =&StateM::E9;
        
        table[s_H5][LEX_LF] = &StateM::H5a;
        table[s_H5][LEX_SPACE] = &StateM::H5;
        table[s_H5][LEX_SEMICOLON] = &StateM::H5b;

        table[s_H5][LEX_L_BRACKET] = &StateM::E9;
        table[s_H5][LEX_R_BRACKET] = &StateM::E9;
        table[s_H5][LEX_AR_OPERATION] = &StateM::E9;
        table[s_H5][LEX_RATIO] = &StateM::E9;
        table[s_H5][LEX_COLON] = &StateM::E9;
        table[s_H5][LEX_ERR_SYMB] = &StateM::E2;
        table[s_H5][LEX_L_SQ_BRACKET] = &StateM::E9;
        table[s_H5][LEX_R_SQ_BRACKET] = &StateM::E9;
        table[s_H5][LEX_COMMA] =&StateM::E9;
        table[s_H5][LEX_DIGIT] =&StateM::E9;

        //comment
        table[s_G1][LEX_CHARACTER] = &StateM::C1b;
        table[s_G1][LEX_DIGIT] = &StateM::C1b;
        table[s_G1][LEX_SPACE] = &StateM::G1d;


        table[s_G1a][LEX_AR_OPERATION] = &StateM::G1a;
        table[s_G1a][LEX_RATIO] = &StateM::G1a;
        table[s_G1a][LEX_CHARACTER] = &StateM::G1a;
        table[s_G1a][LEX_COLON] = &StateM::G1a;
        table[s_G1a][LEX_COMMA] = &StateM::G1a;
        table[s_G1a][LEX_DIGIT] = &StateM::G1a;
        table[s_G1a][LEX_ERR_SYMB] = &StateM::G1a;
        table[s_G1a][LEX_L_BRACKET] = &StateM::G1a;
        table[s_G1a][LEX_L_SQ_BRACKET] = &StateM::G1a;
        table[s_G1a][LEX_R_BRACKET] = &StateM::G1a;
        table[s_G1a][LEX_R_SQ_BRACKET] = &StateM::G1a;
        table[s_G1a][LEX_SPACE] = &StateM::G1a;
        table[s_G1a][LEX_SEMICOLON] = &StateM::G1b;
        table[s_G1a][LEX_LF] = &StateM::G1c;
        //table[s_G1a][LEX_LF] = &StateM::O1;


        //метка
        table[s_T1][LEX_DIGIT] = &StateM::T1a;
        table[s_T1a][LEX_DIGIT] = &StateM::T1b;
        table[s_T1a][LEX_SPACE] = &StateM::T2;
        table[s_T1a][LEX_LF] = &StateM::T2a;

        table[s_T1a][LEX_AR_OPERATION] = &StateM::E5;
        table[s_T1a][LEX_RATIO] = &StateM::E5;
        table[s_T1a][LEX_CHARACTER] = &StateM::E5;
        table[s_T1a][LEX_COLON] = &StateM::E5;
        table[s_T1a][LEX_COMMA] = &StateM::E5;
        table[s_T1a][LEX_ERR_SYMB] = &StateM::E2;
        table[s_T1a][LEX_L_BRACKET] = &StateM::E5;
        table[s_T1a][LEX_L_SQ_BRACKET] = &StateM::E5;
        table[s_T1a][LEX_R_BRACKET] = &StateM::E5;
        table[s_T1a][LEX_SEMICOLON] = &StateM::E5;

        table[s_T1][LEX_AR_OPERATION] = &StateM::E5;
        table[s_T1][LEX_RATIO] = &StateM::E5;
        table[s_T1][LEX_CHARACTER] = &StateM::E5;
        table[s_T1][LEX_COLON] = &StateM::E5;
        table[s_T1][LEX_COMMA] = &StateM::E5;
        table[s_T1][LEX_ERR_SYMB] = &StateM::E2;
        table[s_T1][LEX_L_BRACKET] = &StateM::E5;
        table[s_T1][LEX_L_SQ_BRACKET] = &StateM::E5;
        table[s_T1][LEX_LF] = &StateM::E5a;
        table[s_T1][LEX_R_BRACKET] = &StateM::E5;
        table[s_T1][LEX_R_SQ_BRACKET] = &StateM::E5;
        table[s_T1][LEX_SEMICOLON] = &StateM::E5;
        table[s_T1][LEX_SPACE] = &StateM::E5;

        table[s_J1][LEX_DIGIT] = &StateM::J1;
        table[s_J1][LEX_CHARACTER] = &StateM::J1;
        table[s_J1][LEX_AR_OPERATION] = &StateM::J1;
        table[s_J1][LEX_RATIO] = &StateM::J1;
        table[s_J1][LEX_L_BRACKET] = &StateM::J1;
        table[s_J1][LEX_R_BRACKET] = &StateM::J1;
        table[s_J1][LEX_SPACE] = &StateM::J1;
        table[s_J1][LEX_LF] = &StateM::A0a;
        table[s_J1][LEX_COMMA] = &StateM::J1;
        table[s_J1][LEX_SEMICOLON] = &StateM::J1;
        table[s_J1][LEX_ERR_SYMB] = &StateM::J1;
        table[s_J1][LEX_COLON] = &StateM::J1;
        table[s_J1][LEX_L_SQ_BRACKET] = &StateM::J1;
        table[s_J1][LEX_R_SQ_BRACKET] = &StateM::J1;

        
        //goto, then, else
        table[s_K1][LEX_SPACE] = &StateM::K1;
        table[s_K1][LEX_CHARACTER] = &StateM::C1b;
        table[s_K1][LEX_DIGIT] = &StateM::C1b;


        table[s_K1][LEX_RATIO] = &StateM::E5;
        table[s_K1][LEX_SEMICOLON] = &StateM::E5;
        table[s_K1][LEX_LF] = &StateM::E5a;
        table[s_K1][LEX_L_BRACKET] = &StateM::E5;
        table[s_K1][LEX_R_BRACKET] = &StateM::E5;
        table[s_K1][LEX_AR_OPERATION] = &StateM::E5;
        table[s_K1][LEX_COMMA] = &StateM::E5;  
        table[s_K1][LEX_COLON] = &StateM::E5;
        table[s_K1][LEX_ERR_SYMB] = &StateM::E2;
        table[s_K1][LEX_L_SQ_BRACKET] = &StateM::E5;
        table[s_K1][LEX_R_SQ_BRACKET] = &StateM::E5;


        table[s_K2][LEX_SPACE] = &StateM::K2;
        table[s_K2][LEX_DIGIT] = &StateM::K2a;

        table[s_K2][LEX_AR_OPERATION] = &StateM::E5;
        table[s_K2][LEX_RATIO] = &StateM::E5;
        table[s_K2][LEX_CHARACTER] = &StateM::E5;
        table[s_K2][LEX_COLON] = &StateM::E5;
        table[s_K2][LEX_COMMA] = &StateM::E5;
        table[s_K2][LEX_ERR_SYMB] = &StateM::E5;
        table[s_K2][LEX_L_BRACKET] = &StateM::E5;
        table[s_K2][LEX_L_SQ_BRACKET] = &StateM::E5;
        table[s_K2][LEX_LF] = &StateM::E5a;
        table[s_K2][LEX_R_BRACKET] = &StateM::E5;
        table[s_K2][LEX_R_SQ_BRACKET] = &StateM::E5;
        table[s_K2][LEX_SEMICOLON] = &StateM::E5;


        table[s_K3][LEX_DIGIT] = &StateM::K3b;
        table[s_K3][LEX_SPACE] =&StateM::K4a;
        table[s_K3][LEX_LF] = &StateM::K4b;
        table[s_K3][LEX_SEMICOLON] = &StateM::K4c;

        table[s_K3][LEX_AR_OPERATION] = &StateM::E5;
        table[s_K3][LEX_RATIO] = &StateM::E5;
        table[s_K3][LEX_CHARACTER] = &StateM::E5;
        table[s_K3][LEX_COLON] = &StateM::E5;
        table[s_K3][LEX_COMMA] = &StateM::E5;
        table[s_K3][LEX_ERR_SYMB] = &StateM::E5;
        table[s_K3][LEX_L_BRACKET] = &StateM::E5;
        table[s_K3][LEX_L_SQ_BRACKET] = &StateM::E5;
        table[s_K3][LEX_R_BRACKET] = &StateM::E5;
        table[s_K3][LEX_R_SQ_BRACKET] = &StateM::E5;

        table[s_Z1][LEX_SPACE] = &StateM::Z1a;
        table[s_Z1][LEX_R_SQ_BRACKET] = &StateM::Z1b;
        table[s_Z1][LEX_DIGIT] = &StateM::Z2a;

        table[s_Z1][LEX_RATIO] = &StateM::E4;
        table[s_Z1][LEX_AR_OPERATION] = &StateM::E4;
        table[s_Z1][LEX_CHARACTER] = &StateM::E4;
        table[s_Z1][LEX_COLON] = &StateM::E4;
        table[s_Z1][LEX_COMMA] = &StateM::E4;
        table[s_Z1][LEX_ERR_SYMB] = &StateM::E2;
        table[s_Z1][LEX_L_BRACKET] = &StateM::E4;
        table[s_Z1][LEX_L_SQ_BRACKET] = &StateM::E4;
        table[s_Z1][LEX_LF] = &StateM::E4a;
        table[s_Z1][LEX_R_BRACKET] = &StateM::E4;
        table[s_Z1][LEX_SEMICOLON] = &StateM::E4;
        
        table[s_Z2][LEX_DIGIT] = &StateM::Z2b;
        table[s_Z2][LEX_SPACE] = &StateM::Z2c;
        table[s_Z2][LEX_R_SQ_BRACKET] = &StateM::Z2d; // final
        table[s_Z2][LEX_COMMA] = &StateM::E4;

        table[s_Z2][LEX_RATIO] = &StateM::E4;
        table[s_Z2][LEX_AR_OPERATION] = &StateM::E4;
        table[s_Z2][LEX_CHARACTER] = &StateM::E4;
        table[s_Z2][LEX_COLON] = &StateM::E4;
        table[s_Z2][LEX_ERR_SYMB] = &StateM::E2;
        table[s_Z2][LEX_L_BRACKET] = &StateM::E4;
        table[s_Z2][LEX_L_SQ_BRACKET] = &StateM::E4;
        table[s_Z2][LEX_LF] = &StateM::E4a;
        table[s_Z2][LEX_R_BRACKET] = &StateM::E4;
        table[s_Z2][LEX_SEMICOLON] = &StateM::E4;

        table[s_Z3][LEX_SPACE] = &StateM::Z3a;
        table[s_Z3][LEX_R_SQ_BRACKET] = &StateM::Z2d;
        table[s_Z3][LEX_COMMA] = &StateM::E4;

        table[s_Z3][LEX_RATIO] = &StateM::E4;
        table[s_Z3][LEX_AR_OPERATION] = &StateM::E4;
        table[s_Z3][LEX_CHARACTER] = &StateM::E4;
        table[s_Z3][LEX_COLON] = &StateM::E4;
        table[s_Z3][LEX_DIGIT] = &StateM::Z2b;
        table[s_Z3][LEX_ERR_SYMB] = &StateM::E2;
        table[s_Z3][LEX_L_BRACKET] = &StateM::E4;
        table[s_Z3][LEX_L_SQ_BRACKET] = &StateM::E4;
        table[s_Z3][LEX_LF] = &StateM::E4a;
        table[s_Z3][LEX_R_BRACKET] = &StateM::E4;
        table[s_Z3][LEX_SEMICOLON] = &StateM::E4;

        table[s_Z4][LEX_SPACE] = &StateM::Z5a;
        table[s_Z4][LEX_DIGIT] = &StateM::Z2a;

        table[s_Z4][LEX_R_SQ_BRACKET] = &StateM::E4;
        table[s_Z4][LEX_RATIO] = &StateM::E4;
        table[s_Z4][LEX_AR_OPERATION] = &StateM::E4;
        table[s_Z4][LEX_CHARACTER] = &StateM::E4;
        table[s_Z4][LEX_COMMA] = &StateM::E4;
        table[s_Z4][LEX_COLON] = &StateM::E4;
        table[s_Z4][LEX_ERR_SYMB] = &StateM::E2;
        table[s_Z4][LEX_L_BRACKET] = &StateM::E4;
        table[s_Z4][LEX_L_SQ_BRACKET] = &StateM::E4;
        table[s_Z4][LEX_LF] = &StateM::E4a;
        table[s_Z4][LEX_R_BRACKET] = &StateM::E4;
        table[s_Z4][LEX_SEMICOLON] = &StateM::E4;
        
    }

    ~StateM()
    {
        /*for (int i = 0; i < state_number; ++i) {
            delete[] table[i];
        }
        delete[] table;*/
    }
};

void StateM::StartDKA(const char *NameFile)
{
    flagAnalyzer = true;
    fstream buff(NameFile);

    if (!buff.is_open())
    {
        cout << "file "<< NameFile << " didn't open" <<   endl;
        return;
    }

    string RegisterStr;
    while (!buff.eof())
    {
        if (!RegisterStr.empty()) {
            RegisterStr.clear();
        }

        getline(buff, RegisterStr);
        RegisterStr += '\n';
        LineProcessing(RegisterStr);
    }

    if (cur_state == s_G1a) {
        vecToken.emplace_back(reg_str_comment, ERR_TOKEN);
        vec_errors.emplace_back(to_string(reg_str_comment+1) + ": comment isn't closed");
        flagAnalyzer = false;
    }
    
    vecToken.emplace_back(0, END_MARKER);
    buff.close();
}

void StateM::LineProcessing(const string &RegisterStr)
{
    for (int i = 0; i < RegisterStr.size(); ++i)
    {
        transliterator(RegisterStr[i]);
        cur_state = (this->*table[cur_state][s.SToken])();
    }
}


#endif