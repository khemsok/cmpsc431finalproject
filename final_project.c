/*
 * Change your function "main" to "xmain"
 * Leave all of your project code intact.
 * Write a main to match the expected output:
   I attest that the code submitted here is the
   same code that I will submit in Canvas
   and demonstrate to Dr. Shaffer
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAXFIELDS 100 // for now
#define MAXINPUTLENGTH 5000
#define MAXLENOFFIELDNAMES 50
#define MAXLENOFFIELDTYPES 50
struct _field {
        char fieldName[MAXLENOFFIELDNAMES];
        char fieldType[MAXLENOFFIELDTYPES];
        int fieldLength;
};
struct _table {
        char* tableFileName;
        char* schemaName;
        int reclen;
        int fieldcount;
        struct _field fields[MAXFIELDS];
};
typedef enum {
        false,
        true
} bool;



void addBin(char* binFileName, char* temp) {
        strcpy(binFileName, temp);
        strcat(binFileName, ".bin");
}

void addSchema(char* schemaFileName, char* temp) {
        strcpy(schemaFileName, temp);
        strcat(schemaFileName, ".schema");
}

void trimwhitespace(char* buffer)
{
        if (*buffer == 0)
                return;
        while (isspace((unsigned char)*buffer))
                buffer++;
        char* end;
        end = buffer + strlen(buffer) - 1;
        while (end > buffer && isspace((unsigned char)*end))
                end--;
        *(end + 1) = 0;
}
bool loadDatabase(struct _table* table, char* buffer)
{
        FILE* fp;
        fp = fopen(table->tableFileName, "ab");
        char* temp;
        char* temp2 = calloc(1, MAXINPUTLENGTH);
        temp = strtok(buffer, " ");
        temp = strtok(NULL, " ");
        temp = strtok(NULL, " ");
        temp = strtok(NULL, ",");
        int x = 0;
        while (x < table->fieldcount) {
                if (strlen(temp) > table->fields[x].fieldLength) {
                        printf("*** WARNING: Data in field %s is being truncated ***\n",
                               table->fields[x].fieldName);
                }
                strncpy(temp2, temp, table->fields[x].fieldLength);
                fwrite(temp2, table->fields[x].fieldLength, 1, fp);
                if (x < table->fieldcount - 1) {
                        temp = strtok(NULL, ",\n");
                }
                x++;
        }
        fclose(fp);

        return 1;
}
// READ THE DATA FROM STDIN AS THE DESIGN OF THE DATABASE TABLE
// LOAD "table" WITH THE APPROPRIATE INFO
bool loadSchema(struct _table* table)
{
        struct _field* fieldss = (struct _field*)malloc(sizeof(struct _field));
        char buffer[MAXINPUTLENGTH];
        char* temp;
        int x = 0;
        //printf("TESTING SCHEMA NAME: %s\n", table->schemaName);
        FILE* fp = fopen(table->schemaName, "rb");
// fprintf(stderr, "TESTING NAME: %s\n", table->schemaName);
        /*
           if(strcmp(table->schemaName, "temp.schema") == 0){

           fprintf(stderr, "TESTING BUFFER: %s\n", fgets(buffer, MAXINPUTLENGTH-1, fp));
                }*/
        while (fgets(buffer, MAXINPUTLENGTH - 1, fp)) {
                temp = strtok(buffer, " ");

                if (strcmp(temp, "ADD") == 0) {

                        int num;
                        temp = strtok(NULL, " ");
                        /*
                           if(strcmp(table->schemaName, "temp.schema") == 0) {
                             fprintf(stderr, "TESTING LENGTH: %d\n", table->reclen);
                           }*/
                        strcpy(table->fields[x].fieldName, temp);
                        temp = strtok(NULL, " ");
                        strcpy(table->fields[x].fieldType, temp);
                        temp = strtok(NULL, " ");
                        num = atoi(temp);
                        table->fields[x].fieldLength = num;
                        table->reclen += num;
                        x++;
                        /*
                           if(strcmp(table->schemaName, "temp.schema")==0) {
                             fprintf(stderr, "TEST FIELDNAME: %d\n", table->reclen);
                           }*/
                }
                if (strcmp(temp, "END\n") == 0) {
                        break;
                }
        }

        table->fieldcount = x;
        //if(strcmp(table->schemaName, "temp.schema") == 0)
        // fprintf(stderr, "yo: %d\n", table->reclen);

        fclose(fp);

        return 1;
}
// GET THE RECORD FROM THE FILE BY FSEEKING TO THE RIGHT SPOT AND READING IT
bool getRecord(int recnum, char* record, struct _table* table)
{
        FILE* fp;
        fp = fopen(table->tableFileName, "rb");
        fseek(fp, recnum * table->reclen, 0);
        fread(record, table->reclen, 1, fp);
        fclose(fp);
        return 1;
}
// DISPLAY THE CURRENT RECORD USING THE ASSOCIATED FIELD NAMES
void showRecord(struct _field* fields, char* record, int fieldcount, char* fieldName)
{
        int x = 0;
        int offset = 0;

        while (x < fieldcount) {
                if (strcmp(fields[x].fieldName, fieldName) == 0) {
                        printf("%s", record + offset);
                }
                offset += fields[x].fieldLength;
                x++;
        }
}

int showRecord2(struct _table *table, char* record, char fieldName[100][MAXINPUTLENGTH], int countA, char* fieldX, char* fieldNameX){
        int x = 0;
        int offset = 0;
        // < search return 1, == return 0, else return 2
        //fprintf(stderr, "TESTING: %d\n", table->fieldcount);

        if(strcmp(record, fieldNameX) < 0) {
                printf("TRACE: ");
                while(x < countA) {
                        printf("%s", record+offset);
                        if(x < countA - 1) {
                                printf(",");
                        }
                        offset += table->fields[x].fieldLength;
                        x++;
                }
                printf("\n");
                return 1;
        }
        else if(strcmp(record, fieldNameX) == 0) {
                printf("TRACE: ");
                while(x < countA) {
                        printf("%s", record+offset);
                        if(x < countA - 1) {
                                printf(",");
                        }
                        offset += table->fields[x].fieldLength;
                        x++;
                }
                printf("\n");
                x = 0, offset = 0;
                while(x < countA) {
                        printf("%s", record+offset);
                        if(x < countA - 1) {
                                printf(",");
                        }
                        offset += table->fields[x].fieldLength;
                        x++;
                }
                printf("\n");
                return 0;
        }
        else{
                printf("TRACE: ");
                while(x < countA) {
                        printf("%s", record+offset);
                        if(x < countA - 1) {
                                printf(",");
                        }
                        offset += table->fields[x].fieldLength;
                        x++;
                }
                printf("\n");
                return 2;
        }

}

