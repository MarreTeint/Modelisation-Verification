/*@ ensures A: *a == \old(*b) ;
@ ensures B: *b == \old(*a) ; */
void swap(int *a,int *b)
{
 int tmp = *a ;
 *a = *b ;
 *b = tmp ;
}