#ifndef TRANSLITERATOR_H
#define TRANSLITERATOR_H

#include "StateMachine.h"

void StateM::transliterator(char ch)
{
    s.value = -10;
    if (ch >= '0' && ch <= '9')
    {
        s.SToken = LEX_DIGIT;
        s.value = ch;
    }
    else if ((ch >= 'a' && ch <= 'z') || ((ch >= 'A') && (ch <= 'Z')) || ch == '_')
    {
        s.SToken = LEX_CHARACTER;
        s.value = ch;
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
    {
        s.SToken = LEX_AR_OPERATION;
        s.value = ch;
    }
    else if (ch == '>' || ch == '<' || ch == '=' || ch == '!')
    {
        s.SToken = LEX_RATIO;
        s.value = ch;
    }
    else if (ch == '(')
    {
        s.SToken = LEX_L_BRACKET;
        s.value = ch;
    }
    else if (ch == ')')
    {
        s.SToken = LEX_R_BRACKET;
        s.value = ch;
    }
    else if (ch == ' ')
    {
        s.SToken = LEX_SPACE;
        s.value = ch;
    }
    else if (ch == '\n')
    {
        s.SToken = LEX_LF;
    }
    else if (ch == ',')
    {
        s.SToken = LEX_COMMA;
    }
    else if (ch == ';')
    {
        s.SToken = LEX_SEMICOLON;
    }
    else if (ch == ':')
    {
        s.SToken = LEX_COLON;
    }
    else if (ch == '[')
    {
        s.SToken = LEX_L_SQ_BRACKET;
    }
    else if (ch == ']')
    {
        s.SToken = LEX_R_SQ_BRACKET;
    }
    else
    {
        s.SToken = LEX_ERR_SYMB;
    }
}

#endif