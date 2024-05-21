/*@ axiomatic Fact {
 @   logic integer Fact(integer n);
 @   axiom Fact_1: Fact(0) == 1;
 @   axiom Fact_rec: \forall integer n; n > 0 ==> Fact(n) == n * Fact(n-1);
 @}*/

/*@ requires n >= 0;
 @ ensures \result == Fact(n);
*/
int fact (int n) {
 int y = 1;
 int x = n;
 /*@ 
      @ loop invariant 1 <= x <= n + 1;
      @ loop invariant y == Fact(n) / Fact(x - 1);
      @ loop assigns y, x;
      @ loop variant x;
      @*/
 while (x > 1) {
   y = y * x;
   x = x - 1;
 }; 
 return y;
}