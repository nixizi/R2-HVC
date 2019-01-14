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

#include "unionFilter.h"
#include "counterHash.h"
#include "arrayList.h"

/*** global variables *************************************/

arrayList members;              /**< List of members */
counterHash presences;          /**< Hash of presences */
	
/*** file scope macro definitions *************************/

/*** file scope type declarations *************************/
	
/*** file scope variables *********************************/
	
/*** file scope functions declarations ********************/

/*** public functions declarations ************************/

/*** file scope functions *********************************/

/* ------------------------------------------------------ */

/*** public functions *************************************/

void initUnion(int n)
{
  static int size = 0;

  if(size < n)
    {
      if(size != 0)
        { /* Free current structs first */
          freeArrayList(&(members));
          CHfree(&(presences));
        }

      size = 2*n;

      members = newArrayList(size);
      presences = CHalloc(size);
    }
}

void finishUnion(void)
{
  freeArrayList(&members);
  CHfree(&presences);
}

void resetUnion(void)
{
  int i;

  i = 0;
  while(i < size(members))
    {
      CHzero(presences, get(members)[i]);
      i++;
    }
  clean(members);
}

int member(int i)
{
  return CHget(presences, i);
}

void insertUnion(int i)
{
  if(!member(i))
    pushAL(members, i);

  CHinc(presences, i, 1);
}

