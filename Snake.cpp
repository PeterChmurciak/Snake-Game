#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

bool gameOver;
const int fieldWidth = 30;
const int fieldHeight = 15;
const int fieldArea = fieldWidth*fieldHeight;
int headX, headY, fruitX, fruitY, score;
enum eDirection {STOP,LEFT,RIGHT,UP,DOWN} direction;
int tailX[fieldArea],tailY[fieldArea];
int tailLength = 0;

void Setup()
{
    gameOver = false;
    direction = STOP;
    headX = fieldWidth/2;
    headY = fieldHeight/2;
    srand(time(NULL));
    fruitX = 1+rand()%fieldWidth;
    fruitY = 1+rand()%fieldHeight;
    score = 0;
}

void Draw()
{
    system("cls");
    std::cout<<"Press W,S,A,D to move. Press X to end the game.\n"<<std::endl;
    for(int i=0; i<fieldHeight+2; i++)
    {
        for(int j=0; j<fieldWidth+2; j++)
        {
            if(i==0 || i==fieldHeight+1 || j==0 || j==fieldWidth+1)
                std::cout<<'#';
            else if(j==headX && i==headY)
                std::cout<<'O';
            else if(j==fruitX && i==fruitY)
                std::cout<<'F';
            else
            {
                bool tailPrint = false;
                for(int k=1; k<=tailLength; k++)
                {
                    if(j==tailX[k] && i==tailY[k])
                    {
                        std::cout<<'o';
                        tailPrint = true;
                    }
                }
                if(!tailPrint)
                    std::cout<<' ';
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<"\nScore: "<<score<<std::endl;
}

void Input()
{
    if(_kbhit())
    {
        switch(_getch())
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

void Logic()
{
    tailX[0] = headX;
    tailY[0] = headY;
    for(int i=tailLength; i>0; i--)
    {
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }

    switch(direction)
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

    if(headX<=0)
        headX = fieldWidth;
    else if(headX>=fieldWidth+1)
        headX = 1;
    else if(headY<=0)
        headY = fieldHeight;
    else if(headY>=fieldHeight+1)
        headY = 1;

    if(headX==fruitX && headY==fruitY)
    {
        score++;
        srand(time(NULL));
        fruitX = 1+rand()%fieldWidth;
        fruitY = 1+rand()%fieldHeight;
        tailLength++;
    }
}

int main()
{
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
    }
    return 0;
}
