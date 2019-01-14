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

/** \file  quickvolume.h
 *  \brief Header: copy quickvolume
 */
	
#ifndef QUICKVOLUME_H
#define QUICKVOLUME_H

#include "point.h"

/// For N points do cache-oblivious HSO
#ifndef COUNT
#if D == 2
#define N 1
#define HSOL N-N          /**< For larger values run HSO */
#elif D == 3
#define N 8 // Never Set larger than 31 for IEC
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 4
#define N 8
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 5
#define N 8
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 6
#define N 9
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 7
#define N 9
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 8
#define N 10
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 9
#define N 10
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 10
#define N 10
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 11
#define N 10
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 12
#define N 10
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 13
#define N 12
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 14
#define N 10
#define HSOL N-0          /**< For larger values run HSO */
#elif D == 15
#define N 10
#define HSOL N-0          /**< For larger values run HSO */
#else /* D == 16 */
#error Wrong D
#endif /* D == 9 */
#else  /* COUNT undef */
#define N 1
#define HSOL N-1
#endif /* COUNT undef */


/*** typedefs(not structures) and defined constants *******/
	
/*** enums ************************************************/
	
/*** structures declarations (and typedefs of )************/
	
/*** global variables defined in .c file ******************/
	
/*** declarations of public functions *********************/

/** 
 * @param n Number of selected points
 * @param PS List of points
 * @param exHV Returns the exclusive volume of each point
 * 
 * @return 
 */
double quickExHVolume(int n, point* PS, double* exHV);
	
/*** inline functions *************************************/

#endif /* QUICKVOLUME_H */
