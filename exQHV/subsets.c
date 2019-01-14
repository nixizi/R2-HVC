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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "macros.h"
#include "subsets.h"

/*** global variables *************************************/
struct setIterator git;

/*** file scope macro definitions *************************/

/*** file scope type declarations *************************/

struct setIterator{
  int i;                          /**< The current subset */
  unsigned int S[32];              /**< Array of elements */
};
	
/*** file scope variables *********************************/
	
/*** file scope functions declarations ********************/

/*** public functions declarations ************************/

/*** file scope functions *********************************/

/* ------------------------------------------------------ */

/*** public functions *************************************/

void newSets(unsigned int t)
{
  int i;
  
  i = 0;
  while(t > 0)
    {
      git.S[i] = Rbit(t);
      i++;
      t = Rpop(t);
    }

  git.i = (1<<i) - 1;
}

int hasNextSet(void)
{
  return git.i > 0;
}

unsigned int nextSet(void)
{
  int i;
  int res;

  res = 0;
  i = git.i;
  git.i--;

  while(i > 0)
    {
      res |= git.S[fastLog2(Rbit(i))];
      i = Rpop(i);
    }

  return res;
}

/** 
 *
 * Simple test for the subset Iterators
 * 
 * @param argc The number of arguments
 * @param argv A list with string arguments
 * 
 * @return 0 because everything was okay.
 */
/* int main(int argc, char** argv) */
/* { */
/*   newSets(128+64+1); */

/*   while(hasNextSet()) */
/*     { */
/*       printf("%d\n", nextSet()); */
/*     } */
      
/*   return 0; */
/* } */
