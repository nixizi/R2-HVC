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
 * @file   unionFilter.h
 * @author Luis Russo <lsr@lsr-ThinkPad-X201>
 * @date   Thu Mar  1 16:09:11 2012
 * 
 * @brief  Structure for uniting two sets, without repetition
 */
	
#ifndef UNIONFILTER_H
#define UNIONFILTER_H

/*** typedefs(not structures) and defined constants *******/
	
/*** enums ************************************************/
	
/*** structures declarations (and typedefs of )************/
	
/*** global variables defined in .c file ******************/
	
/*** declarations of public functions *********************/
	
/*** inline functions *************************************/

/** 
 * Initial procedures
 * 
 * @param n Maximal number of elements
 */
void initUnion(int n);

/** 
 * Finish the Union data structure
 * 
 */
void finishUnion(void);

/** 
 * Set the object for the empty set
 * 
 */
void resetUnion(void);

/** 
 * 
 * @param i The element
 * 
 * @return True if i is an element of the set
 */
int member(int i);

/** 
 * Insert this element into the current set
 * 
 * @param i The element
 */
void insertUnion(int i);

#endif /* UNIONFILTER_H */
