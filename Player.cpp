#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food *currFood)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    food = currFood;

    // more actions to be included
    playerPosList = new objPosArrayList();
    playerPos = new objPos(10, 10, '*');
    playerPosList->insertHead(*playerPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
    playerPosList = NULL;
    delete playerPos;
    playerPos = NULL;
}

objPosArrayList* Player::getPlayerPosList()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    
    char input = (*mainGameMechsRef).getInput();
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case 'w':
                if(myDir != DOWN) {
                    myDir = UP;
                }
                break;
            case 'a':
                if(myDir != RIGHT) {
                    myDir = LEFT;
                }
                break;
            case 's':
                if(myDir != UP) {
                    myDir = DOWN;
                }
                break;
            case 'd':
                if(myDir != LEFT) {
                    myDir = RIGHT;
                }
                break;

            default:
                break;
        }
        (*mainGameMechsRef).setInput(0);
    }
}

bool Player::checkSelfCollision()
{
    objPos bodyPart;

    for(int i=1; i< playerPosList->getSize(); i++)
    {
        playerPosList->getElement(bodyPart, i);
        if (playerPos->isPosEqual(&bodyPart))
        {
            return true;
        }
    }


    return false;
}

void Player::movePlayer()
{
    if (checkSelfCollision())
    {
        (*mainGameMechsRef).setExitTrue();
        (*mainGameMechsRef).setLoseFlag();

        return;
    }

    // PPA3 Finite State Machine logic
    switch(myDir) {
        case UP:
            playerPos->y--;
            if(playerPos->y == 0) playerPos->y = (*mainGameMechsRef).getBoardSizeY() - 2;
            break;
        case DOWN:
            playerPos->y++;
            playerPos->y %= (*mainGameMechsRef).getBoardSizeY() - 1;
            if(playerPos->y < 1) playerPos->y = 1;
            break;
        case LEFT:
            playerPos->x--;
            if(playerPos->x == 0) playerPos->x = (*mainGameMechsRef).getBoardSizeX() - 2;
            break;
        case RIGHT:
            playerPos->x++;
            playerPos->x %= (*mainGameMechsRef).getBoardSizeX() - 1;
            if(playerPos->x < 1) playerPos->x = 1;
            break;
    }

    objPos foodPos;
    food->getFoodPos(foodPos);

    if(myDir != STOP) {
        if(playerPos->isPosEqual(&foodPos)) {
            objPos *next = new objPos(playerPos->x, playerPos->y, '*');
            playerPosList->insertHead(*next);
            delete next;
            next = NULL;

            food->generateFood(*playerPosList);
        }
        else {
            objPos *next = new objPos(playerPos->x, playerPos->y, '*');
            playerPosList->insertHead(*next);
            delete next;
            next = NULL;

            playerPosList->removeTail();
        }
    }
    
}

