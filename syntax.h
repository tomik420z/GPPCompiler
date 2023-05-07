#ifndef OBJECT_SYNTAX_H
#define OBJECT_SYNTAX_H
#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "analyzer.h"
using namespace std;

enum TypeEl
{
    _S,
    _T,
    _R,
    _A,
    _C,
    _B,
    a,
    d,
    c,
    _Bottom_
};

enum TypeStore
{
    _LS,
    _EQ,
    _MR
};

struct classific
{
    TypeEl value;
    bool IsTerminal;
};

class Syntax : public StateM
{
protected:
    list<data_token>::iterator VecIter;
    bool CheckRule(list<TypeEl> &temp, vector<pair<TypeEl, bool>> &Vec);
    typedef void (Syntax::*function_pointer)();
    function_pointer **table1; // ������� ���������� �� ��������� ��������
    enum StateSyntax
    {
        _ACCEPT,
        _ERROR,
        _PROCESSING
    };
    StateSyntax state;

public:
    bool flagSyntax;
    list<TypeEl> store; // �������
    TypeStore reg_table;
    void TestTable();
    void MemoryTable();
    void Initialization(); // ��� ������ ���������� ����������� Error
    void Filling_EQ();     // ���������� ����� ���������� "="
    void Filling_LS();     // ���������� ����� ���������� "<"
    void Filling_MR();     // ���������� ����� ���������� ">"
    void Filling_Bottom(); // ���������� �������� ��������
    void transformation();
    void ClassificationFunction();
    bool CheckTableEq(TypeEl ind1, TypeEl ind2);
    bool CheckTableLs(TypeEl ind1, TypeEl ind2);
    bool CheckTableMr(TypeEl ind1, TypeEl ind2);
    void PrintBeg();
    void PrintBack();
    void PrintCompFirst1();
    void PrintTableClass();
    void PrintElementCl(const TypeEl &el);           // ����������� �������
    void RuleInitialisation();                       // ������������� ������ ����������
    void BeginFunction();                            // ������� ��� ���������� ���
    void BackFunction();                             // ������� ��� ���������� ���
    void CompFirst1Function();                       // ������� ��� ���������� FIRST1*(��� ���)
    bool FindEl(const int &index, const TypeEl &el); // ��� ��� ���
    bool FindEl2(const int &index, const TypeEl &el);
    void ComputBegEl(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule); // ��������� ��� �������
    void ComputEndEl(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule); // ��������� ��� �������
    vector<pair<TypeEl, bool>> ComputFirst1El(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj);
    pair<TypeEl, bool> CallFirst(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule); // ������� ������ ��-� ������
    pair<TypeEl, bool> CallLast(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule);  // ������� ��������� ��-�

    void Ls();
    void Eq();
    void Mr();
    void accept();
    void Error();

    vector<vector<pair<TypeEl, bool>>> BeginList;           // ������ ���
    vector<vector<pair<TypeEl, bool>>> BackList;            // ������ ���
    vector<vector<pair<TypeEl, bool>>> First1List;          // ������ Fist1
    vector<pair<TypeEl, bool>> El;                          // �������� ����������
    vector<pair<TypeEl, vector<pair<TypeEl, bool>>>> rules; //������ ������
    set<pair<TypeEl, bool>> RegRules;

    Syntax()
    {
        state_number = 72;
        class_number = 72;
        transformation();         // ��������������� ������� ������������ �����
        ClassificationFunction(); // ������������� ������� ��� ��������� � �����������, ����������� - 0, ��������� - 1
        RuleInitialisation();     // ������������� ������
        BeginFunction();          // ���������� ���
        BackFunction();           // ���������� ���
        CompFirst1Function();     // ���������� FIRST1
        MemoryTable();            // ��������� ������ ��� �������
        Initialization();         // ��������� ������� Err
        Filling_EQ();             // ���������� ������� EQ
        Filling_LS();             // ���������� ������� LS
        Filling_MR();             // ���������� ������� MR
        Filling_Bottom();

        PrintBeg();
        PrintBack();
        PrintCompFirst1();

        for (size_t i = 0; i < 8; ++i)
        {
            for (size_t j = 0; j < 8; ++j)
            {
                (this->*table1[i][j])();
            }
            cout << "\n";
        }
    }

    void Init() { store.emplace_front(_Bottom_); }

