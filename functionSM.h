#pragma once
#ifndef FUNCTION_SM_H
#define FUNCTION_SM_H

#include "StateMachine.h"

int StateM::Error1()
{
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::J1() {
    return s_J1;
}

int StateM::A0()
{
    return s_A0;
}

int StateM::A0a()
{
    ++reg_num_str;
    return s_A0;
}

int StateM::D1()
{
    vecToken.emplace_back(reg_num_str, SEMICOLON);
    return s_A0;

}

int StateM::B1()
{
    reg_const = (s.value - '0');
    return s_B1; 
}

int StateM::B1a()
{
    reg_const = reg_const* 10 + (s.value - '0');
    return s_B1;
}


// создание константы 
int StateM::B1c() 
{
    set_const.insert(reg_const);
    vecToken.emplace_back(reg_num_str,CONSTANT, reg_const);
    return s_A0;
}


int StateM::B1d() 
{
    B1c();
    return D1();
}

int StateM::B1g() 
{
    B1c();
    return A0a();
}


int StateM::B1s() 
{
    B1c();
    return A0();
}

int StateM::B1h() {
    B1c();
    return G1();
}

int StateM::B1i() {
    B1c();
    return F1();
}

int StateM::C1a() {
    reg_name.clear();
    reg_name.push_back(s.value);
    switch (s.value)
    {
    case 'd':
        discovery_register = 1;
        return s_M1;
        break;
    case 'a':
        discovery_register = 3;
        return s_M1;
        break;
    case 'u':
        discovery_register = 4;
        return s_M1;
        break;
    case 'h':
        discovery_register = 7;
        return s_M1;
        break;
    case 'l':
        discovery_register = 10;
        return s_M1;
        break;
    case 'f':
        discovery_register = 12;
        return s_M1;
        break;
    case 'i':
        discovery_register = 14;
        return s_M1;
        break;
    case 'n':
        discovery_register = 15;
        return s_M1;
        break;
    case 't':
        discovery_register = 18;
        return s_M1;
        break;
    case 'e':
        discovery_register = 21;
        return s_M1;
        break;
    case 'p':
        discovery_register = 26;
        return s_M1;
        break;
    case 'g':
        discovery_register = 28;
        return s_M1;
        break;
    case 's':
        discovery_register = 31;
        return s_M1;
    case 'c':
        discovery_register = 36;
        return s_M1;
    case 'b':
        discovery_register = 39;
        return s_M1;
    case 'r':
        discovery_register = 43;
        return s_M1;
    case '_':
        discovery_register = 100;
        return s_M1;
    default:
        return s_C1;
        break;
    }
    return s_C1;
}

int StateM::B1u() {
    B1c();
    return R1();
}

int StateM::C1b() {
    reg_name.push_back(s.value);
    return s_C1;
}

int StateM::C1c() {
    reg_name.push_back(s.value);
    return s_C1;
}

int StateM::C1d() {
    set_var.insert(reg_name);
    vecToken.emplace_back(reg_num_str, VARIABLE, std::move(reg_name));
    return s_A0;
}

int StateM::C1e() {
    C1d();
    return F1();
}

int StateM::C1f() {
    C1d();
    return D1();
}

int StateM::C1g() {
    C1d();
    return A0a();
}

int StateM::C1k() {
    C1d();
    return R1();
}

int StateM::C1l(){
    C1d();
    switch(s.value)
    {
    case '+':
        vecToken.emplace_back(reg_num_str,BIN_SUM);
        break;
    case '-':
        vecToken.emplace_back(reg_num_str,BIN_SUB);
        break;
    case '*':
        vecToken.emplace_back(reg_num_str,BIN_MOD);
        break;
    case '/':
        vecToken.emplace_back(reg_num_str,BIN_DIV);
        break;
    case '%':
        vecToken.emplace_back(reg_num_str,BIN_MOD);
        break;
    }
    return s_A0;
}

int StateM::G1e()
{
    
    vecToken.emplace_back(reg_num_str,register_ar_operations);
    return s_A0;
}

int StateM::G1f()
{
    vecToken.emplace_back(reg_num_str,register_ar_operations);
    return A0a();
}

int StateM::G1g()
{
    vecToken.emplace_back(reg_num_str,register_ar_operations);
    return D1();
}

int StateM::G1h()
{
    vecToken.emplace_back(reg_num_str,register_ar_operations);
    return B1();
}

int StateM::G1y()
{
    vecToken.emplace_back(reg_num_str,register_ar_operations);
    return F1();
}

int StateM::G1k()
{
    vecToken.emplace_back(reg_num_str,register_ar_operations);
    return C1a();
}

int StateM::G1l()
{
    vecToken.emplace_back(reg_num_str,register_ar_operations);
    return R1();
}

int StateM::G1m()
{
    vecToken.emplace_back(reg_num_str,register_ar_operations);
    return T1();
}

int StateM::G1n()
{
    vecToken.emplace_back(reg_num_str,register_ar_operations);
    return S1a();
}

int StateM::G1o()
{
    vecToken.emplace_back(reg_num_str,register_ar_operations);
    return Z1();
}

int StateM::G1() 
{
    switch (s.value) 
    {
        case '+':
        register_ar_operations = BIN_SUM;  
        break;
        
        case '-':
        register_ar_operations = BIN_SUB;   
        break;
        
        case '*':
        register_ar_operations = BIN_MULT;   
        break;
        
        case '/':
        register_ar_operations = BIN_DIV;   
        break;
        
        case '%':
        register_ar_operations = BIN_MOD;   
        break;
    }

    return s_W1;
}


int StateM::F1() {
    register_ratio = s.value;
    return s_F1;
}

int StateM::F2b()
{
    F2_add();
    return C1a();
}

int StateM::F2() {
    if (s.value == '=') {
        switch(register_ratio) {
            case '<':
                vecToken.emplace_back(reg_num_str,RATIO, TypeRatio::LESS_EQUAL);
                break;
            case '>':
                vecToken.emplace_back(reg_num_str,RATIO, TypeRatio::MORE_EQUAL);
                break;
            case '=':
                vecToken.emplace_back(reg_num_str,RATIO, TypeRatio::EQUAL);
                break;
            case '!':
                vecToken.emplace_back(reg_num_str,RATIO, TypeRatio::INEQUAL);
                break;
        }
    } else if (s.value == '>' && register_ratio == '>') {
        vecToken.emplace_back(reg_num_str,DUAL_MORE);
    } else {
        vec_errors.emplace_back(to_string(reg_num_str+1) + ": there isn't such a ratio");
        vecToken.emplace_back(reg_num_str, ERR_TOKEN);
        flagAnalyzer = false;
        return s_J1;
    }

    return s_A0;
}


int StateM::F2_add() {
    switch(register_ratio) {
    case '<':
        vecToken.emplace_back(reg_num_str,RATIO, TypeRatio::LESS);
        break;
    case '>':
        vecToken.emplace_back(reg_num_str,RATIO, TypeRatio::MORE);
        break;
    case '=':
        vecToken.emplace_back(reg_num_str,ASSIGN);
        break;
    default :
        vecToken.emplace_back(reg_num_str,ERR_TOKEN);
        break;
    }   
    return s_F2;
}

int StateM::F2a() {
    F2_add();
    return B1();
}

int StateM::F2c() {
    F2_add();
    return s_A0;
}

int StateM::H1()
{
    vecToken.emplace_back(reg_num_str,reg_token);
    return s_A0;
}

int StateM::H1a() 
{
    H1();
    return D1();
}

int StateM::H3()
{
    return s_H3;
}

int StateM::H3a()
{
    if(s.value == 's')
    {
        discovery_register = 1;
        return s_H4;
    }
    else
    {
        vec_errors.emplace_back(to_string(reg_num_str+1) + ": incorrect format of 'end switch'");
        vecToken.emplace_back(reg_num_str, ERR_TOKEN);
        flagAnalyzer = false;
        return s_J1;
    }
}

int StateM::H4() 
{
    if(discovery_register == 1 && s.value == 'w') {
        ++discovery_register;
    } else if( discovery_register == 2 && s.value == 'i') {
        ++discovery_register;
    } else if(discovery_register == 3 && s.value == 't') {
        ++discovery_register;
    } else if(discovery_register == 4 && s.value == 'c') {
        ++discovery_register;
    } else if(discovery_register == 5 && s.value == 'h') {
        return s_H5;
    } else {
        vec_errors.emplace_back(to_string(reg_num_str+1) + ": incorrect format of 'end switch'");
        vecToken.emplace_back(reg_num_str, ERR_TOKEN);
        flagAnalyzer = false;
        return s_J1;
    }
    return s_H4;
}

int StateM::H5()
{
    vecToken.emplace_back(reg_num_str,END_SWITCH);
    return s_A0;
}

int StateM::H5a()
{
    vecToken.emplace_back(reg_num_str,END_SWITCH);
    return A0a();
}

int StateM::H5b()
{
    vecToken.emplace_back(reg_num_str,END_SWITCH);
    return D1();
}

int StateM::H6() {
    return s_H6;
}

int StateM::H6a() {
    ++reg_num_str;
    return s_H6;
}

int StateM::L1() {
    return s_L1;
}

int StateM::L1a() {
    ++reg_num_str;
    return s_L1;
}

int StateM::L2a() {
    reg_name.clear();
    reg_name += s.value;
    return s_L2;
}

int StateM::L2() {
    reg_name += s.value;
    return s_L2;
}

int StateM::L3a() {
    ++reg_num_str;
    return s_L3;
}

int StateM::L3b() {
    return s_L3;
}

int StateM::L4() {
    reg_load_names.emplace_back(std::move(reg_name));
    return s_L4;
}

int StateM::L4a() {
    return s_L4;
}

int StateM::L4b() {
    ++reg_num_str;
    return s_L4;
}

int StateM::L5() {
    reg_load_names.emplace_back(std::move(reg_name));
    vecToken.emplace_back(reg_num_str, LOAD, std::move(reg_load_names));
    return s_A0;
}

int StateM::H7() {
    return s_H7;
}

int StateM::H7a() {
    ++reg_num_str;
    return s_H7;
}

int StateM::H7b() {
    vecToken.emplace_back(reg_num_str, reg_token);
    return s_A0;
}

int StateM::H8a() {
    return s_H8;
}

int StateM::H8b() {
    ++reg_num_str;
    return s_H8;
}

int StateM::H8() {
    vecToken.emplace_back(reg_num_str, BREAK);
    vecToken.emplace_back(reg_num_str, SEMICOLON);
    return s_A0;
}


int StateM::G1d()
{
    return s_G1a;
}

int StateM::G1a()
{
    return s_G1a;
}

int StateM::G1b()
{
    vecToken.emplace_back(reg_str_comment,COMMENT);
    return s_A0;
}

int StateM::G1c()
{
    ++reg_num_str;
    return s_G1a;
}

int StateM::Q1()
{
    vecToken.emplace_back(reg_str_comment,reg_token);
    ++reg_num_str;
    return s_A0;
}

// считать один пробел 
int StateM::K1() {
    return s_K2;
}

// остальные пробелы 
int StateM::K2() {
    return s_K2;
}

int StateM::K2a() {
    reg_const = (s.value - '0');
    return s_K3;
}

int StateM::K3b() {
    reg_const = (reg_const * 10) + (s.value - '0');
    return s_K3;
}

//space
int StateM::K4a() {
    vecToken.emplace_back(reg_num_str,reg_token, reg_const);
    return s_A0;
}

// LF
int StateM::K4b() {
    K4a();
    return A0a();
}

// SEMICOLON
int StateM::K4c() {
    K4a();
    return D1();
}





int StateM::M1()
{
    reg_name.push_back(s.value);
    if(discovery_register == 1 && s.value=='i')
    {
        ++discovery_register;
    }
    else if(discovery_register ==2 && s.value == 'm')
    {
        reg_token = DIM;
        return s_H1;
    }
    else if(discovery_register==3 && s.value =='s')
    {
        reg_token = AS;
        return s_H1;
    }
    else if(discovery_register == 4 && s.value == 'i')
    {
        ++discovery_register;
    }
    else if(discovery_register == 5 && s.value == 'n')
    {
        ++discovery_register;
    }
    else if(discovery_register == 6 && s.value == 't')
    {
        reg_token = UINT;
        return s_H1;
    }
    else if(discovery_register == 100 && s.value == 'h')
    {
        ++discovery_register;
    }
    else if(discovery_register == 101 && s.value == 'a')
    {
        ++discovery_register;
    }
    else if(discovery_register == 102 && s.value == 's')
    {
        ++discovery_register;
    }
    else if(discovery_register == 103 && s.value == 'h')
    {
        reg_token = HASH;
        return s_H1;
    }
    else if(discovery_register == 10 && s.value == 'e')
    {
        ++discovery_register;
    }
    else if(discovery_register == 11 && s.value == 't')
    {
        reg_token = LET;
        return s_H1;
    }
    else if(discovery_register == 12 && s.value == 'o')
    {
        ++discovery_register;
    }
    else if(discovery_register == 13 && s.value == 'r')
    {
        reg_token = FOR;
        return s_K4;
    }
    else if(discovery_register == 14 && s.value == 'n')
    {
        reg_token = IN;
        return s_H7;
    }
    else if(discovery_register == 15 && s.value == 'e')
    {
        ++discovery_register;
    }
    else if(discovery_register == 16 && s.value == 'x')
    {
        ++discovery_register;
    }
    else if(discovery_register == 17 && s.value == 't')
    {
        reg_token = NEXT;
        return s_K1;
    }
    else if(discovery_register == 14 && s.value == 'f')
    {
        reg_token = IF;
        return s_H1;
    }
    else if(discovery_register == 18 && s.value == 'h')
    {
        ++discovery_register;
    }
    else if(discovery_register == 19 && s.value == 'e')
    {
        ++discovery_register;
    }
    else if(discovery_register == 20 && s.value == 'n')
    {
        reg_token = THEN;
        return s_K1;
    }
    else if(discovery_register == 21 && s.value == 'l')
    {
        ++discovery_register;
    }
    else if(discovery_register == 22 && s.value == 's')
    {
        ++discovery_register;
    }
    else if(discovery_register == 23 && s.value == 'e')
    {
        reg_token = ELSE;
        return s_K1;
    }
    else if(discovery_register == 10 && s.value == 'o')
    {
        discovery_register = 24;
    }
    else if(discovery_register == 24 && s.value == 'a')
    {
        ++discovery_register;
    }
    else if(discovery_register == 25 && s.value == 'd')
    {
        reg_token = LOAD;
        return s_H6;
    }
    else if(discovery_register == 26 && s.value == 'u')
    {
        ++discovery_register;
    }
    else if(discovery_register == 27 && s.value == 't')
    {
        reg_token = PUT;
        return s_H7;
    }
    else if(discovery_register == 28 && s.value == 'o')
    {
        ++discovery_register;
    }
    else if(discovery_register == 29 && s.value == 't')
    {
        ++discovery_register;
    }
    else if(discovery_register == 30 && s.value == 'o')
    {
        reg_token = GOTO;
        return s_K1;
    }
    else if(discovery_register == 31 && s.value == 'w')
    {
        ++discovery_register;
    }
    else if(discovery_register == 32 && s.value == 'i')
    {
        ++discovery_register;
    }
    else if(discovery_register == 33 && s.value == 't')
    {
        ++discovery_register;
    }
    else if(discovery_register == 34 && s.value == 'c')
    {
        ++discovery_register;
    }
    else if(discovery_register == 35 && s.value == 'h')
    {
        reg_token = SWITCH;
        return s_H7;
    }
    else if(discovery_register == 36 && s.value == 'a')
    {
        ++discovery_register;
    }
    else if(discovery_register == 37 && s.value == 's')
    {
        ++discovery_register;
    }
    else if(discovery_register == 38 && s.value == 'e')
    {
        reg_token = CASE;
        return s_H1;
    }
    else if(discovery_register == 39 && s.value == 'r')
    {
        ++discovery_register;
    }
    else if(discovery_register == 40 && s.value == 'e')
    {
        ++discovery_register;
    }
    else if(discovery_register == 41 && s.value == 'a')
    {
        ++discovery_register;
    }
    else if(discovery_register == 42 && s.value == 'k')
    {
        reg_token = BREAK;
        return s_H8;
    }
    else if(discovery_register == 43 && s.value == 'a')
    {
        ++discovery_register;
    }
    else if(discovery_register == 44 && s.value == 'i')
    {
        ++discovery_register;
    }
    else if(discovery_register == 45 && s.value == 's')
    {
        ++discovery_register;
    }
    else if(discovery_register == 46 && s.value == 'e')
    {
        reg_token = RAISE;
        return s_R1;
    }
    else if(discovery_register == 21 && s.value == 'n')
    {
        discovery_register = 51;
    }
    else if(discovery_register == 51 && s.value == 'd')
    {
        return s_H2;
    } 
    else if(discovery_register == 36 && s.value == 'o')
    {
        discovery_register = 55;
    }
    else if(discovery_register == 55 && s.value == 'm')
    {
        ++discovery_register;
    }
    else if(discovery_register == 56 && s.value == 'm')
    {
        ++discovery_register;
    }
    else if(discovery_register == 57 && s.value == 'e')
    {
        ++discovery_register;
    }
    else if(discovery_register == 58 && s.value == 'n')
    {
        ++discovery_register;
    }
    else if(discovery_register == 59 && s.value == 't')
    {
        reg_str_comment = reg_num_str;
        return s_G1;
    }
    else if(discovery_register == 4 && s.value == 'n')
    {
        discovery_register = 60;
    }
    else if(discovery_register == 60 && s.value == 'i')
    {
        ++discovery_register;
    }
    else if(discovery_register == 61 && s.value == 'o')
    {
        ++discovery_register;
    }
    else if(discovery_register == 62 && s.value == 'n')
    {
        reg_token = UNION;
        return s_H1;
    }
    else if(discovery_register == 7 && s.value =='a')
    {
        discovery_register = 63;
    }
    else if(discovery_register == 63 && s.value == 's')
    {
        ++discovery_register;
    }
    else if(discovery_register == 64 && s.value == 'h')
    {
        ++discovery_register;
    }
    else if(discovery_register == 65 && s.value == '_')
    {
        ++discovery_register;
    }
    else if(discovery_register == 66 && s.value == 'i')
    {
        ++discovery_register;
    }
    else if(discovery_register == 67 && s.value == 'n')
    {
        ++discovery_register;
    }
    else if(discovery_register == 68 && s.value == 't')
    {
        ++discovery_register;
    }
    else if(discovery_register == 69 && s.value == 'e')
    {
        ++discovery_register;
    }
    else if(discovery_register == 70 && s.value == 'r')
    {
        ++discovery_register;
    }
    else if(discovery_register == 71 && s.value == 's')
    {
        ++discovery_register;
    }
    else if(discovery_register == 72 && s.value == 'e')
    {
        ++discovery_register;
    }
    else if(discovery_register == 73 && s.value == 'c')
    {
        reg_token = HASH_INTERSEC;
        return s_H1;
    }
    else if(discovery_register ==2 && s.value == 'f')
    {
        discovery_register = 74;
    }
    else if(discovery_register ==74 && s.value == 'f')
    {
        reg_token = DIFF;
        return s_H1;
    }
    else if(discovery_register == 31 && s.value == 'i')
    {
        discovery_register = 75;
    }
    else if(discovery_register == 75 && s.value == 'm')
    {
        ++discovery_register;
    }
    else if(discovery_register == 76 && s.value == 'd')
    {
        ++discovery_register;
    }
    else if(discovery_register == 77 && s.value == 'i')
    {
        ++discovery_register;
    }
    else if(discovery_register == 78 && s.value == 'f')
    {
        ++discovery_register;
    }
    else if(discovery_register == 79 && s.value == 'f')
    {
        reg_token = SIMDIFF;
        return s_H1;
    }
    else if(discovery_register==3 && s.value =='c')
    {
        discovery_register = 80;
    }
    else if(discovery_register==80 && s.value =='c')
    {
        ++discovery_register;
    }
    else if(discovery_register==81 && s.value =='e')
    {
        ++discovery_register;
    }
    else if(discovery_register==82 && s.value =='s')
    {
        ++discovery_register;
    }
    else if(discovery_register==83 && s.value =='s')
    {
        reg_token = ACCESS;
        return s_H1;
    }
    else if(discovery_register == 26 && s.value == 'o')
    {
        discovery_register = 84;
    }
    else if(discovery_register == 84 && s.value == 'w')
    {
        reg_token = POW;
        return s_H1;
    }
    else if(discovery_register == 66 && s.value == 'a')
    {
        discovery_register = 85;
    }
    else if(discovery_register == 85 && s.value == 'd')
    {
        ++discovery_register;
    }
    else if(discovery_register == 86 && s.value == 'd')
    {
        reg_token = HASH_ADD;
        return s_H1;
    } else if(discovery_register == 1 && s.value == 'e') {
        discovery_register = 140;
    } else if (discovery_register == 140 && s.value == 'f') {
        ++discovery_register;
    } else if (discovery_register == 141 && s.value == 'a') {
        ++discovery_register;
    } else if (discovery_register == 142 && s.value == 'u') {
        ++discovery_register;
    } else if (discovery_register == 143 && s.value == 'l') {
        ++discovery_register;
    } else if (discovery_register == 144 && s.value == 't') {
        reg_token = DEFAULT;
        return s_H1;
    }
    else 
    {
        return s_C1;
    }
    return s_M1;
}

int StateM::P1()
{
    return s_P1;
}

int StateM::R1()
{
    if(s.value == '(')
    {
        vecToken.emplace_back(reg_num_str,LEFT_BRACKET);
    }
    else if(s.value == ')')
    {
        vecToken.emplace_back(reg_num_str,RIGHT_BRACKET);
    }
    return s_A0;
}

int StateM::R1a()
{
    vecToken.emplace_back(reg_num_str,reg_token);
    return R1();
}

int StateM::T1()
{
    return s_T1;
}

int StateM::T1a()
{
    reg_const = (s.value - '0');
    return s_T1a; 
}



int StateM::T1b()
{
    reg_const = reg_const* 10 + (s.value - '0');
    return s_T1a;
}

int StateM::T2()
{
    vecToken.emplace_back(reg_num_str,LABLE,reg_const);
    return s_A0;
}

int StateM::T2a() {
    T2();
    return A0a();   
}

int StateM::T2c() {
    vecToken.emplace_back(reg_num_str, COLON);
    vecToken.emplace_back(reg_num_str, SEMICOLON);
    return s_A0;
}

int StateM::T2d() {
    vecToken.emplace_back(reg_num_str, COLON);
    vecToken.emplace_back(reg_num_str, SEMICOLON);
    ++reg_num_str;
    return s_A0;
}

int StateM::T1e() {
    B1c();
    vecToken.emplace_back(reg_num_str, COLON);
    vecToken.emplace_back(reg_num_str, SEMICOLON);
    return s_A0;
}

int StateM::T1f() {
    H1();
    vecToken.emplace_back(reg_num_str, COLON);
    vecToken.emplace_back(reg_num_str, SEMICOLON);
    return s_A0;
}


int StateM::S1a() {
    vecToken.emplace_back(reg_num_str,COMMA);
    return s_A0;
}

int StateM::S1b() {
    B1c();
    return S1a();
}

int StateM::S1c() {
    C1d();
    return S1a();
}

int StateM::Z1() {
    reg_hash.clear();
    return s_Z1;
}


int StateM::Z1a() {
    return s_Z1;
}

int StateM::Z2a() {
    reg_const = (s.value - '0');
    return s_Z2;
}

int StateM::Z1b() {
    vecToken.emplace_back(reg_num_str,HASH_CONST, hash_set());
    return A0();
}

int StateM::Z2b() {
    reg_const = 10 * reg_const + (s.value - '0');
    return s_Z2;
}

int StateM::Z2c() {
    reg_hash.insert(static_cast<int>(reg_const));
    return s_Z4;
}


int StateM::Z2d() {
    reg_hash.insert(static_cast<int>(reg_const));
    vecToken.emplace_back(reg_num_str,HASH_CONST, reg_hash);
    return A0();
}

int StateM::Z2e() {
    reg_hash.insert(static_cast<int>(reg_const));
    return s_Z4;
}

int StateM::Z3a() {
    return s_Z3;
}

int StateM::Z5a(){
    return s_Z4;
}

int StateM::Z3e() {
    return Z2e();
}

int StateM::E1()
{
    vec_errors.emplace_back(to_string(reg_num_str+1) + ": incorrect variable input: it can't start with a digit");
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::E2()
{
    vec_errors.emplace_back(to_string(reg_num_str+1) + ": unexpected simbol");
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::E3()
{
    vec_errors.emplace_back(to_string(reg_num_str+1) + ": there isn't such an operation");
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::E4()
{
    vec_errors.emplace_back(to_string(reg_num_str+1) + ": incorrect hash input (correct format : [v1,v2,..,vn])");
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::E4a() {
    E4();
    return A0a();
}

int StateM::E5()
{
    vec_errors.emplace_back(to_string(reg_num_str+1) + ": incorrect lable input (correct format : ':L' or 'goto L' or 'then/else L')");
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::E5a() {
    E5();
    return A0a();
}

int StateM::E6()
{
    vec_errors.emplace_back(to_string(reg_num_str+1) + ": incorrect exception input (correct input: 'raise ;')");
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::E6a() {
    E6();
    return A0a();
}

int StateM::E7()
{
    vec_errors.emplace_back(to_string(reg_num_str+1) + ": the comment isn't closed");
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::E8()
{
    vec_errors.emplace_back(to_string(reg_num_str+1) + ": you can't write ',' after operative words");
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::E9()
{
    vec_errors.emplace_back(to_string(reg_num_str+1) + ": incorrect format of 'end switch'");
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::E9a()
{
    E9();
    return A0a();
}

int StateM::E10()
{
    vec_errors.emplace_back(to_string(reg_num_str+1) + ": incorrect format of '(E>>E)'");
    vecToken.emplace_back(reg_num_str, ERR_TOKEN);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::K4() {
    return s_K4;
}

int StateM::K4d() {
    ++reg_num_str;
    return s_K4;
}

int StateM::K5() {
    reg_name.clear();
    reg_name = s.value;
    return s_K5;
}

int StateM::K5a() {
    reg_name += s.value;
    return s_K5;
}

int StateM::K5b() {
    vecToken.emplace_back(reg_num_str, FOR, std::move(reg_name));
    return s_A0;
}

int StateM::K5c() {
    vecToken.emplace_back(reg_num_str, FOR, std::move(reg_name));
    ++reg_num_str;
    return s_A0;
}

#endif