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
 * @file   arrayList.h
 * @author Luis Russo <lsr@lsr-ThinkPad-X201>
 * @date   Wed Feb 29 17:06:11 2012
 * 
 * @brief  This header implements an arrayList for integers
 * 
 */
	
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>
#include <limits.h>
#include "macros.h"

/*** typedefs(not structures) and defined constants *******/
typedef struct arrayList* arrayList;

/*** enums ************************************************/
	
/*** structures declarations (and typedefs of )************/
struct arrayList{
  int* A;                       /**< The array itself */
  int  n;                       /**< Number of items inserted */
  int  bound;                   /**< Maximum array size */
  int  f;                       /**< Dividing percentage */
};
	
/*** global variables defined in .c file ******************/
	
/*** declarations of public functions *********************/
	
/*** inline functions *************************************/

static sureInline(arrayList) newArrayList(int bound)
{
  arrayList S;

  S = calloc(1, sizeof(struct arrayList));
  S->bound = bound;
  S->f = bound;
  
  S->A = (int*)calloc(S->bound/S->f, sizeof(int));

  return S;
}

static sureInline(arrayList) newArrayListDef()
{
  return newArrayList(INT_MAX);
}

static sureInline(void) freeArrayList(arrayList* S)
{
  free((*S)->A);
  free(*S);
  *S = NULL;
}

static sureInline(int*) splitAL(arrayList* S)
{
  int* R;
  
  R = (int*)realloc((*S)->A, ((*S)->n)*sizeof(int));
  free(*S);
  *S = NULL;

  return R;
}

static sureInline(void) clean(arrayList S)
{
  S->n = 0;
}

static sureInline(int*) get(arrayList S)
{
  return S->A;
}

static sureInline(int) size(arrayList S)
{
  return S->n;
}

static sureInline(void) pushAL(arrayList S, int k)
{
  if(S->n == (S->bound/S->f))
    {                           /**< Hitted the array Limit */
      S->f /= 2;
      if(S->f < 1) S->f = 1;

      S->A = (int*) realloc(S->A, (S->bound/S->f)*sizeof(int));
    }

  S->A[S->n] = k;
  (S->n)++;
}
static sureInline(void) popAL(arrayList S)
{
  (S->n)--;
}

#endif /* ARRAYLIST_H */
