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
 * @file   splitter.h
 * @author Luis Russo <lsr@lsr-ThinkPad-X201>
 * @date   Sat Nov 26 09:44:56 2011
 * 
 * @brief A splitter for storing classified points. The splitter is an array
 * that grows dinamically, when all points are inserted they are
 * separeted into classes by sorting. Preferably count sort or hased
 * count sort.
 * 
 */
	
#ifndef SPLITTER_H
#define SPLITTER_H

#include "division.h"

/*** typedefs(not structures) and defined constants *******/
	
/*** enums ************************************************/
	
/*** structures declarations (and typedefs of )************/
	
/*** global variables defined in .c file ******************/
	
/*** declarations of public functions *********************/

/** 
 * Initial routines of the splitter object
 */
void initSplitter(void);

/** 
 * Frees the global variables
 */
void destroySplitter(void);

/** 
 * Push a new elements into the splitter
 * 
 * @param S The splitter
 * @param idx The point index
 * @param tp The type/oct
 */
void push(int idx, int tp);

/** 
 * 
 * @return A division object from the current splitter state. The
 * splitter is reset to empty.
 */
division newDivision(point* PS, point* o, point* p);

/*** inline functions *************************************/

#endif /* SPLITTER_H */
