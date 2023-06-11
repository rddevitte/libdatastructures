/**
 * \file   fruit.h
 * \brief  Auxiliary lib for tests which creates, prints, compares and destroys fruit elements
 */
#ifndef LIBDATASTRUCTURES_FRUIT_H
#define LIBDATASTRUCTURES_FRUIT_H

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************************/

/** Fruit names' enumeration */
enum fruit {
    APPLE,
    AVOCADO,
    BANANA,
    BLACKBERRY,
    BLUEBERRY,
    CANTALOUPE,
    CHERRY,
    CLEMENTINE,
    COCONUT,
    CUCUMBER,
    GRAPE,
    GRAPEFRUIT,
    KIWIFRUIT,
    LEMON,
    LIME,
    MANGO,
    ORANGE,
    PAPAYA,
    PEACH,
    PEAR,
    PERSIMMON,
    PINEAPPLE,
    PLUM,
    POMEGRANATE,
    PUMPKIN,
    RASPBERRY,
    STRAWBERRY,
    TAMARIND,
    TANGERINE,
    TOMATO,
    WATERMELON,
    MAX_FRUIT
};

/** Fruit enumeration's type */
typedef enum fruit fruit_e;

/* ************************************************************************************************/

const char *fruit_to_string(fruit_e fruit);

/**
 * \brief   Create a fruit element.
 * \param   fruit  the fruit value to be stored on the element
 * \return  pointer to the allocated fruit element
 */
void *fruit_new(fruit_e fruit);

/**
 * \brief  Print a fruit element.
 * \param  fruit  the fruit element to be printed
 */
void fruit_print(void *fruit);

/**
 * \brief   Compare two fruit elements.
 * \param   f1  the first fruit element
 * \param   f2  the second fruit element
 * \return  a value which is a difference between the two elements; either 0 if they're equal, > 0
 *          if f2 > f1, or < 0 if f2 < f1
 */
int fruit_compare(void *f1, void *f2);

/**
 * \brief  Deallocate ('destroy') a fruit element.
 * \param  fruit  pointer to the fruit element to be destroyed
 */
void fruit_destroy(void **fruit);

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIBDATASTRUCTURES_FRUIT_H */
