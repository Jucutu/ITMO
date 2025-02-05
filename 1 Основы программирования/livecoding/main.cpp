#include <iostream>
#include "Parsing.cpp"

int main(int argc, char* argv[]) {
    if(argc != 5) {
        std::cerr << "Использование " << argv[0] << " --input PATH --top N\n";
        return 1;
    }

    char inputPath[256];
    int topN = 0;

    for(int i = 1; i < argc; i+=2){
        if(strcmp(argv[i], "--input") == 0) {
            strcpy(inputPath, argv[i+1]);
        }
        else if(strcmp(argv[i], "--top") == 0) {
            topN = atoi(argv[i+1]);
        }
    }

    if(topN <= 0) {
        std::cerr << "N должно быть положительным числом.\n";
        return 1;
    }

    std::ifstream file(inputPath);
    if(!file.is_open()) {
        std::cerr << "Не удалось открыть файл\n";
        return 1;
    }

    WordCount words[MAX_WORDS];
    int wordCount = 0;
    char line[1025];

    while(file.getline(line, sizeof(line))){
        int len = strlen(line);
        int start = 0;
        for(int i = 0; i <= len; i++) {
            if(line[i] == ' ' || line[i] == '\0') {
                if(i > start) {
                    char word[MAX_WORD_LENGTH];
                    int w = 0;
                    for(int j = start; j < i && w < MAX_WORD_LENGTH - 1; j++) {
                        word[w++] = line[j];
                    }
                    word[w] = '\0';
                    toLowerCase(word);
                    int index = findWord(words, wordCount, word);
                    if(index != -1) {
                        words[index].count += 1;
                    }
                    else {
                        if(wordCount < MAX_WORDS) {
                            strcpy(words[wordCount].word, word);
                            words[wordCount].count = 1;
                            wordCount++;
                        }
                        else {
                            std::cerr << "Достигнуто максимальное количество уникальных слов.\n";
                            break;
                        }
                    }
                }
                start = i + 1;
            }
        }
    }
    file.close();

    quickSort(words, 0, wordCount - 1);
    for(int i = 0; i < topN && i < wordCount; i++){
        std::cout << words[i].word << "\n";
    }
    return 0;
}
