/*@
    requires b > 0;                                 
    ensures 0 <= \result < b;
    ensures \exists integer q; a == b * q + \result;
*/
int rem(int a, int b) {
    /*@
        loop invariant a < b;
        loop invariant 0 <= a < b * (\at(a, Pre)/b + 1);
        loop assigns a;
        loop variant a;
    */
 while (a >= b){
   a = a - b;
}
 return a;
}