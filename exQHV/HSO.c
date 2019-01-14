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
#include "quickhvolume.h"
#include "HSO.h"
#include "macros.h"

/* global variables */

/* file scope macro definitions */

/* file scope type declarations */

/* file scope variables */
static int i;                 /**< The dimension counter */
static unsigned char p;       /**< The point that gets inserted */
/// A counter for every dimension + 1
static unsigned char c[D] __attribute__ ((aligned (CLS)));
/// A volume value for every dimension + 1
static double V[D-1] __attribute__ ((aligned (CLS)));
/// A stack for every dimension, first one repeated. Aligned on cache.
static unsigned char S[D][N+2] __attribute__ ((aligned (CLS)));
/// A local stash of points. 
/// Two sentinels: * P[0] is the zero sentinel
///                * P[1] is all 1 except for last dimension, which is 0
static point P[N+2] __attribute__ ((aligned (CLS)));
static double tX[N+2] __attribute__ ((aligned (CLS)));
	
/* file scope functions declarations */

/** 
 * For debugging Purposes. Shows point a.
 * 
 * @param a The index of the point to show.
 */
static sureInline(void) showPoint(int a);

/** 
 * For debugging Purposes. Show the stack status.
 * 
 */
static sureInline(void) showS();

/** 
 * Calculates the 2D volume, for the points in S[D-2]
 */
static sureInline(void) get2D();

/** 
 * Insert the point in stack i.
 */
static sureInline(void) insert();

/* file scope functions */

static sureInline(void) showPoint(int a)
{
  int t;
  
  t = 0;
  printf("(");
  while(t < D)      {
    printf("%.1f ", P[a].x[t]);
    t++;
  }
  printf("), ");    
}

static sureInline(void) showS()
{                             /**< Shows the stack S */
  int t;
  int cc;
    
  t = 0;
  while(t < D-1)
    {
      printf("V[%d]=%.1f ", t, V[t]);
      cc = c[t];
      while(cc <= N+1)
        {
          showPoint(S[t][cc]);
          cc++;
        }
      printf("/\n");
      t++;
    }
}

static sureInline(void) insert()
{
  unsigned char* s;
  int k, l;

  if (i < D-2) {
    s = &S[i][c[i]-1];          /**< Overwrite the 0 sentinel */
    do
      {
        s++;
        *s = *(s+1);
      }while(P[p].x[i] > P[*s].x[i]); /**< i-Dim is smaller for p than
                                       for current element */
    *s = p;
    c[i]--;                       /**< Re-insert the 0 sentinel */
    S[i][c[i]] = 0;

    V[i] = 0;
    /**vvv Reset stack bellow */
    c[i+1] = N;
    S[i+1][c[i+1]] = 0;
    S[i+1][N+1] = 1;
    if (i == D-3) {
      V[i+1] = 0;
      c[i+2] = N;
      S[i+2][c[i+2]] = 1;
      S[i+2][N+1] = 1;
    }
  } else {

    tX[p] = P[p].x[i+1];
    tX[1] = P[1].x[i+1];

    k = c[i];
    S[i][k] = S[i][k+1];
    S[i+1][k] = S[i+1][k+1];

    c[i]--;
    l = c[i];
    S[i][c[i]] = 0;
    c[i+1]--;
    S[i+1][c[i+1]] = 1;

    while (S[i+1][k] == 0 || P[p].x[i] > P[S[i][k]].x[i]) {

      if (S[i+1][k] == 1 && tX[p] > tX[S[i][k]]) {
        V[D-2] += (tX[p] - tX[S[i][k]])
                * (P[S[i][k]].x[i] - P[S[i][l]].x[i]);
	
        tX[S[i][k]] = tX[p];
      }

      if (S[i+1][k] == 1) l = k;
      k++;
      S[i][k] = S[i][k+1];
      S[i+1][k] = S[i+1][k+1];
    }

    if (S[i+1][k] == 1 && tX[p] > tX[S[i][k]]) {
      V[D-2] += (tX[p] - tX[S[i][k]])
              * (P[p].x[i] - P[S[i][l]].x[i]);

      if (P[p].x[i] == P[S[i][k]].x[i]) { 
        tX[S[i][k]] = tX[p];
        S[i+1][k+1] = 0;
      }    
    }
    
    if (P[p].x[i] <= P[S[i][k]].x[i] && tX[p] < tX[S[i][k]]) {
      tX[p] = tX[S[i][k]];
      S[i+1][k] = 0;
    } else {
      S[i+1][k] = 1;
    }
    
    S[i][k] = p;
  } 
}

static sureInline(void) get2D()
{
  double m;

  /// Calculate a 2D volume
  V[D-2] = 0;

  c[D-1] = N+1;
  m = P[S[D-2][c[D-1]]].x[D-1];
  while(c[D-1] > c[D-2])
    {
      c[D-1]--;
      V[D-2] += (m-P[0].x[D-1])*(P[S[D-2][c[D-1]+1]].x[D-2] - P[S[D-2][c[D-1]]].x[D-2]);
      if(P[S[D-2][c[D-1]]].x[D-1] > m)
        m = P[S[D-2][c[D-1]]].x[D-1];
    }
}

/* public functions */

void resetHSO()
{
  i = 0;
  while(i < D)
    {
      S[i][N+1] = 1;          /**< Put 1 sentinels to finish every stack */
      c[i]      = N;
      S[i][N]   = 0;
      i++;
    }
  S[D-1][N] = 1;
}

double HSO(point* zero,  point* one, int n, int* idx, point* PS)
{
  int t;

  assert(n <= N);

  /// Store points, sorted, in local stash
  i = 0;                        /**< Important for insert */
  V[i] = 0;
  c[i] = N;
  S[i][c[i]] = 0;               /**< 1s do not need reseting */

  V[D-2] = 0;

  P[0] = *zero;
  P[1] = *one;
  P[1].x[D-1] = P[0].x[D-1];    /**< Makes one null measured */
  tX[0] = P[0].x[D-1];
  tX[1] = P[1].x[D-1];

  t = n;
  while(t > 0)             /**< Ends with c[0] == 0 */
    {
      t--;
      p = t+2;
      intercept(&(P[p]), one, &(PS[idx[t]]));
      insert();
    }

  /// Start Sliding
  do {  
    /* printf("Before Insert\n"); */
    /* showS(); */
      if(c[i] < c[i+1])         /**< Compute HV in the next dimension */
        {                       /**< The previous List has one more element */          
          while(i+2 < D)       /* Propagate elements down */
            {
              i++;
              do{
                p = S[i-1][c[i]];   /**< Push a value form this stack downwards */
                insert();
              }while(c[i-1] < c[i] && equal(&P[p], &P[S[i-1][c[i]]], i-1) );
            }

          // get2D(); /// Calculate a 2D volume
        }
      else
        {                       /**< Same number of points or sentinel finish */
          i--;
          if(i >= 0)
            V[i] += V[i+1] * (P[S[i][c[i+1]+1]].x[i] - P[S[i][c[i+1]]].x[i]);
        }
    } while(i >= 0);     /**< Ends when List 1 is full */

    /* printf("End\n"); */
    /* showS(); */

  return V[0];
}

double exHSO(point* zero,  point* one, int n, int* idx, point* PS, double* exHV)
{
  int j;                        /**< Index value */
  double T;                     /**< Total volume */

  T = HSO(zero, one, n, idx, PS);

  j = 0;
  while(j < n)
    {
      swap(idx, 0, j);
      exHV[idx[0]] += T - HSO(zero, one, n-1, &(idx[1]), PS);
      j++;
    }

  return T;
}

/* ------------------------------------------------------ */
