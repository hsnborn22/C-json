#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct OBJECT_STRUCT {
    char * name;
    int age;
} object;

typedef struct MULTI_TYPE_ARRAY_STRUCT {
    int stringCount;
    int objectCount;
    char ** stringList;
    object * objectList;
} multitypearray;

void parseArray(char * input, int stringLength) {
    multitypearray * mltReturn;
    mltReturn = malloc(sizeof(struct MULTI_TYPE_ARRAY_STRUCT));
    if (mltReturn == NULL) {
        
    } else {
        printf("Memory allocation successfull. \n");
    }
    int stringCount, objectCount;
    stringCount = objectCount = 1;
    char ** stringList;
    stringList = malloc(stringCount*sizeof(char*));
    if (stringList == NULL) {
        printf("Not good");
    } else {
        printf("Good\n");
    }
    for (int i = 0; i < stringLength; i++) {
        if (input[i] == '[') {
            // Start parsing for array
            i++;
            while (input[i] != ']') {
                if (input[i] == '"') {
                    // start parsing for string
                    char * str;
                    int parseLength = 1;
                    str = malloc(parseLength*sizeof(char));
                    i++;
                    while (input[i] != '"') {
                        str[parseLength-1] = input[i];
                        parseLength++;
                        str = realloc(str, sizeof(char) * parseLength);
                        i++;
                    }
                    stringList[stringCount - 1] = malloc(sizeof(char) * parseLength);
                    strcpy(stringList[stringCount-1], str);
                    stringCount++;
                    stringList = realloc(stringList, sizeof(char *) * stringCount);
                    printf("%s \n", stringList[stringCount - 2]);
                    free(str);
                }
                i++;
            }
        }
    }
    free(stringList);
    free(mltReturn);

}

int main(void) {
    char input[] = "[\"hello\", \"hi\"]";
    int length = strlen(input);
    parseArray(input, length);
    return 0;
}