#include <limits.h>
/*@
   requires a > INT_MIN;
   ensures \result == \abs(a);
 */
int abs (int  a){
    int aux = a;
    if (aux < 0){
        aux = - aux;
    }
    return a;
}