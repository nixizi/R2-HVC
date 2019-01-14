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

#ifndef MACROCYCLE_H
#define MACROCYCLE_H

#if(CLS == 0)
#undef CLS
#define CLS 1024
#endif 

#define sureInline(X) __inline X __attribute__((__gnu_inline__, __always_inline__, __artificial__))

#define B1(X) (X)
#define B2(X) B1(X), (X)
#define B3(X) B2(X), (X)
#define B4(X) B3(X), (X)
#define B5(X) B4(X), (X)
#define B6(X) B5(X), (X)
#define B7(X) B6(X), (X)
#define B8(X) B7(X), (X)
#define B9(X) B8(X), (X)
#define B10(X) B9(X), (X)
#define B11(X) B10(X), (X)
#define B12(X) B11(X), (X)
#define B13(X) B12(X), (X)
#define B14(X) B13(X), (X)
#define B15(X) B14(X), (X)
#define B16(X) B15(X), (X)
#define B17(X) B16(X), (X)
#define B18(X) B17(X), (X)
#define B19(X) B18(X), (X)
#define B20(X) B19(X), (X)
#define B21(X) B20(X), (X)
#define B22(X) B21(X), (X)
#define B23(X) B22(X), (X)
#define B24(X) B23(X), (X)
#define B25(X) B24(X), (X)
#define B26(X) B25(X), (X)
#define B27(X) B26(X), (X)
#define B28(X) B27(X), (X)
#define B29(X) B28(X), (X)
#define B30(X) B29(X), (X)

#define B_(x, i) B##i(x)
#define B(x, i) B_(x, i)

#define P1 0
#define P2 1
#define P3 2
#define P4 3
#define P5 4
#define P6 5
#define P7 6
#define P8 7
#define P9 8
#define P10 9
#define P11 10
#define P12 11
#define P13 12
#define P14 13
#define P15 14
#define P16 15
#define P17 16
#define P18 17
#define P19 18
#define P20 19
#define P21 20
#define P22 21
#define P23 22
#define P24 23
#define P25 24
#define P26 25
#define P27 26
#define P28 27
#define P29 28
#define P30 29
#define P31 30
#define P32 31
#define P33 32

#define P_(i) P##i
#define P(i) P_(i)

#endif /* MACROCYCLE_H */
