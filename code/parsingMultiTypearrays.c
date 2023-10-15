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
    int subArrayCount;
    char ** stringList;
    object * objectList;
    struct MULTI_TYPE_ARRAY_STRUCT * subArrayList;
} multitypearray;

multitypearray * parseArray(char * input, int stringLength) {
    multitypearray * mltReturn;
    mltReturn = malloc(sizeof(struct MULTI_TYPE_ARRAY_STRUCT));
    if (mltReturn == NULL) {
        
    } else {
        printf("Memory allocation successfull. \n");
    }
    int stringCount, objectCount, subArrayCount;
    stringCount = objectCount = subArrayCount = 1;
    char ** stringList;
    stringList = malloc(stringCount*sizeof(char*));
    if (stringList == NULL) {
        printf("Not good");
    } else {
        printf("Good\n");
    }
    object * objectList;
    objectList = malloc(sizeof(struct OBJECT_STRUCT)*objectCount);
    multitypearray * subArrayList;
    subArrayList = malloc(sizeof(struct MULTI_TYPE_ARRAY_STRUCT) * subArrayCount);
    for (int i = 0; i < stringLength; i++) {
        if (input[i] == '[') {
            // Start parsing for array
            i++;
            D:
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
                    i++;
                    while (input[i] == ' ') {
                        i++;
                    }
                    if (input[i] == ',') {
                        i++;
                        goto D;
                    }
                } else if (input[i] == '{') {
                    object * newObject;
                    newObject = malloc(sizeof(struct OBJECT_STRUCT));
                    objectList[objectCount-1] = *newObject;
                    objectCount++;
                    objectList = realloc(objectList, sizeof(struct OBJECT_STRUCT)*objectCount);
                    printf("%d",i);
                    free(newObject);      
                } else if (input[i] == '[') {
                    int k = i;
                    while (input[k] != ']') {
                        k++;
                    }
                    char * splitString;
                    int splitStringLength;
                    // stuff
                    multitypearray * subArray = parseArray(splitString, splitStringLength);
                }
                i++;
            }
        }
    }
    mltReturn->stringCount = stringCount;
    mltReturn->objectCount = objectCount;
    mltReturn->subArrayCount = subArrayCount;
    mltReturn->stringList = stringList;
    mltReturn->objectList = objectList;
    free(objectList);
    free(stringList);
    return mltReturn;

}

int main(void) {
    char input[] = "[\"hello\", {\"ciao ciao\"}]";
    int length = strlen(input);
    multitypearray* ab = parseArray(input, length);
    printf("\n %d %d %d \n", ab->stringCount, ab->objectCount, ab->subArrayCount);
    return 0;
}