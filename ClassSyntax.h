#ifndef CLASS_SYNTAX_H
#define CLASS_SYNTAX_H
#include <functional>
#include "analyzer.h"

enum TypeEl
{
    _Program_,
    _Operator_,
    _Lc1_,
    _Lc2_,
    _Switch_,
    _When__,
    _Otherwise_,
    _Switch1_,
    _Switch2_,
    _List_const1_,
    _List_const2_,
    _nont_otherwise_,
    _E_bracket1_,
    _Load_list2_,
    _Load_list1_,
    _Symm_diff_,
    _Diff_,
    _Intersec_,
    _Unit_,
    _Li_const_,
    _Nont_comma,
    _E_bracket_,
    _Add_,
    _Pow_,
    _Item_,
    _Comment_,
    _Nont_goto_,
    _Goto_,
    _Lable_,
    _Nont_error_,
    _Error_,
    _Nont_Put1_,
    _Nont_Put_,
    _Put_,
    _Nont_else_,
    _Nont_If1_,
    _If_,
    _Then_,
    _Else_,
    _Nont_Exp_,
    _Nont_for_,
    _For_,
    _Each_,
    _In__,
    _List_let1_,
    _List_let_,
    _Let_,
    _Assign_,
    _Nont_let_,
    _Nont_load1_,
    _Nont_load,
    _Load_,
    _Nont_v_,
    _Expr_list1_,
    _Nont_R_br_,
    _Ty_li_,
    _Ty_uint_,
    _Declaration_,
    _Dec_1_,
    _Colon_,
    _Comma_,
    _Nont_While_,
    _End_,
    _While_,
    _Do_,
    _Semicolon_,
    _Test_,
    _Expression_,
    _E_list_,
    _Term_,
    _T_list_,
    _Factor_,
    _Plus_,
    _Minus_,
    _Mult_,
    _Div_,
    _Mod_,
    _Const__,
    _Variable_,
    _L_Bracket_,
    _R_Bracket_,
    _Equal_,
    _Inequal_,
    _Less_,
    _More_,
    _Less_eq_,
    _More_eq_,
    _Attitude_,
    _Bottom_
};

enum TypeStore
{
    _LS,
    _EQ,
    _MR
};

class Syntax32 : public StateM
{
protected:
    list<data_token>::iterator VecIter;
    bool CheckRule(list<TypeEl> &temp, vector<pair<TypeEl, bool>> &Vec);
    typedef void (Syntax32::*function_pointer)();
    function_pointer **table1; // Таблица указателей на процедуры автомата.
    list<TypeEl> store;        // магазин
    TypeStore reg_table;
    vector<pair<TypeEl, vector<pair<TypeEl, bool>>>> rules; //вектор правил
    void ClassificationFunction();
    void transformation();
    void RuleInitialisation();     // инициализация правил грамматики
    vector<pair<TypeEl, bool>> El; // элементы грамматики
    void MemoryTable();
    void InitializationTable(); // инициализация таблицы синтаксиса
    void InitializationFunction();
    vector<string> outputSyntax;

    void Init() { store.emplace_front(_Bottom_); }
    void Ls() { reg_table = _LS; }
    void Mr() { reg_table = _MR; }
    void Eq() { reg_table = _EQ; }
    void Error() { f1 = _STATE_ERROR_; }
    void accept() { f1 = _STATE_ACCEPT_; }

    vector<string> vecstr;

public:
    enum FlagState
    {
        _STATE_PROCESSING_,
        _STATE_ACCEPT_,
        _STATE_ERROR_
    };

    friend void TranslitC(const char *Foutput, bool &flagTranlit, set<pair<string, bool>> &SetVar);

    FlagState f1;

    Syntax32()
    {
        state_number = 89;
        class_number = 89;
        transformation();         // переопределение вектора лексического блока
        ClassificationFunction(); // инициализация таблицы для терминало и нетерминало, нетерминалы - 0, терминалы - 1
        RuleInitialisation();     // инициализация правил
        MemoryTable();
        InitializationTable();

        f1 = _STATE_PROCESSING_; // ФЛАГ состояния
    }

