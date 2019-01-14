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

#ifndef DIVISION_H
#define DIVISION_H

/*** typedefs(not structures) and defined constants *******/
typedef struct division* division;
	
/*** enums ************************************************/

/*** structures declarations (and typedefs of )************/
	
/*** global variables defined in .c file ******************/
	
/*** declarations of public functions *********************/
	
/*** inline functions *************************************/

/// New divisions are created in the splitter object

/** 
 * Free the division object
 * 
 * @param d 
 */
void freeDivision(division* d);

/** 
 * @param d The division
 * 
 * @return True if there are points of another type to process
 */
int hasNext(division d);

/** 
 * @param d The division
 * @param typ Return type by argument
 * @param n Return size of array by argument
 * 
 * @return A pointer to the array of indexes
 */
int* next(division d, int* typ, int* n);

#endif /* DIVISION_H */
