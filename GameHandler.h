// Header Files and Macros //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>

#include "NewUtilities.h"

// Function Declarations, User-Defined types, Global Variables//

void StartScreen();
void Instructions();
void Draw(int, int);
int Random(int);
void Game();

int Wins = 0, Loses = 0;

const char* Words[] = {"Hello", "Friend", "Nice"}; // All the Words in the Game

bool InGame = false;

enum InstructionInputs{

  YES = 'Y',
  NO = 'N',

};
typedef enum DrawTypes{

  HANG,
  STICK,

}DrawTypes;

typedef struct NewGameInfo{

 int Lives;
 int Current;
 char LettersFound[100];
 char* Word;


}NewGameInfo;

// Function Definitions //

void StartScreen(){

 printf("\t------------------------\n");
 printf("\t Hangman The Game!\n");
 printf("\t------------------------\n");
 printf("\t Coded By: ThatCodedDude\n");
 printf("\t------------------------\n");

 printf("\n\n\t\t\tWins: %d\n\t\t\tLoses: %d\n\n", Wins, Loses);

 printf("New Game: Press A\n");
 printf("Instructions: Press B\n");

  while(1){

    int Input = getch();

    if(tolower(Input) == tolower('A') || tolower(Input) == tolower('B')){

        if(tolower(Input) == tolower('A')){

           Game();
           break;

        }else if(tolower(Input) == tolower('B')){

           Instructions();
           break;

        }
    }

  }

}

void Instructions(){

  ClrScreen();

  printf("\nHangman is a game programmed by ThatCodedDude!!");
  printf("\n\nThe objective is simple, try to guess the word within the blank spaces, if you get too many wrong, the stickman will be drawn more and more, until, it's fully drawn, to which you will lose after too many wrong attempts");

  printf("\n\nDo you understand??");

  printf("\nYes: Y\tNo: N\n");

  while(1){

    int Input = getch();

    if(tolower(Input) == tolower('Y')){

    if(InGame == false){

        ClrScreen();
        StartScreen();
        break;

    }else{

       Game();
       break;

    }

  }else if(tolower(Input) == tolower('N')){

    printf("\nToo bad, lol XD");

    wait(3);

    if(InGame == false){

        ClrScreen();
        StartScreen();
        break;

    }else{

       Game();
       break;

    }

  }

    wait(0.1);
   }
}

int Random(int MaxNum){

   srand(time(0)); // Initializes Random?? I think...

   int Output = rand() % MaxNum;

   return Output;

}

void Draw(int Type, int Lives){

   // This Code is finna be messy XD

  char* HangDraw = "|-----------\n"
                   "|          |\n"
                   "|          |\n"
                   "|          |\n"
                   "|\n"
                   "|\n"
                   "|\n"
                   "|\n"
                   "|\n"
                   "|\n"
                   "|\n";

 char* StickDraw1 = "|-----------\n"
                    "|          |\n"
                    "|          |\n"
                    "|          |\n"
                    "|          O\n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n";

 char* StickDraw2 = "|-----------\n"
                    "|          |\n"
                    "|          |\n"
                    "|          |\n"
                    "|          O\n"
                    "|          |\n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n";

 char* StickDraw3 = "|-----------\n"
                    "|          |\n"
                    "|          |\n"
                    "|          |\n"
                    "|          O\n"
                    "|         /|\n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n";

 char* StickDraw4 = "|-----------\n"
                    "|          |\n"
                    "|          |\n"
                    "|          |\n"
                    "|          O\n"
                    "|         /|\\\n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n";
 char* StickDraw5 = "|-----------\n"
                    "|          |\n"
                    "|          |\n"
                    "|          |\n"
                    "|          O\n"
                    "|         /|\\\n"
                    "|         / \n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n";

 char* StickDraw6 = "|-----------\n"
                    "|          |\n"
                    "|          |\n"
                    "|          |\n"
                    "|          O\n"
                    "|         /|\\\n"
                    "|         / \\\n"
                    "|\n"
                    "|\n"
                    "|\n"
                    "|\n";

 switch(Type){

   case HANG:

       printf("%s", HangDraw);
       break;

   case STICK:

       if(Lives == 5){

         printf("%s", StickDraw1);
         break;

       }else if(Lives == 4){

         printf("%s", StickDraw2);
         break;

       }else if(Lives == 3){

         printf("%s", StickDraw3);
         break;

       }else if(Lives == 2){

         printf("%s", StickDraw4);
         break;

       }else if(Lives == 1){

         printf("%s", StickDraw5);
         break;

       }else if(Lives == 0){

         printf("%s", StickDraw6);
         break;

       }

 }
}

