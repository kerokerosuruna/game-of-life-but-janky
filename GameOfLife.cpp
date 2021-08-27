#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL)); //random
    char board[20][20]; //game board filled with - to represent dead sqaures
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            board[y][x] = '-';
        }
    }
    int state = 0; //state machine thing
    int times = 1; //number of placed tiles
    int num; //number of tiles
    while (state == 0)//general i/o
    {
        cout << "How many tiles do you want to fill up? (number between 1 and 20)\n";
        cin >> num;
        if (num > 20 || num < 0)
        {
            cout << "Invalid number of tiles, try again.\n";
        }
        else
        {
            state = 1;
            break;
        }
    }
    while (state == 1) //inputing pixels
    {
        cout << "Where would you like to place pixel " << times << "?\n(input it as 2 coordinates between 0 and 19 inclusive, seperated by a space, ie: 0 19)\n" << "Alternatively, set one of the coordinates to 100 to randomly generate the rest of the points.\n";
        int x, y;
        scanf_s("%d%d", &x, &y); //omg scanf
        if (x == 100 || y == 100)
        {
            for (int i = times; i <= num; i++)
            {
                bool good = false;
                while (good == false)
                {
                    y = rand() % 20;
                    x = rand() % 20;
                    if (board[y][x] == '0') //prevents them from placing a pixel on filled space
                    {
                        good = false;
                    }
                    else
                    {
                        board[y][x] = '0';
                        good = true;
                    }
                }
            }
            state = 2;
            break;
        }
        else if (x >= 0 && x < 20)
        {
            if (y >= 0 && y < 20)
            {
                if (board[y][x] == '-') //checking to see if its a valid space and what not
                {
                    board[y][x] = '0';
                    if (times == num)
                    { 
                        state = 2;
                        break;
                    }
                    else
                    {
                        times += 1;
                    }
                }
                else
                {
                    cout << "That spot already has a pixel there, try again\n";
                    x = 0;
                    y = 0;
                }
            }
            else
            {
                cout << "Invalid y value, try again\n";
                x = 0;
                y = 0;
            }
        }
        else
        {
            cout << "Invalid x value, try again\n";
            x = 0;
            y = 0;
        }
    }
    while (state == 2)//actual game
    {
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                cout << board[y][x];
            }
            cout << endl;
        }
        char newboard[20][20]; //second array that stores the new generation to allow me to update things without it effecting unupdated parts
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                newboard[y][x] = '-';
            }
        }
        cout << "This is the board, press any key to continue to the next generation, press escape to quit\n\n";
        int in = _getch(); //i dont know a better way
        if (in == 27)
        {
            cout << "Ending the program, press any key to exit...";
            _getch(); //any key. There is a warning here but that can be ignored because the value doesnt need to be read, just waiting for an input
            return 0;
        }
        else
        {
            for (int y = 0; y < 20; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    if (board[y][x]== '-') //dead
                    {
                        int neighbours = 0;
                        int a = 0, b = 0;
                        for (int i = 0; i < 8; i++)
                        {
                            switch (i)
                            {
                                case (0):
                                {
                                    a = y - 1;
                                    b = x - 1;
                                    break;
                                }
                                case (1):
                                {
                                    a = y - 1;
                                    b = x;
                                    break;
                                }
                                case (2):
                                {
                                    a = y - 1;
                                    b = x+1;
                                    break;
                                }
                                case (3):
                                {
                                    a = y;
                                    b = x-1;
                                    break;
                                }
                                case (4):
                                {
                                    a = y;
                                    b = x+1;
                                    break;
                                }
                                case (5):
                                {
                                    a = y+1;
                                    b = x-1;
                                    break;
                                }
                                case (6):
                                {
                                    a = y+1;
                                    b = x;
                                    break;
                                }
                                case (7):
                                {
                                    a = y+1;
                                    b = x+1;
                                    break;
                                }
                            }
                            if (a == -1)
                            {
                                a = 19;
                            }
                            else if (a == 20)
                            {
                                a = 0;
                            }
                            if (b == -1)
                            {
                                b = 19;
                            }
                            else if (b == 20)
                            {
                                b = 0;
                            }
                            if (board[a][b] == '0')
                            {
                                neighbours += 1;
                            }
                        }
                        if (neighbours == 3)
                        {
                            newboard[y][x] = '0';
                        }
                        else
                        {
                            newboard[y][x] = '-';
                        }
                    }
                    else //alive
                    {
                        int neighbours = 0;
                        int a = 0, b = 0;
                        for (int i = 0; i < 8; i++)
                        {
                            switch (i)
                            {
                                case (0):
                                {
                                    a = y - 1;
                                    b = x - 1;
                                    break;
                                }
                                case (1):
                                {
                                    a = y - 1;
                                    b = x;
                                    break;
                                }
                                case (2):
                                {
                                    a = y - 1;
                                    b = x + 1;
                                    break;
                                }
                                case (3):
                                {
                                    a = y;
                                    b = x - 1;
                                    break;
                                }
                                case (4):
                                {
                                    a = y;
                                    b = x + 1;
                                    break;
                                }
                                case (5):
                                {
                                    a = y + 1;
                                    b = x - 1;
                                    break;
                                }
                                case (6):
                                {
                                    a = y + 1;
                                    b = x;
                                    break;
                                }
                                case (7):
                                {
                                    a = y + 1;
                                    b = x + 1;
                                    break;
                                }
                            }
                            if (a == -1)
                            {
                                a = 19;
                            }
                            else if (a == 20)
                            {
                                a = 0;
                            }
                            if (b == -1)
                            {
                                b = 19;
                            }
                            else if (b == 20)
                            {
                                b = 0;
                            }
                            if (board[a][b] == '0')
                            {
                                neighbours += 1;
                            }
                        }
                        if (neighbours < 2 || neighbours > 3)
                        {
                            newboard[y][x] = '-';
                        }
                        else
                        {
                            newboard[y][x] = '0';
                        }
                    }
                }
            }
            copy(&newboard[0][0], &newboard[0][0] + 20 * 20, &board[0][0]); //copy(mem of array, mem of array added to size, mem of array 2) i think
        }
    }
}