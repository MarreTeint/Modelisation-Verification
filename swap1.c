void swap(int a, int b) {
 int x = a;
 int y = b;
 int tmp;
 //@ assert x == a && y == b;
 tmp = x;
 x = y;
 y = tmp;
 //@ assert y == a && x == b;
}
