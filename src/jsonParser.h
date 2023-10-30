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

char * splitString(char * splitting, int start,int end);


struct MULTI_TYPE_ARRAY_STRUCT {
    int stringCount;
    int objectCount;
    int subArrayCount;
    char ** stringList;
    json_object * objectList;
    struct MULTI_TYPE_ARRAY_STRUCT * subArrayList;
};

json_object * parseJson(char * stringToParse);

multitypearray * parseArray(char * input, int stringLength);
