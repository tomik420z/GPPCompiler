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
    BIN_SUM,
    BIN_SUB,
    BIN_MULT,
    BIN_DIV,
    BIN_MOD,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    END_MARKER,
    SEMICOLON,
    ASSIGN,
    ATTITUDE,
    COLON,
    LABLE,
    COMMENT,
    TYPE_LI,
    TYPE_UINT,
    ERR_TOKEN
};

struct data_token
{
    TokenClass CToken;
    std::any ptr;
        
    data_token() : CToken(), ptr() {}

    data_token(TokenClass CToken) : CToken(CToken), ptr() {}

    template<typename Type>
    data_token(TokenClass CToken, const Type & ptr) : CToken(CToken), ptr(ptr) {} 

    template<typename Type>
    data_token(TokenClass CToken, Type && move_ptr) : CToken(CToken), ptr(std::forward<Type>(move_ptr)) {}
    
};


#endif