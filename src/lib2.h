#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <regex.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

bool isFileExist(char *fileName);
void replace(char *fileName, char *oldText, char *newText);
void delete(char *fileName, char *textToDelete);
void prefix(char *fileName, char *text);
void postfix(char *fileName, char *text);
void getCmd(char *argv[]);
