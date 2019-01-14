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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include "point.h"
#include "splitter.h"
#include "division.h"         
#include "divisionStruct.c" /**< This is only a struct definition. */
#include "arrayList.h"
#include "counterHash.h"
#include "unionFilter.h"
#include "subsets.h"
#include "dominant.h"

/*** global variables *************************************/

arrayList hoList[D+1];          /**< Array with hyperoctant lists */
arrayList piList[D+1];          /**< Array with point index lists */
counterHash counters;           /**< Hash with counter values */
point* PS;                      /**< Need the points themselves */

/*** file scope macro definitions *************************/

/*** file scope type declarations *************************/

/*** file scope variables *********************************/
	
/*** file scope functions declarations ********************/

static sureInline(int) popcount(unsigned int i);

/*** public functions declarations ************************/

/*** file scope functions *********************************/

/* Classic binary divide-and-conquer popcount.
   This is popcount_2() from
   http://en.wikipedia.org/wiki/Hamming_weight */
/* 15 ops, 3 long immediates, 14 stages */
static sureInline(int) popcount(unsigned int x)
{
    unsigned int m1 = 0x55555555;
    unsigned int m2 = 0x33333333;
    unsigned int m4 = 0x0f0f0f0f;
    x -= (x >> 1) & m1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    x += x >>  8;
    return (x + (x >> 16)) & 0x3f;
}

/* ------------------------------------------------------ */

/*** public functions *************************************/

void initSplitter(void)
{
  int i;

  i = 0;
  while(i <= D)
    {
      hoList[i] = newArrayListDef(); /**< Change to binomials */
      piList[i] = newArrayListDef();
      i++;
    }
  counters = CHalloc(1<<D);
}

void destroySplitter(void)
{
  int i;
  i = 0;
  while(i <= D)
    {
      freeArrayList(&(hoList[i]));
      freeArrayList(&(piList[i]));
      i++;
    }
  CHfree(&counters);
  finishUnion();                /**< Terminate union filter */
}

void push(int idx, int tp)
{
  int i;

  i = popcount(tp);

  pushAL(hoList[i], tp);        /**< Put type */
  pushAL(piList[i], idx);       /**< Put point */
  CHinc(counters, tp, -1);       /**< Add another one of this type */
}

division newDivision(point* tPS, point* o, point* p)
{
  division d;
  int i;
  int j;
  int jj;
  int limit; 
  int k;
  arrayList hypocts;
  arrayList pPositions;
  int piAL;                    /**< Alloced point index space */
  int tc;                       /**< Total counter */

  PS = tPS;

  hypocts = newArrayList(1<<D);
  pPositions = newArrayListDef();
  d = (division) calloc(1, sizeof(struct division));

  limit = 0;
  piAL = 10;
  d->points = (int*) calloc(piAL, sizeof(int));

  i = D;
  while(i > 0)
    {
      /// 1. Do Count Sort
      /// 1.1 Pass hypocts to division & accumulate counters
      tc = limit;
      k = d->n;
      j = 0;
      while(j < size(hoList[i]))
        {
          if(CHget(counters, get(hoList[i])[j]) < 0)
            {            /**< First time hypoct is seen */
              d->n++;
              pushAL(pPositions, tc);
              tc -= CHget(counters, get(hoList[i])[j]);
              /* printf("tc %d\n", tc); */
              pushAL(hypocts, get(hoList[i])[j]);
              CHinc(counters, get(hoList[i])[j], tc);
            }
          j++;
        }
      pushAL(pPositions, tc);

      if(piAL < tc)
        { /* Alloc until position is accessible */
          while(piAL < tc)
            piAL *= 2;
          d->points = (int*) realloc(d->points, piAL*sizeof(int));
        }

      /// 1.2 Group Elements together
      j = 0;
      while(j < size(piList[i]))
        {
          jj = CHget(counters, get(hoList[i])[j]);
          d->points[jj] = get(piList[i])[j];
          CHinc(counters, get(hoList[i])[j], 1);
          j++;
        }

      /// 2. Do union filter
      jj = k;
      j = get(pPositions)[jj];
      while(jj < d->n)
        {
          resetUnion();
          get(pPositions)[jj] = limit;
          /* printf("%d - (", limit); */
          while(j < get(pPositions)[jj+1])
            {
              if(!member(d->points[j]))
                {
                  insertUnion(d->points[j]);
                  /* printf("%d, ", d->points[j]); */
                  d->points[limit] = d->points[j];
                  limit++;
                }
              j++;
            }
          /* printf(")\n"); */
          jj++;
        }
      get(pPositions)[jj] = limit;

      /// 3. Add projections to the level bellow
      int L;                    /**< left part of oct */
      int R;                    /**< Right part of oct */
      int B;                    /**< Bit, dimension project */

      while(k < d->n)
        {
          L = get(hypocts)[k];
          R = 0;
          B = 0;
          while(L != 0)
            {
              R = R | B;
              B = Rbit(L);
              L = Rpop(L);
              if((L | R) != 0)
                {
                  jj = get(pPositions)[k];
                  /// Computes the number of dominant points j and reorders
                  /// the array so that they appear at the beginning
                  j = dominant(PS, &(d->points[jj]), 
                               get(pPositions)[k+1] - jj, 
                               o, p, 
                               L | R,
                               B);
                  while(j > 0)
                    {
                      j--;
                      push(d->points[jj+j], L | R);
                    }
                }
            }
          k++;
        }

      /// Last position was there because of the previous procedure
      /// Update
      popAL(pPositions);
      i--;
    }
  pushAL(pPositions, limit);

  /// Doing cleanUp Stuff
  i = D;
  while(i > 0)
    {
      j = 0;
      while(j < size(hoList[i]))
        {
          CHzero(counters, get(hoList[i])[j]);
          j++;
        }
      clean(hoList[i]);
      clean(piList[i]);
      i--;
    }
  

  /// Preparing the struct for output
  d->hypocts = splitAL(&hypocts);
  d->pPositions = splitAL(&pPositions);
  d->points = (int*) realloc(d->points, limit*sizeof(int));

  return d;
}
