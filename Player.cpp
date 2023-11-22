#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.x = 10;
    playerPos.y = 10;
    playerPos.symbol = '*';
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos = playerPos;
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

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch(myDir) {
        case UP:
            playerPos.y--;
            if(playerPos.y == 0) playerPos.y = (*mainGameMechsRef).getBoardSizeY() - 2;
            break;
        case DOWN:
            playerPos.y++;
            playerPos.y %= (*mainGameMechsRef).getBoardSizeY() - 1;
            if(playerPos.y < 1) playerPos.y = 1;
            break;
        case LEFT:
            playerPos.x--;
            if(playerPos.x == 0) playerPos.x = (*mainGameMechsRef).getBoardSizeX() - 2;
            break;
        case RIGHT:
            playerPos.x++;
            playerPos.x %= (*mainGameMechsRef).getBoardSizeX() - 1;
            if(playerPos.x < 1) playerPos.x = 1;
    }
}

