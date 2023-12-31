#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* currFood);
        ~Player();

        objPosArrayList* getPlayerPosList(); // Upgrade this in iteration 3.
        void updatePlayerDir();
        void movePlayer();
        bool checkSelfCollision();
        int getScore();
        void updateScore(int x);

    private:
        objPosArrayList *playerPosList;   // Upgrade this in iteration 3.       
        enum Dir myDir;
        objPos *playerPos;
        int score = 0;
        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* food;
};

#endif