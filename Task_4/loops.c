/*@ requires x>=0 ; 
ensures \result==0 ;
*/
int loop1(int x){
 int n = x;
 /*@  
     loop invariant n>=0;
     loop assigns n;
     loop variant n;

 */
 while (n>0) n--;
 return n;
}

/*@ requires x<100 ; 
@ensures \result==100 ;
*/
int loop2(int x){
 int  n=x;
 /*@  
    loop invariant n < 100;
    loop assigns n;
    loop variant 100 - n;
 */
 while (n<100) n++;
 return n;
}

/*@ ensures \result==100 ;
*/
int loop3(int x){
 int  n=x;
 if (n>=100) 
 return 100;
 else {
 /*@  
     loop invariant n < 100 ;
     loop assigns n ;
     loop variant 100 - n;
 */
 while (n<100) n++;
 return n;
 }
}