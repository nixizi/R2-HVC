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

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#undef _GNU_SOURCE
#include <string.h>
#include <assert.h>
#include <sys/resource.h>
#include "point.h"
#include "quickhvolume.h"
#include "splitter.h"
#include "subsets.h"
#include "unionFilter.h"
#include "naiverandom.h"
#include "HSO.h"
#include "inexclusion.h"

/** 
 * @param s The number of seconds to wait
 * @param n The number of points
 * @param L The points
 * 
 * @return The quickvolume, recomputed to s seconds
 */
/* static double testQV(int s, int n, point* L); */

/*** public functions *************************************/

/* static double testQV(int s, int n, point* L) */
/* { */
/*   int r; */
/*   double res; */
/*   struct timeb bg; */
/*   struct timeb end; */

/*   ftime(&bg); */

/*   r = 0; */
/*   do { */
/*       res = quickHVolume(n, L); */
/*       r++; */
/*       ftime(&end); */
/*   }   while(end.time - bg.time < s); */

/*   printf("Rep:%d\t ", r); */

/*   return res; */
/* } */

void Pswap(point *A, int i, int j)
{
  point t;
  
  t = A[i];
  A[i] = A[j];
  A[j] = t;
}

/** 
 * simple input parser for quickvolume
 * 
 * @param argc 
 * @param argv 
 * 
 * @return 0 because everything was ok
 */
int main(int argc, char** argv)
{
  int i;                        /**< Counter to n */
  int n;                        /**< Size of point list */
  int a;                        /**< Amount of alloced memory */
  point* L;                     /**< List of alloced points */
  double* exHV;                 /**< List of exclusive volumes */
  point* T;                     /**< Temporary pointer */
  size_t k;                     /**< Size of alloced line */
  char* line;
  int read;
  double HV;                    /**< The HyperVolume */

  struct timeval tv1, tv2;
  struct rusage ru_before, ru_after;

  double max = 1.0;

  if (argc > 1) stdin = fopen(argv[1], "r");
  if (argc > 2) max = atof(argv[2]);

  printf("Copyright (c) Year(s), 2013, Luis M. S. Russo and Alexandre \n");
  printf("P. Francisco / KDBIO / INESC-ID, <qhv@kdbio.inesc-id.pt> \n");
  printf(" \n");
  printf("Any published media that is related with to use of the distributed \n");
  printf("software, or derived software, must contain a reference to \"Luís  \n");
  printf("M. S. Russo, Alexandre P. Francisco: Extending quick hypervolume.  \n");
  printf("J. Heuristics 22(3): 245-271 (2016).\" \n");
  printf("  \n");
  printf("Permission to use, copy, modify, and/or distribute this software for  \n");
  printf("any purpose with or without fee is hereby granted, provided that the  \n");
  printf("above copyright notice and this permission notice appear in all  \n");
  printf("copies.  \n");
  printf("  \n");
  printf("THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL  \n");
  printf("WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED  \n");
  printf("WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE  \n");
  printf("AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL  \n");
  printf("DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR  \n");
  printf("PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER  \n");
  printf("TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR  \n");
  printf("PERFORMANCE OF THIS SOFTWARE.  \n");
  
  a = 0;
  n = 0;
  k = 0;
  line = NULL;
  L = NULL;
  exHV = NULL;
  read = 0;
  resetHSO();                   /**< Initiate the HSO sub-calculator */
  IECinit();
  initSplitter();
  /* printf("N is %d\n", N); */

  do{
    read = getline(&line, &k, stdin);
    if(read > 0)
      {
        switch(line[0])
          {
          case '#':
            if(n > 0)
              {
#ifndef COUNT
                getrusage (RUSAGE_SELF, &ru_before);
#endif /* COUNT */
                initUnion(n);
                HV = quickExHVolume(n, L, exHV);
#ifndef COUNT
                printf("%1.10f\n", HV);

                i = 0;
                while(i < n)
                  {
                    printf("Ex[%d] = %1.10f\t", i, exHV[i]);
                    if(((i-1) % 10) == 0)
                      printf("\n");
                    i++;
                  }
                printf("\n");

                /* i = 0; */
                /* while(i < n) */
                /*   { */
                /*     Pswap(L, 0, i); */
                /*     HV = quickExHVolume(n, L, exHV); */
                /*     HV -= quickExHVolume(n-1, &(L[1]), &(exHV[1])); */
                /*     printf("ExHv[%d] = %1.10f\n", i, HV); */
                /*     assert((exHV[0] < 0.000000001) || fabs(1-(HV/exHV[0])) < 0.0000001); */

                /*     if(((i-1) % 10) == 0) */
                /*       printf("\n"); */
                /*     i++; */
                /*   } */
                /* printf("\n"); */

                getrusage (RUSAGE_SELF, &ru_after);
		        tv1 = ru_before.ru_utime;
                tv2 = ru_after.ru_utime;
                printf("Time: %f (s)\n", tv2.tv_sec + tv2.tv_usec * 1e-6 - tv1.tv_sec - tv1.tv_usec * 1e-6);
#endif /* COUNT */
              }
            n = 0;
            break;
          default:
            if(n == a)
              {
                a++;
                a*=2;
                exHV = (double*) realloc(exHV, a*sizeof(double));
                L = (point*) realloc(L, a*sizeof(point));
                if(((int)L % 16) != 0)
                  {
                    posix_memalign((void**)&T, 16, a*sizeof(point));
                    memcpy(T, L, n*sizeof(point));
                    free(L);
                    L = T;
                  }
              }
            
            parsePoint(line, &L[n], max);
            n++;
            break;
          }
      }
  }while(read > 0);

  free(exHV);
  free(L);
  free(line);
  destroySplitter();

  if (argc > 1) fclose(stdin);

  return 0;
}
