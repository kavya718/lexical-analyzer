/*
NAME : KAVYA P
DESCRIPTION:This project implements a lexical analyzer that scans a source program and breaks it into meaningful
tokens such as keywords, identifiers, operators, literals, and symbols. It eliminates comments and unnecessary
whitespace and detects lexical errors. The lexical analyzer acts as the first phase of a compiler and provides tokenized input to the syntax analyzer for further processing.
DATE: 22/12/2025
SAMPLE I/O:
input:-
#include <stdio.h>          

int main()
{
    int num = 0xABC;        

    
    for (int i = 0; i < num; i++)
    {
        printf("Hello\n"); 

    }
    return 0;               
}
output:-
try.c is present

KEYWORD      : int
IDENTIFIER   : main
SYMBOL       : (
SYMBOL       : )
SPEC CHAR    : {
KEYWORD      : int
IDENTIFIER   : num
SYMBOL       : =
NUMERIC CONST: 0
IDENTIFIER   : xABC
SPEC CHAR    : ;
KEYWORD      : for
SYMBOL       : (
KEYWORD      : int
IDENTIFIER   : i
SYMBOL       : =
NUMERIC CONST: 0
SPEC CHAR    : ;
IDENTIFIER   : i
SYMBOL       : <
IDENTIFIER   : num
SPEC CHAR    : ;
IDENTIFIER   : i
SYMBOL       : ++
SYMBOL       : )
SPEC CHAR    : {
IDENTIFIER   : printf
SYMBOL       : (
SYMBOL       : (
KEYWORD      : int
IDENTIFIER   : i
SYMBOL       : =
NUMERIC CONST: 0
SPEC CHAR    : ;
IDENTIFIER   : i
SYMBOL       : <
IDENTIFIER   : num
SPEC CHAR    : ;
IDENTIFIER   : i
SYMBOL       : ++
SYMBOL       : )
SPEC CHAR    : {
IDENTIFIER   : printf
SYMBOL       : (
NUMERIC CONST: 0
SPEC CHAR    : ;
IDENTIFIER   : i
SYMBOL       : <
IDENTIFIER   : num
SPEC CHAR    : ;
IDENTIFIER   : i
SYMBOL       : ++
SYMBOL       : )
SPEC CHAR    : {
IDENTIFIER   : printf
SYMBOL       : (
IDENTIFIER   : num
SPEC CHAR    : ;
IDENTIFIER   : i
SYMBOL       : ++
SYMBOL       : )
SPEC CHAR    : {
IDENTIFIER   : printf
SYMBOL       : (
SYMBOL       : ++
SYMBOL       : )
SPEC CHAR    : {
IDENTIFIER   : printf
SYMBOL       : (
SPEC CHAR    : {
IDENTIFIER   : printf
SYMBOL       : (
SYMBOL       : (
SYMBOL       : )
SPEC CHAR    : ;
KEYWORD      : return
NUMERIC CONST: 0
SPEC CHAR    : ;
SPEC CHAR    : }

ERROR   : missing closing }

*/



#include <stdio.h>      // Standard input-output header
#include "lexer.h"      // Header file for lexical analyzer functions

int main(int argc, char *argv[])
{
    // Check whether source file name is passed as argument
    if (argc != 2)
    {
        // Print correct usage format
        printf("Usage: ./a.out <source_file.c>\n");
        return 1;       // Exit if argument count is wrong
    }

    // Call lexical analyzer function with source file name
    analyzeFile(argv[1]);

    return 0;           // Successful program termination
}

