/*@
   requires a > -2147483648;
   ensures \result == (a < 0 ? -a : a);
 */
int abs (int  a){
    int aux = a;
    if (aux < 0){
        aux = - aux;
    }
    return a;
}