    void StartSyntax()
    {
        state = _PROCESSING;
        Init();
        VecIter = vecToken.begin();
        while (state == _PROCESSING)
        {
            if (store.size() <= 2 && store.back() == _S && VecIter->CToken == _Bottom_)
                return accept();

            auto it = store.end();
            --it;
            (this->*table1[*it][VecIter->CToken])();
            if (reg_table == _EQ)
                Transfer();
            else if (reg_table == _LS)
                Transfer();
            else if (reg_table == _MR)
                Convolution();
        }
    }

    void Transfer()
    {
        store.emplace_back(static_cast<TypeEl>(VecIter->CToken));
        ++VecIter;
    }

    void Convolution()
    {

        list<TypeEl> temp; // ��������, ������� ����� �������
        while (reg_table != _LS)
        {
            auto it = store.end();
            --it;
            auto it1 = store.end();
            --it1;
            --it1;

            (this->*table1[*it1][*it])();
            temp.push_front(*it);
            store.pop_back();
        }

        for (size_t i = 0; i < rules.size(); ++i)
        {
            if (CheckRule(temp, rules[i].second))
            {
                store.push_back(rules[i].first);
                return;
            }
        }

        if (store.size() <= 2 && store.back() == _S && VecIter->CToken == _Bottom_)
            return accept();

        cout << "there were no rules for convolution" << endl;
        return Error();
    }
};

void Syntax::ClassificationFunction()
{

    El = {
        {{_S}, {0}},
        {{_T}, {0}},
        {{_R}, {0}},
        {{_A}, {0}},
        {{_C}, {0}},
        {{_B}, {0}},
        {{a}, {1}},
        {{d}, {1}},
        {{c}, {1}},
        {{_Bottom_}, {0}}};
}

void Syntax::RuleInitialisation()
{
    rules.resize(8);
    rules[0].first = _S;
    rules[0].second = {El[_T], El[_S]};

    rules[1].first = _S;
    rules[1].second = {El[_T]};

    rules[2].first = _T;
    rules[2].second = {El[a], El[_R], El[_A]};

    rules[3].first = _A;
    rules[3].second = {El[a]};

    rules[4].first = _B;
    rules[4].second = {El[_C], El[c]};

    rules[5].first = _R;
    rules[5].second = {El[_B], El[_R], El[_B]};

    rules[6].first = _R;
    rules[6].second = {El[d]};

    rules[7].first = _C;
    rules[7].second = {El[c]};
}

void Syntax::transformation()
{
    /*
    for (list<data_token>::iterator el = vecToken.begin(); el != vecToken.end(); ++el)
    {
        switch (el->CToken)
        {
        case SEMICOLON:
            el->CToken = _Semicolon;
            break;
        case DIM:
            el->CToken = _Dim;
            break;
        case TYPE:
            el->CToken = _Type;
            break;
        case AS:
            el->CToken = _As;
            break;
        case LET:
            el->CToken = _Let;
            break;
        case FOR:
            el->CToken = _For;
            break;
        case EACH:
            el->CToken = _Each;
            break;
        case IN:
            el->CToken = _In;
            break;
        case NEXT:
            el->CToken = _Next;
            break;
        case GOTO:
            el->CToken = _Goto;
            break;
        case WHEN:
            el->CToken = _When;
            break;
        case LOAD:
            el->CToken = _Load;
            break;
        case PUT:
            el->CToken = _Put;
            break;
        case LABLE:
            el->CToken = _Lable;
            break;
        case ON:
            el->CToken = _On;
            break;
        case CASE:
            el->CToken = _Case;
            break;
        case FAIL:
            el->CToken = _Fail;
            break;
        case COMMENT:
            el->CToken = _Comment;
            break;
        case BIN_OPERATION:
            switch (*static_cast<TypeOperation *>(el->ptr))
            {
            case BIN_SUM:
                el->CToken = _Sum;
                break;
            case BIN_SUB:
                el->CToken = _Sub;
                break;
            case BIN_MULT:
                el->CToken = _Mult;
                break;
            case BIN_DIV:
                el->CToken = _Div;
                break;
            case BIN_MOD:
                el->CToken = _Mod;
                break;
            }
            break;
        case ATTITUDE:
            el->CToken = _Attitide;
            break;
        case LEFT_BRACKET:
            el->CToken = _Left_bracket;
            break;
        case RIGHT_BRACKET:
            el->CToken = _Right_bracket;
            break;
        case COMMA:
            el->CToken = _Comma;
            break;
        case VARIABLE:
            el->CToken = _Var;
            break;
        case CONSTANT:
            el->CToken = _Const;
            break;
        case ASSIGN:
            el->CToken = _Assign;
            break;
        case COLON:
            el->CToken = _Colon;
            break;
        case DO:
            el->CToken = _Do;
            break;
        case END_MARKER:
            el->CToken = _Bottom_;
            break;
        }
    }
    */
}

