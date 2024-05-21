/*@ ensures \result == (\max(x, y));
    assigns \nothing;
*/
int maxint(int x, int y) {
    return (x > y) ? x : y;
}