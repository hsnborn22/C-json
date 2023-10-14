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
	int keyCount;
	json_key * keyList;
} json_object;

void parseJson(char * stringToParse, char * parsedString) {
	int stringToParseLength = strlen(stringToParse);
	for (int i = 0; i < stringToParseLength;i++) {
		// Start parsing an object
		if (stringToParse[i] == '{')  {
			while (stringToParse[i] != '}') {
				i++;
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
					for (int j = 0; j < keyLength; j++) {
						printf("%c", key[j]);
					}

					printf(": %d\n", keyLength);
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
								key = realloc(value,valueLength);
								i++;
							}
							// String finishes
							i++;
						} else {
							while (stringToParse[i] != ',') {
								if (stringToParse[i] != ' ') {
									value[valueLength - 1] = stringToParse[i];
									valueLength++;
									key = realloc(value,valueLength);
								}
								i++;
							}
						}
					}
					printf("%d :", valueLength);
					for (int k = 0; k < valueLength; k++) {
						printf("%c", value[k]);
					}
					keyValuePair->keyName = key;
					keyValuePair->value = value; 
					keyValuePair->keyLength = keyLength - 1;
					keyValuePair->valueLength = valueLength -1;
					
				} else if (stringToParse[i] != ' ') {
					printf("%c \n", stringToParse[i]);
					continue;
				}
					// If not inside a string (i.e value or key) type token
				
			}
		}
	}
}

int main(void) {
	char * buffer = "{\"name\":\"test\"}";
	char parsedJson[1024];
	parseJson(buffer,parsedJson);
	
	return 0;
}
