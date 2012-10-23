#include "json.h"
#include <stdio.h>
#include <stdlib.h>

const char *emptyJSONTest= "{}";
const char *simpleJSONTest= "{\"taco\":\"cheese\"}";
const char *simpleJSONTest2= "{\"taco\":7}";
const char *simpleJSONTest3= "{\"taco\":\"cheese\",\"woozle\":7}";
const char *simpleJSONTest4= "{\"taco\":\"cheese\",\"woozle\":{\"taco\":6}}";
const char *simpleJSONTest5= "{\"taco\":[1,2,3,4]}";

void doTest(const char *s) {
    fprintf(stdout, "%s\n", s);
    struct JSON_Value *pValue= JSON_Decode(s);
    const char *s2= JSON_Encode(pValue, 512, 0);
    fprintf(stdout, "%s\n", s2);
    free((void*)s2);
    JSON_Value_Free(pValue);
}

void doFileTest(const char *fileName) {
    FILE* fptr= fopen(fileName, "r");
    fseek(fptr, 0, SEEK_END);
    long count= ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *buffer= (char*)malloc(count * sizeof(char));
    fread(buffer, 1, count, fptr);
    fclose(fptr);
    struct JSON_Value *pValue= JSON_Decode(buffer);
    if (pValue->type == JSON_VALUE_TYPE_ERROR) {
        struct JSON_Error *pError = (struct JSON_Error*)pValue;
        fprintf(stderr, "Error on line %d: %s\n", pError->line_number, pError->message);
    }
    free(buffer);

    unsigned long len;
    const char *outBuffer= JSON_Encode(pValue, 1024*1024, &len);
    JSON_Value_Free(pValue);

    fptr= fopen("out.json", "wt");
    fwrite(outBuffer, len, 1, fptr);
    fclose(fptr);
    free((void*)outBuffer);
}

int main (int argc, char *argv[]) {
    doTest(emptyJSONTest);
    doTest(simpleJSONTest);
    doTest(simpleJSONTest2);
    doTest(simpleJSONTest3);
    doTest(simpleJSONTest4);
    doTest(simpleJSONTest5);
    doFileTest("test/test.json");

    return 0;
}