void showRecord3(struct _field* fields, char* record, int fieldcount, char* fieldName, char* fieldX,
                 char* fieldNameX, char* fieldXX, char* fieldNameXX, int countA, int a)
{
        int x = 0;
        int offset = 0;
        int offset2 = 0;
        int y = 0;
        int z = 0;
        int offset3 = 0;
        int check1 = 0;
        int check2 = 0;
        while (x < fieldcount) {
                if (strcmp(fields[x].fieldName, fieldX) == 0) {
                        check1 = x;
                        break;
                }
                offset += fields[x].fieldLength;
                x++;
        }
        // fprintf(stderr, "TESTING FIELDNAME: %s\n", record+offset);
        x = 0;
        while (x < fieldcount) {
                if (strcmp(fields[x].fieldName, fieldXX) == 0) {
                        check2 = x;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }
        // fprintf(stderr, "TESTING FIELDNAME: %s\n", record+offset);
        x = 0;
        if ((strcmp(fieldNameX, record + offset) == 0) && (strcmp(fieldNameXX, record + offset2) == 0)) {
                while (x < fieldcount) {
                        if (strcmp(fields[x].fieldName, fieldName) == 0) {
                                printf("%s", record + offset3);
                                if (a < countA - 1)
                                        printf(",");
                        }
                        offset3 += fields[x].fieldLength;
                        x++;
                }
                if (a == countA - 1) {
                        printf("\n");
                }
        }
}

void showRecord5(struct _field* fields, char *record, int fieldcount, char fieldName[100][MAXINPUTLENGTH], int countA, char fieldCompare[20][MAXINPUTLENGTH], int countComp){

        int x = 0;
        int offset1 = 0;
        int check1 = 0;
        int offset2 = 0;
        int check2 = 0;
        //(fields[x].fieldName,
//       int y = 0;
//       int checkArr[countComp];
//       int offseta = 0;
//       int offsetb = 0;
//       while(y < countComp){
//         int p = 0;
//         while(p < fieldcount){
//           int a = y;
//           int b = y+1;
//           if(strcmp(fieldCompare[a], fields[p].fieldName) == 0){
//             checkArr[a] = offseta;
//           }
//           if(strcmp(fieldCompare[b], fields[p].fieldName) == 0){
//             checkArr[b] = offsetb;
//           }
//           offseta += fields[p].fieldLength;
//           offsetb += fields[p].fieldLength;
//           p++;
//         }
//         y = y+2;
// }
// y = 0;
// while(y < countComp){
//   if(strcmp(record+checkArr[y], record+checkArr[y+1]) != 0){
//     break;
//   }
//   y = y+2;
// }
// if(y == countComp){
//   x = 0;
//   int offsetcheck = 0;
//   while(x < countA){
//     int z = 0;
//     offsetcheck = 0;
//     while(z < fieldcount){
//       if(strcmp(fieldName[x], fields[z].fieldName) == 0){
//         printf("%s,", record+offsetcheck);
//       }
//       offsetcheck += fields[z].fieldLength;
//
//
//       z++;
//     }
//     x++;
//   }
//   printf("\n");
// }
        while(x < fieldcount) {
                if(strcmp(fieldCompare[0], fields[x].fieldName) == 0) {
                        check1 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[1], fields[x].fieldName) == 0) {
                        check2 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        offset1 = 0;
        int check3 = 0;
        offset2 = 0;
        int check4 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[2], fields[x].fieldName) == 0) {
                        check3 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[3], fields[x].fieldName) == 0) {
                        check4 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }

        x = 0;
        offset1 = 0;
        int check5 = 0;
        offset2 = 0;
        int check6 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[4], fields[x].fieldName) == 0) {
                        check5 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[5], fields[x].fieldName) == 0) {
                        check6 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }

        x = 0;
        offset1 = 0;
        int check7 = 0;
        offset2 = 0;
        int check8 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[6], fields[x].fieldName) == 0) {
                        check7 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[7], fields[x].fieldName) == 0) {
                        check8 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }

        x = 0;
        offset1 = 0;
        int check9 = 0;
        offset2 = 0;
        int check10 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[8], fields[x].fieldName) == 0) {
                        check9 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[9], fields[x].fieldName) == 0) {
                        check10 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        int offsetcheck = 0;

        if( (strcmp(record+check1, record+check2) == 0) && (strcmp(record+check3, record+check4) == 0) && (strcmp(record+check5, record+check6) == 0) && (strcmp(record+check7, record+check8) == 0) && (strcmp(record+check9, record+check10) == 0)) {

                while(x < countA) {
                        int y = 0;
                        offsetcheck = 0;
                        while(y < fieldcount) {
                                if(strcmp(fieldName[x], fields[y].fieldName) == 0) {
                                        printf("%s", record+offsetcheck);
                                        if(x < countA - 1)
                                                printf(",");
                                }
                                offsetcheck += fields[y].fieldLength;


                                y++;
                        }
                        x++;
                }
                printf("\n");
        }
}

void showRecord6(struct _field* fields, char *record, int fieldcount, char fieldName[100][MAXINPUTLENGTH], int countA, char fieldCompare[20][MAXINPUTLENGTH], int countComp){

        int x = 0;
        int offset1 = 0;
        int check1 = 0;
        int offset2 = 0;
        int check2 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[0], fields[x].fieldName) == 0) {
                        check1 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[1], fields[x].fieldName) == 0) {
                        check2 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        offset1 = 0;
        int check3 = 0;
        offset2 = 0;
        int check4 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[2], fields[x].fieldName) == 0) {
                        check3 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[3], fields[x].fieldName) == 0) {
                        check4 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }

        x = 0;
        offset1 = 0;
        int check5 = 0;
        offset2 = 0;
        int check6 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[4], fields[x].fieldName) == 0) {
                        check5 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[5], fields[x].fieldName) == 0) {
                        check6 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }

        x = 0;
        offset1 = 0;
        int check7 = 0;
        offset2 = 0;
        int check8 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[6], fields[x].fieldName) == 0) {
                        check7 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[7], fields[x].fieldName) == 0) {
                        check8 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        int offsetcheck = 0;

        if( (strcmp(record+check1, record+check2) == 0) && (strcmp(record+check3, record+check4) == 0) && (strcmp(record+check5, record+check6) == 0) && (strcmp(record+check7, record+check8) == 0)) {

                while(x < countA) {
                        int y = 0;
                        offsetcheck = 0;
                        while(y < fieldcount) {
                                if(strcmp(fieldName[x], fields[y].fieldName) == 0) {
                                        printf("%s", record+offsetcheck);
                                        if(x < countA - 1)
                                                printf(",");
                                }
                                offsetcheck += fields[y].fieldLength;


                                y++;
                        }
                        x++;
                }
                printf("\n");
        }
}

