#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// todo: can be closed formula ?
// todo: 9 per string even length, edges depends on range
unsigned long rangeCount(char bot[], char top[]){
    unsigned long count = 0;
    unsigned long botVal = strtol(bot, NULL, 10);
    unsigned long topVal = strtol(top, NULL, 10);

    printf("strlen(bot) : %d\n", (int)strlen(bot));
    printf("strlen(top) : %d\n", (int)strlen(top));
    // iterate through each number lenght in string
    for(int strLength = strlen(bot);  strLength < strlen(top) + 1; strLength++) {
        // iterate through each half number, [h_1 h_2]
        if(strLength % 2 == 0){
            int intShift = pow(10, ((float)strLength/2)-1);
            unsigned long half = 1 * intShift;

            printf("half: %lu\n", half);
            unsigned long full = half * intShift * 10 + half;
            printf("full eg: %lu\n", full);

            while(half < 1 * intShift * 10 ){
                full = half * intShift * 10 + half;
                if (full >= botVal && full <= topVal) {
                    printf("invalid id: %lu\n", full);
                    count += full;
                }
                half++;
            }
        }
    }
    // check if double number is in range, number is invalid
    return count;
}


// TODO could combine ranges to reduce counting work
int main(){

    // char * ranges[] = {"11-22","95-115","998-1012","1188511880-1188511890","222220-222224","1698522-1698528","446443-446449","38593856-38593862","565653-565659","824824821-824824827","2121212118-2121212124"};
    unsigned long count = 0;

    FILE * fptr = fopen("input_p1.txt", "r");
    int rangeNum = 2;
    char strBuffer[1024];
    
    if (fptr != NULL) {

        // only one line exptected
        fgets(strBuffer, sizeof(strBuffer), fptr);

        // ranges seperated by comma
        char * token = strtok(strBuffer, ",");
        while (token != NULL) {

            // split values
            char * currRange = malloc(sizeof(char) * strlen(token));
            strcpy(currRange, token);
            char * p = strstr(currRange, "-");
            *p = '\0';

            printf("range: %s-%s\n", currRange, p+1);
            count += rangeCount(currRange, p+1);
            printf("count: %lu\n", count );

            free(currRange);
            token = strtok(NULL, ",");
        }
        fclose(fptr);
    }

    // printf("final count : %lu \n", count);

    // for (int i = 0; i < 11; i++){
    //     printf("range: %s\n", ranges[i]);
    //     char * currRange = malloc(sizeof(char) * strlen(ranges[i]));
    //     strcpy(currRange, ranges[i]);
    //     char * p = strstr(currRange, "-");
    //     *p = '\0';
    //     count += rangeCount(currRange, p+1);
    //     printf("%lu\n", count );
    //     free(currRange);
    // }

    return 0;
}