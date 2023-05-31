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
    DEFAULT,
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

    data_token(int num, int CToken) : num_str(num), CToken(CToken), ptr() {}

    data_token(const data_token & rhs) : num_str(rhs.num_str), CToken(rhs.CToken), ptr(rhs.ptr) {}

    data_token(data_token && rhs) : num_str(rhs.num_str), CToken(rhs.CToken), ptr(std::move(rhs.ptr)) {}

    template<typename Type>
    data_token(int num, int CToken, Type && ptr) : num_str(num), CToken(CToken), ptr(std::forward<Type>(ptr)) {}

    ~data_token() {}
};


#endif