void Syntax::Ls()
{
    reg_table = _LS;
    cout << " < ";
}

void Syntax::Mr()
{
    reg_table = _MR;
    cout << " > ";
}
void Syntax::Eq()
{
    reg_table = _EQ;
    cout << " = ";
}

void Syntax::Error()
{
    cout << "   ";

    state = _ERROR;
    flagSyntax = false;
}

void Syntax::accept()
{
    state = _ACCEPT;
    flagSyntax = true;
}

bool Syntax::CheckRule(list<TypeEl> &temp, vector<pair<TypeEl, bool>> &Vec)
{
    if (temp.size() != Vec.size())
        return 0;
    int count = 0;
    for (auto i = temp.begin(); i != temp.end(); ++i)
    {
        if (Vec[count].first != *i)
            return 0;
        ++count;
    }
    return 1;
}

void Syntax::Filling_Bottom()
{
    for (size_t i = 0; i < BeginList[0].size(); ++i)
        table1[_Bottom_][BeginList[0][i].first] = &Syntax::Ls;

    for (size_t i = 0; i < BackList[0].size(); ++i)
        table1[BackList[0][i].first][_Bottom_] = &Syntax::Mr;
}

void Syntax::Filling_MR()
{
    TypeEl temp1, temp2;
    for (size_t i = 0; i < rules.size(); ++i)
    {
        for (size_t j = 0; j < rules[i].second.size() - 1; ++j)
        {
            temp1 = rules[i].second[j].first;
            temp2 = rules[i].second[j + 1].first;
            if (rules[i].second[j].second == 0)
                for (size_t k = 0; k < BackList[temp1].size(); ++k)
                    for (size_t c = 0; c < First1List[temp2].size(); ++c)
                        if (CheckTableMr(BackList[temp1][k].first, First1List[temp2][c].first))
                            table1[BackList[temp1][k].first][First1List[temp2][c].first] = &Syntax::Mr;
        }
    }
}

void Syntax::TestTable()
{
    for (size_t i = 0; i < state_number; ++i)
    {
        for (size_t j = 0; j < state_number; ++j)
        {
            (this->*table1[i][j])();
        }
        cout << '\n';
    }
}

void Syntax::Filling_EQ()
{
    TypeEl temp1, temp2;
    for (size_t i = 0; i < rules.size(); ++i)
    {
        for (size_t j = 0; j < rules[i].second.size() - 1; ++j)
        {
            temp1 = rules[i].second[j].first;
            temp2 = rules[i].second[j + 1].first;
            if (CheckTableEq(temp1, temp2))
                table1[temp1][temp2] = &Syntax::Eq;
        }
    }
}

void Syntax::Filling_LS()
{
    TypeEl temp1, temp2;

    for (size_t i = 0; i < rules.size(); ++i)
    {
        for (size_t j = 0; j < rules[i].second.size() - 1; ++j)
        {
            temp1 = rules[i].second[j].first;
            temp2 = rules[i].second[j + 1].first;
            if (rules[i].second[j + 1].second == 0)
            {
                for (int k = 0; k < BeginList[temp2].size(); ++k)
                    if (CheckTableLs(temp1, BeginList[temp2][k].first))
                        table1[temp1][BeginList[temp2][k].first] = &Syntax::Ls;
            }
        }
    }
}

void Syntax::Initialization()
{
    for (size_t i = 0; i < state_number; ++i)
        for (size_t j = 0; j < state_number; ++j)
            table1[i][j] = &Syntax::Error;
}

bool Syntax::CheckTableEq(TypeEl ind1, TypeEl ind2)
{
    if (table1[ind1][ind2] == &Syntax::Error || table1[ind1][ind2] == &Syntax::Eq)
        return true;
    else
    {
        cout << "������ : ";
        PrintElementCl(ind1);
        cout << '\n';
        cout << "������� : ";
        PrintElementCl(ind2);
        cout << '\n';
        throw "�������� ������� Eq...";
    }
}

bool Syntax::CheckTableLs(TypeEl ind1, TypeEl ind2)
{
    if (table1[ind1][ind2] == &Syntax::Error || table1[ind1][ind2] == &Syntax::Ls)
        return true;
    else
    {
        if (table1[ind1][ind2] == &Syntax::Eq)
            cout << "Eq\n";
        if (table1[ind1][ind2] == &Syntax::Ls)
            cout << "Ls\n";

        cout << "������ : ";
        PrintElementCl(ind1);
        cout << '\n';
        cout << "������� : ";
        PrintElementCl(ind2);
        cout << '\n';
        throw "�������� ������� Ls...";
    }
}

