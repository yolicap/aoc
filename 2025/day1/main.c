#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// takes in string steps and returns password
int getPassword(char * steps[], int numSteps){
    int currValue = 50;
    int password = 0;

    // for each step, calc next dial value
    for (int i = 0; i < numSteps; i++){
        int currOperation = 0;
        char * clicksStr = steps[i]+ 1;

        printf("%d : D%cC%s", i, steps[i][0], clicksStr);

        if (steps[i][0] == 'L') currOperation = 100 - atoi(clicksStr);
        else currOperation = atoi(clicksStr);

        currValue += currOperation;
        currValue = currValue % 100;

        printf(" -> %d\n", currValue);

        if (currValue == 0) password++;
    }

    return password;
}

int main(){

    // char ** steps = (char**)malloc(10 * sizeof(char*));
    // char * steps[10] = {"L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82"};
    // printf("created array. good job \n");
    // printf("%s\n", steps[1]);

    char ** steps;

    FILE * fptr = fopen("input_p1.txt", "r");
    int lineNum = 1;
    char strBuffer[8];
    
    if (fptr != NULL) {
        char ch;
        // get num of lines to allocate
        while ((ch = fgetc(fptr)) != EOF) {
            if (ch == '\n') lineNum++;
        }

        printf("lines %d\n", lineNum);
        steps = malloc(sizeof(char*) * lineNum);
        lineNum=0;
        rewind(fptr);

        while (fgets(strBuffer, sizeof(strBuffer), fptr)) {
            char * p = strstr(strBuffer, "\n");
            if(p) strcpy(p, "\0");
            else strcat(strBuffer, "\0");
            steps[lineNum] = malloc(sizeof(char) * strlen(strBuffer));
            strcpy(steps[lineNum], strBuffer);
            printf("%d: %s\n", lineNum+1,steps[lineNum]);
            lineNum++;
        }
        fclose(fptr);
    }

    printf("first element : %s\n", steps[0]);
    int password = getPassword(steps, lineNum);
    printf("password: %d\n", password);

    return 0;
}
