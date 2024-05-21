void swap(int a, int b) {
 int x = a;
 int y = b;
 //@ assert x == a && y == b;
 x = 2 * (x + y);
 y = x / 2 - y;
 x = x / 2 - y;
 //@ assert y == a && x == b;
}