    void StartSyntax()
    {
        Init();                     // инициализация магазина (первый эл-т - дно)
        VecIter = vecToken.begin(); // устанавливаем итератор на начло массива лексем
        while (f1 == _STATE_PROCESSING_)
        {
            if (store.size() <= 2 && store.back() == _Program_ && VecIter->CToken == _Bottom_)
                return accept();

            auto it = store.end();
            --it;
            (this->*table1[*it][VecIter->CToken])();
            if (reg_table == _EQ) // смотрим на начало входного магазина
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

        list<TypeEl> temp; // фрагмент, который нужно удалить
        while (reg_table != _LS)
        {
            auto it = store.end();
            --it;
            auto it1 = store.end();
            --it1;
            --it1;
            // вызов таблицы, по магазину идём справа налево
            (this->*table1[*it1][*it])();
            temp.push_front(*it);
            store.pop_back();
        }

        // ищем правило
        for (size_t i = 0; i < rules.size(); ++i)
        {
            // если правило совпадает
            if (CheckRule(temp, rules[i].second))
            {
                store.push_back(rules[i].first);
                return;
            }
        }

        if (store.size() <= 2 && store.back() == _Program_ && VecIter->CToken == _Bottom_)
            return accept();
    }

    void PrintConfig()
    {
        switch (f1)
        {
        case _STATE_ACCEPT_:
            cout << "SYNTAX: accept";
            break;
        case _STATE_ERROR_:
            cout << "SYNTAX: error";
            break;
        case _STATE_PROCESSING_:
            cout << "SYNTAX: undefined";
            break;
        }
    }

    void PrintOutput()
    {
        for (size_t i = 0; i < vecstr.size(); ++i)
            cout << vecstr[i] << endl;
    }
};

void Syntax32::transformation()
{
    for (list<data_token>::iterator el = vecToken.begin(); el != vecToken.end(); ++el)
    {
        switch (el->CToken)
        {
        case SWITCH:
            el->CToken = _Switch_;
            break;
        case OTHERWISE:
            el->CToken = _Otherwise_;
            break;
        case WHEN:
            el->CToken = _When__;
            break;
        case BIN_UNIT:
            el->CToken = _Unit_;
            break;
        case BIN_INTERS:
            el->CToken = _Intersec_;
            break;
        case BIN_DIFF:
            el->CToken = _Diff_;
            break;
        case BIN_SYMM_DIFF:
            el->CToken = _Symm_diff_;
            break;
        case CONST_LIST:
            el->CToken = _Li_const_;
            break;
        case UN_ITEM:
            el->CToken = _Item_;
            break;
        case UN_POW:
            el->CToken = _Pow_;
            break;
        case UN_ADD:
            el->CToken = _Add_;
            break;
        case COMMENT:
            el->CToken = _Comment_;
            break;
        case GOTO:
            el->CToken = _Goto_;
            break;
        case LABLE:
            el->CToken = _Lable_;
            break;
        case ERROR:
            el->CToken = _Error_;
            break;
        case PUT:
            el->CToken = _Put_;
            break;
        case IF:
            el->CToken = _If_;
            break;
        case THEN:
            el->CToken = _Then_;
            break;
        case ELSE:
            el->CToken = _Else_;
            break;
        case FOR:
            el->CToken = _For_;
            break;
        case EACH:
            el->CToken = _Each_;
            break;
        case IN:
            el->CToken = _In__;
            break;
        case LET:
            el->CToken = _Let_;
            break;
        case ASSIGN:
            el->CToken = _Assign_;
            break;
        case LOAD:
            el->CToken = _Load_;
            break;
        case END:
            el->CToken = _End_;
            break;
        case TYPE_UINT:
            el->CToken = _Ty_uint_;
            break;
        case TYPE_LI:
            el->CToken = _Ty_li_;
            break;
        case COLON:
            el->CToken = _Colon_;
            break;
        case COMMA:
            el->CToken = _Comma_;
            break;
        case WHILE:
            el->CToken = _While_;
            break;
        case DO:
            el->CToken = _Do_;
            break;
        case SEMICOLON:
            el->CToken = _Semicolon_;
            break;
        case VARIABLE:
            el->CToken = _Variable_;
            break;
        case BIN_SUM:
            el->CToken = _Plus_;
            break;
        case BIN_MULT:
            el->CToken = _Mult_;
            break;
        case CONSTANT:
            el->CToken = _Const__;
            break;
        case LEFT_BRACKET:
            el->CToken = _L_Bracket_;
            break;
        case RIGHT_BRACKET:
            el->CToken = _R_Bracket_;
            break;
        case BIN_SUB:
            el->CToken = _Minus_;
            break;
        case BIN_DIV:
            el->CToken = _Div_;
            break;
        case BIN_MOD:
            el->CToken = _Mod_;
            break;
        case END_MARKER:
            el->CToken = _Bottom_;
            break;
        case ATTITUDE:
            switch (*static_cast<TypeAttitude *>(el->ptr))
            {
            case LESS:
                el->CToken = _Less_;
                break;
            case MORE:
                el->CToken = _More_;
                break;
            case EQUAL:
                el->CToken = _Equal_;
                break;
            case INEQUAL:
                el->CToken = _Inequal_;
                break;
            case LESS_EQUAL:
                el->CToken = _Less_eq_;
                break;
            case MORE_EQUAL:
                el->CToken = _More_eq_;
                break;
            }
            break;
        }
    }
}

void Syntax32::ClassificationFunction()
{
    El = {
        {{_Program_}, {0}},
        {{_Operator_}, {0}},
        {{_Lc1_}, {0}},
        {{_Lc2_}, {0}},
        {{_Switch_}, {1}},
        {{_When__}, {1}},
        {{_Otherwise_}, {1}},
        {{_Switch1_}, {0}},
        {{_Switch2_}, {0}},
        {{_List_const1_}, {0}},
        {{_List_const2_}, {0}},
        {{_nont_otherwise_}, {0}},
        {{_E_bracket1_}, {0}},
        {{_Load_list2_}, {0}},
        {{_Load_list1_}, {0}},
        {{_Symm_diff_}, {1}},
        {{_Diff_}, {1}},
        {{_Intersec_}, {1}},
        {{_Unit_}, {1}},
        {{_Li_const_}, {1}},
        {{_Nont_comma}, {0}},
        {{_E_bracket_}, {0}},
        {{_Add_}, {1}},
        {{_Pow_}, {1}},
        {{_Item_}, {1}},
        {{_Comment_}, {1}},
        {{_Nont_goto_}, {0}},
        {{_Goto_}, {1}},
        {{_Lable_}, {1}},
        {{_Nont_error_}, {0}},
        {{_Error_}, {1}},
        {{_Nont_Put1_}, {0}},
        {{_Nont_Put_}, {0}},
        {{_Put_}, {1}},
        {{_Nont_else_}, {0}},
        {{_Nont_If1_}, {0}},
        {{_If_}, {1}},
        {{_Then_}, {1}},
        {{_Else_}, {1}},
        {{_Nont_Exp_}, {0}},
        {{_Nont_for_}, {0}},
        {{_For_}, {1}},
        {{_Each_}, {1}},
        {{_In__}, {1}},
        {{_List_let1_}, {0}},
        {{_List_let_}, {0}},
        {{_Let_}, {1}},
        {{_Assign_}, {1}},
        {{_Nont_let_}, {0}},
        {{_Nont_load1_}, {0}},
        {{_Nont_load}, {0}},
        {{_Load_}, {1}},
        {{_Nont_v_}, {0}},
        {{_Expr_list1_}, {0}},
        {{_Nont_R_br_}, {0}},
        {{_Ty_li_}, {1}},
        {{_Ty_uint_}, {1}},
        {{_Declaration_}, {0}},
        {{_Dec_1_}, {0}},
        {{_Colon_}, {1}},
        {{_Comma_}, {1}},
        {{_Nont_While_}, {0}},
        {{_End_}, {1}},
        {{_While_}, {1}},
        {{_Do_}, {1}},
        {{_Semicolon_}, {1}},
        {{_Test_}, {0}},
        {{_Expression_}, {0}},
        {{_E_list_}, {0}},
        {{_Term_}, {0}},
        {{_T_list_}, {0}},
        {{_Factor_}, {0}},
        {{_Plus_}, {1}},
        {{_Minus_}, {1}},
        {{_Mult_}, {1}},
        {{_Div_}, {1}},
        {{_Mod_}, {1}},
        {{_Const__}, {1}},
        {{_Variable_}, {1}},
        {{_L_Bracket_}, {1}},
        {{_R_Bracket_}, {1}},
        {{_Equal_}, {1}},
        {{_Inequal_}, {1}},
        {{_Less_}, {1}},
        {{_More_}, {1}},
        {{_Less_eq_}, {1}},
        {{_More_eq_}, {1}},
        {{_Attitude_}, {0}},
        {{_Bottom_}, {0}}};
}

void Syntax32::RuleInitialisation()
{
    rules.resize(83);
    // выражения
    rules[0].first = _Expression_;
    rules[0].second = {El[_Term_]};

    rules[1].first = _Expression_;
    rules[1].second = {El[_Term_], El[_E_list_]};

    rules[2].first = _E_list_;
    rules[2].second = {El[_Plus_], El[_Term_], El[_E_list_]};

    rules[3].first = _E_list_;
    rules[3].second = {El[_Plus_], El[_Term_]};

    rules[4].first = _E_list_;
    rules[4].second = {El[_Minus_], El[_Term_], El[_E_list_]};

    rules[5].first = _E_list_;
    rules[5].second = {El[_Minus_], El[_Term_]};

    rules[6].first = _Term_;
    rules[6].second = {El[_Factor_]};

    rules[7].first = _Term_;
    rules[7].second = {El[_Factor_], El[_T_list_]};

    rules[8].first = _T_list_;
    rules[8].second = {El[_Mult_], El[_Factor_], El[_T_list_]};

    rules[9].first = _T_list_;
    rules[9].second = {El[_Mult_], El[_Factor_]};

    rules[10].first = _T_list_;
    rules[10].second = {El[_Div_], El[_Factor_], El[_T_list_]};

    rules[11].first = _T_list_;
    rules[11].second = {El[_Div_], El[_Factor_]};

    rules[12].first = _T_list_;
    rules[12].second = {El[_Mod_], El[_Factor_], El[_T_list_]};

    rules[13].first = _T_list_;
    rules[13].second = {El[_Mod_], El[_Factor_]};

    rules[14].first = _Factor_;
    rules[14].second = {El[_L_Bracket_], El[_Expression_], El[_R_Bracket_]};

    rules[15].first = _Factor_;
    rules[15].second = {El[_Const__]};

    rules[16].first = _Factor_;
    rules[16].second = {El[_Variable_]};
    // отношения
    rules[17].first = _Test_;
    rules[17].second = {El[_Expression_], El[_Attitude_], El[_Expression_]};

    rules[18].first = _Attitude_;
    rules[18].second = {El[_Equal_]};

    rules[19].first = _Attitude_;
    rules[19].second = {El[_Inequal_]};

    rules[20].first = _Attitude_;
    rules[20].second = {El[_Less_]};

    rules[21].first = _Attitude_;
    rules[21].second = {El[_More_]};

    rules[22].first = _Attitude_;
    rules[22].second = {El[_More_eq_]};

    rules[23].first = _Attitude_;
    rules[23].second = {El[_Less_eq_]};

    rules[24].first = _Program_;
    rules[24].second = {El[_Operator_]};

    rules[25].first = _Program_;
    rules[25].second = {El[_Operator_], El[_Program_]};
    // пустой оператор
    rules[26].first = _Operator_;
    rules[26].second = {El[_Semicolon_]};
    // вайл
    rules[27].first = _Operator_;
    rules[27].second = {El[_Nont_While_], El[_End_], El[_Semicolon_]};

    rules[28].first = _Nont_While_;
    rules[28].second = {El[_While_], El[_Test_], El[_Do_], El[_Program_]};

    // выражения для списков
    rules[29].first = _Factor_;
    rules[29].second = {El[_Pow_], El[_L_Bracket_], El[_Expression_], El[_R_Bracket_]};

    rules[30].first = _Factor_;
    rules[30].second = {El[_Add_], El[_L_Bracket_], El[_Expression_], El[_R_Bracket_]};

    rules[31].first = _Factor_;
    rules[31].second = {El[_Item_], El[_L_Bracket_], El[_Expression_], El[_Nont_comma], El[_E_bracket_]};

    rules[32].first = _Factor_;
    rules[32].second = {El[_Li_const_]};

    rules[33].first = _Factor_;
    rules[33].second = {El[_Unit_], El[_L_Bracket_], El[_Expression_], El[_Nont_comma], El[_E_bracket_]};

    rules[34].first = _Factor_;
    rules[34].second = {El[_Intersec_], El[_L_Bracket_], El[_Expression_], El[_Nont_comma], El[_E_bracket_]};

    rules[35].first = _Factor_;
    rules[35].second = {El[_Diff_], El[_L_Bracket_], El[_Expression_], El[_Nont_comma], El[_E_bracket_]};

    rules[36].first = _Factor_;
    rules[36].second = {El[_Symm_diff_], El[_L_Bracket_], El[_Expression_], El[_Nont_comma], El[_E_bracket_]};

    rules[37].first = _E_bracket_;
    rules[37].second = {El[_Expression_], El[_R_Bracket_]};

    rules[38].first = _Nont_comma;
    rules[38].second = {El[_Comma_]};

    // LET
    rules[39].first = _Operator_;
    rules[39].second = {El[_Nont_let_], El[_Semicolon_]};

    rules[40].first = _Nont_let_;
    rules[40].second = {El[_Let_], El[_Variable_], El[_Assign_], El[_List_let_]};

    rules[41].first = _List_let_;
    rules[41].second = {El[_Variable_], El[_Assign_], El[_List_let_]};

    rules[42].first = _List_let_;
    rules[42].second = {El[_List_let1_]};

    rules[43].first = _List_let1_;
    rules[43].second = {El[_Expression_]};

    // вывод
    rules[44].first = _Operator_;
    rules[44].second = {El[_Nont_Put_], El[_Semicolon_]};

    rules[45].first = _Nont_Put_;
    rules[45].second = {El[_Put_], El[_Expr_list1_]};

    rules[46].first = _Expr_list1_;
    rules[46].second = {El[_Expression_], El[_Nont_comma], El[_Expr_list1_]};

    rules[47].first = _Expr_list1_;
    rules[47].second = {El[_Expression_], El[_Nont_comma], El[_E_bracket_]};

    rules[48].first = _Operator_;
    rules[48].second = {El[_Nont_Put1_], El[_Semicolon_]};

    rules[49].first = _Nont_Put1_;
    rules[49].second = {El[_Put_], El[_E_bracket_]};

    // ввод
    rules[50].first = _Operator_;
    rules[50].second = {El[_Nont_load1_], El[_Semicolon_]};

    rules[51].first = _Nont_load1_;
    rules[51].second = {El[_Load_list1_], El[_Nont_R_br_]};

    rules[52].first = _Load_list1_;
    rules[52].second = {El[_Load_], El[_Variable_]};

    rules[53].first = _Load_list1_;
    rules[53].second = {El[_Load_list2_], El[_Variable_]};

    rules[54].first = _Load_list2_;
    rules[54].second = {El[_Load_list1_], El[_Comma_]};

    rules[55].first = _Nont_R_br_;
    rules[55].second = {El[_R_Bracket_]};

    // объявдение
    rules[56].first = _Operator_;
    rules[56].second = {El[_Declaration_], El[_Semicolon_]};

    rules[57].first = _Declaration_;
    rules[57].second = {El[_Ty_uint_], El[_Colon_], El[_Variable_]};

    rules[58].first = _Declaration_;
    rules[58].second = {El[_Dec_1_], El[_Variable_]};

    rules[59].first = _Dec_1_;
    rules[59].second = {El[_Declaration_], El[_Comma_]};

    rules[60].first = _Declaration_;
    rules[60].second = {El[_Ty_li_], El[_Colon_], El[_Variable_]};

    // IF
    rules[61].first = _Operator_;
    rules[61].second = {El[_Nont_If1_], El[_End_], El[_Semicolon_]};

    rules[62].first = _Nont_If1_;
    rules[62].second = {El[_If_], El[_Test_], El[_Then_], El[_Program_]};

    rules[63].first = _Nont_If1_;
    rules[63].second = {El[_Nont_else_], El[_Program_]};

    rules[64].first = _Nont_else_;
    rules[64].second = {El[_Nont_If1_], El[_Else_]};

    // FOR EACH -
    rules[65].first = _Operator_;
    rules[65].second = {El[_Nont_for_], El[_End_], El[_Semicolon_]};

    rules[66].first = _Nont_for_;
    rules[66].second = {El[_For_], El[_Each_], El[_Variable_], El[_In__], El[_List_let1_], El[_Do_], El[_Program_]};

    // LABLE
    rules[67].first = _Operator_;
    rules[67].second = {El[_Lable_]};

    // GOTO
    rules[68].first = _Operator_;
    rules[68].second = {El[_Nont_goto_], El[_Semicolon_]};

    rules[69].first = _Nont_goto_;
    rules[69].second = {El[_Goto_], El[_Const__]};

    // ERR
    rules[70].first = _Operator_;
    rules[70].second = {El[_Nont_error_], El[_Semicolon_]};

    rules[71].first = _Nont_error_;
    rules[71].second = {El[_Error_]};

    // COMMENT
    rules[72].first = _Operator_;
    rules[72].second = {El[_Comment_]};

    // switch
    rules[73].first = _Operator_;
    rules[73].second = {El[_Switch1_], El[_End_], El[_Semicolon_]};

    rules[74].first = _Switch1_;
    rules[74].second = {El[_Switch_], El[_L_Bracket_], El[_Expression_], El[_R_Bracket_], El[_List_const1_]};

    rules[75].first = _List_const1_;
    rules[75].second = {El[_List_const2_], El[_List_const1_]};

    rules[76].first = _List_const1_;
    rules[76].second = {El[_List_const2_]};

    rules[77].first = _List_const2_;
    rules[77].second = {El[_Lc1_], El[_Colon_], El[_Program_]};

    rules[78].first = _Lc1_;
    rules[78].second = {El[_When__], El[_Const__]};

    rules[79].first = _Lc1_;
    rules[79].second = {El[_Lc2_], El[_Const__]};

    rules[80].first = _Lc2_;
    rules[80].second = {El[_Lc1_], El[_Comma_]};

    rules[81].first = _List_const1_;
    rules[81].second = {El[_nont_otherwise_]};

    rules[82].first = _nont_otherwise_;
    rules[82].second = {El[_Otherwise_], El[_Colon_], El[_Program_]};
}

void Syntax32::MemoryTable()
{
    table1 = new function_pointer *[state_number];
    for (size_t i = 0; i < state_number; ++i)
        table1[i] = new function_pointer[class_number];
}

bool Syntax32::CheckRule(list<TypeEl> &temp, vector<pair<TypeEl, bool>> &Vec)
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

#endif