#pragma once
#ifndef VECTORLEX_H
#define VECTORLEX_H

#include "StateMachine.h"
#include <unordered_set>

template<typename __Iter>
void print_set(__Iter first, __Iter last) {
    cout << "{ ";
    for(; first != last; ++first) {
        cout << *first << " "; 
    }
    cout << "}" << endl;

}

void PrintVec(const list<data_token> &obj)
{

    cout << "size Vector: " << obj.size() << endl;
    cout << "Token                           Value\n";
    cout << "-------------------------------------\n";
    for (const auto &[num_str, type, val] : obj)
    {
        cout.width(10);
        std::cout << num_str + 1;
        switch (type)
        {
        case HASH_CONST:
            cout.width(15);
            cout << "HASH_CONST";
            cout.width(10);
            /*for(auto &it:any_cast<hash_set>(val))
            {
                cout<< it<< ",";
            }*/
            cout << any_cast<hash_set>(val);
            break;
        case VARIABLE:
            cout.width(15);
            cout << "VARIABLE";
            cout.width(10);
            cout << any_cast<string>(val);
            break;
        case ASSIGN:
            cout.width(15);
            cout << "ASSIGN";
            break;
        case BIN_SUM:
            cout.width(15);
            cout << "AR_OP ";
            cout.width(10);
            cout << "+";
            break;
        case BIN_SUB:
            cout.width(15);
            cout << "AR_OP ";
            cout.width(10);
            cout << "-";
            break;
        case BIN_MULT:
            cout.width(15);
            cout << "AR_OP ";
            cout.width(10);
            cout << "*";
            break;
        case BIN_DIV:
            cout.width(15);
            cout << "AR_OP ";
            cout.width(10);
            cout << "/";
            break;
        case DUAL_MORE:
            cout.width(15);
            cout << "DUAL_MORE ";
            cout.width(10);
            cout << ">>";
            break;
        case BIN_MOD:
            cout.width(15);
            cout << "AR_OP ";
            cout.width(10);
            cout << "%";
            break;
        case CONSTANT:
            cout.width(15);
            cout << "CONSTANT ";
            cout.width(10);
            cout << std::any_cast<int>(val);
            break;
        case ERR_TOKEN:
            cout.width(15);
            cout << "ERROR ";
            break;
        case SEMICOLON:
            cout.width(15);
            cout << "SEMICOLON ";
            break;
        case END_MARKER:
            cout.width(15);
            cout << "END_MARKER ";
            break;
        case LET: 
            cout.width(15);
            cout << "LET";
            break;
        case DIM:
            cout.width(15);
            cout << "DIM";
            break;
        case AS:
            cout.width(15);
            cout << "AS";
            break;
        case FOR:
            cout.width(15);
            cout << "FOR";
            cout.width(10);
            cout << any_cast<std::string>(val);
            break;
        case UINT:
            cout.width(15);
            cout << "TYPE UINT";
            break;
        case HASH:
            cout.width(15);
            cout << "TYPE HASH";
            break;
        case IN:
            cout.width(15);
            cout << "IN";
            break;
        case NEXT:
            cout.width(15);
            cout << "NEXT";
            cout.width(10);
            cout << any_cast<int>(val);
            break;
        case IF:
            cout.width(15);
            cout << "IF";
            break;
        case THEN:
            cout.width(15);
            cout << "THEN";
            cout.width(10);
            cout << any_cast<int>(val);
            break;
        case ELSE:
            cout.width(15);
            cout << "ELSE";
            cout.width(10);
            cout << any_cast<int>(val);
            break;
        case LOAD:  
            cout.width(15);
            cout << "LOAD";
            cout.width(10);
            std::cout << "[ ";
            for(const auto& name : any_cast<std::vector<std::string>>(val)) {
                std::cout << name << " ";
            }
            std::cout << "]" << std::endl;
            break;
        case PUT:   
            cout.width(15);
            cout << "PUT";
            break;
        case GOTO:
            cout.width(15);
            cout << "GOTO";
            cout.width(10);
            cout << any_cast<int>(val);
            break;
        case SWITCH:
            cout.width(15);
            cout << "SWITCH";
            break;
        case CASE:
            cout.width(15);
            cout << "CASE";
            break;
        case BREAK:
            cout.width(15);
            cout << "BREAK";
            break;
        case END_SWITCH:
            cout.width(15);
            cout << "END_SWITCH";
            break;
        case RAISE:
            cout.width(15);
            cout << "RAISE";
            break;
        case COMMENT:   
            cout.width(15);
            cout << "COMMENT";
            break;
        case LEFT_BRACKET:
            cout.width(15);
            cout << "LEFT_BRACKET";
            break;
        case RIGHT_BRACKET:
            cout.width(15);
            cout << "RIGHT_BRACKET";
            break;
        case LABLE:
            cout.width(15);
            cout << "LABLE";
            cout.width(10);
            cout<< ":"<<any_cast<int>(val); 
            break;
        case UNION:
            cout.width(15);
            cout << "UNION";
            break;
        case HASH_INTERSEC:
            cout.width(15);
            cout << "HASH_INTERSEC";
            break;
        case DIFF:
            cout.width(15);
            cout << "DIFF";
            break;
        case SIMDIFF:
            cout.width(15);
            cout << "SIMDIFF";
            break;
        case ACCESS:
            cout.width(15);
            cout << "ACCESS";
            break;
        case POW:
            cout.width(15);
            cout << "POW";
            break;
        case HASH_ADD:
            cout.width(15);
            cout << "HASH_ADD";
            break;
        case COMMA:
            cout.width(15);
            cout << "COMMA";
            break;
        case RATIO:
            cout.width(15);
            cout << "RATIO ";
            cout.width(10);
            switch (std::any_cast<TypeRatio>(val))
            {
            case LESS:
                cout << "<";
                break;
            case MORE:
                cout << ">";
                break;
            case LESS_EQUAL:
                cout << "<=";
                break;
            case MORE_EQUAL:
                cout << ">=";
                break;
            case EQUAL:
                cout << "==";
                break;
            case INEQUAL:
                cout << "!=";
                break;
            }
            break;
       
        }
        cout << '\n';
    }
}

void PrintVariableSet(set<pair<string, bool>> &obj) // печать переменных
{
    cout << "{ ";
    for (set<pair<string, bool>>::iterator it = obj.begin(); it != obj.end(); ++it)
        cout << it->first << " ";
    cout << "}";
}

void PrintConst(set<long double> &obj) // печать констант
{
    cout << "{ ";
    for (set<long double>::iterator it = obj.begin(); it != obj.end(); ++it)
        cout << *it << "   ";
    cout << "}";
}

void PrintErrors()
{
    for(auto & line:vec_errors)
    {
        cout<<line<< endl;
    }
}

#endif