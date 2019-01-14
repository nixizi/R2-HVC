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
 * @file   inexclusion.h
 * @author Luis Russo <lsr@lsr-ThinkPad-X201>
 * @date   Fri Feb  3 16:30:06 2012
 * 
 * @brief  Inclusion Exclusion Algorithm better than HSO for high d and small n
 * 
 */
	
#ifndef INEXCLUSION_H
#define INEXCLUSION_H

#include "point.h"

/*** typedefs(not structures) and defined constants *******/
	
/*** enums ************************************************/
	
/*** structures declarations (and typedefs of )************/
	
/*** global variables defined in .c file ******************/
	
/*** declarations of public functions *********************/

/** 
 * This algorithm also needs to be initialized 
 */
void IECinit(void);

/** 
 * 
 * @param zero The min coordinates point
 * @param one The max coordinates point
 * @param n The number of points
 * @param idx The idx array
 * @param PS The point array
 * 
 * @return The hyperVolume computed with cache-oblivious IEC
 */
double exInExClusion(point* zero, point* one, int n, int* idx, point* PS, double* exHV);
	
/*** inline functions *************************************/

#endif /* INEXCLUSION_H */
