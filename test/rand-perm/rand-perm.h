/**
 * \file   rand-perm.h
 * \brief  Auxiliary lib to generate random permutations, giving a range of integers.
 */
#ifndef RAND_PERM_H
#define RAND_PERM_H

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************************************/

/** Random permutation generator structure */
typedef struct {
    /** Pointer to an array of integers */
    int *nums;
    /** Start of value range */
    int m;
    /** End of value range, included */
    int n;
    /** Internal range control variable */
    int max;
} rand_perm_gen_t;

/* ************************************************************************************************/

/**
 * \brief  Initialize the random permutation generator struct.
 * \param  gen  pointer to the random permutation generator struct
 * \param  m    the integer of the beginning of range
 * \param  n    the integer of the end of the range, included
 */
void rand_perm_gen_init(rand_perm_gen_t *gen, int m, int n);

/**
 * \brief   Get the next integer of the random permutation generator.
 * \param   gen  pointer to the random permutation generator struct
 * \return  the next integer of the random permutation generator
 */
int rand_perm_gen_get_next(rand_perm_gen_t *gen);

/**
 * \brief  Destroy the random permutation generator.
 * \param  gen  pointer to the random permutation generator struct
 */
void rand_perm_gen_destroy(rand_perm_gen_t *gen);

/* ************************************************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* RAND_PERM_H */
