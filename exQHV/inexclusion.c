/* 
 * 
 * Copyright (c) Year(s), 2013, Luis M. S. Russo and Alexandre 
 * P. Francisco / KDBIO / INESC-ID, <qhv@kdbio.inesc-id.pt> 
 *  
 * Any published media that is related with to use of the distributed 
 * software, or derived software, must contain a reference to "Extending 
 * quick hypervolume. Luís M. S. Russo, Alexandre P. Francisco: 
 * J. Heuristics 22(3): 245-271 (2016)".
 *  
 * Permission to use, copy, modify, and/or distribute this software for 
 * any purpose with or without fee is hereby granted, provided that the 
 * above copyright notice and this permission notice appear in all 
 * copies. 
 *  
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL 
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE 
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL 
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR 
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER 
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR 
 * PERFORMANCE OF THIS SOFTWARE. 
 * 
 */

/**
 * @file   inexclusion.c
 * @author Luis Russo <lsr@lsr-ThinkPad-X201>
 * @date   Fri Feb  3 16:35:27 2012
 * 
 * @brief The PTS array is where I store the points. The combinations
 *  are simply integers. The bits to one indicate the points included
 *  in the combination. The C2P array maps from combinations to
 *  positions in PTS.
 * 
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "point.h"
#include "quickhvolume.h"
#include "macros.h"
#include "subsets.h"
#include "inexclusion.h"

/*** global variables *************************************/
	
/*** file scope macro definitions *************************/

/*** file scope type declarations *************************/
	
/*** file scope variables *********************************/

static point PTS[1<<N] __attribute__ ((aligned (CLS))); /**< Initial and generated points */
static int C2P[1<<N] __attribute__ ((aligned (CLS)));   /**< Combination to position map */
static int C[N][N+1] __attribute__ ((aligned (CLS)));   /**< Acumulated Binomial Coeficients */

/*** file scope functions declarations ********************/

static double InExClusion(point* zero, point* one, int n, int* idx, point* P);

/*** public functions declarations ************************/

/*** file scope functions *********************************/

/* ------------------------------------------------------ */

/*** public functions *************************************/

void IECinit(void)
{
  int i;
  int j;

  /// Calculating the binomials
  i = 0;
  while(i < N)
    {
      C[i][0] = 1;
      C[i][i] = 1;
      j = 1;
      while(j < i)
        {
          C[i][j] = C[i-1][j-1] + C[i-1][j];
          j++;
        }
      i++;
    }

  /// Accumulating the binomials
  i = 0;
  while(i < N)
    {
      j = 1;
      while(j <= i)
        {
          C[i][j] += C[i][j-1];
          j++;
        }
      i++;
    }
}

static double InExClusion(point* zero, point* one, int n, int* idx, point* PS)
{
  assert(n <= N);

  double res;
  int i;
  int j;
  int twoton;
  int ones;                     /**< Number of bits set to 1 in i */
  int counts[N+2];              /**< A counters array */

  res = 0;
  
  /// Local stash of points
  i = 0;
  j = 1;
  while(i < n)
    {
      intercept(&(PTS[i+1]), one, &(PS[idx[i]]));
      i++;
      res += HV(zero, &(PTS[i]));
      C2P[j] = i;
      j <<= 1;
    }

  twoton = 1 << n;              /**< Upper limit */
  memcpy(&counts[1], &C[n][0], (n+1)*sizeof(int)); /**< Reinit counters */
  i = 1;
  ones = 1;
  while(i < twoton)             /**< Running through all combinations */
    {
      if(ones > 1)
        {                       /**< These are already included */
          C2P[i] = counts[ones];
          counts[ones]++;
          intercept(&(PTS[C2P[i]]), &(PTS[C2P[Rbit(i)]]), &(PTS[C2P[Rpop(i)]]));
          if(ones & 1)          /**< Inclusion */
            res += HV(zero, &(PTS[C2P[i]]));
          else                  /**< Exclusion */
            res -= HV(zero, &(PTS[C2P[i]]));
        }
      i++;
      ones++;
      ones-=fastLog2(Rbit(i));
    }

  return res;
}

/* double exInExClusion(point* zero, point* one, int n, int* idx, point* PS, double* exHV) */
/* { */
/*   assert(n <= N); */

/*   int j;                        /\**< Index value *\/ */
/*   double T;                     /\**< Total volume *\/ */

/*   T = InExClusion(zero, one, n, idx, PS); */

/*   j = 0; */
/*   while(j < n) */
/*     { */
/*       swap(idx, 0, j); */
/*       exHV[idx[0]] += T - InExClusion(zero, one, n-1, &(idx[1]), PS); */
/*       j++; */
/*     } */

/*   return T; */
/* } */

double exInExClusion(point* zero, point* one, int n, int* idx, point* PS, double* exHV)
{
  assert(n <= N);

  int i;
  int j;
  int twoton;
  int ones;                     /**< Number of bits set to 1 in i */
  double T;                     /**< Total volume */
  double H;                     /**< Temporary volume */

  T = InExClusion(zero, one, n, idx, PS);

  twoton = 1 << n;              /**< Upper limit */
  i = 1;
  ones = 1;
  while(i < twoton)             /**< Running through all combinations */
    {
      j = i;
      H = HV(zero, &(PTS[C2P[i]]));
      if(0 == (ones & 1))          /**< Exclusion */
        H = -H;

      while(0 != j)
        {
          exHV[idx[fastLog2(Rbit(j))]] += H;
          j = Rpop(j);
        }
      i++;
      ones++;
      ones-=fastLog2(Rbit(i));
    }

  return T;
}


