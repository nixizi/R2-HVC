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
 * @file   division.c
 * @author Luis Russo <lsr@lsr-ThinkPad-X201>
 * @date   Thu Mar  1 11:01:56 2012
 * 
 * @brief  The splitter data structure
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "division.h"
	
/*** typedefs(not structures) and defined constants *******/
	
/*** enums ************************************************/
	
/*** structures declarations (and typedefs of )************/
#include "divisionStruct.c"

/*** global variables defined in .c file ******************/
	
/*** declarations of public functions *********************/
	
/*** inline functions *************************************/

void freeDivision(division* d)
{
  free((*d)->hypocts);
  free((*d)->pPositions);
  free((*d)->points);
  free(*d);
  
  *d = NULL;
}

int hasNext(division d)
{
  return d->n > 0;
}

int* next(division d, int* hypoct, int* n)
{
  d->n--;
  *hypoct = d->hypocts[d->n];
  *n = d->pPositions[d->n+1] - d->pPositions[d->n];

  /* printf("%d ->(%d ...) %d\n", d->pPositions[d->n], d->points[d->pPositions[d->n]], d->pPositions[d->n+1]); */

  return &(d->points[d->pPositions[d->n]]);
}

