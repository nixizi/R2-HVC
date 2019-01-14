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

#include <assert.h>
#include <stdio.h>
#include "dominant.h"
#include "point.h"

/*** global variables *************************************/
#define NPs 1001
#define DC  2                   /**< From this dominated count exclude point */

/// The array with a local copy of the points
static point PTS[NPs] __attribute__ ((aligned (CLS)));
	
/*** file scope macro definitions *************************/

struct ci                       /**< Counting index structure */
{
  int i;                        /**< The index of the point */
  int c;                        /**< Dominant count */
};

typedef struct ci* ci;

/*** file scope type declarations *************************/
	
/*** file scope variables *********************************/

/*** file scope functions declarations ********************/

/*** public functions declarations ************************/

/*** file scope functions *********************************/

/* ------------------------------------------------------ */

/*** public functions *************************************/

int dominant(point* PS, int* idx, int n, 
             point *o, 
             point *p,
             int hypoct,
             int exclude)
{
  int i;                        /**< Counters */
  int j;
  int k;

  static point newo;

  static struct ci localidx[NPs];     /**< A local ordering of points */

/* #warning TODO: Needs updating to more effective version. Exclude from double dominated forward */


  /// This version is brute force. Multidimension D&C is next.
  assert(n < NPs);


  /// Local stash of points
  projectOne(&newo, p, hypoct, o);
  i = 0;
  while(i < n)
    {
      intercept(&(PTS[i]), &newo, &(PS[idx[i]]));
      localidx[i].c = 0;
      localidx[i].i = i;
      i++;
    }

  /// Reorder points
  k = n;
  i = n;
  while(i > 0)
    {
      i--;
      j = n;
      while(localidx[i].c < DC && j > k) 
        {
          j--;
          localidx[i].c += 
            (classify(&(PTS[localidx[j].i]), &(PTS[localidx[i].i])) & ~exclude) == 0;
        }
      
      if(localidx[i].c < DC)        /**< i was never dominated in local list */
        {
          k--;
          localidx[k] = localidx[i];
        }
    }

  /**< Already true i = 0 */
  while(k < n)
    {
      j = 0;
      while(localidx[k].c < DC && j < i)
        {
          localidx[k].c += 
            (classify(&(PTS[localidx[j].i]), &(PTS[localidx[k].i])) & ~exclude) == 0;
          j++;
        }
      
      if(localidx[i].c < DC)     /**< localidx[k] was not DC dominated in local list */
        {
          localidx[i] = localidx[k];
          i++;
        }
      k++;
    }

  /* n = compact(localidx, n, exclude); */
  /* revert(localidx, n); */
  /* n = compact(localidx, n, exclude); */
  /* revert(localidx, n); */

  /// Now the points in localidx[] from 0 to i-1 contain the non-dominated set
  i = 0;
  while(i < n)
    {
      swap(idx, i, localidx[i].i);
      i++;
    }

  return n;
}

  /* printf("Initial pass %d points \t", n-k); */
  /* j = k; */
  /* while(j < n) */
  /*   { */
  /*     printf("%.2f %.2f %.2f \t", PTS[localidx[j]].x[0], PTS[localidx[j]].x[1], PTS[localidx[j]].x[2]); */
  /*     j++; */
  /*   } */
  /* printf("\n"); */

  /* printf("Second pass %d points \t", i); */
  /* j = 0; */
  /* while(j < i) */
  /*   { */
  /*     printf("%.2f %.2f %.2f \t", PTS[localidx[j]].x[0], PTS[localidx[j]].x[1], PTS[localidx[j]].x[2]); */
  /*     j++; */
  /*   } */
  /* printf("\n"); */


  /* printf("First %d points \t", i); */
  /* j = 0; */
  /* while(j < n) */
  /*   { */
  /*     printf("point %d : %.2f %.2f %.2f \t", idx[j], PS[idx[j]].x[0], PS[idx[j]].x[1], PS[idx[j]].x[2]); */
  /*     j++; */
  /*   } */
  /* printf("\n"); */



