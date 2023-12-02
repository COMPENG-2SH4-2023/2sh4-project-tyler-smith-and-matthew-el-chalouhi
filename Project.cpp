#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"


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
Food *food;
objPos foodPos;

int main(void)
{

    Initialize();

    while((*gm).getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        if ((*gm).getExitFlagStatus() == true) 
        {
            break;
        }
        DrawScreen();
        LoopDelay();
    }

    MacUILib_clearScreen();   

    MacUILib_printf("\nGame Over!\n \nFinal Score: %d \n \n \n", player->getScore());

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // exitFlag = false;
    gm = new GameMechs();
    food = new Food(gm);
    player = new Player(gm, food);
    food->generateFood(*(player->getPlayerPosList()));
    MacUILib_printf("done init");

}

// Get updated keyboard input from player
void GetInput(void)
{
    if(MacUILib_hasChar()) gm->setInput(MacUILib_getChar());
    else gm->setInput(0);

    if(gm->getInput() == ' ') gm->setExitTrue();
}

// Update player direction and motion based on input
void RunLogic(void)
{
    (*player).updatePlayerDir();
    (*player).movePlayer();
    
}

// Draw gameboard
void DrawScreen(void)
{
    MacUILib_clearScreen();   

    objPos *stensil = new objPos(0, 0, '#');
    int sizeX = (*gm).getBoardSizeX();
    int sizeY = (*gm).getBoardSizeY();
    food->getFoodPos(foodPos);
    objPos nextPlayerItem;

    // Loop through all board positions
    int i, j, k;
    for(i = 0; i < sizeY; i++) {
        for(j = 0; j < sizeX; j++) {
            objPos *curr = new objPos(j, i, 0);

            bool contFlag = false;

            // If current position is equal to a player segment print the segment symbol
            for(k = 0; k < (*(player->getPlayerPosList())).getSize(); k++) {
                (*(player->getPlayerPosList())).getElement(nextPlayerItem, k);
                if(nextPlayerItem.isPosEqual(curr)) {
                    MacUILib_printf("%c", nextPlayerItem.getSymbol());
                    contFlag = true;
                }
            }

            if(contFlag) {
                delete curr;
                curr = NULL;
                continue;
            } 

            // If this position is a boarder position print the boarder symbol
            if(i == 0 || i == sizeY - 1 || j == 0 || j == sizeX - 1) {
                if(j == sizeX - 1) MacUILib_printf("%c\n", stensil->getSymbol());
                else MacUILib_printf("%c", stensil->getSymbol());
            }
            // If this is position is the food position print the food
            else if(foodPos.isPosEqual(curr)) MacUILib_printf("%c", foodPos.getSymbol());
            else if(j == sizeX - 1) MacUILib_printf("%c\n", stensil->getSymbol());

            // Print space if not a 'special' position
            else MacUILib_printf(" ");

            delete curr;
            curr = NULL;

            
        }
    }
    
    int score = player->getScore();

    MacUILib_printf("\nScore: %d", score); //Prints the score.
    
    delete stensil;
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

// Deallocate all heap objects
void CleanUp(void)
{

    delete gm;
    gm = NULL;
    delete player;
    player = NULL;
    delete food;
    food = NULL;

    MacUILib_uninit();
}
