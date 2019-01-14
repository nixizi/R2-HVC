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

#ifndef DOMINANT_H
#define DOMINANT_H

#include "point.h"

/*** typedefs(not structures) and defined constants *******/
	
/*** enums ************************************************/
	
/*** structures declarations (and typedefs of )************/
	
/*** global variables defined in .c file ******************/
	
/*** declarations of public functions *********************/

/** 
 * Reorganizes points, so that the first j points are non-dominated. Where j is the return value.
 * 
 * @param PS The array with the points
 * @param idx An array with point indexes
 * @param n The number of points
 * @param z The zero bounding point
 * @param o The one bounding point
 * @param p The pivot point
 * @param hypoct The hyperoctant in question
 * @param exclude BitMask with excluded dimensions
 * 
 * @return The number of non-dominated points
 */
int dominant(point* PS, int* idx, int n, 
             point *o, 
             point *p,
             int hypoct,
             int exclude);
	
/*** inline functions *************************************/

#endif /* DOMINANT_H */
