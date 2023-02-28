#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include <list>
#include <set>
#include "data_token.h"
#include "LIST.h"

using namespace std;

enum SymbolToken
{
    LEX_DIGIT,
    LEX_CHARACTER,
    LEX_AR_OPERATION,
    LEX_ATTITUDE,
    LEX_L_BRACKET,
    LEX_R_BRACKET,
    LEX_SPACE,
    LEX_LF,
    LEX_COMMA,
    LEX_SEMICOLON,
    LEX_ERR_SYMB,
    LEX_COLON,
    LEX_L_SQ_BRACKET,
    LEX_R_SQ_BRACKET
};



enum TypeAttitude
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
    s_Error,
    s_Stop
};

struct Variable
{
    int Type;          // 0 -  ����������, 1 - ���������, 2 - ������-���������
    bool TypeVariable; // ��� ������������ ����� ������� ������
    string name_value;
    int const_value;
    List uintList;

    Variable &operator=(Variable &obj)
    {
        if (this == &obj)
            return *this;

        if (obj.Type != Type)
            throw "Err";

        name_value = obj.name_value;
        const_value = obj.const_value;

        return *this;
    }
};

string getFromVar(void *i)
{
    string res;

    if (((Variable *)(i))->Type == 1)
    {
        res += to_string(((Variable *)(i))->const_value);
    }
    else if (((Variable *)(i))->Type == 0)
    {
        res += ((Variable *)(i))->name_value;
    }
    if (((Variable *)(i))->Type == 2)
    {
        res = "{";
        for (List::Iterator it = (((Variable *)(i))->uintList.begin()); it != (((Variable *)(i))->uintList.end()); ++it)
        {
            res += to_string(*it);
            if (it + 1 != (((Variable *)(i))->uintList.end()))
                res += ",";
        }
        res += "}";
    }
    return res;
}

struct PairToken
{
    SymbolToken SToken;
    char value;
};

list<data_token> vecToken;      
set<pair<string, bool>> SetVar; 

class StateM
{
protected:
    PairToken s;
    int discovery_register;
    int reg_const;
    string reg_name;
    int reg_num_str;
    char register_ratio;
    int cur_state;

    int state_number; 
    int class_number; 
    typedef int (StateM::*function_pointer)();
    function_pointer **table; 
                              
    void MemoryTable();
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

    int C1a();
    int C1b();  
    int C1c();
    int C1d();
    int C1e();
    int C1f();
    int C1g();
    int C1h();
    int C1i();  

    int D1();

    int G1();
    
    int F1();
    int F2();
    int F2a();
    int F2b();
    int F2c();
    int F2_add();

    int M1();
    int M2();
    

    
  /*  int A0b();
    int A0c();
    int A0d();
    int A0e();
    int A0i();
    int A0j();
    int A0k();
    int A0l();
    int A0m();
    int A0n();
    int A0o();
    int A0p();
    int A0q();
    int A0r();
    int A0s();
    int A0t();
    int A0u();

    int A1();
    int A1a();
    int A1vb();
    int A1c();
    int A1vd();
    int A1ce();
    int A1vf();
    int A1vi();
    int A1cg();
    int A1ci();
    int A1vj();
    int A1cj();
    int A1vk();
    int A1vn();
    int A1vo();
    int A1ck();
    int A1vl();
    int A1cl();
    int A1h();
    int A1vm();
    int A1i();
    int A1j();
    int B1a();
    int B1b();
    int C1a();
    int C1b();
    int D1();
    int E1();
    int F1();
    int G1a();
    int G1b();
    int F1a();
    int H1();
    int N1a();
    int N1b();
    int N1c();
    int N1d();

    int M1();

    int O1();
    int O1a();
    int O1b();
    int O1c();

    int O2a();
    int O2b();
    int O3a();
    int O3b();
    int O3c();
    int O3d();

    int P2();
    int P3();
    int P4();
    int P5();

    int R1();
    int R2();
    int R3a();
    int R3b();
    int R4b();
    int R5a();
    int R5b();

    int Q1a();
    int Q1b();

    int Z1a(); // UNIT
    int Z1b(); // INTERS
    int Z1c(); // DIFF
    int Z1d(); //SYMM_DIFF
    int Z1e(); // ADD
    int Z1f(); // ACCES
    int Z1g(); // POW

    int Z2();
    int J1();

    int Z2a(); // LOAD
    int Z2b(); // LOAD*

    int Z3a();
    int Z3b(); // PUT*
    */

