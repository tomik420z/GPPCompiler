#pragma once
#ifndef FUNCTION_SM_H
#define FUNCTION_SM_H

#include "StateMachine.h"

int StateM::Error1()
{
    data_token el;
    el.CToken = ERR_TOKEN;
    vecToken.emplace_back(el);
    flagAnalyzer = false;
    return s_J1;
}

/*
void StateM::CreateVariable()
{
    Variable v;
    v.Type = 0;
    v.name_value = reg_name;

    data_token el;
    el.CToken = VARIABLE;
    el.ptr = new Variable(v);
    vecToken.emplace_back(el);

    pair<string, bool> t;
    t.first = reg_name;
    SetVar.emplace(t);
}

void StateM::CreateConst()
{
    Variable v;
    v.Type = 1;
    v.const_value = reg_const;

    data_token el;
    el.CToken = CONSTANT;
    el.ptr = new Variable(v);
    vecToken.emplace_back(el);
}*/
/*
void StateM::CreateAttitude()
{
    //cout << reg_att << endl;
    data_token el;
    el.CToken = ATTITUDE;
    TypeAttitude t;
    if (reg_att == "<")
        t = LESS;
    else if (reg_att == ">")
        t = MORE;
    else if (reg_att == ">=")
        t = MORE_EQUAL;
    else if (reg_att == "<=")
        t = LESS_EQUAL;
    else if (reg_att == "==")
    {
        vecToken.pop_back();
        t = EQUAL;
    }
    else if (reg_att == "!=")
        t = INEQUAL;

    el.ptr = new TypeAttitude(t);
    vecToken.emplace_back(el);
}*/
/*
void StateM::CreateList()
{
    data_token el;
    el.CToken = CONST_LIST;
    Variable v;
    v.Type = 2;
    v.uintList = RegList;
    el.ptr = new Variable(v);
    vecToken.emplace_back(el);
}*/

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
    vecToken.emplace_back(SEMICOLON);
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
    std::cout << reg_const << std::endl;
    vecToken.emplace_back(data_token{CONSTANT, reg_const});
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
    default:
        return s_C1;
        break;
    }
    return s_C1;
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
    vecToken.emplace_back(VARIABLE, std::move(reg_name));
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



int StateM::G1() 
{
    switch (s.value) 
    {
        case '+':
        vecToken.emplace_back(BIN_SUM);   
        break;
        
        case '-':
        vecToken.emplace_back(BIN_SUB);   
        break;
        
        case '*':
        vecToken.emplace_back(BIN_MULT);   
        break;
        
        case '/':
        vecToken.emplace_back(BIN_DIV);   
        break;
        
        case '%':
        vecToken.emplace_back(BIN_MOD);   
        break;
    }

    return s_A0;
}


int StateM::F1() {
    register_ratio = s.value;
    return s_F1;
}

int StateM::F2() {
    if (s.value == '=') {
        switch(register_ratio) {
            case '<':
                vecToken.emplace_back(ATTITUDE, TypeAttitude::LESS_EQUAL);
                break;
            case '>':
                vecToken.emplace_back(ATTITUDE, TypeAttitude::MORE_EQUAL);
                break;
            case '=':
                vecToken.emplace_back(ATTITUDE, TypeAttitude::EQUAL);
                break;
            case '!':
                vecToken.emplace_back(ATTITUDE, TypeAttitude::INEQUAL);
                break;
        }
    } else if (s.value == '>' && register_ratio == '>') {
        vecToken.emplace_back(DUAL_MORE);
    } else {
        vecToken.emplace_back(ERR_TOKEN);
    }

    return s_A0;
}


