/**
 * \file   number.c
 * \brief  Auxiliary lib for tests which creates, prints, compares and destroys number elements
 */
#include <stdio.h>
#include <stdlib.h>

#include "number.h"

/* ************************************************************************************************/

void *number_new(int num)
{
    int *new_num = (int *)malloc(sizeof(*new_num));

    *new_num = num;

    return (void *)new_num;
}

/* ************************************************************************************************/

void number_print(void *num)
{
    printf("num = %p", num);

    if (NULL != num)
        printf(", *num = %d", *(int *)num);

    putchar('\n');

    return;
}

/* ************************************************************************************************/

int number_compare(void *n1, void *n2)
{
    if (NULL == n2 && NULL == n1)
        return 0;
    else if (NULL == n2)
        return -(*(int *)n1);
    else if (NULL == n1)
        return *(int *)n2;

    return *(int *)n2 - *(int *)n1;
}

/* ************************************************************************************************/

void number_destroy(void **n)
{
    if (NULL == n || NULL == *n)
        return;

    free(*n);
    *n = NULL;

    return;
}
