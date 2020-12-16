#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include <time.h>
#define MAX 10
#define GMAX 25

typedef struct cyrpt {
    char symbol;
    int value;
} crypt;


/********************************************************
selectProblem
Parameters: int a
Returns a selected puzzle as a string
********************************************************/
char* selectProblem(int a) {
    char* puzzle[MAX];
    puzzle[0] = "MIGHT + MATH = HAPPY";
    puzzle[1] = "BASE + BALL = GAMES";
    puzzle[2] = "SEND + MORE = MONEY";
    puzzle[3] = "CRASH + HACKER = REBOOT";
    puzzle[4] = "CPU + ERROR + ROM = MODEM";
    puzzle[5] = "BASIC + LOGIC = PASCAL";
    puzzle[6] = "C + CPP = PLI";
    puzzle[7] = "SIX + SEVEN + SEVEN = TWENTY";
    puzzle[8] = "EAGER + MATH = TREAT";
    puzzle[9] = "BOB x BOB = MARLEY";
    char *prob = puzzle[a];
    return prob;
}

/********************************************************
selectedAnswer
Parameters: int a
Returns a selected answer for the corresponding puzzle
in selectPuzzle.
********************************************************/
char* selectedAnswer(int a){
    char* answers[MAX];
    answers[0]="65873 + 6237 = 72110";
    answers[1]="7483 + 7455 = 14938";
    answers[2]="9567 + 1085 = 10652";
    answers[3]="36845 + 583926 = 620771";
    answers[4]="742 + 58808 + 806 = 60356";
    answers[5]="60852 + 47352 = 108204";
    answers[6]="8 + 899 = 907";
    answers[7]="650 + 68782 + 68782 = 138214";
    answers[8]="14713 + 8429 = 23142";
    answers[9]="353 x 353 = 124609";
    char* ans = answers[a];
    return ans;
}

/********************************************************
findLetter
Parameters:  crypt lets[], int length, char find
Searches array of crypt structs for find. Returns -1 if not
found or the index number if found.
********************************************************/
int findLetter(crypt lets[], int length, char find){
    int i;
    for(i=0; i<length; i++){
        if (lets[i].symbol == find){
            return i;
        }
    }
    return -1;
}

/********************************************************
findLetterValue
Parameters:  crypt lets[], int length, char find
Searches array of crypt structs for find. Returns value
of letter if found. Otherwise returns -2
********************************************************/
int findLetterValue(crypt lets[], int length, char find){
    int i;
    for(i=0; i<length; i++){
        if (lets[i].symbol == find){
            return lets[i].value;
        }
    }
    return -2;
}

/********************************************************
printCrypt
Parameters: crypt lets[], int length
Cycles through an array of crypt structs and prints the
symbol and value so long as the value is between 0 and 9
as cryptarithms values will never exceed 9.
********************************************************/
void printCrypt(crypt lets[], int length){
    int a;

    for(a=0; a<length; a++){
        if (lets[a].value >=0 && lets[a].value <=9 && isalpha(lets[a].symbol)){
            printf("%c=%d  ", lets[a].symbol, lets[a].value);
        }
    }
    printf("\n");

    return;
}

/********************************************************
checkGuess
Parameters: char* theguess (user's guess), int pNum (puzzle number)
Returns 1 if guess works or 0 if it doesn't.
Verifies answer by ensuring each letter is assigned a single
digit value and then builds each integer and performs
the associated arithmetic to confirm.
********************************************************/
int checkGuess(char* theguess, char* problem){
    int i, c;
    int int1=-1, int2=-1, int3=-1, int4=-1, j=0, count=0, term=0;
    char puzz[strlen(problem) + 1];
    strcpy(puzz, problem);
    int pLength = strlen(puzz);
    crypt letters[pLength];
    char temp;
    char function;
    int inLetters;
    int tempSP[GMAX];

    // TODO: make dictionary to assign key-value and lookup if time
    
    // verify each letter is assigned a single digit
    for (i=0; i<pLength; i++){
        // Skip if space, +, x, or =.
        char tempP = puzz[i];
        if (tempP == ' '){ 
            continue; 
        }
        else if (tempP == '+' || tempP == 'x'){
            j += 1;
            function = tempP; // save the type of operation

            // compute the integer and save
            // TODO: make separate function if time
            int tempD = 0;
            int multi = 1;
            for (c=(count-1); c >= term; c--){
                int tempE = letters[tempSP[c]].value;
                tempD += (tempE * multi);
                multi *= 10;
            }
            term = count;
            if (int1 == -1){ int1 = tempD; }
            else if (int2 == -1){ int2 = tempD; }
            else if (int3 == -1){ int3 = tempD; }

            continue;
        }
        else if (tempP == '='){
            j += 1;
            // compute the integer and save as int
            int tempD = 0;
            int multi = 1;
            for (c=(count-1); c >= term; c--){
                int tempE = letters[tempSP[c]].value;
                tempD += (tempE * multi);
                multi *= 10;
            }
            term = count;
            if (int1 == -1){ int1 = tempD; }
            else if (int2 == -1){ int2 = tempD; }
            else if (int3 == -1){ int3 = tempD; }
            continue;
        }
        
        char tempG = theguess[j];
        count += 1;
        int digG = (int)(tempG);
        digG -= 48;
        j += 1;

        inLetters = findLetter(letters, pLength, tempP);

        // Save if letter not found. Otherwise ensure digits are equal.
        if (inLetters == -1){
            letters[i].symbol = tempP;
            letters[i].value = digG;
            tempSP[count-1] = i;
        }
        else{
            if (digG != letters[inLetters].value){ return 0; }
            tempSP[count-1] = inLetters;
        }
    }

    // convert int4 into appropriate number of integers
    int4 = 0;
    int multi = 1;
    for (c=(count-1); c >= term; c--){
        int tempE = letters[tempSP[c]].value;
        int4 += (tempE * multi);
        multi *= 10;
    }

    printf("int1=%d, int2=%d, int4=%d\n", int1, int2, int4);
    
    // check solution based on saved function character
    if (function == '+'){
        int check = int1 + int2;
        if (int3 != -1){ check += int3; }
        if (check != int4) { return 0; }
    }
    else {
        int check = int1 * int2;
        if (int3 != -1){ check *= int3; }
        if (check != int4) { return 0; }
    }

    // print letters and return with true
    printCrypt(letters, pLength);

    return 1;
}

