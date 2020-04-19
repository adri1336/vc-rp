enum TutorialFlags:(<<= 1)
{
    TUTORIAL_1 = 1, //open inv close, stats
    TUTORIAL_2, //sube taxi ve a tienda
    TUTORIAL_3, //compra gps movil
    TUTORIAL_4, //movil
    TUTORIAL_5, //gps
    TUTORIAL_6, //clothes
    TUTORIAL_7 //car
};

new bool:pTutorialCheck[MAX_PLAYERS],
    TutorialFlags:pInTutorial[MAX_PLAYERS],
    Timer:pTutorialTimer[MAX_PLAYERS] = {Timer:-1, ...},
    bool:pCarTutorialDoors[MAX_PLAYERS];

#define MAX_TUTORIAL_BOX_STEPS 5
new bool:pTutorialSteps[MAX_PLAYERS][MAX_TUTORIAL_BOX_STEPS];

//tds
#define TUTORIAL_BOX_X 20.0
#define TUTORIAL_BOX_Y 145.0
#define TUTORIAL_BOX_SX 140.0
#define TUTORIAL_BOX_MARGIN 7.0
#define TUTORIAL_BOX_PADDING 3.0
#define TUTORIAL_BOX_LY 1.052443

new Float:TutorialBoxLetterSizeX;

new PlayerText:pTutorialBoxTd[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
    PlayerText:pTutorialStepTd[MAX_PLAYERS][MAX_TUTORIAL_BOX_STEPS][2];