void Game(NewGameInfo* PTInfo){ // Put the struct as parameters, to save the data

    static Counter = 0;

  if(InGame == false){

    InGame = true;

    ClrScreen();

    NewGameInfo* GameInfo = malloc(sizeof(*GameInfo));

    GameInfo->Lives = 6;
    GameInfo->Current = 1;
    int RandomNumber = Random(sizeof(Words) / sizeof(char*));
    char* ChosenWord = Words[RandomNumber];

    GameInfo->Word = ChosenWord;

    char StringSpliter[100]; strcpy(StringSpliter, ChosenWord);

    Draw(HANG, 0);
    printf("Lives: %d", GameInfo->Lives);

    printf("\n\t\tWord: ");

    for(int i = 0; i < strlen(ChosenWord); i++){
        printf("_");
    }

    printf("\n\nInput a Letter: ");

    char Letter;
    Letter = getchar();
    fflush(stdin); // Clears Buffer

    bool Checker = false;

    for(int i = 0; i < strlen(ChosenWord); i++){
        if(tolower(StringSpliter[i]) == tolower(Letter)){
            Checker = true;
        }
    }

    if(Checker == true){

      GameInfo->LettersFound[Counter] = Letter;
      GameInfo->Current++;

      Counter++;

    }else{

      GameInfo->Lives--;

    }

    Game(GameInfo);

  }else{

    ClrScreen();

    char StringSpliter[100]; strcpy(StringSpliter, PTInfo->Word);

    if(PTInfo->Lives == 6){
        Draw(HANG, 0);
    }else{
        Draw(STICK, PTInfo->Lives);
    }
    printf("Lives: %d", PTInfo->Lives);

    printf("\n\t\tWord: ");

    char NewArray[100] = "";

     for(int i = 0; i < strlen(PTInfo->Word); i++){

        for(int k = 0; k <= Counter; k++){

            if(tolower(StringSpliter[i]) == tolower(PTInfo->LettersFound[k])){

                NewArray[i] = StringSpliter[i];

                k = Counter;

            }else{

               NewArray[i] = '_';

            }

        }
      printf("%c", NewArray[i]);

    }

    printf("\n\nInput a Letter: ");


    if(PTInfo->Lives == 0){

        wait(4);

        ClrScreen();

        printf("GAME OVER...");

        wait(3);

        ClrScreen();

        Loses++;

        free(PTInfo);
        Counter = 0;
        InGame = false;

        StartScreen();

        return;

    }else if(strlen(PTInfo->Word) == PTInfo->Current){

        wait(4);

        ClrScreen();

        printf("Congratulations! You won!");

        wait(3);

        ClrScreen();

        Wins++;

        free(PTInfo);
        Counter = 0;
        InGame = false;

        StartScreen();

        return;

    }

    char Letter;
    Letter = getchar();
    fflush(stdin); // Clears Buffer

    bool Checker = false;

    for(int i = 0; i < strlen(PTInfo->Word); i++){
        if(tolower(StringSpliter[i]) == tolower(Letter)){
            Checker = true;
        }
    }

    if(Checker == true){

      PTInfo->LettersFound[Counter] = Letter;
      PTInfo->Current++;
      Counter++;


    }else{

      PTInfo->Lives--;

    }

      Game(PTInfo);

  }

}

