#include <math.h>
#include "antipole.h"


double dist( struct point p1, struct point p2 ) {
   int i;
   double sum = 0;
   for( i = 0; i < DIM; i++ )
      sum += pow(p1.vec[i]-p2.vec[i],2);
   return sqrt(sum);
}

