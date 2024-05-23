/*@
    requires b > 0;
    ensures 0 <= \result < b;
    ensures \exists integer q; a == b * q + \result;
*/
int rem(int a, int b) {
    /*@
        loop invariant a >= 0;
        loop invariant \exists integer k; \at(a, Pre) == b * k + a;
        loop assigns a;
        loop variant a;
    */
 while (a >= b){
   a = a - b;
}
 return a;
}