#include "GameMechs.h"


GameMechs::GameMechs()
{
    score = 0;
    loseFlag = false;
    exitFlag = false;
    boardSizeX = 30;
    boardSizeY = 15;
    clearInput();
}

GameMechs::GameMechs(int boardX, int boardY)
{
    score = 0;
    loseFlag = false;
    exitFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
    clearInput();
}

// do you need a destructor?
GameMechs::~GameMechs()
{

}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    setInput(0);
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore() {
    score++;
}
