/**
 * \file   number.h
 * \brief  Auxiliary lib for tests which creates, prints, compares and destroys number elements
 */
#ifndef LIBDATASTRUCTURES_NUMBER_H
#define LIBDATASTRUCTURES_NUMBER_H

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************************/

/**
 * \brief   Create a number element.
 * \param   num  the number (signed integer) to be stored on the element
 * \return  a pointer to the allocated number element
 */
void *number_new(int num);

/**
 * \brief   Print a number element.
 * \param   num  the number element to be printed
 */
void number_print(void *num);

/**
 * \brief   Compare two number elements.
 * \param   n1  the first number element
 * \param   n2  the second number element
 * \return  a value which is a difference between the two elements; either 0 if they're equal, > 0
 *          if n2 > n1, or < 0 if n2 < n1
 */
int number_compare(void *n1, void *n2);

/**
 * \brief   Deallocate ('destroy') the number element.
 * \param   n  pointer to the number element to be destroyed
 */
void number_destroy(void **n);

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LIBDATASTRUCTURES_NUMBER_H */
