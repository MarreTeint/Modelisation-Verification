/*@ ensures \result == (\max(x, y));
    assigns \nothing;
*/
int maxint(int x, int y) {
    return (x > y) ? x : y;
}

/*@ ensures \result == (\max(\max(x, y), z));
    assigns \nothing;
*/
int maxint3(int x, int y, int z) {
    return maxint(maxint(x, y), z);
}