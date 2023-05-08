#pragma once 
#ifndef DATA_TOKEN_H
#define DATA_TOKEN_H

#include <any>

enum TokenClass
{
    DIM,
    AS,
    UINT,
    HASH,
    LET,
    FOR,
    IN,
    NEXT,
    IF,
    THEN,
    ELSE,
    LOAD,
    PUT,
    GOTO,
    SWITCH,
    CASE,
    BREAK,
    RAISE,
    END_SWITCH,
    DUAL_MORE,
    VARIABLE,
    CONSTANT,
    HASH_CONST,
    BIN_SUM,
    BIN_SUB,
    BIN_MULT,
    BIN_DIV,
    BIN_MOD,
    UNION,
    HASH_INTERSEC,
    DIFF,
    SIMDIFF,
    ACCESS,
    POW,
    HASH_ADD,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    END_MARKER,
    SEMICOLON,
    ASSIGN,
    RATIO,
    COLON,
    LABLE,
    COMMENT,
    TYPE_LI,
    TYPE_UINT,
    ERR_TOKEN
};

struct data_token
{
    int num_str;
    int CToken;
    std::any ptr;
        
    data_token() : num_str(0), CToken(), ptr() {}

    data_token(int num, TokenClass CToken) : num_str(num), CToken(CToken), ptr() {}

    template<typename Type>
    data_token(int num, TokenClass CToken, const Type & ptr) :num_str(num), CToken(CToken), ptr(ptr) {} 

    template<typename Type>
    data_token(int num, TokenClass CToken, Type && move_ptr) : num_str(num), CToken(CToken), ptr(std::forward<Type>(move_ptr)) {}
};


#endif