int StateM::F2_add() {
    switch(register_ratio) {
    case '<':
        vecToken.emplace_back(ATTITUDE, TypeAttitude::LESS);
        break;
    case '>':
        vecToken.emplace_back(ATTITUDE, TypeAttitude::LESS);
        break;
    case '=':
        vecToken.emplace_back(ASSIGN);
        break;
    default :
        vecToken.emplace_back(ERR_TOKEN);
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
    vecToken.emplace_back(reg_token);
    return s_A0;
}

int StateM::H3()
{
    return s_H3;
}

int StateM::H3a()
{
    vecToken.emplace_back(END_SWITCH);
    return s_H4;
}

int StateM::M1()
{
    reg_name.push_back(s.value);
    if(discovery_register==1 && s.value=='i')
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
    else if(discovery_register == 7 && s.value == 'a')
    {
        ++discovery_register;
    }
    else if(discovery_register == 8 && s.value == 's')
    {
        ++discovery_register;
    }
    else if(discovery_register == 9 && s.value == 'h')
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
        return s_H1;
    }
    else if(discovery_register == 14 && s.value == 'n')
    {
        reg_token = IN;
        return s_H1;
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
        return s_H1;
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
        return s_H1;
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
        return s_H1;
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
        return s_H1;
    }
    else if(discovery_register == 26 && s.value == 'u')
    {
        ++discovery_register;
    }
    else if(discovery_register == 27 && s.value == 't')
    {
        reg_token = PUT;
        return s_H1;
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
        return s_H1;
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
        return s_H1;
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
        return s_H1;
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
        return s_H1;
    }
    else if(discovery_register == 21 && s.value == 'n')
    {
        discovery_register = 51;
    }
    else if(discovery_register == 51 && s.value == 'd')
    {
        return s_H2;
    } 
    else 
    {
        return s_C1;
    }
    return s_M1;
}

