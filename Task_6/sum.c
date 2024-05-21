/*@ ensures \result == n * n; */
int f(int n) {
 int i = 0;
 int s = 0;
 /*@ loop invariant i * i == s;
   @ loop assigns i, s; */
 while (i != n) {
   i++;
   s += 2 * i - 1;
 };
 return s;
}