/*@ requires \valid(t+(0..n-1)) && \valid(u+(0..n-1));
  ensures \result <==> \forall integer i; 0 <= i < n ==> t[i]==u[i]; 
 @*/
int equal(int t[], int u[], int n) {
   /*@ loop invariant 0 <= k <= n;
        loop invariant \forall integer i; 0 <= i < k ==> t[i] == u[i];
        loop assigns k;
        loop variant n - k;
      @*/
   for (int k = 0; k < n; k++) if (t[k]!=u[k]) return 0;
   return 1;
}