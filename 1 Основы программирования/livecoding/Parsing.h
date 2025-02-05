#pragma once 

#include <iostream>
#include <cstring>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <string>


#define MAX_WORDS 10000
#define MAX_WORD_LENGTH 100

struct WordCount{
    char word[MAX_WORD_LENGTH];
    int count;
};

void toLowerCase(char* str);

int findWord(WordCount words[], int wordCount, const char* word);

void quickSort(WordCount words[], int left, int right);


