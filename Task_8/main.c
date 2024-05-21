/*@
    requires b > 0;                                 
    ensures 0 <= \result < b;
    ensures \exists integer q; a == b * q + \result;
*/
int rem(int a, int b) {
    /*@
        loop invariant a < b;
        loop assigns a;
        loop variant a;
    */
 while (a >= b){
   a = a - b;
}
 return a;
}