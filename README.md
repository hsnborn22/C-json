# C-json
Trying to write a functioning C json parser from scratch in as few lines of code as possible.

# Documentation

## Including the library inside your project

To use the library in your C program,  put both the source code file jsonParser.c and the header file jsonParser.h inside your working directory; then include the header file at the start of your program like this:

```c
#include "jsonParser.h"
```
(here we're assuming you included it directly into the working directory, if not just change the path to the subdirectory you put the file in)
Also, remember to include the jsonParser.c in the list of files for the compilation, or if you're using a makefile, add it in there. 



Now you are ready to use the library inside your program.  

## Parsing JSON

The library is able to parse json with almost all key-value pairs you would need for an application:

1) key-string
2) key-number (int or floating point number)
3) key-multi type array (i.e javascript multi type array)
4) key- other json object

(note that multi type arrays can also contain other json objects inside them, and the json object in question can also have as many nested json objects you want)

To parse json you will use the parseJson function included in the jsonParser.c file. It will take a string as an input (the raw JSON you want to parse) and return a json_object pointer.
```c
json_object * parseJson(char * stringToParse)
```

### The json_object type:

The json_object type is defined at the beginning of the jsonParser.c file: it has the following attributes:
#### 1) keyCount:
the number of keys inside the jsonObject.


**type**: int
#### 2) keyList:
The list of key-value pairs inside your json object. 
**type**:: json_key * (pointer to json_key object)
The json_key object is also defined at the beginning of the file: we will cover it later.
#### 3) subObjectCount
The number of nested json sub objects inside our objects.


**type**:: int
#### 4) subObjects
The list of the json sub-objects contained in our object.


**type**:: json_object * (pointer to json_object)
#### 5) subArrayCount
it is the number of multi type arrays contained inside your json object.


**type**:: int
#### 6) subArrayList
The list of the multi type arrays contained in your json object.


**type**:: multitypearray * (pointer to multitypearray)
Like the other types employed in this library, also the multitypearray is defined at the beginning of the file.

The code for the json_object type is, in particular:

```c
typedef struct JSON_OBJECT_STRUCT {
	char * name;
	int keyCount;
	json_key * keyList;
	int subObjectCount;
	struct JSON_OBJECT_STRUCT * subObjects;
    int subArrayCount;
    multitypearray * subArrayList;
} json_object;
```

Let us now focus our attention to the other types we used

### json_key type
The json_key type has the following attributes:

#### 1) keyName:
The name of the key. 
**e.g**
```json
{
	"name": "Mark",
	"age": 19,
	"favCountry":"France"
}
```
For the second json_key object inside this json object (i.e the second key-value pair) the name of the key would be the string "age".


**type**: char * (char pointer)
#### 2) keyLength:
The length of the keyName string. 


**type**:: int
#### 3) value
The value corresponding to the key. In the same example presented above, if we consider the first key-value pair, then the value would be "Mark". For the second key-value pair, on the other hand, the value would be the string "19".


**type**: char *
#### 4) valueLength
The length of the value string.


**type**: int

The code for the json_key type is:

```c
typedef struct JSON_KEY_STRUCT {
	char * keyName;
	char * value;
	int keyLength;
	int valueLength;
} json_key;
```

### multitypearray type
The multitypearray type has the following attributes

#### 1) stringCount
The number of strings contained in our array.


**type**: int
#### 1) objectCount
The number of objects contained in our array.


**type**: int
#### 3) subArrayCount
The number of subArrays contained in our multi type array


**type**: int
#### 4) stringList
The list of strings contained inside our array.


**type**: char ** (a pointer to a pointer to a char)
#### 5) objectList
The list of objects contained inside our array.


**type**: json_object * (a pointer to a json_object)
#### 6) subArrayList
The list of arrays contained in our array.


**type**: multitypearray * (a pointer to a pointer to a multi type array)

### Parsing json

Now that you are familiar with the objects returned by the parsing methods, you are now ready to start parsing your own json. Let us give some examples.

#### example 1:

We pass the following json in the format of a string to our function

```json
{
	"name": "Frank",
	"country": "Canada",
	"friends": [
		{
		"name": "Jack",
		"age": 21,
		"country":"USA"
		},
		{
		"name": "Ivan",
		"age": 22,
		"country": "Russia"
		}
	]
}
```

We first save it in a string variable called input.
```c
char input[] ="{\"name\": \"Frank\",\"country\": \"Canada\",\"friends\":[{\"name\": \"Jack\",\"age\": 21,\"country\":\"USA\"},{\"name\": \"Ivan\",\"age\": 22,\"country\": \"Russia\"}]}";
```

We then pass it to our parseJson function: we call the json object we obtained res.

```c
json_object * res = parseJson(input);
```

Let us now print all of the values contained inside our object and the nested objects inside in our C program using the json_object we just obtained with the parsing.

```c
printf("%s: %s\n", res->keyList[0].keyName, res->keyList[0].value); // output: name: Frank
printf("%s: %s\n", res->keyList[1].keyName, res->keyList[1].value); // output: country: Canada
```
Now, we should be careful because the value of the third argument is a list (of objects). To get the values of the objects in the list, remembering what we said above, we will use:

```c
printf("%s: %s\n", res->subArrayList[0].objectList[0].keyList[0].keyName, res->subArrayList[0].objectList[0].keyList[0].value); // output: name: Jack
```

As an exercise, you can try doing the same for the other entries of the first object, and all of the entries of the second.
After using the res object, dont forget to free it!  (unless you like memory leaks)
```c
free(res);
```

With all of this said, you should now be ready to use the library without problems. I hope this brief documentation was sufficient; in the case it was not, you can still check out the source code, considering its very small size.

### Things I want to improve:

1) readability of the code
2) handle javascript boolean values better (true, false): at the current stage theyre parsed just like strings, and it is left to whoever is using the library to convert them into 0s or 1s.
