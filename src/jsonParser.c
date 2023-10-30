#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MULTI_TYPE_ARRAY_STRUCT multitypearray;

typedef struct JSON_KEY_STRUCT {
	char * keyName;
	char * value;
	int keyLength;
	int valueLength;
} json_key;

typedef struct JSON_OBJECT_STRUCT {
	char * name;
	int keyCount;
	json_key * keyList;
	int subObjectCount;
	struct JSON_OBJECT_STRUCT * subObjects;
    int subArrayCount;
    multitypearray * subArrayList;
} json_object;

typedef struct MIXED_ARRAY_STRUCT {
	int objectCount;
	int stringCount;
	char ** stringList;
	json_object * objectList;
} mixedArray;

char * splitString(char * splitting, int start,int end) {
	char * splittedString;
	splittedString = malloc(end - start + 1);
	for (int i = 0; i <= end-start; i++) {
		splittedString[i] = splitting[start+i];
	}
	return splittedString;
}

struct MULTI_TYPE_ARRAY_STRUCT {
    int stringCount;
    int objectCount;
    int subArrayCount;
    char ** stringList;
    json_object * objectList;
    struct MULTI_TYPE_ARRAY_STRUCT * subArrayList;
};

json_object * parseJson(char * stringToParse);

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
    json_object * objectList;
    objectList = malloc(sizeof(struct JSON_OBJECT_STRUCT)*objectCount);
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
                    stringList[stringCount - 1] = str;
                    // strcpy(stringList[stringCount-1], str);
                    stringCount++;
                    stringList = realloc(stringList, sizeof(char *) * stringCount);
                    i++;
                    while (input[i] == ' ') {
                        i++;
                    }
                    if (input[i] == ',') {
                        i++;
                        goto D;
                    }
                    goto D;
                } else if (input[i] == '{') {
                    int k = i;
                    while (input[k] != '}') {
                        k++;
                    }
                    char * splittedString = splitString(input, i , k);
                    json_object * newObject = parseJson(splittedString);
                    objectList[objectCount-1] = *newObject;
                    objectCount++;
                    objectList = realloc(objectList, sizeof(struct JSON_OBJECT_STRUCT)*objectCount);
                } else if (input[i] == '[') {
                    int k = i;
                    while (input[k] != ']') {
                        k++;
                    }
                    char * splittedString = splitString(input, i, k);
                    int splitStringLength = k - i + 1;
                    // stuff
                    multitypearray * subArray = parseArray(splittedString, splitStringLength);
                    subArrayList[subArrayCount-1] = *subArray;
                    subArrayCount++;
                    subArrayList = realloc(subArrayList, subArrayCount* sizeof(struct MULTI_TYPE_ARRAY_STRUCT));
                }
                i++;
            }
        }
    }
    mltReturn->stringCount = stringCount-1;
    mltReturn->objectCount = objectCount-1;
    mltReturn->subArrayCount = subArrayCount-1;
    mltReturn->stringList = stringList;
    mltReturn->objectList = objectList;
    mltReturn->subArrayList = subArrayList;
    return mltReturn;
}

