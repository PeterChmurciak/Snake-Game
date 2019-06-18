#include <iostream>                                       // To be able to use cout,endl
#include <cstdlib>                                        // To be able to use rand(),srand()
#include <ctime>                                          // To be able to use time()
#include <conio.h>                                        // To be able to use _kbhit(),_getch()
#include <windows.h>                                      // To be able to use system(),Sleep()

bool gameOver;                                            // Flag to end the game
const int fieldWidth = 30;                                // Size and area of playing field for snake
const int fieldHeight = 15;
const int fieldArea = fieldWidth*fieldHeight;
int headX, headY, fruitX, fruitY, score;                  // Coordinates of snakes head,fruit and score counter
enum eDirection {STOP,LEFT,RIGHT,UP,DOWN} direction;      // Variable to store current direction
int tailX[fieldArea],tailY[fieldArea];                    // Arrays to store tail segment coordinates
int tailLength = 0;                                       // Number of tail segments
int slowDown = 50;                                        // Variable to slow down snake movement

void Setup()                                              // Initialization of variables
{
    gameOver = false;
    direction = STOP;
    headX = fieldWidth/2;                                 // Start in the middle of field
    headY = fieldHeight/2;
    srand(time(NULL));                                    // Random initial position of fruit
    fruitX = 1+rand()%fieldWidth;
    fruitY = 1+rand()%fieldHeight;
    score = 0;
}

void Draw()                                                              // Drawing the content into console window
{
    system("cls");                                                       // Clear the console window
    std::cout<<"Press W,S,A,D to move. Press X to end the game.\n"<<std::endl;
    for(int i=0; i<fieldHeight+2; i++)                                   // Iterate through rows of console window
    {
        for(int j=0; j<fieldWidth+2; j++)                                // Iterate through columns of console window
        {
            if(i==0 || i==fieldHeight+1 || j==0 || j==fieldWidth+1)      // Draw field borders
                std::cout<<'#';
            else if(j==headX && i==headY)                                // Draw snakes head
                std::cout<<'O';
            else if(j==fruitX && i==fruitY)                              // Draw fruit
                std::cout<<'F';
            else
            {
                bool tailPrint = false;
                for(int k=1; k<=tailLength; k++)                         // Iterate through tail segments
                {
                    if(j==tailX[k] && i==tailY[k])                       // Draw snakes tail
                    {
                        std::cout<<'o';
                        tailPrint = true;
                    }
                }
                if(!tailPrint)                                           // Draw empty spaces
                    std::cout<<' ';
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<"\nScore: "<<score<<std::endl;
}

void Input()                       // Getting input from user
{
    if(_kbhit())                   // If key on keyboard is pressed
    {
        switch(_getch())           // Make a decision based on which key is pressed
        {
        case 'a':
            direction = LEFT;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'w':
            direction = UP;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()                          // Controlling the movement of snake
{
    tailX[0] = headX;
    tailY[0] = headY;
    for(int i=tailLength; i>0; i--)   // Moving each tail segment into next position
    {
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }

    switch(direction)                 // Move snakes head based on currently pressed key
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    }

    if(headX<=0)                        // Ability to warp between upper/lower and left/right wall
        headX = fieldWidth;
    else if(headX>=fieldWidth+1)
        headX = 1;
    else if(headY<=0)
        headY = fieldHeight;
    else if(headY>=fieldHeight+1)
        headY = 1;

    if(headX==fruitX && headY==fruitY)  // If fruit has been eaten
    {
        score++;
        srand(time(NULL));              // Generate new fruit position
        fruitX = 1+rand()%fieldWidth;
        fruitY = 1+rand()%fieldHeight;
        tailLength++;                   // Add a new tail segment
        if(slowDown>0)                  // Speed up snake a little
            slowDown--;
    }

    for(int j=1; j<=tailLength; j++)    // Detect collision with tail
    {
        if(headX==tailX[j] && headY==tailY[j])
            gameOver = true;
    }
}

int main()
{
    Setup();             // Initialization of variables
    while(!gameOver)
    {
        Draw();          // Drawing the content into console window
        Input();         // Getting input from user
        Logic();         // Controlling the movement of snake
        Sleep(slowDown); // Slowing down the snakes movement
    }
    return 0;
}
