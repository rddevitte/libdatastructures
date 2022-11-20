/**
 * \file   fruit.c
 * \brief  Auxiliary lib for tests which creates, prints, compares and destroys fruit elements
 */
#include <stdio.h>
#include <stdlib.h>

#include "fruit.h"

/* ************************************************************************************************/

/*static*/ const char *fruit_to_string(fruit_e fruit)
{
    switch (fruit) {
        case APPLE:
            return "apple";
        case AVOCADO:
            return "avocado";
        case BANANA:
            return "banana";
        case BLACKBERRY:
            return "blackberry";
        case BLUEBERRY:
            return "blueberry";
        case CANTALOUPE:
            return "cantaloupe";
        case CHERRY:
            return "cherry";
        case CLEMENTINE:
            return "clementine";
        case COCONUT:
            return "coconut";
        case CUCUMBER:
            return "cucumber";
        case GRAPE:
            return "grape";
        case GRAPEFRUIT:
            return "grapefruit";
        case KIWIFRUIT:
            return "kiwifruit";
        case LEMON:
            return "lemon";
        case LIME:
            return "lime";
        case MANGO:
            return "mango";
        case ORANGE:
            return "orange";
        case PAPAYA:
            return "papaya";
        case PEACH:
            return "peach";
        case PEAR:
            return "pear";
        case PERSIMMON:
            return "persimmon";
        case PINEAPPLE:
            return "pineapple";
        case PLUM:
            return "plum";
        case POMEGRANATE:
            return "pomegranate";
        case PUMPKIN:
            return "pumpkin";
        case RASPBERRY:
            return "raspberry";
        case STRAWBERRY:
            return "strawberry";
        case TAMARIND:
            return "tamarind";
        case TANGERINE:
            return "tangerine";
        case TOMATO:
            return "tomato";
        case WATERMELON:
            return "watermelon";
        default:
            break;
    }

    return "(unknown)";
}

/* ************************************************************************************************/

void *fruit_new(fruit_e fruit)
{
    fruit_e *new_fruit = (fruit_e *)malloc(sizeof(*new_fruit));

    *new_fruit = fruit;

    return (void *)new_fruit;
}

/* ************************************************************************************************/

void fruit_print(void *fruit)
{
    printf("fruit = %p", fruit);

    if (NULL != fruit)
        printf(", *fruit = \"%s\"", fruit_to_string(*(fruit_e *)fruit));

    putchar('\n');

    return;
}

/* ************************************************************************************************/

int fruit_compare(void *f1, void *f2)
{
    if (NULL == f1 && NULL == f2)
        return 0;
    else if (NULL == f2)
        return -*(int *)f1;
    else if (NULL == f1)
        return *(int *)f2;

    return *(int *)f2 - *(int *)f1;
}

/* ************************************************************************************************/

void fruit_destroy(void **fruit)
{
    if (NULL == fruit || NULL == *fruit)
        return;

    free(*fruit);
    *fruit = NULL;

    return;
}
