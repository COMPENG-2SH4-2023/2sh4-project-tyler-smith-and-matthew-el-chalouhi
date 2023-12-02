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
    // PPA3 input processing logic, update direction state based on keyboard input   
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

bool Player::checkSelfCollision() //COMPLETELY REWRITE -- CHECK IF NEXT POS DEPENDING ON DIRECTION == BODYPOS (DO NOT NEED TO DO THIS ANYMORE - TYLER)
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

// Update player position based on the diretion FSM.
void Player::movePlayer()
{

    // PPA3 Finite State Machine logic, updates next position position based on state
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


    // If next position is the same as the position of the food, do not remove from tail, increment score.
    objPos foodPos;
    food->getFoodPos(foodPos);
    if(myDir != STOP) {
        if(playerPos->isPosEqual(&foodPos)) {
            objPos *next = new objPos(playerPos->x, playerPos->y, '*');
            playerPosList->insertHead(*next);
            updateScore(1); // Updates score by +1
            delete next;
            next = NULL;

            food->generateFood(*playerPosList);
        }

        // Update list by adding next state to head, removing item from tail
        else {
            objPos *next = new objPos(playerPos->x, playerPos->y, '*');
            playerPosList->insertHead(*next);
            delete next;
            next = NULL;

            playerPosList->removeTail();
        }
    }

    // If updated head position is a collision with another body element, end the game.
    if (checkSelfCollision())
    {
        (*mainGameMechsRef).setExitTrue();
        (*mainGameMechsRef).setLoseFlag();
    }
    
}

//Additional Methods to get and update the score

int Player::getScore()
{
    return score;
}

void Player::updateScore(int x)
{
    score += x;
}

