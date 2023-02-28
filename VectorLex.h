#pragma once
#ifndef VECTORLEX_H
#define VECTORLEX_H

#include "StateMachine.h"

void PrintVec(const list<data_token> &obj)
{

    cout << "size Vector: " << obj.size() << endl;
    cout << "Token                           Value\n";
    cout << "-------------------------------------\n";
    for (const auto &[type, val] : obj)
    {
        //std::cout << type << std::endl;
        switch (type)
        {
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
        case ATTITUDE:
            cout.width(15);
            cout << "ATTITUDE ";
            cout.width(10);
            switch (std::any_cast<TypeAttitude>(val))
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

void PrintVariableSet(set<pair<string, bool>> &obj) // ��� ����������
{
    cout << "{ ";
    for (set<pair<string, bool>>::iterator it = obj.begin(); it != obj.end(); ++it)
        cout << it->first << " ";
    cout << "}";
}

void PrintConst(set<long double> &obj)
{
    cout << "{ ";
    for (set<long double>::iterator it = obj.begin(); it != obj.end(); ++it)
        cout << *it << "   ";
    cout << "}";
}

#endif