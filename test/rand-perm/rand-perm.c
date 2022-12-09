/**
 * \file   rand-perm.c
 * \brief  Auxiliary lib to generate random permutations, giving a range of integers.
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rand-perm.h"

/* Static (helper) functions - declarations *******************************************************/

static int rand_between(int m, int n);

static void swap(int *m, int *n);

/* All other functions ****************************************************************************/

void rand_perm_gen_init(rand_perm_gen_t *gen, int m, int n)
{
    if (NULL == gen)
        return;

    if (m > n)
        swap(&m, &n);

    int c = n - m + 1;

    gen->nums = (int *)calloc((size_t)c, sizeof(int));

    if (NULL == gen->nums)
        return;

    for (int i = 0; i < c; i++)
        gen->nums[i] = i + m;

    gen->m = m;
    gen->n = n;
    gen->max = n - m;
}

/* ************************************************************************************************/

int rand_perm_gen_get_next(rand_perm_gen_t *gen)
{
    if (NULL == gen)
        return 0;

    int r = rand_between(0, gen->max);
    int n = gen->nums[r];

    swap(&gen->nums[r], &gen->nums[gen->max]);

    gen->max = (0 == gen->max ? gen->n - gen->m : gen->max - 1);

    return n;
}

/* ************************************************************************************************/

void rand_perm_gen_destroy(rand_perm_gen_t *gen)
{
    if (NULL == gen)
        return;

    free(gen->nums);
    gen->m = gen->n = gen->max = 0;
}

/* Static (helper) functions - implementations ****************************************************/

static int rand_between(int m, int n)
{
    static bool init_seed = false;

    if (!init_seed) {
        srand((unsigned int)time(NULL));
        init_seed = true;
    }

    if (n < m)
        swap(&m, &n);

    return (rand() % (n - m + 1)) + m;
}

/* ************************************************************************************************/

static void swap(int *m, int *n)
{
    if (NULL != m && NULL != n) {
        int tmp = *m;
        *m = *n;
        *n = tmp;
    }
}
