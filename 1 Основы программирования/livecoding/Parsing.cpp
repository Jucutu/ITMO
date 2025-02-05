#include "Parsing.h"

void toLowerCase(char* str) {
    for(int i = 0; str[i]; i++){
        if('A' <= str[i] && str[i] <= 'Z')
            str[i] = str[i] + ('a' - 'A');
    }
}

int findWord(WordCount words[], int wordCount, const char* word) {
    for(int i = 0; i < wordCount; i++) {
        if(strcmp(words[i].word, word) == 0)
            return i;
    }
    return -1;
}

void quickSort(WordCount words[], int left, int right) {
    if (left >= right) {
        return;
    }
    int i = left;
    int j = right;
    WordCount pivot = words[left];
    while(i < j) {
        while(i < j && words[j].count <= pivot.count) {
            j--;
        }
        if(i < j) {
            words[i++] = words[j];
        }
        while(i < j && words[i].count >= pivot.count) {
            i++;
        }
        if(i < j) {
            words[j--] = words[i];
        }
    }
    words[i] = pivot;
    quickSort(words, left, i - 1);
    quickSort(words, i + 1, right);
}