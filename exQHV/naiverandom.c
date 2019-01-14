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

#include "naiverandom.h"

/*** global variables *************************************/
	
/*** file scope macro definitions *************************/

/*** file scope type declarations *************************/
	
/*** file scope variables *********************************/
	
/*** file scope functions declarations ********************/

/*** public functions declarations ************************/

/*** file scope functions *********************************/

/* ------------------------------------------------------ */

/*** public functions *************************************/

double randomVolume(int n, point* PS)
{
  point p;                      /**< The random point */
  int i, j;                     /**< Counters */
  int d;                        /**< Number of dominated */
  unsigned int t;               /**< Last classification */

  /* i = n; */
  /* while(i > 0) */
  /*   { */
  /*     i--; */
  /*     t = classify(&PS[i], &cOne); */
  /*     if(t != 0) */
  /*       printf("Not in [0,1]^2\n"); */
  /*   } */

  i = 1<<20;
  d = 0;
  while(i > 0)
    {
      randomPoint(&p);
      
      t = 1;
      j = n;
      while(j > 0 && t != 0)
        {
          j--;
          t = classify(&PS[j], &p);
        }
      d += (t == 0);

      i--;
    }

  return (double)d/(double)(1<<20);
}
