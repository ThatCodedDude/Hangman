#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void wait(int);
void ClrScreen();

void wait(int Secs){

  Sleep(Secs * 1000);

}


void ClrScreen(){
  
  system("cls");

}
