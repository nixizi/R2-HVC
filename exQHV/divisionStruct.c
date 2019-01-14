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

/// This struct is public because of splitter. Do not use direct access
struct division{
  int n;                        /**< Number of hypocts left in the division.
                                 This number is decreased in each iteration */
  int* hypocts;                 /**< The hyperoctant types */
  int* pPositions;              /**< Acumulated counters give positions in point array */
  int* points;                  /**< Point indexes */
};