json_object * parseJson(char * stringToParse) {
	int flagEnd = 0;
	int stringToParseLength = strlen(stringToParse);
	int keyCount = 1;
	int subObjCount = 1;
    int subArrayCount = 1;
	json_key * keyList;
	keyList = malloc(sizeof(struct JSON_KEY_STRUCT) * keyCount);
	json_object * subObjects;
	subObjects = malloc(sizeof(struct JSON_OBJECT_STRUCT) * subObjCount);
    multitypearray * subArrayList;
    subArrayList = malloc(sizeof(struct MULTI_TYPE_ARRAY_STRUCT) * subArrayCount);
	for (int i = 0; i < stringToParseLength;i++) {
		// Start parsing an object
		if (stringToParse[i] == '{')  {
			while (stringToParse[i] != '}') {
				i++;
				D:
				json_key * keyValuePair;
				keyValuePair = malloc(sizeof(struct JSON_KEY_STRUCT));
				if (stringToParse[i] == '"') {
					i++;
					int keyLength, valueLength;
					keyLength = valueLength = 1;
					char * key;
					char * value;
					key = malloc(keyLength);
					value = malloc(valueLength);
					while (stringToParse[i] != '"') {
						key[keyLength - 1] = stringToParse[i];
						keyLength++;
						key = realloc(key,keyLength);
						i++;
					}
					i++;

					S: 
					if (stringToParse[i] == ' ') {
						// skip it
						i++;
						goto S;
					} else if (stringToParse[i] == ':') {
						i++;
						while (stringToParse[i] == ' ') {
							//skip
							i++;
						}
						// start parsing for the value
						if (stringToParse[i] == '"') {
							i++;
							while (stringToParse[i] != '"') {
								value[valueLength - 1] = stringToParse[i];
								valueLength++;
								value = realloc(value,valueLength);
								i++;
							}
							// String finishes
							i++;
						} else if (stringToParse[i] == '{') {
							// parse the object as before, but this time store the object in the subObjects array of structs inside our parsedJson struct
							int k = i;
							while (stringToParse[k] != '}') {
								k++;
							}
							char * subString = splitString(stringToParse, i, k);
							json_object * subObject = parseJson(subString);
							subObjects[subObjCount - 1].keyCount = subObject->keyCount;
							subObjects[subObjCount - 1].keyList = subObject->keyList;
							subObjects[subObjCount-1].name = key;
							subObjCount++;
							subObjects = realloc(subObjects, subObjCount*sizeof(struct JSON_OBJECT_STRUCT));
                            i = k;
                            i++;
							goto H;
						} else if (stringToParse[i] == '[') {
                            int k= 1;
                            while (stringToParse[k] != ']') {
                                k++;
                            }
                            char * subString = splitString(stringToParse,i,k);
                            multitypearray * mltArr= parseArray(subString, k - i +1);
                            subArrayList[subArrayCount-1] = *mltArr;
                            subArrayCount++;
                            subArrayList = realloc(subArrayList, sizeof(struct MULTI_TYPE_ARRAY_STRUCT)*subArrayCount);
                            i=k;
                            i++;
                            goto H;
						} else {
							while (stringToParse[i] != ',' && stringToParse[i] != '}' ) {
								if (stringToParse[i] != ' ') {
									value[valueLength - 1] = stringToParse[i];
									valueLength++;
									value = realloc(value,valueLength);
								}
								i++;
							}
							if (stringToParse[i]=='}') {
								flagEnd = 1;
							}
						}
					}
					keyValuePair->keyName = key;
					keyValuePair->value = value; 
					keyValuePair->keyLength = keyLength - 1;
					keyValuePair->valueLength = valueLength -1;
					keyList[keyCount - 1].keyName = keyValuePair->keyName;
					keyList[keyCount - 1].value = keyValuePair->value;
					keyList[keyCount - 1].keyLength = keyValuePair->keyLength;
					keyList[keyCount - 1].valueLength = keyValuePair->valueLength;
					keyCount++;
					keyList = realloc(keyList, sizeof(struct JSON_KEY_STRUCT) * keyCount);
					
                    H:
					while (stringToParse[i] == ' ') {
						// skip character
						i++;
					}
					if (stringToParse[i] == ',') {
						// parse next key value pair:
						i++;
						goto D;
					} else if (stringToParse[i] == '}') {
						// we will return the json parsed object.
						json_object * parsedJson;
						parsedJson = malloc(sizeof(struct JSON_OBJECT_STRUCT));
						parsedJson->keyCount = keyCount - 1;
						parsedJson->keyList = keyList;
						parsedJson->subObjects = subObjects;
						parsedJson->subObjectCount = subObjCount - 1;
                        parsedJson->subArrayCount = subArrayCount;
                        parsedJson->subArrayList = subArrayList;
						return parsedJson;
					}			
				} else if (stringToParse[i] != ' ') {
					continue;
				}
			}
		}
	}
}
