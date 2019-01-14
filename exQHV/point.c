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

#define _SVID_SOURCE
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#undef _SVID_SOURCE
#include "point.h"
#include "macros.h"

/*** global variables *************************************/
	
/*** file scope macro definitions *************************/

/*** file scope type declarations *************************/
	
/*** file scope variables *********************************/

point cZero = {{ B(0, D) }};
point cOne =  {{ B(1, D) }};
	
/*** file scope functions declarations ********************/

/*** public functions declarations ************************/

/*** file scope functions *********************************/

/* ------------------------------------------------------ */

/*** public functions *************************************/

void parsePoint(char* S, point* p, double max)
{
  char* tok;
  int i;

  tok = strtok(S, " \n");
  
  i = 0;
  while(i < D)
    {
      sscanf(tok, "%le", &p->x[i]);
      p->x[i] = p->x[i] / max;
      tok = strtok(NULL, " \n");
      i++;
    }
}

void randomPoint(point* p)
{
  int i;

  i = 0;
  while(i < D)
    {
      p->x[i] = (double)random()/(double)RAND_MAX;
      i++;
    }
}