void showRecord7(struct _field* fields, char *record, int fieldcount, char fieldName[100][MAXINPUTLENGTH], int countA, char fieldCompare[20][MAXINPUTLENGTH], int countComp){

        int x = 0;
        int offset1 = 0;
        int check1 = 0;
        int offset2 = 0;
        int check2 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[0], fields[x].fieldName) == 0) {
                        check1 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[1], fields[x].fieldName) == 0) {
                        check2 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        offset1 = 0;
        int check3 = 0;
        offset2 = 0;
        int check4 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[2], fields[x].fieldName) == 0) {
                        check3 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[3], fields[x].fieldName) == 0) {
                        check4 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }

        x = 0;
        offset1 = 0;
        int check5 = 0;
        offset2 = 0;
        int check6 = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[4], fields[x].fieldName) == 0) {
                        check5 = offset1;
                        break;
                }
                offset1 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        while(x < fieldcount) {
                if(strcmp(fieldCompare[5], fields[x].fieldName) == 0) {
                        check6 = offset2;
                        break;
                }
                offset2 += fields[x].fieldLength;
                x++;
        }
        x = 0;
        int offsetcheck = 0;

        if( (strcmp(record+check1, record+check2) == 0) && (strcmp(record+check3, record+check4) == 0) && (strcmp(record+check5, record+check6) == 0)) {

                while(x < countA) {
                        int y = 0;
                        offsetcheck = 0;
                        while(y < fieldcount) {
                                if(strcmp(fieldName[x], fields[y].fieldName) == 0) {
                                        printf("%s", record+offsetcheck);
                                        if(x < countA - 1)
                                                printf(",");
                                }
                                offsetcheck += fields[y].fieldLength;


                                y++;
                        }
                        x++;
                }
                printf("\n");
        }
}


void createTable(char* buffer)
{
        struct _table table;
        char *temp = malloc(strlen(buffer)+1);
        strcpy(temp, buffer);
        temp = strtok(temp, " ");
        temp = strtok(NULL, " ");
        temp = strtok(NULL, " ");
        table.tableFileName = malloc(strlen(temp)+5);
        table.schemaName = malloc(strlen(temp)+8);
        addBin(table.tableFileName, temp);
        addSchema(table.schemaName, temp);
        FILE *binFP = fopen(table.tableFileName, "wb"), *schemaFP = fopen(table.schemaName, "wb");
        char* endline = "\n";
        strcat(buffer, endline);
        //fwrite(buffer, strlen(buffer) * sizeof(char), 1, schemaFP);
        static char buffer2[MAXINPUTLENGTH];
        memset(buffer2, 0, MAXINPUTLENGTH);
        int x = 0;
        while (fgets(buffer2, MAXINPUTLENGTH - 1, stdin)) {
                if (strcmp(buffer2, "\n") == 0) {
                        break;
                }
                if (strcmp(buffer2, "END\n") == 0) {
                        printf("===> %s", buffer2);
                        break;
                }
                printf("===> %s", buffer2);
                //  printf("TESTING BUFFER2: %s\n", buffer2);
                fwrite(buffer2, strlen(buffer2) * sizeof(char), 1, schemaFP);
                x++;
        }
        fclose(binFP);
        fclose(schemaFP);
}

