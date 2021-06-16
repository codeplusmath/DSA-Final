#ifndef MORSE_H_INCLUDED
#define MORSE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
#include <conio.h>
#endif


#define clrscr() printf("\e[1;1H\e[2J")
#define DOT '.'
#define DASH '-'
#define SEP '_'
#define GRAPHIC 18
#define color(color) printf("\033[1;%dm", color)
#define resetColor printf("\033[0m")

/** Defination of Colors **/
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36

/* Structure of node */
typedef struct Node{
    struct Node * dot;
    struct Node * dash;
    char character;
}Node, *Tree;

/* Creation of a new node */
Tree new_node();

/* Adding a character to the tree */
Tree add_char(Tree * tree, char * morse, char c);

/* Construction of the tree */
Tree initForMorse();

/* Search for the character in the tree */
char seekChar(Tree tree, char * morse);

/* Morse code decoding */
char * morseDecoder(Tree tree, char * morse);

/* Morse code Encoding */
char * morseEncrypter(Tree tree, char * text);

/* Destroy tree */
void destroyTree(Tree tree);

/* Split a character string and return as an array */
char ** str_split(char * s, const char * ct);

/* Display Morse Table */
void morseTable(Tree tree);


/** Function which runs this software **/
int mainProg(Tree tree, int argc, char ** argv);

//Testing


#endif // MORSE_H_INCLUDED