    int Error1();
    void CreateVariable();
    void CreateConst();
    void CreateList();
    void CreateAttitude();

public:
    bool flagAnalyzer;
    set<int> SetConst; 
    List RegList;

    void transliterator(char ch);                 
    void StartDKA(const char *NameFile);            
    void LineProcessing(const string &RegisterStr); 
    friend void PrintVec(list<data_token> &obj);
    friend void PrintVarList(vector<Variable> &obj);
    friend void PrintLableList(set<int> &obj);
    friend void PrintConst(set<int> &obj);

    StateM()
    {
        
        cur_state = s_A0;
        state_number = 32;
        class_number = 14;
        reg_num_str = 0;
        MemoryTable();

        for (int i = 0; i < state_number; ++i)
            for (int j = 0; j < class_number; ++j)
                table[i][j] = &StateM::Error1;
        
        table[s_A0][LEX_SPACE] = &StateM::A0; //пропуск пробелов
        table[s_A0][LEX_LF] = &StateM::A0a; //перевод строки, регистр строки +1
        table[s_A0][LEX_SEMICOLON] = &StateM::D1; //создание лексемы ;
        table[s_A0][LEX_DIGIT] = &StateM::B1;   // создание строки
        table[s_A0][LEX_AR_OPERATION] = &StateM::G1;
        table[s_A0][LEX_ATTITUDE] = &StateM::F1;
        table[s_A0][LEX_CHARACTER] = &StateM::C1a;

        table[s_B1][LEX_DIGIT] = &StateM::B1a;
        table[s_B1][LEX_SPACE] = &StateM::B1c;
        table[s_B1][LEX_SEMICOLON] = &StateM::B1d;
        table[s_B1][LEX_SPACE] = &StateM::B1s;
        table[s_B1][LEX_LF] = &StateM::B1g;
        table[s_B1][LEX_AR_OPERATION] = &StateM::B1h;
        table[s_B1][LEX_ATTITUDE] = &StateM::B1i;

        table[s_C1][LEX_CHARACTER] = &StateM::C1b;
        table[s_C1][LEX_DIGIT] = &StateM::C1c;
        table[s_C1][LEX_SPACE] = &StateM::C1d;
        table[s_C1][LEX_ATTITUDE] = &StateM::C1e;
        table[s_C1][LEX_SEMICOLON] = &StateM::C1f;
        table[s_C1][LEX_LF] = &StateM::C1g;
        //table[s_C1][LEFT_BRACKET] = &StateM::C1h;
        //table[s_C1][RIGHT_BRACKET] = &StateM::C1i;
    

        table[s_F1][LEX_ATTITUDE] = &StateM::F2; // двухсимвольный знак отношения 
        table[s_F1][LEX_DIGIT] = &StateM::F2a;
        //table[s_F1][LEX_CHARACTER] = &StateM::F2b; 
        table[s_F1][LEX_SPACE] = &StateM::F2c;

        
        /*
        table[s_A0][LEX_SPACE] = &StateM::A1;
        table[s_A0][LEX_L_BRACKET] = &StateM::G1a;
        table[s_A0][LEX_R_BRACKET] = &StateM::G1b;
        table[s_A0][LEX_SEMICOLON] = &StateM::D1;
        table[s_A0][LEX_LF] = &StateM::A1a;
        table[s_A0][LEX_CHARACTER] = &StateM::Q1a;
        table[s_A0][LEX_DIGIT] = &StateM::Q1a;

        table[s_A1][LEX_SPACE] = &StateM::A1;
        table[s_A1][LEX_LF] = &StateM::A1a;
        table[s_A1][LEX_CHARACTER] = &StateM::F1;
        table[s_A1][LEX_DIGIT] = &StateM::C1a;
        table[s_A1][LEX_SEMICOLON] = &StateM::D1;
        table[s_A1][LEX_AR_OPERATION] = &StateM::E1;
        table[s_A1][LEX_L_BRACKET] = &StateM::G1a;
        table[s_A1][LEX_R_BRACKET] = &StateM::G1b;
        table[s_A1][LEX_ATTITUDE] = &StateM::H1;
        table[s_A1][LEX_COLON] = &StateM::O1;
        table[s_A1][LEX_L_SQ_BRACKET] = &StateM::R2;
        table[s_A1][LEX_COMMA] = &StateM::Z2;

        table[s_B1][LEX_CHARACTER] = &StateM::B1b;
        table[s_B1][LEX_DIGIT] = &StateM::B1a;
        table[s_B1][LEX_SPACE] = &StateM::A1vb;
        table[s_B1][LEX_LF] = &StateM::A1vd;
        table[s_B1][LEX_AR_OPERATION] = &StateM::A1vf;
        table[s_B1][LEX_SEMICOLON] = &StateM::A1vi;
        table[s_B1][LEX_L_BRACKET] = &StateM::A1vj;
        table[s_B1][LEX_R_BRACKET] = &StateM::A1vk;
        table[s_B1][LEX_ATTITUDE] = &StateM::A1vl;
        table[s_B1][LEX_COMMA] = &StateM::A1vm;
        table[s_B1][LEX_COLON] = &StateM::O1b;

        table[s_C1][LEX_DIGIT] = &StateM::C1b;
        table[s_C1][LEX_SPACE] = &StateM::A1c;
        table[s_C1][LEX_LF] = &StateM::A1ce;
        table[s_C1][LEX_AR_OPERATION] = &StateM::A1cg;
        table[s_C1][LEX_SEMICOLON] = &StateM::A1ci;
        table[s_C1][LEX_L_BRACKET] = &StateM::A1cj;
        table[s_C1][LEX_R_BRACKET] = &StateM::A1ck;
        table[s_C1][LEX_ATTITUDE] = &StateM::A1cl;
        table[s_C1][LEX_COLON] = &StateM::O1a;
        table[s_C1][LEX_COMMA] = &StateM::O1c;

        table[s_F1][LEX_CHARACTER] = &StateM::M1;
        table[s_F1][LEX_DIGIT] = &StateM::B1a;
        table[s_F1][LEX_SPACE] = &StateM::A1vb;
        table[s_F1][LEX_LF] = &StateM::A1vd;
        table[s_F1][LEX_AR_OPERATION] = &StateM::A1vf;a
        table[s_F1][LEX_SEMICOLON] = &StateM::A1vi;
        table[s_F1][LEX_L_BRACKET] = &StateM::A1vj;
        table[s_F1][LEX_R_BRACKET] = &StateM::A1vk;
        table[s_F1][LEX_ATTITUDE] = &StateM::A1vl;
        table[s_F1][LEX_COLON] = &StateM::A1vn;
        table[s_F1][LEX_COMMA] = &StateM::A1vo;

        table[s_H1][LEX_ATTITUDE] = &StateM::N1a;
        table[s_H1][LEX_CHARACTER] = &StateM::N1b;
        table[s_H1][LEX_DIGIT] = &StateM::N1c;
        table[s_H1][LEX_SPACE] = &StateM::N1d;

        table[s_O1][LEX_DIGIT] = &StateM::O2a;
        table[s_O1][LEX_SPACE] = &StateM::O3c;
        table[s_O1][LEX_LF] = &StateM::O3d;

        table[s_O2][LEX_DIGIT] = &StateM::O2b;
        table[s_O2][LEX_SPACE] = &StateM::O3a;
        table[s_O2][LEX_LF] = &StateM::O3b;

        table[s_P1][LEX_ATTITUDE] = &StateM::P2;

        table[s_P2][LEX_ATTITUDE] = &StateM::P3;

        table[s_P3][LEX_DIGIT] = &StateM::P3;
        table[s_P3][LEX_CHARACTER] = &StateM::P3;
        table[s_P3][LEX_AR_OPERATION] = &StateM::P3;
        table[s_P3][LEX_ATTITUDE] = &StateM::P3;
        table[s_P3][LEX_L_BRACKET] = &StateM::P3;
        table[s_P3][LEX_R_BRACKET] = &StateM::P3;
        table[s_P3][LEX_SPACE] = &StateM::P3;
        table[s_P3][LEX_LF] = &StateM::P3;
        table[s_P3][LEX_COMMA] = &StateM::P3;
        table[s_P3][LEX_SEMICOLON] = &StateM::P3;
        table[s_P3][LEX_ERR_SYMB] = &StateM::P3;
        table[s_P3][LEX_COLON] = &StateM::P3;
        table[s_P3][LEX_L_SQ_BRACKET] = &StateM::P3;
        table[s_P3][LEX_R_SQ_BRACKET] = &StateM::P3;

        table[s_P4][LEX_DIGIT] = &StateM::P4;
        table[s_P4][LEX_CHARACTER] = &StateM::P4;
        table[s_P4][LEX_AR_OPERATION] = &StateM::P4;
        table[s_P4][LEX_ATTITUDE] = &StateM::P4;
        table[s_P4][LEX_L_BRACKET] = &StateM::P4;
        table[s_P4][LEX_R_BRACKET] = &StateM::P4;
        table[s_P4][LEX_SPACE] = &StateM::P4;
        table[s_P4][LEX_LF] = &StateM::P4;
        table[s_P4][LEX_COMMA] = &StateM::P4;
        table[s_P4][LEX_SEMICOLON] = &StateM::P4;
        table[s_P4][LEX_ERR_SYMB] = &StateM::P4;
        table[s_P4][LEX_COLON] = &StateM::P4;
        table[s_P4][LEX_L_SQ_BRACKET] = &StateM::P4;
        table[s_P4][LEX_R_SQ_BRACKET] = &StateM::P4;

        table[s_P5][LEX_DIGIT] = &StateM::P5;
        table[s_P5][LEX_CHARACTER] = &StateM::P5;
        table[s_P5][LEX_AR_OPERATION] = &StateM::P5;
        table[s_P5][LEX_ATTITUDE] = &StateM::P5;
        table[s_P5][LEX_L_BRACKET] = &StateM::P5;
        table[s_P5][LEX_R_BRACKET] = &StateM::P5;
        table[s_P5][LEX_SPACE] = &StateM::P5;
        table[s_P5][LEX_LF] = &StateM::P5;
        table[s_P5][LEX_COMMA] = &StateM::P5;
        table[s_P5][LEX_SEMICOLON] = &StateM::P5;
        table[s_P5][LEX_ERR_SYMB] = &StateM::P5;
        table[s_P5][LEX_COLON] = &StateM::P5;
        table[s_P5][LEX_L_SQ_BRACKET] = &StateM::P5;
        table[s_P5][LEX_R_SQ_BRACKET] = &StateM::P5;

        table[s_R2][LEX_R_SQ_BRACKET] = &StateM::R5b;
        table[s_R2][LEX_DIGIT] = &StateM::R3a;

        table[s_R3][LEX_DIGIT] = &StateM::R3b;
        table[s_R3][LEX_COMMA] = &StateM::R4b;
        table[s_R3][LEX_R_SQ_BRACKET] = &StateM::R5a;

        table[s_R4][LEX_DIGIT] = &StateM::R3a;

        table[s_Z1][LEX_L_BRACKET] = &StateM::G1a;

        table[s_J1][LEX_DIGIT] = &StateM::J1;
        table[s_J1][LEX_CHARACTER] = &StateM::J1;
        table[s_J1][LEX_AR_OPERATION] = &StateM::J1;
        table[s_J1][LEX_ATTITUDE] = &StateM::J1;
        table[s_J1][LEX_L_BRACKET] = &StateM::J1;
        table[s_J1][LEX_R_BRACKET] = &StateM::J1;
        table[s_J1][LEX_SPACE] = &StateM::J1;
        table[s_J1][LEX_LF] = &StateM::A1a;
        table[s_J1][LEX_COMMA] = &StateM::J1;
        table[s_J1][LEX_SEMICOLON] = &StateM::J1;
        table[s_J1][LEX_ERR_SYMB] = &StateM::J1;
        table[s_J1][LEX_COLON] = &StateM::J1;
        table[s_J1][LEX_L_SQ_BRACKET] = &StateM::J1;
        table[s_J1][LEX_R_SQ_BRACKET] = &StateM::J1;

        table[s_Z2][LEX_SPACE] = &StateM::Z2a;
        table[s_Z2][LEX_L_BRACKET] = &StateM::Z2b;

        table[s_Z3][LEX_SPACE] = &StateM::Z3a;
        table[s_Z3][LEX_L_BRACKET] = &StateM::Z3b;
        */
    }

    ~StateM()
    {
        // TODO : deallocate memmory from table 
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
    data_token k;
    k.CToken = END_MARKER;
    vecToken.emplace_back(k);
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

void StateM::MemoryTable()
{
    table = new function_pointer *[state_number];
    for (size_t i = 0; i < state_number; ++i)
        table[i] = new function_pointer[class_number];
}

#endif