bool Syntax::CheckTableMr(TypeEl ind1, TypeEl ind2)
{
    if (table1[ind1][ind2] == &Syntax::Error || table1[ind1][ind2] == &Syntax::Mr)
        return true;
    else
    {
        if (table1[ind1][ind2] == &Syntax::Eq)
            cout << "Eq\n";
        if (table1[ind1][ind2] == &Syntax::Ls)
            cout << "Ls\n";
        cout << "������ ";
        PrintElementCl(ind1);
        cout << '\n';
        cout << "������� : ";
        PrintElementCl(ind2);
        cout << '\n';
        throw "�������� ������� Mr...";
    }
}

void Syntax::MemoryTable()
{
    table1 = new function_pointer *[state_number];
    for (size_t i = 0; i < state_number; ++i)
        table1[i] = new function_pointer[class_number];
}

void Syntax::PrintTableClass()
{
    for (auto &el : El)
    {
        PrintElementCl(el.first);
        cout << "  : " << el.second << endl;
    }
}

void Syntax::PrintBeg()
{
    cout << "SetSymb.size : " << BeginList.size() << endl;
    int count = 0;
    for (auto el : BeginList)
    {
        cout << count << ") ���(";

        PrintElementCl(static_cast<TypeEl>(count));
        cout << ") = {";
        ++count;
        for (auto el1 : el)
        {
            PrintElementCl(el1.first);
            cout << "  ";
        }
        cout << "}\n";
    }
    cout << '\n';
}

void Syntax::PrintBack()
{
    cout << "SetSymb.size : " << BackList.size() << endl;
    int count = 0;
    for (auto el : BackList)
    {
        cout << count << ") ���(";

        PrintElementCl(static_cast<TypeEl>(count));
        cout << ") = {";
        ++count;
        for (auto el1 : el)
        {
            PrintElementCl(el1.first);
            cout << "  ";
        }
        cout << "}\n";
    }
    cout << '\n';
}

void Syntax::PrintCompFirst1()
{
    cout << "SetSymb.size : " << First1List.size() << endl;
    int count = 0;
    for (auto el : First1List)
    {
        cout << count << ") FIRST1(";

        PrintElementCl(static_cast<TypeEl>(count));
        cout << ") = {";
        ++count;
        for (auto el1 : el)
        {
            PrintElementCl(el1.first);
            cout << "  ";
        }
        cout << "}\n";
    }
    cout << '\n';
}

void Syntax::PrintElementCl(const TypeEl &el)
{

    switch (el)
    {
    case _S:
        cout << "S";
        break;
    case _T:
        cout << "T";
        break;
    case _R:
        cout << "R";
        break;
    case _A:
        cout << "K";
        break;
    case a:
        cout << "a";
        break;
    case d:
        cout << "d";
        break;
    case c:
        cout << "c";
        break;
    }
}

bool Syntax::FindEl(const int &index, const TypeEl &el)
{
    for (auto obj : BeginList[index])
        if (obj.first == el)
            return 1;
    return 0;
}

void Syntax::BeginFunction()
{
    BeginList.resize(El.size());
    for (size_t i = 0; i < rules.size(); ++i) //�������� �� ���� ��������
    {
        ComputBegEl(rules[i]);                                       // ���������� ��� ��� �������� �������
        for (auto it = RegRules.begin(); it != RegRules.end(); ++it) // ������� �������� �� �����
        {
            if (FindEl(rules[i].first, it->first) == 0) // ��� ������������� ��������� � ���������
                BeginList[rules[i].first].push_back(*it);
        }

        if (!RegRules.empty())
            RegRules.clear();
    }
}

void Syntax::ComputBegEl(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule)
{                                                             // ����� �������
    set<pair<TypeEl, bool>> ListSymb = {CallFirst(obj_rule)}; // ������� ������ ��-�
lable1:
    int count = ListSymb.size(); // ��������� ���-�� ��������� ����

    for (auto it = ListSymb.begin(); it != ListSymb.end(); ++it) //������� ��� �������� ���� � ���������
        RegRules.emplace(*it);

    for (auto jt = ListSymb.begin(); jt != ListSymb.end(); ++jt)
        for (size_t i = 0; i < rules.size(); ++i) // ���������� ��� �������
            if (rules[i].first == jt->first)      // ����������� ���������, �� ���������� ������ � ������������ �� �����
            {
                pair<TypeEl, bool> p;
                p = CallFirst(rules[i]);

                ListSymb.emplace(p);
            }

    if (ListSymb.size() == count)
        return;
    else
        goto lable1;
}

