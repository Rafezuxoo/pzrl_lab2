#include "lib2.h"

bool isFileExist(char *fileName) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Invalid file or directory\n");
        exit(1);
    }

    return true;
}

void replace(char *fileName, char *oldText, char *newText) {
    FILE *tmp = tmpfile(), *file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "cannot open file\n");
        exit(1);
    }

    if (tmp == NULL) {
        fprintf(stderr, "cannot create temp file\n");
        exit(1);
    }
    
    //copying file to end file
    int c;
    while ((c = fgetc(file)) != EOF) {
        fputc(c, tmp);
    }

    fseek(tmp, 0, SEEK_SET);
    fclose(file);

    file = fopen(fileName, "w");

    if (file == NULL) {
        fprintf(stderr, "cannot open file\n");
        exit(1);
    }

    regex_t regex;
    regmatch_t match[1];
    char *line = NULL; 
    size_t uselessVar; // exist cuz getline does not work without it

    if (regcomp(&regex, oldText, REG_EXTENDED)) {
        fprintf(stderr, "Error while compiling regex\n");
        exit(1);
    }
                      
    while (getline(&line, &uselessVar, tmp) != -1) {
        while (!regexec(&regex, line, ARRAY_SIZE(match), match, 0)) {
            for (char *i = line; i < line + match[0].rm_so; ++i) {
                fputc(*i, file);
            }
            for (size_t i = 0; i < strlen(newText); ++i) {
                fputc(newText[i], file);
            }

            line += match[0].rm_eo;

        }

        while (*line != '\0') {
            fputc(*line, file);
            line++;
        }
    }

    fclose(tmp);
    fclose(file);
}

void delete(char *fileName, char *textToDelete) {
    char pass[] = "";
    replace(fileName, textToDelete, pass);
}   

void postfix(char *fileName, char *text) {
    FILE *file = fopen(fileName, "r");
    FILE *tmp = tmpfile();

    if (file == NULL) {
        fprintf(stderr, "cannot open file\n");
        exit(1);
    }

    if (tmp == NULL) {
        fprintf(stderr, "cannot create temp file\n");
        exit(1);
    }
    
    //copying file to end file
    int c;
    while ((c = fgetc(file)) != EOF) {
        fputc(c, tmp);
    }

    fclose(file);

    char *line = NULL;
    size_t uselessVar; //exist cuz getline not working without it

    fseek(tmp, 0, SEEK_SET);
    file = fopen(fileName, "w");

    if (file == NULL) {
        fprintf(stderr, "cannot create temp file\n");
        exit(1);
    }

    while (getline(&line, &uselessVar, tmp) != -1) {
        for (size_t i = 0; i < strlen(line) - 1; ++i) {
            fputc(line[i], file);
        }
        for (size_t i = 0; i < strlen(text); ++i) {
            fputc(text[i], file);
        }
        fputc('\n', file);
    }

//    fwrite(text, sizeof(char), strlen(text), file);
    free(line);
    fclose(file);
    fclose(tmp);
}

void prefix(char *fileName, char *text) {
    FILE *file = fopen(fileName, "r");
    FILE *tmp = tmpfile();

    if (file == NULL) {
        fprintf(stderr, "cannot open file\n");
        exit(1);
    }

    if (tmp == NULL) {
        fprintf(stderr, "cannot create temp file\n");
        exit(1);
    }
    
    //copying file to end file
    int c;
    while ((c = fgetc(file)) != EOF) {
        fputc(c, tmp);
    }

    fclose(file);

    char *line = NULL;
    size_t uselessVar; //exist cuz getline not working without it

    fseek(tmp, 0, SEEK_SET);
    file = fopen(fileName, "w");

    if (file == NULL) {
        fprintf(stderr, "cannot create temp file\n");
        exit(1);
    }

    while (getline(&line, &uselessVar, tmp) != -1) {
        for (size_t i = 0; i < strlen(text); ++i) {
            fputc(text[i], file);
        }
        for (size_t i = 0; i < strlen(line) - 1; ++i) {
            fputc(line[i], file);
        }
        fputc('\n', file);
    }

//    fwrite(text, sizeof(char), strlen(text), file);
    free(line);
    fclose(file);
    fclose(tmp);
}


void getCmd(char *argv[]) {
    regex_t regularRegex, deleteRegex;
    regmatch_t match[1];

    char *start, *end; //starts and ends of strings to replace or delete


     if (regcomp(&regularRegex, "s/", REG_EXTENDED)) {
        fprintf(stderr, "Error while compiling regex\n");
        exit(1);
    }   

    if (regcomp(&deleteRegex, "/d", REG_EXTENDED)) {
        fprintf(stderr, "Error while compiling regex\n");
        exit(1);    
    }

    if (!regexec(&regularRegex, argv[2], ARRAY_SIZE(match), match, 0) 
            && argv[2][0] == 's' && argv[2][1] == '/') {
        start = argv[2] + strlen("s/");
        end =  start;

        while (*end != '/') {
            end++; 
        }

        char *str1 = strndup(start, sizeof(char) * (end - start)); // no including '/'

        start = end + 1;
        end = start;

        while (*end != '/') {
            end++;
        }

        if (start == end) {
            fprintf(stderr, "incorrect input, nothing between slashes\n");
            exit(1);
        }

        char *str2 = strndup(start, sizeof(char) * (end - start)); // no including '/'

        if (str1 == NULL || str2 == NULL) {
            fprintf(stderr, "cannot read args\n");
            exit(1);
        }

        if (strlen(str1) == 1 && str1[0] == '^') {
            prefix(argv[1], str2);
        } else if (strlen(str1) == 1 && str1[0] == '$') {
            postfix(argv[1], str2);
        } else {
            replace(argv[1], str1, str2);
        }

        free(str1);
        free(str2);
    } else if (!regexec(&deleteRegex, argv[2], ARRAY_SIZE(match), match, 0)
            && argv[2][0] == '/' ) {
        start = argv[2] + strlen("/");
        end = start;

        while (*end != '/') {
            end++;
        }

            
        if (start == end) {
            fprintf(stderr, "incorrect input, nothing between slashes\n");
            exit(1);
        }

        char *str = strndup(start, sizeof(char) * (end - start)); //not including '/'

        if (*(end + 1) == 'd') {
            delete(argv[1], str);
            free(str);
        } else {
            fprintf(stderr, "didn't found flag, did u mean /<text_to_delete>/d ?\n");
            free(str);
            exit(1);
        } 
    } else {
            fprintf(stderr, "did'nt found flag, nothing to do, not d at the end or s at the start, exit\n");
            exit(1);
    }
}
