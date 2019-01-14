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
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <strings.h>
#include "quickhvolume.h"
#include "HSO.h"
#include "subsets.h"
#include "division.h"
#include "splitter.h"
#include "macros.h"
#include "inexclusion.h"

/* global variables */

/* file scope macro definitions */

/* file scope type declarations */

/* file scope variables */

#ifdef COUNT                    /**< Count QuickHvolumeR T(n) */
static double tops;             /**< Count the number of ops, instead of time */
#endif  /* COUNT */
	
/* file scope functions declarations */

/** 
 * The recursive version is private for this file
 * 
 * @param zero The min coordinates point
 * @param one The max coordinates point
 * @param n Number of selected points
 * @param idx List of indexes
 * @param PS List of points
 * 
 * @return The resulting hyperVolume
 */
static double quickExHVolumeR(point* zero,
                              point* one,
                              int n,
                              int* idx,
                              point* PS,
                              double* exHV);
#ifdef COUNT
static double WrappedExQuickHVolumeR(point* z,
                                     point* o,
                                     int n,
                                     int* idx,
                                     point* PS,
                                     double* exHV);
#endif /* COUNT */

/* paper: 1 */
static double quickExHVolumeR(point* z,
                              point* o,
                              int n,
                              int* idx,
                              point* PS,
                              double* exHV)
/* paper: 0 */
#ifdef COUNT
{
  tops += n;
  WrappedQuickExHVolumeR(z, o, n, idx, PS, exHV);

  return 0;
}

static double WrappedQuickExHVolumeR(point* z,
                                   point* o,
                                   int n,
                                   int* idx,
                                   point* PS,
                                   double* exHV);
#endif /* COUNT */
/* paper: 1 */
{
  double tp[3];                 /**< Temporary values */
  double hv;                    /**< hyperVolume */
  division d;                   /**< The division structure */
  int i, j, k;                  /**< Counters */
  point p;                      /**< Pivot */
  point pp;                     /**< Temporary point */
/* paper: 0 */
  point ppp;                    /**< Another temporary point */
/* paper: 1 */
  point newo;                   /**< The new o point */
  point newz;                   /**< The new z point */
  double max;                   /**< maximize objective */
  point* A[3];                 /**< Array with pointers to points */

  ///1. Select Pivot

  k = 0;
  A[0] = o;
  A[1] = &ppp;
  A[2] = &p;
  while(k < 2)                  /**< Selection is now a 2 pass process */
    {
      max = -DBL_MAX;               /**< Forces initial loop */
      i = k;
      while(i < n)
        {
          intercept(&pp, A[k], &(PS[idx[i]]));
          hv = objective(z, &pp, o);
          if(hv > max)
            {                       /**< New Pivot Candidate */
              max = hv;
              j = i;
            }
          i++;
        }

      intercept(A[k+1], A[k], &(PS[idx[j]]));
      swap(idx, k, j);          /**< Avoids this point on next run */
      k++;
    }

  hv = HV(z, &p);

  /// 2. Divide Points
  i = 0;
  while(i < n)
    {
      intercept(&pp, o, &(PS[idx[i]]));
      push(idx[i], classify(&p, &pp));
      i++;
    }
  d = newDivision(PS, o, &p);

  /// 3. Conquer
  while(hasNext(d))
    {
      idx = next(d, &j, &n);
      projectZero(&newz, &p, j, z);
      projectOne(&newo, &p, j, o);

/* paper: 0 */
      if(n < N)
        {  /**< For very few points use cache oblivious */
          switch(n)
            {
            case 1:             /**< Simple volume */
              intercept(&pp, &newo, &(PS[idx[0]]));
              tp[0] =  HV(&newz, &pp);
              hv += tp[0];
              exHV[idx[0]] += tp[0]; /**< Exclusive */
              break;

            case 2:             /**< Simple IEX */
              intercept(&pp, &newo, &(PS[idx[0]]));
              tp[0] =  HV(&newz, &pp);
              hv += tp[0];

              intercept(&ppp, &newo, &(PS[idx[1]]));
              tp[1] =  HV(&newz, &ppp);
              hv += tp[1];

              intercept(&pp, &pp, &ppp); /**< Exclude part */
              tp[2] =  HV(&newz, &pp);
              hv -= tp[2];

              exHV[idx[0]] += tp[0] - tp[2];  /**< Exclusive */
              exHV[idx[1]] += tp[1] - tp[2];  /**< Exclusive */
              break;

            default:
              if(HSOL < n)
                hv += exHSO(&newz, &newo, n, idx, PS, exHV);
              else
                hv += exInExClusion(&newz, &newo, n, idx, PS, exHV);
                break;
            }
        }
      else
/* paper: 1 */
        { /**< Recursive call */
          /* if(on > 10 && bits(j)+log2((double)n/(double)on) > 3) */
          /*   printf("bits:%d  number:%d  fraction:%f\n", bits(j), on, log2((double)n/(double)on)); */
          hv += quickExHVolumeR(&newz, &newo, n, idx, PS, exHV);
        }
    }
  freeDivision(&d);

  return hv;
}
/* paper: 0 */

/* public functions */

double quickExHVolume(int n, point* PS, double* exHV)
{
  double res;
  int* idx;
  int i;

#ifdef COUNT
  tops = 0;
#endif /* COUNT */

  idx = (int*) malloc(n*sizeof(int));
  i = 0;
  while(i < n)
    {
      if(exHV != NULL)
        exHV[i] = 0;              /**< Exclusive volume is 0 */
      idx[i] = i;
      i++;
    }

  res = quickExHVolumeR(&cZero, &cOne, n, idx, PS, exHV);
  
  free(idx);

#ifdef COUNT
  printf("%d %d %f\n", n, D, tops);
#endif /* COUNT */

  return res;
}

/* ------------------------------------------------------ */