void processCommand(char* buffer)
{
        struct _table table;
        char* tempBuffer = malloc(strlen(buffer)+1);

        strcpy(tempBuffer, buffer);
        tempBuffer = strtok(tempBuffer, " ");
        if (strcmp(tempBuffer, "CREATE") == 0) {
                tempBuffer = strtok(NULL, " ");
                if(strcmp(tempBuffer, "TABLE") == 0) {

                        createTable(buffer);
                }
                else if(strcmp(tempBuffer, "INDEX") == 0) {
                        char* tempIndex = malloc(strlen(buffer)+1);
                        strcpy(tempIndex, buffer);
                        tempIndex = strtok(tempIndex, " ");
                        tempIndex = strtok(NULL, " ");
                        tempIndex = strtok(NULL, " ");
                        char* indexName = malloc(strlen(tempIndex)+1);
                        strcpy(indexName, tempIndex);

                        // parsing USING

                        tempIndex = strtok(NULL, " ");
                        char indexFields[100][MAXINPUTLENGTH];

                        // parsing field names of indexName

                        int countIndex = 0;
                        while(tempIndex != NULL) {
                                tempIndex = strtok(NULL, " ,\n");
                                if(tempIndex == NULL) {
                                        break;
                                }
                                strcpy(indexFields[countIndex], tempIndex);
                                countIndex++;
                        }

                        // parsing to get FROM file names

                        static char tempFromIndex[MAXINPUTLENGTH];
                        memset(tempFromIndex, 0, MAXINPUTLENGTH);
                        while(fgets(tempFromIndex, MAXINPUTLENGTH - 1, stdin)) {
                                trimwhitespace(tempFromIndex);
                                printf("===> %s\n", tempFromIndex);

                                if(strcmp(tempFromIndex, "END") == 0) {
                                        break;
                                }

                                else{
                                        // parsing to get the file name

                                        char* fromIndex;
                                        fromIndex = strtok(tempFromIndex, " \n");
                                        fromIndex = strtok(NULL, " \n");

                                        struct _table tableIndex, tableIndex2;
                                        tableIndex.tableFileName = malloc(strlen(indexName)+1);
                                        tableIndex2.tableFileName = malloc(strlen(fromIndex)+1);
                                        strcpy(tableIndex.tableFileName, indexName);
                                        strcpy(tableIndex2.tableFileName, fromIndex);


                                        char* schemaIndex = malloc(strlen(indexName)+8);
                                        char* binIndex = malloc(strlen(indexName)+5);
                                        strcpy(schemaIndex, indexName);
                                        strcpy(binIndex, indexName);
                                        strcat(schemaIndex, ".schema");
                                        strcat(binIndex, ".bin");

                                        tableIndex.schemaName = malloc(strlen(schemaIndex)+1);
                                        strcpy(tableIndex.schemaName, schemaIndex);

                                        char* binIndex2 = malloc(strlen(tableIndex2.tableFileName)+5);
                                        char* schemaIndex2 = malloc(strlen(tableIndex2.tableFileName)+8);
                                        addBin(binIndex2, tableIndex2.tableFileName);
                                        addSchema(schemaIndex2, tableIndex2.tableFileName);

                                        tableIndex2.schemaName = malloc(strlen(schemaIndex2)+1);
                                        strcpy(tableIndex2.schemaName, schemaIndex2);

                                        FILE *schemaFP = fopen(schemaIndex, "wb");
                                        FILE *binFP = fopen(binIndex, "wb");

                                        FILE *schemaFP2 = fopen(schemaIndex2, "rb");

                                        char c[MAXINPUTLENGTH];
                                        char create[MAXINPUTLENGTH];
                                        //fprintf(stderr, "TESTING: %s\n", tableIndex.tableFileName);
                                        strcat(create, "CREATE TABLE ");
                                        strcat(create, tableIndex.tableFileName);
                                        strcat(create, "\n");
                                        fputs(create, schemaFP);
                                        // copy schema from input people to ipeople
                                        //fgets(c, MAXINPUTLENGTH, schemaFP2)
                                        while(fgets(c,MAXINPUTLENGTH, schemaFP2)) {
                                                char* buffer = malloc(strlen(c)+1);
                                                strcpy(buffer, c);
                                                //  fprintf(stderr, "TESTING BUFFER: %s\n", buffer);
                                                char* temp = strtok(buffer, " \n");

                                                temp = strtok(NULL, " \n");
                                                for(int j = 0; j < countIndex; j++) {
                                                        if(strcmp(indexFields[j], temp) == 0) {
                                                                fputs(c, schemaFP);
                                                        }
                                                }
                                        }
                                        fclose(schemaFP);
                                        fclose(schemaFP2);

                                        //fprintf(stderr, "TESTING: %s\n", tableIndex2.schemaName);
                                        loadSchema(&tableIndex2);
                                        char* index2FileNameBin = malloc(strlen(tableIndex2.tableFileName)+5);
                                        addBin(index2FileNameBin, tableIndex2.tableFileName);

                                        FILE *fp2Bin = fopen(index2FileNameBin, "rb");
                                        char* record = calloc(1, tableIndex2.reclen);
                                        //fprintf(stderr, "TESTING FILENAME: %s\n", index2FileNameBin);
                                        //fprintf(stderr, "TESTING: %d\n", tableIndex2.fieldcount);
                                        int x = 0;
                                        int counter = 0;
                                        int offsetNums[tableIndex2.fieldcount];
                                        while(x < countIndex) {
                                                int y = 0;
                                                int offset = 0;
                                                while(y < tableIndex2.fieldcount) {
                                                        if(strcmp(tableIndex2.fields[y].fieldName, indexFields[x]) == 0) {
                                                                offsetNums[counter] = offset;
                                                                counter++;
                                                                break;
                                                        }
                                                        offset += tableIndex2.fields[y].fieldLength;
                                                        y++;
                                                }
                                                x++;
                                        }
                                        loadSchema(&tableIndex);
                                        char str[50][50];
                                        char temp[25];
                                        int count = 0;
                                        while(fread(record, tableIndex2.reclen, 1, fp2Bin)) {
                                                x = 0;
                                                int indexFieldCount = 0;
                                                trimwhitespace(record);
                                                while(x < countIndex) {
                                                        strcat(str[count], record+offsetNums[x]);
                                                        if(x < countIndex-1) {
                                                                strcat(str[count], ",");
                                                        }
                                                        //fprintf(stderr, "TESTING RECORD: %s\n", record+offsetNums[x]);
                                                        x++;
                                                        indexFieldCount++;
                                                }
                                                //fprintf(stderr, "TESTING STR: %s\n", str[count]);
                                                count++;

                                        }
                                        //fprintf(stderr, "TESTING LAST: %s\n", str[0]);

                                        for(int i = 0; i <= count; i++)
                                                for(int j=i+1; j<=count; j++) {
                                                        if(strcmp(str[i], str[j]) > 0) {
                                                                strcpy(temp, str[i]);
                                                                strcpy(str[i],str[j]);
                                                                strcpy(str[j],temp);
                                                        }
                                                }
                                        x = 0;
                                        int p = 0;
                                        char temp2[50] ="";
                                        while(x <= count) {
                                                p = 0;
                                                char* temp =strtok(str[x], ",\n");
                                                while(temp != NULL) {
                                                        //fprintf(stderr, "TESTING TEMP: %s\n", temp);
                                                        strncpy(temp2, temp, 50);
                                                        //fprintf(stderr, "TESTING FIELD LENGTH: %d\n", tableIndex.fields[p].fieldLength);
                                                        fwrite(temp2, tableIndex.fields[p].fieldLength, 1, binFP);
                                                        p++;
                                                        temp = strtok(NULL, ",\n");
                                                }
                                                x++;
                                        }

                                        fclose(binFP);
                                }
                        }


                }
        }
        if (strcmp(tempBuffer, "INSERT") == 0) {
                tempBuffer = strtok(NULL, " ");
                tempBuffer = strtok(NULL, " ");
                table.tableFileName = malloc(strlen(tempBuffer)+5);
                table.schemaName = malloc(strlen(tempBuffer)+8);
                addBin(table.tableFileName, tempBuffer);
                addSchema(table.schemaName, tempBuffer);
                loadSchema(&table);
                loadDatabase(&table, buffer);
        }

        if (strcmp(tempBuffer, "LOAD") == 0) {
                struct _table table2;
                tempBuffer = strtok(NULL, " ");
                tempBuffer = strtok(NULL, " ");
                table2.tableFileName = malloc(strlen(tempBuffer)+5);
                table2.schemaName = malloc(strlen(tempBuffer)+8);
                addBin(table2.tableFileName, tempBuffer);
                addSchema(table2.schemaName, tempBuffer);
                loadSchema(&table);
                int x = 0;
                while (x < table.fieldcount) {
                        x++;
                }
                loadDatabase(&table, buffer);
        }
        if (strcmp(tempBuffer, "SELECT") == 0) {

                struct _table table2;
                table2.reclen = 0;
                table2.fieldcount = 0;


                ///////////////////////////////////////////

                // SAVING SELECT FIELDNAMES INTO AN ARRAY

                //////////////////////////////////////////


                int countA = 0;
                char fieldName[100][MAXINPUTLENGTH];
                char* tempSelect = malloc(strlen(buffer)+1);
                strcpy(tempSelect, buffer);
                tempSelect = strtok(tempSelect, " ,");
                while (tempSelect != NULL) {
                        //printf("TESTING SELECT STATEMENT: %s\n", tempSelect);
                        tempSelect = strtok(NULL, " ,\n");
                        if (tempSelect == NULL) {
                                break;
                        }
                        strcpy(fieldName[countA], tempSelect);
                        countA++;
                }




                static char temp_bufferB[MAXINPUTLENGTH];
                memset(temp_bufferB, 0, MAXINPUTLENGTH);
                fgets(temp_bufferB, MAXINPUTLENGTH - 1, stdin);
                trimwhitespace(temp_bufferB);
                printf("===> %s\n", temp_bufferB);
                char* temp_bufferFrom = malloc(strlen(temp_bufferB));
                strcpy(temp_bufferFrom, temp_bufferB);
                char* tokenFrom;
                tokenFrom = strtok(temp_bufferFrom, ", ");
                int from = 0;
                char fromName[10][MAXINPUTLENGTH];
                while (tokenFrom != NULL) {
                        tokenFrom = strtok(NULL, " ,");
                        if (tokenFrom == NULL)
                                break;
                        strcpy(fromName[from], tokenFrom);
                        from++;
                }
                //fprintf(stderr, "TESTING FROM: %d\n", from);


                ///////////////////////////
                // FROM ONE FILE
                //////////////////////////////



                if (from <= 1) {
                        char tempC[MAXINPUTLENGTH];
                        char* tempD;
                        strcpy(tempC, temp_bufferB);
                        tempD = strtok(tempC, " ");
                        char* selectFileName;
                        selectFileName = strtok(NULL, " ,");
                        char* tempBin;
                        tempBin = malloc(strlen(tempBuffer) + 5);
                        strcpy(tempBin, selectFileName);
                        char* binExt = ".bin";
                        strcat(tempBin, binExt);


                        // IF THE FILE EXISTS

                        if (fopen(tempBin, "rb") != NULL) {
                                table2.tableFileName = malloc(strlen(selectFileName)+5);
                                table2.schemaName = malloc(strlen(selectFileName)+8);
                                addBin(table2.tableFileName, selectFileName);
                                addSchema(table2.schemaName, selectFileName);
                                loadSchema(&table2);
                                int counter = 0;
                                struct stat st;
                                stat(tempBin, &st);
                                int size = st.st_size;
                                int count = size / table2.reclen;

                                static char temp_buffer[MAXINPUTLENGTH];
                                memset(temp_buffer, 0, MAXINPUTLENGTH);
                                fgets(temp_buffer, MAXINPUTLENGTH - 1, stdin);
                                trimwhitespace(temp_buffer);
                                printf("===> %s\n", temp_buffer);

                                //fprintf(stderr, "TESTING: %s\n", table2.tableFileName);
                                // SELECT --- FROM
                                //fprintf(stderr, "TESTING BUFFER BLAH BLAH: %s\n", temp_buffer);
                                if (strcmp(temp_buffer, "END") == 0) {

                                        //  fprintf(stderr, "TESTING FIELDS: %s\n", fieldName[0]);
                                        while (counter < count) {
                                                // fprintf(stderr, "TESTING\n");
                                                char* record = calloc(1, table2.reclen);
                                                getRecord(counter, record, &table2);
                                                char temp3[MAXINPUTLENGTH];
                                                // strcpy(temp3, buffer);
                                                // char* temp4 = strtok(temp3, " ,");
                                                int a = 0;

                                                int b = 0;
                                                while (a < countA) {
                                                        b = 0;
                                                        while (b < table2.fieldcount) {

                                                                if (strcmp(table2.fields[b].fieldName, fieldName[a]) == 0) {
                                                                        showRecord(
                                                                                table2.fields, record, table2.fieldcount, fieldName[a]);
                                                                }
                                                                b++;
                                                        }
                                                        a++;
                                                        if (a < countA) {
                                                                printf(",");
                                                        }
                                                }
                                                printf("\n");
                                                counter++;
                                        }

                                }

                                // SELECT --- FROM -- WHERE

                                else {

                                        static char temp_buffer2[MAXINPUTLENGTH];
                                        memset(temp_buffer2, 0, MAXINPUTLENGTH);
                                        fgets(temp_buffer2, MAXINPUTLENGTH - 1, stdin);
                                        trimwhitespace(temp_buffer2);
                                        printf("===> %s\n", temp_buffer2);
                                        //fprintf(stderr, "TESTING BUFFER WHERE: %s\n", temp_buffer2);

                                        if (strcmp(temp_buffer2, "END") == 0) {
                                                char tempX[MAXINPUTLENGTH];
                                                char* tempY;
                                                strcpy(tempX, temp_buffer);
                                                tempY = strtok(tempX, " ,");
                                                char* fieldX;
                                                fieldX = strtok(NULL, " ,");
                                                strtok(NULL, " ");
                                                char* fieldNameX;
                                                fieldNameX = strtok(NULL, " \"");
                                                int counter = 0;
                                                int check = 0;
                                                int middle = (counter + count)/2;
                                                while(counter <= count) {
                                                        char* record = calloc(1, table2.reclen);
                                                        getRecord(middle, record, &table2);
                                                        check = showRecord2(&table2, record, fieldName, countA, fieldX, fieldNameX);
                                                        if(check == 1) {
                                                                counter = middle + 1;
                                                        }
                                                        if(check == 0) {
                                                                break;
                                                        }
                                                        if(check == 2) {
                                                                count = middle -1;
                                                        }
                                                        middle = (counter + count)/2;
                                                }


                                        }


                                        // SELECT --- FROM --- WHERE --- AND

                                        else {
                                                static char temp_bufferAND[MAXINPUTLENGTH];
                                                memset(temp_bufferAND, 0, MAXINPUTLENGTH);
                                                fgets(temp_bufferAND, MAXINPUTLENGTH - 1, stdin);
                                                trimwhitespace(temp_bufferAND);
                                                printf("===> %s\n", temp_bufferAND);
                                                char* tokenAnd1;
                                                char* tokenAnd2;
                                                static char tempAnd[MAXINPUTLENGTH];
                                                memset(tempAnd, 0, MAXINPUTLENGTH);
                                                char tempX[MAXINPUTLENGTH];
                                                char* tempY;
                                                strcpy(tempX, temp_buffer);
                                                tempY = strtok(tempX, " ,");
                                                char* fieldX;
                                                fieldX = strtok(NULL, " ,");
                                                strtok(NULL, " ");
                                                char* fieldNameX;
                                                fieldNameX = strtok(NULL, " \"");

                                                char tempXX[MAXINPUTLENGTH];
                                                char* tempYY;
                                                strcpy(tempXX, temp_buffer2);
                                                tempYY = strtok(tempXX, " ,");
                                                char* fieldXX;
                                                fieldXX = strtok(NULL, " ,");
                                                strtok(NULL, " ");
                                                char* fieldNameXX;
                                                fieldNameXX = strtok(NULL, " \"");
                                                int a = 0;
                                                int b = 0;
                                                while (counter < count) {
                                                        char* record = calloc(1, table2.reclen);
                                                        getRecord(counter, record, &table2);
                                                        a = 0;
                                                        while (a < countA) {
                                                                b = 0;
                                                                while (b < table2.fieldcount) {
                                                                        if (strcmp(table2.fields[b].fieldName, fieldName[a]) == 0) {
                                                                                showRecord3(table2.fields, record, table2.fieldcount,
                                                                                            fieldName[a], fieldX, fieldNameX, fieldXX, fieldNameXX,
                                                                                            countA, a);
                                                                        }

                                                                        b++;
                                                                }
                                                                a++;
                                                        }

                                                        counter++;
                                                }
                                        }
                                }
                        }



                        /////////////////////////////
                        // FILE DOES NOT EXISTS
                        ////////////////////////////



                        else {
                                static char temp_bufferF[MAXINPUTLENGTH];
                                memset(temp_bufferF, 0, MAXINPUTLENGTH);
                                fgets(temp_bufferF, MAXINPUTLENGTH - 1, stdin);
                                trimwhitespace(temp_bufferF);
                                printf("===> %s\n", temp_bufferF);
                                printf("Table %s does not exist.\n", selectFileName);
                        }
                }

                else{

                        //fprintf(stderr, "TESTING FROM: %d\n", from);
                        int kat = 0;
                        char fieldName1[100][MAXINPUTLENGTH];
                        while(kat < countA) {
                                strcpy(fieldName1[kat], fieldName[kat]);
                                kat++;
                        }
                        //  printf("TESTING FROM : %d\n", from);
                        int from1 = from;
                        struct _table table2[from];
                        static char temp_bufferMulti[MAXINPUTLENGTH];
                        memset(temp_bufferMulti, 0, MAXINPUTLENGTH);
                        char fieldCompare[50][MAXINPUTLENGTH];
                        char tempCompA[MAXINPUTLENGTH];
                        char* tempCompB;
                        int countComp = 0;



                        while (fgets(temp_bufferMulti, MAXINPUTLENGTH - 1, stdin)) {
                                if (strcmp(temp_bufferMulti, "END\n") == 0) {
                                        printf("===> %s", temp_bufferMulti);
                                        break;
                                }

                                trimwhitespace(temp_bufferMulti);
                                printf("===> %s\n", temp_bufferMulti);

                                strcpy(tempCompA, temp_bufferMulti);
                                tempCompB = strtok(tempCompA, " ,");

                                //fprintf(stderr, "TESTING TEMPCOMP %s\n", tempCompB);

                                while (tempCompB != NULL) {
                                        tempCompB = strtok(NULL, " ,=");
                                        if (tempCompB == NULL) {
                                                break;
                                        }
                                        //fprintf(stderr, "TESTTEMPCOMP: %s\n", tempCompB);
                                        if (strcmp(tempCompB, "WHERE") != 0 || strcmp(tempCompB, "FROM") != 0) {
                                                strcpy(fieldCompare[countComp], tempCompB);
                                                //fprintf(stderr, "TESTING FIELD COMPARE : %s\n", fieldCompare[countComp]);
                                                countComp++;
                                        }
                                }
                        }



                        char* extension = ".bin";
                        int x = 0;
                        int countFrom[from1];
                        int countBig = 0;
                        int fileBiggest = 0;

                        // RESET THE VALUES

                        while(x < from) {
                                table2[x].reclen = 0;
                                table2[x].fieldcount = 0;
                                x++;

                        }
                        x = 0;

                        //fprintf(stderr, "TESTING FROM %d\n", from);
                        while (x < from1) {

                                table2[x].tableFileName = malloc(strlen(fromName[x])+5);
                                table2[x].schemaName = malloc(strlen(fromName[x])+8);
                                addBin(table2[x].tableFileName, fromName[x]);
                                addSchema(table2[x].schemaName, fromName[x]);
                                loadSchema(&table2[x]);
                                strcat(fromName[x], ".bin");

                                struct stat st;
                                stat(fromName[x], &st);
                                int size = st.st_size;
                                countFrom[x] = size / table2[x].reclen;
                                //printf("TESTING COUNTFROM SIZE: %d\n", countFrom[x]);
                                //fprintf(stderr, "TESTING COUNT: %d\n", countFrom[x]);
                                if (countFrom[x] > countBig) {
                                        countBig = countFrom[x];
                                        fileBiggest = x;
                                }
                                x++;
                        }
                        int key;
                        struct _table tablekey;

                        //printf("TESTING FROM : %d\n", from);
                        for(int i = 1; i<from1; i++) {
                                key = countFrom[i];
                                tablekey = table2[i];
                                int j = i - 1;
                                while(j>=0 && (countFrom[j] < key)) {
                                        countFrom[j+1] = countFrom[j];
                                        table2[j+1] = table2[j];
                                        j--;
                                }
                                countFrom[j+1] = key;
                                table2[j+1] = tablekey;
                        }
                        x = 0;
                        while(x < from) {
                                table2[x].reclen = 0;
                                table2[x].fieldcount = 0;
                                x++;

                        }


                        // MERGING 2 FILES

                        struct _table tempStruct1;
                        tempStruct1.tableFileName = "temp.bin";
                        tempStruct1.schemaName = "temp.schema";

                        FILE *tempBin1 = fopen("temp.bin", "wb");
                        FILE *tempSchema1 = fopen("temp.schema", "wb");

                        //printf("TESTING FILE NAME: %s %s\n", table2[0].tableFileName, table2[0].schemaName);
                        FILE *readBin1 = fopen(table2[0].tableFileName, "rb");
                        FILE *readSchema1 = fopen(table2[0].schemaName, "rb");

                        FILE *readBin2 = fopen(table2[1].tableFileName, "rb");
                        FILE *readSchema2 = fopen(table2[1].schemaName, "rb");

                        loadSchema(&table2[0]);
                        loadSchema(&table2[1]);

                        char c;
                        while((c = fgetc(readSchema1)) != EOF) {
                                fputc(c, tempSchema1);
                        }
                        while((c = fgetc(readSchema2)) != EOF) {
                                fputc(c, tempSchema1);
                        }
                        int j = 0;
                        while(j < countFrom[0]) {
                                int k = 0;
                                while(k < countFrom[1]) {
                                        fseek(readBin1, j*table2[0].reclen, SEEK_SET);
                                        int recLen = 0;
                                        while(recLen < table2[0].reclen) {
                                                fputc(fgetc(readBin1), tempBin1);


                                                recLen++;
                                        }
                                        recLen = 0;
                                        fseek(readBin2, k*table2[1].reclen, SEEK_SET);
                                        while(recLen < table2[1].reclen) {
                                                fputc(fgetc(readBin2), tempBin1);
                                                recLen++;
                                        }

                                        k++;
                                }
                                j++;
                        }

                        fclose(tempBin1);
                        fclose(readBin1);
                        fclose(readBin2);
                        fclose(tempSchema1);
                        fclose(readSchema1);
                        fclose(readSchema2);

                        // MERGING 3 FILES
                        if(from1 >= 2) {
                                struct _table tempStructA, tempStructB;
                                FILE *tempBin2 = fopen("temp2.bin", "wb");
                                FILE *tempSchema2 = fopen("temp2.schema", "wb");

                                //printf("TESTING FILE NAME: %s %s\n", table2[0].tableFileName, table2[0].schemaName);
                                FILE *readBin3 = fopen("temp.bin", "rb");
                                FILE *readSchema3 = fopen("temp.schema", "rb");

                                FILE *readBin4 = fopen(table2[2].tableFileName, "rb");
                                FILE *readSchema4 = fopen(table2[2].schemaName, "rb");

                                while((c = fgetc(readSchema3)) != EOF) {
                                        fputc(c, tempSchema2);
                                }
                                while((c = fgetc(readSchema4)) != EOF) {
                                        fputc(c, tempSchema2);
                                }
                                fclose(readSchema3);
                                fclose(readSchema4);
                                tempStructA.reclen = 0;
                                tempStructB.reclen = 0;

                                tempStructA.schemaName = "temp.schema";
                                tempStructB.schemaName = table2[2].schemaName;

                                loadSchema(&tempStructA);
                                loadSchema(&tempStructB);

                                int size1 = 0, size2 = 0, recordNum1 = 0, recordNum2 = 0;

                                while((c = fgetc(readBin3)) != EOF) {
                                        //  printf("%c", c);
                                        size1++;
                                }
                                //  printf("TESTING RECLEN : %d\n", tempStructA.reclen);
                                recordNum1 = size1 / tempStructA.reclen;

                                while((c= fgetc(readBin4)) != EOF) {
                                        //printf("%c", c);
                                        size2++;
                                }
                                //printf("TESTING RECLEN : %d\n", size2);
                                recordNum2 = size2 / tempStructB.reclen;

                                fseek(readBin3, 0, SEEK_SET);
                                fseek(readBin4, 0, SEEK_SET);

                                j = 0;
                                while(j < recordNum1) {
                                        int k = 0;
                                        while(k < recordNum2) {
                                                fseek(readBin3, j*tempStructA.reclen, SEEK_SET);
                                                int recLen = 0;
                                                while(recLen < tempStructA.reclen) {
                                                        fputc(fgetc(readBin3), tempBin2);


                                                        recLen++;

                                                }
                                                recLen = 0;
                                                fseek(readBin4, k*tempStructB.reclen, SEEK_SET);
                                                while(recLen < tempStructB.reclen) {
                                                        fputc(fgetc(readBin4), tempBin2);

                                                        recLen++;
                                                }


                                                k++;
                                        }


                                        j++;
                                }
                                fclose(tempBin2);
                                fclose(tempSchema2);
                                fclose(readBin3);
                                fclose(readBin4);
                        }

                        if(from1 >= 3) {
                                struct _table tempStructA, tempStructB;
                                FILE *tempBin3 = fopen("temp3.bin", "wb");
                                FILE *tempSchema3 = fopen("temp3.schema", "wb");

                                //printf("TESTING FILE NAME: %s %s\n", table2[0].tableFileName, table2[0].schemaName);
                                FILE *readBin5 = fopen("temp2.bin", "rb");
                                FILE *readSchema5 = fopen("temp2.schema", "rb");

                                FILE *readBin6 = fopen(table2[3].tableFileName, "rb");
                                FILE *readSchema6 = fopen(table2[3].schemaName, "rb");

                                while((c = fgetc(readSchema5)) != EOF) {
                                        fputc(c, tempSchema3);
                                }
                                while((c = fgetc(readSchema6)) != EOF) {
                                        fputc(c, tempSchema3);
                                }
                                fclose(readSchema5);
                                fclose(readSchema6);
                                tempStructA.reclen = 0;
                                tempStructB.reclen = 0;
                                tempStructA.schemaName = "temp2.schema";
                                tempStructB.schemaName = table2[3].schemaName;

                                loadSchema(&tempStructA);
                                loadSchema(&tempStructB);

                                int size1 = 0, size2 = 0, recordNum1 = 0, recordNum2 = 0;

                                while((c = fgetc(readBin5)) != EOF) {
                                        //  printf("%c", c);
                                        size1++;
                                }
                                //  printf("TESTING RECLEN : %d\n", tempStructA.reclen);
                                recordNum1 = size1 / tempStructA.reclen;

                                while((c= fgetc(readBin6)) != EOF) {
                                        //printf("%c", c);
                                        size2++;
                                }
                                //printf("TESTING RECLEN : %d\n", size2);
                                recordNum2 = size2 / tempStructB.reclen;

                                fseek(readBin5, 0, SEEK_SET);
                                fseek(readBin6, 0, SEEK_SET);

                                j = 0;
                                while(j < recordNum1) {
                                        int k = 0;
                                        while(k < recordNum2) {
                                                fseek(readBin5, j*tempStructA.reclen, SEEK_SET);
                                                int recLen = 0;
                                                while(recLen < tempStructA.reclen) {
                                                        fputc(fgetc(readBin5), tempBin3);
                                                        recLen++;

                                                }
                                                recLen = 0;
                                                fseek(readBin6, k*tempStructB.reclen, SEEK_SET);
                                                while(recLen < tempStructB.reclen) {
                                                        fputc(fgetc(readBin6), tempBin3);

                                                        recLen++;
                                                }


                                                k++;
                                        }


                                        j++;
                                }
                                fclose(tempBin3);
                                fclose(tempSchema3);
                                fclose(readBin5);
                                fclose(readBin6);
                        }
                        if(from1 >= 4) {
                                struct _table tempStructA, tempStructB;
                                FILE *tempBin4 = fopen("temp4.bin", "wb");
                                FILE *tempSchema4 = fopen("temp4.schema", "wb");

                                //printf("TESTING FILE NAME: %s %s\n", table2[0].tableFileName, table2[0].schemaName);
                                FILE *readBin7 = fopen("temp3.bin", "rb");
                                FILE *readSchema7 = fopen("temp3.schema", "rb");

                                FILE *readBin8 = fopen(table2[4].tableFileName, "rb");
                                FILE *readSchema8 = fopen(table2[4].schemaName, "rb");

                                while((c = fgetc(readSchema7)) != EOF) {
                                        fputc(c, tempSchema4);
                                }
                                while((c = fgetc(readSchema8)) != EOF) {
                                        fputc(c, tempSchema4);
                                }
                                fclose(readSchema7);
                                fclose(readSchema8);
                                tempStructA.reclen = 0;
                                tempStructB.reclen = 0;
                                tempStructA.schemaName = "temp3.schema";
                                tempStructB.schemaName = table2[4].schemaName;

                                loadSchema(&tempStructA);
                                loadSchema(&tempStructB);

                                int size1 = 0, size2 = 0, recordNum1 = 0, recordNum2 = 0;

                                while((c = fgetc(readBin7)) != EOF) {
                                        //  printf("%c", c);
                                        size1++;
                                }
                                //  printf("TESTING RECLEN : %d\n", tempStructA.reclen);
                                recordNum1 = size1 / tempStructA.reclen;

                                while((c= fgetc(readBin8)) != EOF) {
                                        //printf("%c", c);
                                        size2++;
                                }
                                //printf("TESTING RECLEN : %d\n", size2);
                                recordNum2 = size2 / tempStructB.reclen;

                                fseek(readBin7, 0, SEEK_SET);
                                fseek(readBin8, 0, SEEK_SET);

                                j = 0;
                                while(j < recordNum1) {
                                        int k = 0;
                                        while(k < recordNum2) {
                                                fseek(readBin7, j*tempStructA.reclen, SEEK_SET);
                                                int recLen = 0;
                                                while(recLen < tempStructA.reclen) {
                                                        fputc(fgetc(readBin7), tempBin4);
                                                        recLen++;

                                                }
                                                recLen = 0;
                                                fseek(readBin8, k*tempStructB.reclen, SEEK_SET);
                                                while(recLen < tempStructB.reclen) {
                                                        fputc(fgetc(readBin8), tempBin4);

                                                        recLen++;
                                                }


                                                k++;
                                        }


                                        j++;
                                }
                                fclose(tempBin4);
                                fclose(tempSchema4);
                                fclose(readBin7);
                                fclose(readBin8);
                        }
                        if(from1 >= 5) {
                                if(from1 == 6) {
                                        struct _table tempStructA, tempStructB;
                                        FILE *tempBin5 = fopen("temp5.bin", "wb");
                                        FILE *tempSchema5 = fopen("temp5.schema", "wb");

                                        //printf("TESTING FILE NAME: %s %s\n", table2[0].tableFileName, table2[0].schemaName);
                                        FILE *readBin9 = fopen("temp4.bin", "rb");
                                        FILE *readSchema9 = fopen("temp4.schema", "rb");

                                        FILE *readBin10 = fopen(table2[5].tableFileName, "rb");
                                        FILE *readSchema10 = fopen(table2[5].schemaName, "rb");

                                        while((c = fgetc(readSchema9)) != EOF) {
                                                fputc(c, tempSchema5);
                                        }
                                        while((c = fgetc(readSchema10)) != EOF) {
                                                fputc(c, tempSchema5);
                                        }
                                        fclose(readSchema9);
                                        fclose(readSchema10);
                                        tempStructA.reclen = 0;
                                        tempStructB.reclen = 0;
                                        tempStructA.schemaName = "temp4.schema";
                                        tempStructB.schemaName = table2[5].schemaName;

                                        loadSchema(&tempStructA);
                                        loadSchema(&tempStructB);

                                        int size1 = 0, size2 = 0, recordNum1 = 0, recordNum2 = 0;

                                        while((c = fgetc(readBin9)) != EOF) {
                                                //  printf("%c", c);
                                                size1++;
                                        }
                                        //  printf("TESTING RECLEN : %d\n", tempStructA.reclen);
                                        recordNum1 = size1 / tempStructA.reclen;

                                        while((c= fgetc(readBin10)) != EOF) {
                                                //printf("%c", c);
                                                size2++;
                                        }
                                        //printf("TESTING RECLEN : %d\n", size2);
                                        recordNum2 = size2 / tempStructB.reclen;

                                        fseek(readBin9, 0, SEEK_SET);
                                        fseek(readBin10, 0, SEEK_SET);

                                        j = 0;
                                        while(j < recordNum1) {
                                                int k = 0;
                                                while(k < recordNum2) {
                                                        fseek(readBin9, j*tempStructA.reclen, SEEK_SET);
                                                        int recLen = 0;
                                                        while(recLen < tempStructA.reclen) {
                                                                fputc(fgetc(readBin9), tempBin5);
                                                                recLen++;

                                                        }
                                                        recLen = 0;
                                                        fseek(readBin10, k*tempStructB.reclen, SEEK_SET);
                                                        while(recLen < tempStructB.reclen) {
                                                                fputc(fgetc(readBin10), tempBin5);

                                                                recLen++;
                                                        }


                                                        k++;
                                                }


                                                j++;
                                        }
                                        fclose(tempBin5);
                                        fclose(tempSchema5);
                                        fclose(readBin9);
                                        fclose(readBin10);
                                }

                        }



                        struct _table tableSelect;
                        if(from1 == 5) {
                                tableSelect.tableFileName = "temp4.bin";
                                tableSelect.schemaName = "temp4.schema";
                        }
                        if(from1 == 6) {
                                tableSelect.tableFileName = "temp5.bin";
                                tableSelect.schemaName = "temp5.schema";
                        }
                        tableSelect.reclen = 0;
                        tableSelect.fieldcount = 0;
                        loadSchema(&tableSelect);
                        struct stat st;
                        stat(tableSelect.tableFileName, &st);
                        int size = st.st_size;
                        int rec_num = size/tableSelect.reclen;
                        // printf("TESTING RECNUM: %d\n", rec_num);
                        // printf("TESTING SIZE: %d\n", size);
                        // printf("TESTING RECLENGTH: %d\n", tableSelect.reclen);
                        // printf("TESTING FIELDCOUNT: %d\n", tableSelect.fieldcount);
                        x = 0;
                        int offset = 0;
                        int numx=0;
                        // printf("TESTING FIELDCOMPARE : %s\n", fieldCompare[3]);
                        //  temp.fields
                        while(numx < rec_num) {
                                char* record = calloc(1, MAXINPUTLENGTH);
                                getRecord(numx, record, &tableSelect);
                                trimwhitespace(record);
                                if(countComp == 10)
                                        showRecord5(tableSelect.fields, record, tableSelect.fieldcount, fieldName1, countA, fieldCompare, countComp);
                                if(countComp == 8)
                                        showRecord6(tableSelect.fields, record, tableSelect.fieldcount, fieldName1, countA, fieldCompare, countComp);
                                if(countComp == 6)
                                        showRecord7(tableSelect.fields, record, tableSelect.fieldcount, fieldName1, countA, fieldCompare, countComp);
                                numx++;
                        }


                }
        }

        if (strcmp(tempBuffer, "DROP") == 0) {
                strtok(NULL, " ");
                tempBuffer = strtok(NULL, " ");
                char* extension = ".bin";
                char* extension2 = ".schema";
                char* tableFileName;
                char* schemaName;
                tableFileName = malloc(strlen(tempBuffer) + 5);
                schemaName = malloc(strlen(tempBuffer) + 8);
                strcpy(tableFileName, tempBuffer);
                strcpy(schemaName, tempBuffer);
                strcat(tableFileName, extension);
                strcat(schemaName, extension2);
                int x, y;
                x = remove(schemaName);
                y = remove(tableFileName);
        }
}

int main()
{
        static char buffer[MAXINPUTLENGTH];
        memset(buffer, 0, MAXINPUTLENGTH);
        printf("Welcome!\n");
        char* status = fgets(buffer, MAXINPUTLENGTH - 1, stdin);
        int x = 0;
        while (status != NULL) {
                trimwhitespace(buffer);
                if (strlen(buffer) < 5)
                        break; // not a real command, CR/LF, extra line, etc.
                printf("===> %s\n", buffer);
                // fprintf(stderr, "TESTING BUFFER: %s\n", buffer);
                processCommand(buffer);
                status = fgets(buffer, MAXINPUTLENGTH - 1, stdin);
                x++;
                // fprintf(stderr, "TESTING X: %d\n", x);
        }
        printf("Goodbye!\n");
        return 0;
}
