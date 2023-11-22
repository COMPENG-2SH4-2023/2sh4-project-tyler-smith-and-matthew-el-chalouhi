#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

// bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player *player;
GameMechs *gm;
objPos playerPos;


int main(void)
{

    Initialize();

    while((*gm).getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // exitFlag = false;
    gm = new GameMechs();
    player = new Player(gm);
}

void GetInput(void)
{
    if(MacUILib_hasChar()) gm->setInput(MacUILib_getChar());
    else gm->setInput(0);

    if(gm->getInput() == ' ') gm->setExitTrue();
}

void RunLogic(void)
{
    (*player).updatePlayerDir();
    (*player).movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   

    objPos *stensil = new objPos(0, 0, '#');
    int sizeX = (*gm).getBoardSizeX();
    int sizeY = (*gm).getBoardSizeY();
    player->getPlayerPos(playerPos);

    int i, j;
    for(i = 0; i < sizeY; i++) {
        for(j = 0; j < sizeX; j++) {
            objPos *curr = new objPos(j, i, 0);
            if(i == 0 || i == sizeY - 1 || j == 0 || j == sizeX - 1) {
                if(j == sizeX - 1) MacUILib_printf("%c\n", stensil->getSymbol());
                else MacUILib_printf("%c", stensil->getSymbol());
            }
            else if(playerPos.isPosEqual(curr)) MacUILib_printf("%c", playerPos.getSymbol());
            else if(j == sizeX - 1) MacUILib_printf("%c\n", stensil->getSymbol());
            else MacUILib_printf(" ");

            delete curr;
            curr = NULL;
        }
    }
    delete stensil;
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete gm;
    gm = NULL;
    delete player;
    player = NULL;
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