/*
int StateM::Z2a()
{
    return s_Z2;
}

int StateM::Z2b()
{
    data_token el;
    el.CToken = LOAD;
    vecToken.emplace_back(el);
    return A1();
}

int StateM::A0b()
{
    data_token el;
    el.CToken = ERROR;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0c()
{
    data_token el;
    el.CToken = IF;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0d()
{
    data_token el;
    el.CToken = WHILE;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0e()
{
    data_token el;
    el.CToken = FOR;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::Z3a()
{
    return s_Z3;
}

int StateM::Z3b()
{
    data_token el;
    el.CToken = PUT;
    vecToken.emplace_back(el);
    return A1();
}

int StateM::A0i()
{
    data_token el;
    el.CToken = SWITCH;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0j()
{
    data_token el;
    el.CToken = EACH;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0k()
{
    data_token el;
    el.CToken = IN;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0l()
{
    data_token el;
    el.CToken = OTHERWISE;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0m()
{
    data_token el;
    el.CToken = GOTO;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0n()
{
    data_token el;
    el.CToken = END;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0o()
{
    data_token el;
    el.CToken = ELSE;
    vecToken.emplace_back(el);
    return s_A0;
}

// DO
int StateM::A0p()
{
    data_token el;
    el.CToken = DO;
    vecToken.emplace_back(el);
    return s_A0;
}

// WHEN
int StateM::A0q()
{
    data_token el;
    el.CToken = WHEN;
    vecToken.emplace_back(el);
    return s_A0;
}

// THEN
int StateM::A0r()
{
    data_token el;
    el.CToken = THEN;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0s()
{
    data_token el;
    el.CToken = LET;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0t()
{
    data_token el;
    el.CToken = TYPE_LI;
    vecToken.emplace_back(el);
    return s_A0;
}

int StateM::A0u()
{
    data_token el;
    el.CToken = TYPE_UINT;
    vecToken.emplace_back(el);
    return s_A0;
}

// ������� ��������
int StateM::A1()
{
    return s_A1;
}

int StateM::A1a()
{
    ++discovery_register;
    return s_A1;
}

int StateM::A1vb()
{
    CreateVariable();
    return s_A1;
}

int StateM::A1c()
{
    CreateConst();
    return s_A1;
}

int StateM::A1vd()
{
    CreateVariable();
    return A1a();
}

int StateM::A1ce()
{
    CreateConst();
    return A1a();
}

int StateM::A1cg()
{
    CreateConst();
    return E1();
}

int StateM::A1vf()
{
    CreateVariable();
    return E1();
}

int StateM::A1vi()
{
    CreateVariable();
    return D1();
}

int StateM::A1ci()
{
    CreateConst();
    return D1();
}

int StateM::A1vj()
{
    CreateVariable();
    return G1a();
}

int StateM::A1cj()
{
    CreateConst();
    return G1a();
}

int StateM::A1vk()
{
    CreateVariable();
    return G1b();
}

int StateM::A1ck()
{
    CreateConst();
    return G1b();
}

int StateM::A1vl()
{
    CreateVariable();
    return H1();
}

int StateM::A1cl()
{
    CreateConst();
    return H1();
}

int StateM::A1vm()
{
    CreateVariable();
    return Z2();
}

int StateM::A1vn()
{
    CreateVariable();
    return Z2();
}

int StateM::A1vo()
{
    CreateVariable();
    return O3a();
}

int StateM::B1a()
{
    reg_name += s.value;
    return s_B1;
}

// ������ ����������
int StateM::B1b()
{
    reg_name += s.value;
    return s_B1;
}

int StateM::C1a()
{
    reg_const = (s.value - '0');
    return s_C1;
}

int StateM::C1b()
{
    reg_const = reg_const * 10 + (s.value - '0');
    return s_C1;
}

// SEMICOLON
int StateM::D1()
{
    data_token el;
    el.CToken = SEMICOLON;
    vecToken.emplace_back(el);
    return s_A1;
}

//  AR_OP
int StateM::E1()
{
    data_token el;
    switch (s.value)
    {
    case '+':
        el.CToken = BIN_SUM;
        break;
    case '-':
        el.CToken = BIN_SUB;
        break;
    case '*':
        el.CToken = BIN_MULT;
        break;
    case '/':
        el.CToken = BIN_DIV;
        break;
    case '%':
        el.CToken = BIN_MOD;
        break;
    }
    vecToken.emplace_back(el);

    return s_A1;
}

int StateM::M1()
{
    reg_name += s.value;
    if (discovery_register == 1 && s.value == 'o')
        return F1a();
    else if (discovery_register == 2 && s.value == 'a')
        return F1a();
    else if (discovery_register == 3 && s.value == 'd')
        return Z2a();
    else if (discovery_register == 7 && s.value == 'r')
        return F1a();
    else if (discovery_register == 8 && s.value == 'r')
        return F1a();
    else if (discovery_register == 9 && s.value == 'o')
        return F1a();
    else if (discovery_register == 10 && s.value == 'r')
        return A0b();
    else if (discovery_register == 11 && s.value == 'f')
        return A0c();
    else if (discovery_register == 14 && s.value == 'h')
        return F1a();
    else if (discovery_register == 15 && s.value == 'i')
        return F1a();
    else if (discovery_register == 16 && s.value == 'l')
        return F1a();
    else if (discovery_register == 17 && s.value == 'e')
        return A0d();
    else if (discovery_register == 18 && s.value == 'o')
        return F1a();
    else if (discovery_register == 19 && s.value == 'r')
        return A0e();
    else if (discovery_register == 22 && s.value == 'u')
        return F1a();
    else if (discovery_register == 23 && s.value == 't')
        return Z3a();
    else if (discovery_register == 30 && s.value == 'w')
        return F1a();
    else if (discovery_register == 31 && s.value == 'i')
        return F1a();
    else if (discovery_register == 32 && s.value == 't')
        return F1a();
    else if (discovery_register == 33 && s.value == 'c')
        return F1a();
    else if (discovery_register == 34 && s.value == 'h')
        return A0i();
    else if (discovery_register == 7 && s.value == 'a')
    {
        discovery_register = 70;
        return F1a();
    }
    else if (discovery_register == 71 && s.value == 'c')
        return F1a();
    else if (discovery_register == 72 && s.value == 'h')
        return A0j();
    else if (discovery_register == 11 && s.value == 'n')
        return A0k();
    else if (discovery_register == 47 && s.value == 'e')
        return F1a();
    else if (discovery_register == 50 && s.value == 't')
        return F1a();
    else if (discovery_register == 51 && s.value == 'h')
        return F1a();
    else if (discovery_register == 52 && s.value == 'e')
        return F1a();
    else if (discovery_register == 53 && s.value == 'r')
        return F1a();
    else if (discovery_register == 54 && s.value == 'w')
        return F1a();
    else if (discovery_register == 55 && s.value == 'i')
        return F1a();
    else if (discovery_register == 56 && s.value == 's')
        return F1a();
    else if (discovery_register == 57 && s.value == 'e')
        return A0l();
    else if (discovery_register == 60 && s.value == 'o')
        return F1a();
    else if (discovery_register == 61 && s.value == 't')
        return F1a();
    else if (discovery_register == 62 && s.value == 'o')
        return A0m();
    else if (discovery_register == 7 && s.value == 'n')
    {
        discovery_register = 80;
        return F1a();
    }
    else if (discovery_register == 81 && s.value == 'd')
        return A0n();
    else if (discovery_register == 7 && s.value == 'l')
    {
        discovery_register = 90;
        return F1a();
    }
    else if (discovery_register == 91 && s.value == 's')
        return F1a();
    else if (discovery_register == 92 && s.value == 'e')
        return A0o();
    else if (discovery_register == 93 && s.value == 'o')
        return A0p();
    else if (discovery_register == 15 && s.value == 'e')
    {
        discovery_register = 100;
        return F1a();
    }
    else if (discovery_register == 101 && s.value == 'n')
        return A0q();
    else if (discovery_register == 110 && s.value == 'h')
        return F1a();
    else if (discovery_register == 111 && s.value == 'e')
        return F1a();
    else if (discovery_register == 112 && s.value == 'n')
        return A0r();
    else if (discovery_register == 1 && s.value == 'e')
    {
        discovery_register = 120;
        return F1a();
    }
    else if (discovery_register == 121 && s.value == 't')
        return A0s();
    else if (discovery_register == 1 && s.value == 'i')
    {
        discovery_register = 198;
        return F1a();
    }
    else if (discovery_register == 199 && s.value == '_')
        return F1a();
    else if (discovery_register == 200 && s.value == 'u')
        return F1a();
    else if (discovery_register == 201 && s.value == 'n')
        return F1a();
    else if (discovery_register == 202 && s.value == 'i')
        return F1a();
    else if (discovery_register == 203 && s.value == 't')
        return Z1a();
    else if (discovery_register == 200 && s.value == 'i')
    {
        discovery_register = 205;
        return F1a();
    }
    else if (discovery_register == 206 && s.value == 'n')
        return F1a();
    else if (discovery_register == 207 && s.value == 't')
        return F1a();
    else if (discovery_register == 208 && s.value == 'e')
        return F1a();
    else if (discovery_register == 209 && s.value == 'r')
        return F1a();
    else if (discovery_register == 210 && s.value == 's')
        return F1a();
    else if (discovery_register == 211 && s.value == 'e')
        return F1a();
    else if (discovery_register == 212 && s.value == 'c')
        return Z1b();
    else if (discovery_register == 200 && s.value == 'd')
    {
        discovery_register = 220;
        return F1a();
    }
    else if (discovery_register == 221 && s.value == 'i')
        return F1a();
    else if (discovery_register == 222 && s.value == 'f')
        return F1a();
    else if (discovery_register == 223 && s.value == 'f')
        return Z1c();
    else if (discovery_register == 200 && s.value == 's')
    {
        discovery_register = 230;
        return F1a();
    }
    else if (discovery_register == 231 && s.value == 'y')
        return F1a();
    else if (discovery_register == 232 && s.value == 'm')
        return F1a();
    else if (discovery_register == 233 && s.value == 'm')
        return F1a();
    else if (discovery_register == 234 && s.value == 'd')
        return F1a();
    else if (discovery_register == 235 && s.value == 'i')
        return F1a();
    else if (discovery_register == 236 && s.value == 'f')
        return F1a();
    else if (discovery_register == 237 && s.value == 'f')
        return Z1d();
    else if (discovery_register == 200 && s.value == 'a')
    {
        discovery_register = 240;
        return F1a();
    }
    else if (discovery_register == 241 && s.value == 'd')
        return F1a();
    else if (discovery_register == 242 && s.value == 'd')
        return Z1e();
    else if (discovery_register == 200 && s.value == 'p')
    {
        discovery_register = 250;
        return F1a();
    }
    else if (discovery_register == 251 && s.value == 'o')
        return F1a();
    else if (discovery_register == 252 && s.value == 'w')
        return Z1f();
    else if (discovery_register == 206 && s.value == 't')
    {
        discovery_register = 260;
        return F1a();
    }
    else if (discovery_register == 261 && s.value == 'e')
        return F1a();
    else if (discovery_register == 262 && s.value == 'm')
        return Z1g();
    else if (discovery_register == 110 && s.value == 'y')
    {
        discovery_register = 270;
        return F1a();
    }
    else if (discovery_register == 271 && s.value == '_')
        return F1a();
    else if (discovery_register == 272 && s.value == 'l')
        return F1a();
    else if (discovery_register == 273 && s.value == 'i')
        return A0t();
    else if (discovery_register == 272 && s.value == 'u')
    {
        discovery_register = 280;
        return F1a();
    }
    else if (discovery_register == 281 && s.value == 'i')
        return F1a();
    else if (discovery_register == 282 && s.value == 'n')
        return F1a();
    else if (discovery_register == 283 && s.value == 't')
        return A0u();
    else
    {
        return s_B1;
    }
}

int StateM::F1()
{
    reg_name = s.value;
    discovery_register = 0;

    char c = s.value;
    switch (c)
    {
    case 'l':
        discovery_register = 1;
        break;
    case 'e':
        discovery_register = 7;
        break;
    case 'i':
        discovery_register = 11;
        break;
    case 'w':
        discovery_register = 14;
        break;
    case 'f':
        discovery_register = 18;
        break;
    case 'p':
        discovery_register = 22;
        break;
    case 's':
        discovery_register = 30;
        break;
    case 'o':
        discovery_register = 50;
        break;
    case 'g':
        discovery_register = 60;
        break;
    case 'd':
        discovery_register = 93;
        break;
    case 't':
        discovery_register = 110;
        break;
    }
    if (discovery_register == 0)
        return s_B1;
    return s_F1;
}

int StateM::F1a()
{
    ++discovery_register;
    return s_F1;
}

int StateM::G1a()
{
    data_token el;
    el.CToken = LEFT_BRACKET;
    vecToken.emplace_back(el);
    return s_A1;
}

int StateM::G1b()
{
    data_token el;
    el.CToken = RIGHT_BRACKET;
    vecToken.emplace_back(el);
    return s_A1;
}

int StateM::H1()
{
    reg_att = s.value;
    if (s.value == '=')
    {
        data_token el;
        el.CToken = ASSIGN;
        vecToken.emplace_back(el);
    }
    return s_H1;
}

// ������� ���������
int StateM::N1a()
{
    if (s.value == '<')
        return s_P1;

    reg_att += s.value;
    CreateAttitude();
    return s_A1;
}

//
int StateM::N1b()
{
    CreateAttitude();
    return F1();
}

int StateM::N1c()
{
    CreateAttitude();
    return C1a();
}

int StateM::N1d()
{
    if (reg_att != "=")
        CreateAttitude();
    return A1();
}

int StateM::O1()
{
    return s_O1;
}

int StateM::O1a()
{
    CreateConst();
    return s_O1;
}

int StateM::O1b()
{
    CreateVariable();
    return O3c();
}

int StateM::O1c()
{
    CreateConst();
    return Z2();
}

int StateM::O2a()
{
    reg_const = (s.value - '0');
    return s_O2;
}

int StateM::O2b()
{
    reg_const = reg_const * 10 + (s.value - '0');
    return s_O2;
}

int StateM::O3a()
{
    Variable v;
    v.const_value = reg_const;
    v.Type = 1;
    data_token el;
    el.CToken = LABLE;
    el.ptr = new Variable(v);
    vecToken.emplace_back(el);
    return A1();
}

int StateM::O3b()
{
    Variable v;
    v.const_value = reg_const;
    v.Type = 1;
    data_token el;
    el.CToken = LABLE;
    el.ptr = new Variable(v);
    vecToken.emplace_back(el);
    return A1a();
}

int StateM::O3c()
{
    data_token el;
    el.CToken = COLON;
    vecToken.emplace_back(el);
    return A1();
}

int StateM::O3d()
{
    data_token el;
    el.CToken = COLON;
    vecToken.emplace_back(el);
    return A1a();
}

int StateM::P2()
{
    if (s.value == '<')
        return s_P3;
    else
        return Error1();
}

int StateM::P3()
{
    if (s.value == '>')
        return s_P4;
    else
        return s_P3;
}

int StateM::P4()
{
    if (s.value == '>')
        return s_P5;
    return s_P3;
}

int StateM::P5()
{
    if (s.value == '>')
    {
        data_token el;
        el.CToken = COMMENT;
        vecToken.emplace_back(el);
        return A1();
    }
    else
        return s_P3;
}

int StateM::Q1a()
{
    vecToken.pop_back();
    return B1b();
}

int StateM::R2()
{
    if (!RegList.empty())
        RegList.clear();
    return s_R2;
}

int StateM::R3a()
{
    reg_const = (s.value - '0');
    return s_R3;
}

int StateM::R3b()
{
    reg_const = reg_const * 10 + (s.value - '0');
    return s_R3;
}

int StateM::R4b()
{
    RegList.push_back(reg_const);

    return s_R4;
}

int StateM::R5a()
{
    RegList.push_back(reg_const);

    CreateList();
    return A1();
}

int StateM::R5b()
{
    CreateList();
    return A1();
}

int StateM::Z1a()
{
    data_token el;
    el.CToken = BIN_UNIT;
    vecToken.emplace_back(el);
    return s_Z1;
}

int StateM::Z1b()
{
    data_token el;
    el.CToken = BIN_INTERS;
    vecToken.emplace_back(el);
    return s_Z1;
}

int StateM::Z1c()
{
    data_token el;
    el.CToken = BIN_DIFF;
    vecToken.emplace_back(el);
    return s_Z1;
}
int StateM::Z1d()
{
    data_token el;
    el.CToken = BIN_SYMM_DIFF;
    vecToken.emplace_back(el);
    return s_Z1;
}

int StateM::Z1e()
{
    data_token el;
    el.CToken = UN_ADD;
    vecToken.emplace_back(el);
    return s_Z1;
}

int StateM::Z1f()
{
    data_token el;
    el.CToken = UN_POW;
    vecToken.emplace_back(el);
    return s_Z1;
}

int StateM::Z1g()
{
    data_token el;
    el.CToken = UN_ITEM;
    vecToken.emplace_back(el);
    return s_Z1;
}

int StateM::Z2()
{
    data_token el;
    el.CToken = COMMA;
    vecToken.emplace_back(el);
    return A1();
}

int StateM::Error1()
{
    data_token el;
    el.CToken = ERR_TOKEN;
    vecToken.emplace_back(el);
    flagAnalyzer = false;
    return s_J1;
}

int StateM::J1()
{
    return s_J1;
}*/

#endif