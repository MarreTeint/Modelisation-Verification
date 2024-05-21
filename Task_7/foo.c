/*@
    requires n >= 0;         
    ensures \result == 2 * n;
*/
int foo(int n) {
 int x = 0;
 int y = x;
 /*@
        loop invariant 0 <= x <= n;
        loop invariant y == -x;
        loop assigns x, y;
        loop variant n - x;
    */
 while (x != n) {
   x = x + 1;
   y = y - 1;
 }
 return x - y;
}