pair<TypeEl, bool> Syntax::CallFirst(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule)
{
    return *(obj_rule.second.begin());
}

pair<TypeEl, bool> Syntax::CallLast(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule)
{
    return (obj_rule.second.back());
}

void Syntax::ComputEndEl(pair<TypeEl, vector<pair<TypeEl, bool>>> &obj_rule)
{
    set<pair<TypeEl, bool>> ListSymb = {CallLast(obj_rule)}; // ������� ��������� ��-�
lable2:
    int count = ListSymb.size(); // ��������� ���-�� ��������� ����

    for (auto it = ListSymb.begin(); it != ListSymb.end(); ++it) //������� ��� �������� ���� � ���������
        RegRules.emplace(*it);

    for (auto jt = ListSymb.begin(); jt != ListSymb.end(); ++jt)
        for (size_t i = 0; i < rules.size(); ++i) // ���������� ��� �������
            if (rules[i].first == jt->first)      // ����������� ���������, �� ���������� ������ � ������������ �� �����
            {
                pair<TypeEl, bool> p;
                p = CallLast(rules[i]);

                ListSymb.emplace(p);
            }

    if (ListSymb.size() == count)
        return;
    else
        goto lable2;
}

bool Syntax::FindEl2(const int &index, const TypeEl &el)
{
    for (auto obj : BackList[index])
        if (obj.first == el)
            return 1;
    return 0;
}

void Syntax::BackFunction()
{
    if (!RegRules.empty())
        RegRules.clear();

    BackList.resize(El.size());
    for (size_t i = 0; i < rules.size(); ++i) //�������� �� ���� ��������
    {

        ComputEndEl(rules[i]); // ���������� ��� ��� �������� �������

        for (auto it = RegRules.begin(); it != RegRules.end(); ++it) // ������� �������� �� �����
        {
            if (FindEl2(rules[i].first, it->first) == 0) // ��� ������������� ��������� � ���������
                BackList[rules[i].first].push_back(*it);
        }

        if (!RegRules.empty())
            RegRules.clear();
    }
}

void Syntax::CompFirst1Function()
{
    // ��� -  �����������
    First1List.resize(El.size());

    for (size_t i = 0; i < BeginList.size(); ++i)
        for (size_t j = 0; j < BeginList[i].size(); ++j)
            if (BeginList[i][j].second == 1)
                First1List[i].push_back(BeginList[i][j]);

    for (size_t i = 0; i < El.size(); ++i)
        if (El[i].second == 1)
            First1List[i].push_back(El[i]);
}

/*


int Syntax::accept()
{
    cout << "ACCEPT";
    exit(10);
}

void Syntax::Transfer()
{
    pair<TypeChar, TypeStore> t;
    t.first = static_cast<TypeChar>(VecIter->CToken);
    store.emplace_back(t);
    ++VecIter;
}
/*
void Syntax::Convolution()
{
    list<TypeList> temp; // ��������, ������� ����� ������ � ����������
    list<pair<TypeList, TypeStore>>::iterator it = store.end();
    --it;
    for (; it->second != _LS; --it) // ���� �� ���������� < , ������� �������
        temp.emplace_back(it->first);
    //  cout <<" it :"<< it->first << endl;
    // temp.emplace_back(it->first); // ������ ������� <
    ++it;
    store.erase(it, store.end()); // ������� ��������

    for (size_t i = 0; i < rules.size(); ++i) // ���� ��������, �� ������� ����� ��������
    {
        if (temp == rules[i].second)
        {
            pair<TypeList, TypeStore> t;
            t.first = rules[i].first;
            store.emplace_back(t);
            return;
        }
    }

    throw "��� ������� ��� ������";
}*/

// �������������
/*
void Syntax::Init()
{
    pair<TypeChar, TypeStore> el;
    el.first = _Bottom_;
    store.emplace_front(el);
}

void Syntax::StartSyntax()
{
    Init();
    VecIter = vecToken.begin();
    while (true)
    {
        (this->*table1[store.back().first][VecIter->CToken])();
        if (store.back().second == _EQ)
        {
            Transfer(); // �������
        }
        if (store.back().second == _LS)
        {
            Transfer(); // �������
        }
        /*if (store.back().second == _MR)
        {
            Convolution(); // ������
        
    }
}


void Syntax::Print()
{
    cout << "PRINT\n";
    for (auto &el : vecToken)
        cout << el.CToken << endl;
}*/

#endif