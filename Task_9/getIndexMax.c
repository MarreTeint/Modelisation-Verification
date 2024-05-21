/*@
    requires \valid(t + (0..n-1)) && n > 0;
    ensures 0 <= \result < n && \forall integer i; 0 <= i < n ==> t[\result] <= t[i];
*/
int getIndexMax(int t[], int n) {
    int maxIndex = 0; // Initialize index of maximum element
    int maxValue = t[0]; // Initialize maximum value

    /*@
        loop invariant 1 <= i <= n && maxIndex >= 0 && maxIndex < n && maxValue == t[maxIndex];
        loop invariant \forall integer j; 0 <= j < i ==> t[maxIndex] >= t[j];
        loop assigns maxIndex, maxValue, i;
        loop variant n - i;
    */
    for (int i = 1; i < n; i++) {
        if (t[i] > maxValue) {
            maxValue = t[i];
            maxIndex = i;
        }
    }
    
    return maxIndex;
}
