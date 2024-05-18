#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h> // 添加这一行来解决 strcmp 的声明问题

int countCharacters(const char *filename);
int countWords(const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c|-w] input_file_name\n", argv[0]);
        return 1;
    }

    const char *param = argv[1];
    const char *filename = argv[2];

    int result;
    if (strcmp(param, "-c") == 0) { // 现在 strcmp 已经被正确声明
        result = countCharacters(filename);
        printf("Characters: %d\n", result);
    } else if (strcmp(param, "-w") == 0) {
        result = countWords(filename);
        printf("Words: %d\n", result);
    } else {
        printf("Invalid parameter. Use '-c' for characters or '-w' for words.\n");
        return 1;
    }

    return 0;
}

int countCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    bool inWord = false;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            inWord = false;
        } else if (!inWord) {
            inWord = true;
            count++;
        }
    }
    fclose(file);
    return count;
}
