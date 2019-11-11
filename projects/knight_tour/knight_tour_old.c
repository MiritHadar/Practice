
#include <stdlib.h>         /*malloc*/
#include <stdio.h>          /*printf*/
#include "knight_tour.h"    /*header*/

/********************Regular Implementation***********************/
static int move_i[] = {-2, -2, -1, -1, 2, 2, 1, 1};
static int move_j[] = {1, -1, -2, 2, 1, -1, 2, -2};
static int chess_board[SIZE][SIZE] = {0};

/*Funcs*/
static size_t CountValidMoves(int chess_board[SIZE][SIZE], int i, int j);
static int IsAvailable(int chess_board[SIZE][SIZE], int i, int j);
static int KTIsFull(size_t counter);

/********************Bits Implementation*************************/
static size_t bit_board = 0x0;
static int bit_path[BITS_ROW][BITS_COLUMN] = {0};

/*Funcs*/
static void KTSetBitOn(int i, int j);
static void SetBitOff(int i, int j);
static int IsValidBit(int i, int j);
static size_t CountValidBitMoves(int i, int j);
static int KTIsFullBits();
static int IsBitOff(int i, int j);


static int KTIsFull(size_t counter)
{
    return (counter > SIZE * SIZE);
}

void KTPrintBoard()
{
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < SIZE; ++i)
	{
		for (j = 0; j < SIZE; ++j)
		{
			printf("%d    ", chess_board[i][j]);
		}

		printf("\n\n\n");
	}
}

/*1 for true = can proceed. 0 for false = when gets stuck */
int KTPlayNaive(int i, int j, size_t counter)
{
    size_t inx = 0;

    chess_board[i][j] = counter;
    ++counter;

    if (KTIsFull(counter))
    {
        printf("%lu\n", counter);
        return 1;
    }

    for (inx = 0; inx < OPTIONS; ++inx)
    {
        if (IsAvailable(chess_board, i + move_i[inx], j + move_j[inx]))
        {
            if (KTPlayNaive(i + move_i[inx], j + move_j[inx], counter))
            {
                return 1;
            }
        }
    }

    chess_board[i][j] = 0;
    return 0;
}

/*1 for true = can proceed. 0 for false = when gets stuck*/ 
int KTPlaySmart(int i, int j, size_t counter)
{
    size_t inx = 0;
    int best_inx = -1;
    size_t count = 0;
    size_t min_count = OPTIONS;

    chess_board[i][j] = counter;
    ++counter;

    if (KTIsFull(counter))
    {
        printf("%lu\n", counter);
        return 1;
    }

    for (inx = 0; inx < OPTIONS; ++inx)
    {
        if (IsAvailable(chess_board, i + move_i[inx], j + move_j[inx]))
        {
            count = CountValidMoves(chess_board, i + move_i[inx], j + move_j[inx]);

            if (count <= min_count)
            {
                min_count = count;
                best_inx = inx;
            }
        }
    }
    if (-1 != best_inx)
    {
        if (KTPlaySmart(i + move_i[best_inx], j + move_j[best_inx], counter))
        {
            return 1;
        }
    }

    chess_board[i][j] = 0;
    return 0;
}

/*static funcs*/
static int IsAvailable(int chess_board[SIZE][SIZE], int i, int j)
{
    return ((i < SIZE) && (j < SIZE) && (i >= 0) && (j >= 0) && (chess_board[i][j] == 0));
}

static size_t CountValidMoves(int chess_board[SIZE][SIZE], int i, int j)
{
    size_t inx = 0;
    size_t count = 0;

    for (inx = 0; inx < OPTIONS; ++inx)
    {
        if (IsAvailable(chess_board, i + move_i[inx], j + move_j[inx]))
        {
            ++count;
        }
    }

    return count;
}

/***********************************BITS**********************************/

int KTPlaySmartBits(int i, int j, size_t counter_bits)
{
    size_t inx = 0;
    int best_inx = -1;
    size_t count = 0;
    size_t min_count = OPTIONS;

    KTSetBitOn(i, j);
    bit_path[i][j] = counter_bits;
    ++counter_bits;

    if (KTIsFullBits())
    {
        return 1;
    }

    for (inx = 0; inx < OPTIONS; ++inx)
    {
        if (IsValidBit(i + move_i[inx], j + move_j[inx]) && IsBitOff(i + move_i[inx], j + move_j[inx]))
        {
            count = CountValidBitMoves(i + move_i[inx], j + move_j[inx]);

            if (count <= min_count)
            {
                min_count = count;
                best_inx = inx;
            }
        }
    }

    if (-1 != best_inx)
    {
        if (KTPlaySmartBits(i + move_i[best_inx], j + move_j[best_inx], counter_bits))
        {
            return 1;
        }
    }

    SetBitOff(i, j);
    return 0;
}


void KTPrintBitBoard()
{
	size_t mask = LEFT_ONE;
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < 8; ++i)
	{
		for (j = 0; j < 8; ++j)
		{
			if (0 == (mask & bit_board))
			{
				printf("0   ");
			}
			else
			{
				printf("1   ");
			}

			bit_board = bit_board << 1;
		}
		puts("\n");
	}
}

void KTPrintBitPath()
{
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < BITS_ROW; ++i)
	{
		for (j = 0; j < BITS_COLUMN; ++j)
		{
			printf("%d   ", bit_path[i][j]);
		}

		printf("\n\n");
	}

	puts("*******************************************************************");
}

/*static funcs*/

static void SetBitOff(int i, int j)
{
	bit_board &= ~((size_t)RIGHT_ONE << (i * BITS_ROW + j));
}

static int IsValidBit(int i, int j)
{
    return (i >= 0 && i < BITS_COLUMN && j >=0 && j < BITS_ROW);
}

static size_t CountValidBitMoves(int i, int j)
{
    size_t inx = 0;
    size_t count = 0;

    for (inx = 0; inx < OPTIONS; ++inx)
    {
        if (IsValidBit(i + move_i[inx], j + move_j[inx]) && IsBitOff(i + move_i[inx], j + move_j[inx]))
        {
            ++count;
        }
    }

    return count;
}

static int IsBitOff(int i, int j)
{
    return (((bit_board >> ((i * BITS_ROW) + j)) & RIGHT_ONE) ^ RIGHT_ONE);
}

static void KTSetBitOn(int i, int j)
{
    bit_board = bit_board | (size_t)RIGHT_ONE << ((i * BITS_ROW) + j);
}


static int KTIsFullBits()
{
    return (bit_board == ~(0ul));
}


