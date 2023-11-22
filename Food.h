#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food {
    private:
        objPos foodPos;
        GameMechs* mainGameMechsRef;
    public:

        Food(GameMechs *gm);
        ~Food();
        void generateFood(objPosArrayList blockedList);
        void getFoodPos(objPos &returnPos);
    
};