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
 * @file   point.h
 * @author Luis Russo <lsr@lsr-ThinkPad-X201>
 * @date   Mon Nov 28 14:39:12 2011
 * 
 * @brief Simple point interface. Contains simple point manipulation
 * functions
 *
 * 
 */

#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <math.h>
#include <float.h>
#include "emmintrin.h"
#include "macros.h"


#ifndef D                       /**< Accept compiler options */
#define D 6                     /**< The number of dimensions */
#endif /* D */

#ifndef Eps
#define Eps 0.0000000001
#endif /* Eps */

/*** typedefs(not structures) and defined constants *******/
/// Point is an array of coordinates, in a struct for simple and fast copy
struct point{
#if (D & 1)
  double x[D+1];
#else /* (D & 1) */
  double x[D];
#endif /* (D & 1) */
};
/// All points must be aligned for SSE2
typedef struct point __attribute__ ((aligned (16))) point;
	
/*** enums ************************************************/

/*** structures declarations (and typedefs of )************/
	
/*** global variables defined in .c file ******************/

extern point cZero;              /**< The origin point */
extern point cOne;               /**< The all 1's point */
	
/*** declarations of public functions *********************/

/** 
 * 
 * @param A First point
 * @param B Second point
 * @param i coordinate to compare
 * 
 * @return True if the i coordinates are almost equal
 */
#define equal(A, B, I) (fabs((A)->x[I] - (B)->x[I]) < Eps)

/** 
 * @param Z The zero bounding point
 * @param A The point to analyze
 * @param O The one bounding point
 * 
 * @return  The objective value to maximize, must be > 0
 */
#define objective(Z, A, O)   HV(Z, A)
//#define objective(Z, A, O)   minCoord(Z, A, O)

/** 
 * Reads a point from the '\0' terminated string. 
 * 
 * @param S The string containing the coordinates, separated by spaces or '\n'
 * @param p The position where to store the point
 */
void parsePoint(char* S, point* p, double max);

/** 
 * Sets p to a random point in [0,1]
 * 
 * @param p The point to alter
 */
void randomPoint(point* p);

static sureInline(void) projectZero(point* res, point* pvt, unsigned int oct, point* zero)
{
  unsigned int B;
  int i;

  i = 0;
  B = 1;

  while(i < D)
    {
      if(B & oct)
        res->x[i] = pvt->x[i];
      else
        res->x[i] = zero->x[i];
      i++;
      B <<= 1;
    }
}

static sureInline(void) projectOne(point* res, point* pvt, unsigned int oct, point* one)
{
  unsigned int B;
  int i;

  i = 0;
  B = 1;

  while(i < D)
    {
      if(B & oct)
        res->x[i] = one->x[i];
      else
        res->x[i] = pvt->x[i];
      i++;
      B <<= 1;
    }
}

/**
 * @param pvt The pivot point
 * @param a The point to classify
 *
 * @return The class of point a, relative to pivot pvt
 */
static sureInline(int) classify(point* pvt, point* a)
{
  unsigned int res;
  unsigned int B;
  int i;

  res = 0;
  i = 0;
  B = 1;

  while(i < D)
    {
      if(a->x[i] > pvt->x[i])
        res |= B;

      i++;
      B <<= 1;
    }

  return res;
}

/** 
 * 
 * @param zero The min coordinates point
 * @param one  The max coordinates point
 * 
 * @return The hyper-volume of the hyper-Rectangle
 */
static sureInline(double) HV(point* zero, point* one)
{
  __m128d  c;
  __m128d* o;
  __m128d* z;
  double*  V;

  int d;

#if (D & 1)
  one->x[D] = 1;
  zero->x[D] = 0;
#endif /* (D & 1) */

  z = (__m128d*)&(zero->x[0]);
  o = (__m128d*)&(one->x[0]);
  c = _mm_set1_pd(1);

  d = 0;
  while(d < ((D+1) >> 1))
    {
      c = _mm_mul_pd(c, _mm_sub_pd(z[d], o[d]));
      d++;
    }

  V = (double*) &c;
  V[0] *= V[1];

  return V[0];
}


/** 
 * 
 * @param pt  The point coordinates
 * 
 * @return The minimal coordinate
 */
static sureInline(double) minCoord(point* zero, point* pt, point* one)
{
  __m128d  t; /* Temporary */
  __m128d  s; /* Scaling */
  __m128d  c;
  __m128d* o;
  __m128d* p;
  __m128d* z;
  double*  V;

  int d;

#if (D & 1)
  one->x[D] = one->x[D-1];
  pt->x[D] = pt->x[D-1];
  zero->x[D] = zero->x[D-1];
#endif /* (D & 1) */

  z = (__m128d*)&(zero->x[0]);
  p = (__m128d*)&(pt->x[0]);
  o = (__m128d*)&(one->x[0]);
  c = _mm_set1_pd(DBL_MAX);

  d = 0;
  while(d < ((D+1) >> 1))
    {
      s = _mm_sub_pd(o[d], z[d]);
      t = _mm_sub_pd(p[d], z[d]);
      t = _mm_div_pd(t, s);

      c = _mm_min_pd(c, t);

      /* printf("Coordinate %f in [%f, %f], scaled value %f\n",  */
      /* 	     ((double*)&(p[d]))[0], */
      /* 	     ((double*)&(z[d]))[0], */
      /* 	     ((double*)&(o[d]))[0], */
      /* 	     ((double*)&t)[0]); */
      /* printf("Coordinate %f in [%f, %f], scaled value %f\n",  */
      /* 	     ((double*)&(p[d]))[1], */
      /* 	     ((double*)&(z[d]))[1], */
      /* 	     ((double*)&(o[d]))[1], */
      /* 	     ((double*)&t)[1]); */
      d++;
    }

  V = (double*) &c;
  if(V[1] < V[0])
    V[0] = V[1];

  return V[0];
}


/** 
 * This is for the inclusion /exclusion algorithm
 * 
 * @param A point A
 * @param B point B
 * 
 * @return intercepted point
 */
static sureInline(void) intercept(point* res, point* A, point* B)
/* static void intercept(point* res, point* A, point* B) */
{
  __m128d* a;
  __m128d* b;
  __m128d* r;

  int d;

  a = (__m128d*)&(A->x[0]);
  b = (__m128d*)&(B->x[0]);
  r = (__m128d*)&(res->x[0]);

  d = 0;
  while(d < ((D+1) >> 1))
    {
      r[d] = _mm_min_pd(a[d], b[d]);
      d++;
    }
}

/** 
 * Swaps index j to n and vice versa
 * 
 * @param idx The index array
 * @param n Last position in array
 * @param j The index to swap
 */
static sureInline(void) swap(int* idx, int n, int j)
{
  int t;
  
  t = idx[n];
  idx[n] = idx[j];
  idx[j] = t;
}

	
/*** inline functions *************************************/

#endif /* POINT_H */