int main(void) {
    // variables
    char* welcome = "\nWelcome to Chantel's Cryptarithm Game!";
    char* instructions = "You will be shown an arithmetic problem\n"
                         "where all of the digits have been replaced\n"
                         "with letters. Each letter represents a digit from\n"
                         "0 to 9. Once you've figured out the code, you\n"
                         "can enter the corresponding digits. Note: once input\n"
                         "is typed, hit the space bar to enter.";
    char* example = "Here is an example (press 1 to view answer or any other character to skip):\nMATH + MATH = HABIT";
    char* answer = "MATH + MATH = HABIT\n A=5 B=0 H=1 I=4 M=7 T=2\n 7521 + 7521 = 15042";
    // char* playorsolve = "Press 1 to play or 2 to enter a puzzle to solve or any other character to exit.";
    char* playorexit = "Press 1 to play or any other character to exit.";
    char* solveorexit = "Press 1 to enter another or any other character to exit.";
    char input;
    char mainInput;
    char mainInput2;
    int compStrings;
    int stopGuess; 
    int correct;
    int play = 0;
    int inputLength;
    char* selectedP;
    char* selectedA;
    char guess[GMAX];
    char stop[1] = "1";
    int test = 2;


    // introduction
    printf("%s\n\n", welcome);
    printf("%s\n\n", instructions);
    printf("%s\n", example);
    scanf("%c", &mainInput);
    fflush(stdin);

    if (mainInput=='1'){
        printf("%s\n", answer);
    }
    else {
        printf("Awesome, you already know how to play!\n");
    }

    mainInput = '1';
    while (mainInput=='1'){
        while (play < MAX){
            stopGuess = 0;
            printf("\nLet's play!\n");
            
            // select problem, inc play count, display puzzle
            selectedP = selectProblem(play);
            selectedA = selectedAnswer(play);
            play += 1;
            printf("%s\n", selectedP);

            // while user is guessing
            while (stopGuess == 0){
                // obtain guess
                printf("Enter your guess as 1+2=3 (no spaces) or enter 1 to view an answer:");
                scanf("%s", guess);
                fflush(stdin);
                printf("Entered: %s\n", guess);
                    
                // if guess == 1, show answer
                compStrings = strcmp(stop, guess);

                if (compStrings == 49){
                    stopGuess = 1;
                    printf("One answer is: %s\n", selectedA);
                }
                    
                // otherwise check guess
                else{
                    correct = checkGuess(guess, selectedP);
                    if (correct == 1){
                        printf("THAT WORKS! YOU'RE AWESOME!\n");
                        stopGuess = 1;
                    }
                    else {
                        printf("Try Again!\n");
                    }
                }
            }
        
            // if play == MAX, no more puzzles
            if (play == MAX){
                printf("There are no more puzzles, sorry!\n");
            }

            // otherwise ask if they want to continue
            else{
                printf("%s\n", playorexit);
                scanf("%s", &mainInput2);
                fflush(stdin);
                compStrings = strcmp(stop, &mainInput2);
                if (compStrings == -1) {
                  play = 10;
                  mainInput = '2';
                }
            }
                
        }
    }
    

    // terminate program
    printf("\nHope you had fun!\n");

  return 0;
}