#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
} json_object;

char * splitString(char * splitting, int start,int end) {
	char * splittedString;
	splittedString = malloc(end - start + 1);
	for (int i = 0; i <= end-start; i++) {
		splittedString[i] = splitting[start+i];
	}
	return splittedString;
}

json_object * parseJson(char * stringToParse) {
	int stringToParseLength = strlen(stringToParse);
	int keyCount = 1;
	int subObjCount = 1;
	json_key * keyList;
	keyList = malloc(sizeof(struct JSON_KEY_STRUCT) * keyCount);
	json_object * subObjects;
	subObjects = malloc(sizeof(struct JSON_OBJECT_STRUCT) * subObjCount);
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
							subObjects = realloc(subObjects, sizeof(struct JSON_OBJECT_STRUCT));
							subObjCount++;
							goto H;
						} else {
							while (stringToParse[i] != ',') {
								if (stringToParse[i] != ' ') {
									value[valueLength - 1] = stringToParse[i];
									valueLength++;
									value = realloc(value,valueLength);
								}
								i++;
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
						return parsedJson;
					}
					
				} else if (stringToParse[i] != ' ') {
					continue;
				}
			}
		}
	}
}

int main(void) {
	char * buffer = "{\"name\":\"test\", \"favcolors\": {\"color1\":\"red\"}, \"surname\":\"Muller\"}";
	json_object * parsedJson = parseJson(buffer);
	printf("%d %d", parsedJson->keyCount, parsedJson->subObjectCount);
	return 0;
}
