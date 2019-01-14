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

#include "counterHash.h"
#include "point.h"

#if D < 20
/// Less than 1K use array of counters

/*** global variables *************************************/
	
/*** file scope macro definitions *************************/

/*** file scope type declarations *************************/

struct counterHash
{
  int* H;
};
	
/*** file scope variables *********************************/
	
/*** file scope functions declarations ********************/

/*** public functions declarations ************************/

/*** file scope functions *********************************/

/* ------------------------------------------------------ */

/*** public functions *************************************/

counterHash CHalloc(int n)
{
  counterHash this;

  this = (counterHash) calloc(1, sizeof(struct counterHash));
  this->H = (int*) calloc(n, sizeof(int));

  return this;
}

void CHfree(counterHash* this)
{
  free((*this)->H);
  free(*this);
  *this = NULL;
}

void CHinc(counterHash this, int i, int a)
{
  this->H[i] += a;
}

void CHzero(counterHash this, int i)
{
  this->H[i] = 0;
}

int CHget(counterHash this, int i)
{
  return this->H[i];
}

#else /* D < 20 */
/// Use a real hash instead
#error TODO: Implement deamortized hash

/*** global variables *************************************/
	
/*** file scope macro definitions *************************/

/*** file scope type declarations *************************/

struct counterHash
{
  
};
	
/*** file scope variables *********************************/
	
/*** file scope functions declarations ********************/

/*** public functions declarations ************************/

/*** file scope functions *********************************/

/* ------------------------------------------------------ */

/*** public functions *************************************/

#endif /* D < 20 */
