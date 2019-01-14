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
 * @file   counterHash.h
 * @author Luis Russo <lsr@lsr-ThinkPad-X201>
 * @date   Thu Mar  1 07:54:29 2012
 * 
 * @brief  A hash for containing counter values.
 * 
 */
	
#ifndef COUNTERHASH_H
#define COUNTERHASH_H

/*** typedefs(not structures) and defined constants *******/
typedef struct counterHash* counterHash;

/*** enums ************************************************/
	
/*** structures declarations (and typedefs of )************/
	
/*** global variables defined in .c file ******************/
	
/*** declarations of public functions *********************/

/** 
 * Alloc a counter hash of size n
 * 
 * @param n The size of the Hash
 * 
 * @return The hash
 */
counterHash CHalloc(int n);

/** 
 * Free the hash and null the pointer
 * 
 * @param this 
 */
void CHfree(counterHash* this);

/** 
 * Increment counter i by a
 * 
 * @param this The hash
 * @param i The counter index
 * @param a The increment
 */
void CHinc(counterHash this, int i, int a);

/** 
 * Zero counter i
 * 
 * @param this The hash
 * @param i the counter index
 */
void CHzero(counterHash this, int i);

/** 
 * 
 * 
 * @param this The hash 
 * @param i The counter index
 * 
 * @return The value of counter i
 */
int CHget(counterHash this, int i);

/*** inline functions *************************************/

#endif /* COUNTERHASH_H */
