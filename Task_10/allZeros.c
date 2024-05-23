/*@ requires \valid(t+(0..n-1));
   ensures \result <==> \forall integer i; 0 <= i < n ==> t[i]==0; 
 @*/
int all_zeros(int t[], int n) {
   /*@ loop invariant 0 <= k <= n;
        loop invariant \forall integer i; 0 <= i < k ==> t[i] == 0;
        loop assigns k;
        loop variant n - k;
      @*/
   for (int k = 0; k < n; k++) if (t[k]!=0) return 0;
   return 1;
}