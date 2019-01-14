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
 * @file   subsets.h
 * @author Luis Russo <lsr@lsr-ThinkPad-X201>
 * @date   Tue Nov 29 11:53:34 2011
 * 
 * @brief This returns iterators for diferent type. WARNING, these
 * objects are singleton, so new overwrites existing iterator;
 * 
 */
	
#ifndef SUBSETS_H
#define SUBSETS_H

/*** typedefs(not structures) and defined constants *******/
	
/*** enums ************************************************/
	
/*** structures declarations (and typedefs of )************/
	
/*** global variables defined in .c file ******************/
	
/*** declarations of public functions *********************/

/** 
 *
 * WARNING: This class is singleton. This function overwrites previous
 * call.
 *
 * @param t The type * 
 * @return A proper subser iterator
 */
void newSets(unsigned int t);

/** 
 * @param it The iterator
 * 
 * @return True if there are more subsets
 */
int hasNextSet(void);

/** 
 * @param it The iterator
 * 
 * @return The next subset
 */
unsigned int nextSet(void);

/** The next bit manipulating ops are usefull in other files **/

/** 
 * @param N The original number
 * 
 * @return The rightmost 1 bit
 */
#define Rbit(N) ((N) & -(N))

/** 
 * @param N The original number
 * 
 * @return N without the rightmost 1 bit
 */
#define Rpop(N) ((N) & ~-(N))

/** 
 * Bit function
 * 
 * @param l The integer, should contain only 1 bit
 * 
 * @return Determine index of Rightmost bit
 */
static sureInline(int) fastLog2(unsigned int l)
{
  float v; /* find int(log2(v)), where v > 0.0 && finite(v) && isnormal(v) */
  int c;   /* 32-bit int c gets the result; */
  
  v = l;
  c = *((int*)&v);
  c = (c >> 23) - 127;
  
  return c;
}

/* static int bits(int i) */
/* { */
/*   int j; */

/*   j = 0; */
/*   while(i > 0) */
/*     { */
/*       j++; */
/*       i = Rpop(i); */
/*     } */

/*   return j; */
/* } */

/*** inline functions *************************************/

#endif /* SUBSETS_H */
