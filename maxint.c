/*@ requires \valid_read(&x);
    requires \valid_read(&y);
    ensures \result == (\max(x, y));
    assigns \nothing;
*/
int maxint(int x, int y) {
    return (x > y) ? x : y;
}