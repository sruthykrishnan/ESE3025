//============================================================================
// Name        : guess_game.c
// Author      : Sruthy Krishnan
// Version     :
// Copyright   : Your copyright notice
// Description : Number guessing game using pthreads
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int num;
int count_1 = 0,count_2 =0;

int number()
{
    time_t r;
    srand((unsigned)time(&r));
    num = rand() % 1000;
    printf("The random generated number is %d \n",num);
}

void* binary_S(void* game)
{
    int lowRange = 0;
    int highRange = 1000;
    int guess = ((lowRange+highRange)/2);
    while(num != guess)
    {
        if((num > guess) && (num < highRange))
        {
            lowRange = guess;
        }
        else if((num>lowRange) && (num < guess))
        {
            highRange = guess;
        }
        guess = ((lowRange+highRange)/2);
        count_1++;
        usleep(1000);
    }
}

void* linear_S(void* game)
{
    for(int i = 0; i <= 1000;i++)
    {
        if(num == i)
            return 0;
        count_2++;
        usleep(1000);
    }
    return count_2;
}

int main()
{
    number(num);
    pthread_t player1;
    pthread_t player2;
    if (pthread_create (&player1, NULL, &binary_S, NULL) != 0)
    {
      printf ("FAILED\n");
      return 1;
    }
    if (pthread_create (&player2, NULL, &linear_S, NULL) != 0)
    {
      printf ("FAILED\n");
      return 1;
    }
    pthread_join (player1, NULL);
    pthread_join (player2, NULL);
    if(count_2 > count_1)
        printf("\nThe winner is player 1");
    else if(count_1 > count_2)
        printf("\nThe winner is player 2");
    else
        printf("Can't find the winner\n");
    printf("\nNumber of turns taken by \nplayer 1 = %d\nplayer 2 = %d\n", count_1, count_2);
    return 0;
}

