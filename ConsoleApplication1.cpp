// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool Gameover;
int height;
int width;

struct Obiect {
    int x;
    int y;
};

enum Directii {
    STOP,
    LEFT,
    RIGHT,
    DOWN,
    UP,
};

Obiect snake;
Obiect fruit;
Directii dir;
Obiect tail[200];
int ntail = 0;
int score = 0;

void Setup() {
    Gameover = false;
    height = 15;
    width = 30;
    snake.x = 5;
    snake.y = 5;
    fruit.x = rand() % (width-3) + 1;
    fruit.y = rand() % (height-3) + 1;
    dir = STOP;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width; i++)
        cout << "#";
    cout << "\n";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
                cout << "#";
            else
                if (i == snake.y && j == snake.x)
                    cout << "O";
                else
                    if (i == fruit.y && j == fruit.x)
                        cout << "*";
                    else {
                        bool ver = false;
                        for (int k = 0; k < ntail; k++) {
                            if (tail[k].x == j && tail[k].y == i) {
                                ver = true;
                                break;
                            }
                        }
                        if(ver)
                            cout << "o";
                        else
                            cout << " ";
                    }
        }
        cout << "\n";
    }

    for (int i = 0; i < width; i++)
        cout << "#";
    cout << "\n";
    cout << "Score: " << score;
}

void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a': if (dir != RIGHT)dir = LEFT; break;
        case 's': if (dir != UP)dir = DOWN; break;
        case 'd': if (dir != LEFT)dir = RIGHT; break;
        case 'w': if (dir != DOWN)dir = UP; break;
        }
    }

}

void Logic() {
    int xprev, yprev;
    xprev = snake.x;
    yprev = snake.y;

    switch (dir) {
    case LEFT:snake.x--;
        break;
    case RIGHT:snake.x++;
        break;
    case DOWN:snake.y++;
        break;
    case UP:snake.y--;
        break;
    }

    if (fruit.x == snake.x && fruit.y == snake.y) {
        score++;
        ntail++;
        bool verand = true;
        while (verand) {
            verand = false;
            fruit.x = rand() % (width - 3) + 1;
            fruit.y = rand() % (height - 3) + 1;
            for (int i = 0; i < ntail; i++)
                if (tail[i].x == fruit.x && tail[i].y == fruit.y)
                    verand = true;
        }
    }

    for (int i = 0; i < ntail; i++) {
        int aux1 = tail[i].x;
        int aux2 = tail[i].y;
        tail[i].x = xprev;
        tail[i].y = yprev;
        xprev = aux1;
        yprev = aux2;

    }

    for (int k = 1; k < ntail; k++) {
        if (tail[k].x == snake.x && tail[k].y == snake.y) {
            Gameover = true;
            break;
        }
    }

    if (snake.x == 0 || snake.x == width-1)
        Gameover = true;
    if (snake.y == -1 || snake.y == height)
        Gameover = true;

}

int main()
{
    Setup();

    while (!Gameover) {
        Input();
        Logic();
        Draw();
        if (dir == UP || dir == DOWN)
            Sleep(80);
        else
            Sleep(40);
            
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
