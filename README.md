# Modelisation-Verification
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Frama-C](https://img.shields.io/badge/Frama--C-00599C?style=for-the-badge&logo=frama-c&logoColor=white)


## Proof of programs -- Mini-Project

This project must be done by teams of (at least 2 and at most 4) students. 
Each team must deliver :
- a detailed report (a pdf file) named *Lastname-ProjectProof.pdf*, e.g.: *Martin-ProjectProof.pdf*
- an archive containing your source files

The deadline for the final submission will be given by the professor.
Please classify the responses in your report by section/number...
Your report must contain the team members names
Your report will be sent to asma.berriri@universite-paris-saclay.fr
This project allows you to apply Hoare logic on C programs. One has first to annotate source code with pre and postconditions, loop invariants and variants (to prove the termination of loops). Then an automatic tool produces a collection of logical formulas (first order logic), called proof obligations (POs). They correspond to the verification conditions of the annotated program. If these proof obligations are valid (true), then the program is correct with respect to its contract. Automatic provers are used to prove the validity of formulas.

## Installation

Frama-C? WP?
Frama-C (pour FRAmework for Modular Analysis of C code) est une plate-forme dédiée à l’analyse de programmes C créée par le CEA List et Inria. Elle est basée sur une architecture modulaire permettant l’utilisation de divers plugins. Les plugins fournis par défaut comprennent diverses analyses statiques (sans exécution du code analysé), dynamiques (avec exécution du code), ou combinant les deux. Ces *plugins* peuvent collaborer ou non, soit en communiquant directement entre eux, soit en utilisant le langage de spécification fourni par Frama-C.

Ce langage de spécification s’appelle ACSL (« Axel ») pour ANSI C Specification Language et permet d’exprimer les propriétés que nous souhaitons vérifier sur nos programmes. Ces propriétés seront écrites sous forme d’annotations dans les commentaires. L’analyse que nous allons utiliser ici est fournie par un plugin appelé WP pour Weakest Precondition, un plugin de vérification déduction. Il implémente la technique dont nous avons parlé dans le cours: à partir des annotations ACSL et du code source, le plugin génère ce que nous appelons des obligations de preuves, qui sont des formules logiques dont nous devons vérifier si elles sont vraies ou fausses (on parle de «satisfiabilité»). Cette vérification peut être faite de manière manuelle ou automatique, ici nous n’utiliserons que des outils automatiques.
Installation Frama-C, WP
Frama-C est un logiciel développé sous Linux et OSX. Son support est donc bien meilleur sous ces derniers. Il existe quand même de quoi faire une installation sous Windows et en théorie l’utilisation sera sensiblement la même que sous Linux, mais :
Je donne ici une possibilité d'installation sous Linux (Via opam) et c'est à vous de chercher comment l'installer avec d'autres gestionnaires de packages, avec Windows ou avec MacOS (selon votre OS);
Les versions récentes de Windows 10 permettent d’utiliser Windows Subsystem for Linux (WSL), en combinaison avec un Xserver installé sous Windows pour avoir la GUI ;

### Installation via Opam

Opam, un gestionnaire de paquets pour les bibliothèques et applications OCaml. D’abord, Opam doit être installé et configuré sur votre distribution (voir leur documentation).
```shell
sudo apt install opam
```
Ensuite, il faut également que quelques paquets de votre distribution soient présents préalablement à l’installation de Frama-C. Sur la plupart des distributions nous pouvons demander à Opam d’aller chercher les bonnes dépendances pour le paquet que nous voulons installer. Pour cela, nous utilisons l’outil depext d’Opam, qu’il faut d’abord installer :
```shell
 opam install depext
```
Puis nous lui demandons de prendre les dépendances de Frama-C :
```shell
 opam depext frama-c
```
Enfin, du côté d’Opam, il reste à installer Frama-C et Alt-Ergo.
```shell
opam install frama-c
opam install why3 why3-ide alt-ergo
```
Pour ajouter d'autres prouvers (cvc4 par exemple)
```shell
wget https://github.com/CVC4/CVC4/releases/download/1.7/cvc4-1.7-x86_64-linux-opt
sudo cp cvc4-1.7-x86_64-linux-opt /usr/local/bin/cvc4
sudo chmod +x /usr/local/bin/cvc4
cvc4 --version
```
Pour ajouter d'autres prouvers (z3)
```shell
wget https://github.com/Z3Prover/z3/releases/download/z3-4.8.6/z3-4.8.6-x64-ubuntu-16.04.zip
unzip z3-4.8.6-x64-ubuntu-16.04.zip
sudo cp z3-4.8.6-x64-ubuntu-16.04/bin/z3 /usr/local/bin
sudo chmod +x /usr/local/bin/z3
z3 --version
```
Après l'installation, n'oubliez pas d'exécuter
```shell
why3 config detect
why3 config list-provers
```

## Tools

This project uses the Frama-C platform (http://frama-c.com) and more precisely the WP plugin.
You can edit the C files as usual with your preferred editor (emacs, vi ...etc.) or by doing a copy-paste from this subject. The verification tools will be run from a terminal window (shell), you can use either the graphical interface (frama-c-gui) or the command line interface (frama-c -wp). See frama-c -help for help and frama-c -wp-help for help on the WP plugin. The gui is preferred for this project.

Before running the WP plugin for the first time, please execute the command why3 config in a shell.

The graphical interface
Execute frama-c-gui file.c
We get a screen with different parts. The right-hand side shows the original source code. In the middle, we see a normalized version of the source code. Frama-C does some re-writing of the source code to make the analysis simpler. For instance, it re-writes all kinds of loops (for-loops, do-while-loops) into simple while-loops, it may split complicated instructions into several simpler instructions, it makes implicite casts explicite, and so on. Ususally, it should not be too difficult to find the correspondences between the original source code and the normalized source code. You can also click onto a certain line in the normalized source code and the tool will automatically highlight the corresponding line in the original source code.

The status of the properties is illustrated with bubbles on the left side of the properties.
A green bubble means that the property is Valid (has been proved). Other colors mean that this is not (yet) the case. blue means waiting for the proof. orange means the proof attempt has failed ; green/orange means proved by assuming an other orange goal. Usually, our objective is to get all bubbles green.

To prove the correctness of a function, right-click onto the contract and choose Prove property by WP (you can also do this using special command-line arguments if you want). The tab WP Proof Obligations shows the different proof goals and their status.

Note that the Frama-C GUI is not a source code editor. That is, you cannot modify the code that is being analyzed directly in the Frama-C GUI. After modifying the source code with some editor, you can either close and re-open the Frama-C GUI, or click on File and then on Reparse for this modification to be recognized by Frama-C. Several provers may be needed to discharge all the proof obligations. Try first with the built-in provers (Qed and alt-ergo), then try also cvc4 and z3.
Qed is not really a proover, it simplifies formulas. It may be enough to prove simple proof obligations.

The command line
 frama-c toto.c -wp 
The option -wp-prover allows the submission of the proof obligations to external prover(s).
Supported provers:
                    - 'alt-ergo' (default)
                    - 'altgr-ergo' (gui)
                    - 'coq', 'coqide' (see also -wp-script)
                    - 'why3:' or '' (why3 prover, see -wp-detect)
                    - 'why3ide' (why3 gui)
You can use here alt-ergo, cvc4, z3 or simplify.
Example :
```shell
frama-c -wp find.c -wp-prover cvc4

[kernel] preprocessing with "gcc -C -E -I.  find.c"
[wp] Running WP plugin...
[wp] Collecting axiomatic usage
[wp] warning: Missing RTE guards
[wp] 9 goals scheduled
[wp] [Qed] Goal typed_find_loop_inv_established : Valid
[wp] [Qed] Goal typed_find_loop_assign : Valid
[wp] [Qed] Goal typed_find_loop_term_decrease : Valid
[wp] [Cvc4] Goal typed_find_complete_not_found_found : Valid (20ms)
[wp] [Qed] Goal typed_find_loop_term_positive : Valid
[wp] [Cvc4] Goal typed_find_loop_inv_preserved : Valid (20ms)
[wp] [Cvc4] Goal typed_find_disjoint_not_found_found : Valid (20ms)
[wp] [Cvc4] Goal typed_find_found_post : Valid (Qed:4ms) (20ms)
[wp] [Cvc4] Goal typed_find_not_found_post : Valid (720ms)
```

## Usage

The first step needs to annotate C programs with formal specifications. The annotations are inserted in the programs as special comments, taking the form /*@ ... * /. Let us verify the following program that computes the minimum element of an array (please do the different steps):
 ```c   
int getMin(int t[], int n) { 
	int res = t[0];
	for (int i = 1; i < n; i++) 
	    if (t[i] < res) res = t[i];
	return res;
    }

 ```
Annotation of the function
A pre-condition is introduced with the keyword requires in a comment before the fonction definition. Then

 ```c
/*@ requires \valid(t+(0..n-1)) && n > 0;
...
 */

 ```
indicates the function getMin waits for an array (non null) that has at least n elements. The new predicate valid(t+(0..n_1)) is used to specify that all memory locations t[i] for i in [0..n-1] are valid.
Don't forget the semicolon at the end of the annotation.
The postcondition is introduced by the keyword ensures. Thus a (partial) postcondition for getMin may be

 ```c
/*@ ...
  ensures \forall integer i; 0 <= i < n ==> \result <= t[i];
 */
  int getMin(int t[], int n) { ... }

 ```
It indicates the result is smaller than each element in t. Remember the value returned by the function is denoted by \result. Notice also that we use a universal quantification (forall) over the type integer, that represents in the formula the mathematical integers (Z) and not the type int of C (machine integers).
Precondition and postcondition are optional; when both are present, they must appear in the same comment and each one ends with a semicolon. Then we write

 ```c
   /*@ requires ...;
       ensures ...;
   */
  int getMin(int t[], int n) { ... }

 ```
Syntax of the annotations
The syntax for the logical formulas used in the annotations is given below. Any pure C expression, that is without side effects (modifications of variables e.g.) and without any function call, can be used in an annotation. The implication is written ==>, the equivalence symbol <==> and the universal quantification \forall.
Annotation in the loops
As explained in the lectures, the formal proof of a program requires usually to annotate loops with loop invariants. A loop invariant is introduced in a comment before the loop with the keywords loop invariant. In the example below, a convenient loop invariant is the following:

 ```c
	/*@ loop_invariant 
	     1 <= i <= n &&
	     (\forall integer j; 0 <= j < i ==> res <= t[j]); 
	 */
	for (int i = 1; i < n; i++) 
            ...

 ```
This invariant expresses that i is always between 1 and n and also that res is smaller than all the values t[0],...,t[i-1]. Notice that we have to wite i <= n (and not i < n) because the invariant must be satisfied at the end of the last execution of the loop body, where i = n.
You can also split this complex invariant in 2 simpler invariants (and also for pre and post conditions in a contract):

 
 ```c
	/*@ loop_invariant 1 <= i <= n ;
	    loop invariant  (\forall integer j; 0 <= j < i ==> res <= t[j]); 
	 */
	for (int i = 1; i < n; i++) 
            ...
To prove the termination of the loop, we need to specify a variant, that is a natural number (or expression) that decreases at each loop execution. Here n-i is OK:

	/*@ loop invariant 
	      ...
	  @ loop variant
	  @   n - i;
	  @*/
	for (int i = 1; i < n; i++) 
            ...

 ```
The invariant and the variant must both be given in a unique comment. Both end with a semicolon. It is also required to add an annotation enumerating the variables which are modified by the loop body in the clause loop assigns. Notice that although i is modified, it does not have to be written because it is a varaible introduced by the for loop.
The entirely annotated source (that should be given in the file getMin.c) is thus the following one:

 ```c
/*@ requires \valid(t+(0..n-1)) && n > 0;
    ensures  \forall integer i; 0 <= i < n ==> \result <= t[i];
 */
int getMin(int t[], int n) { 
	int res = t[0];
	/*@ loop invariant 
	     1 <= i <= n && (\forall integer j; 0 <= j < i ==> res <= t[j]); 
            loop assigns res, i;
            loop variant  n - i;
	  */
	for (int i = 1; i < n; i++) 
	    if (t[i] < res) res = t[i];
	return res;
    }

 ```
The specification is not complete. It only says that the result is a value smaller or equal to any integer stored in the array. It does not say that the minimum is a value stored in the array.
Automatic proof of correctness
In the lab session we'll adopt the following strategy: each proof obligation must be proved by at least a prover, whatever it is. Don't run several provers simultaneusly but sequentially if necessary).
When a proof obligation is not proved, there are 3 possible reasons:

the program is incorrect ; So we have found a bug in the program :)
the specification is incorrect, i.e. it can also be the case that the program is underspecified (we did not tell enough !). It is often the case when we start with formal specification.
the prover is not powerful enough ; it is nearly a fatality because first order logics is undecidable. Nevertheless, in this session lab, the objective is to obtain a 100% score for automatic proofs. It means you will have to call your program or your specification into question before incriminating the provers.
Check the correctness of the annotated previous program (file getMin.c).
Once the program is annotated, you can go on with its verification. To do this, execute the following command:

 ```shell
frama-c -wp getMin.c

 ```
where getMin.c is the file annotated source file.
A window appears, it must look like
FarmaC interface
Then run the automatic proof tools by clicking on the prover(s) you want to execute (z3, etc). The result on each proof obligation is indicated by an icon.

## Tasks

The aim of this mini-project is to use the WP plugin of the Frama-C tool, which uses Hoare's logic, and more precisely the calculation of the weakest precondition to enable the proof of specifications of annotated programs written in C.
Solve each task in a separate c file (For each task give a conclusion about the proof of the POs). Put all files in an archive (e.g., zip, tar). The archive should be sent together with your report to the professor

### Task 1: Maximun of 2 integers - file maxint.c
Let us start with a very simple program

 ```c
int maxint (int x, int y) { return (x > y) ? x : y; }

 ```
This program is supposed to calculate the greatest of both x and y.

Write the contract and run the verification.

Hint : here, the contract contains only a post-condition (ensures clause), as maxint does not have any particular requirement. The first part of the ensures clause expresses the fact that the result of maxint is greater than both x and y, the arguments of maxint. The second part mandates that the result is equal to either x or y. Since both parts (bound with &&) must hold, the specification indeed expresses that the result of maxint is the greatest of its two arguments. The built-in provers should be sufficient. (you can illustrate your answer by screenshots)

### Task 2: Maximum of 3 values - file maxint3.c
Write the contract of the function maxint3
Implement this function using the previous function maxint.
Prove the correctness of maxint3

### Task 3: Swap - file swapX.c

In a swap1.c file, write the following annotated C function:

 ```c
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

 ```
Comments starting with @ are used by the WP plugin to indicate program annotations. In particular, //@assert ... allows you to add assertions of Hoare triples. Run
frama-c-gui swap1.c
Click on swap1.c on the left, its contents appear. By right-clicking on the asserts, ask the WP plugin to prove the assertions. Open the “WP goals” tab at the bottom. We see two green circles in the Qed column, which means that the assertions have been proven only by simplifying the verification conditions, without calling on an external prover.
Close Frame-C, and write a new swap2.c file:

 ```c
void swap(int a, int b) {
  int x = a;
  int y = b;
  //@ assert x == a && y == b;
  x = 2 * (x + y);
  y = x / 2 - y;
  x = x / 2 - y;
  //@ assert y == a && x == b;
}

 ```
Relaunch Frama-C, prove the assertions. In the “WP proof obligations” tab, we notice that the second assertion required the use of an external prover, in this case Alt-Ergo. Alt-Ergo is an automatic prover from the family of SMT provers, which are particularly good in linear arithmetic and when there are no quantifiers.
In general, we do not write the assertions, but we write the specifications of the program functions. Write a swap3.c file containing:

 ```c
/*@ ensures A: *a == \old(*b) ;
@ ensures B: *b == \old(*a) ; */
void swap(int *a,int *b)
{
  int tmp = *a ;
  *a = *b ;
  *b = tmp ;
}

 ```
The ensures ... annotation indicates the contract that the function must respect; \old(x) means the value x had before the function was executed. Use Frama-C to prove that the function verifies its specification
### Task 4: Loop annotations - file loops.c
Here we will just try to verify very simple programs with loops. You have to complete the loop invariant and the loop variant. You have to add a loop assigns clause : this clause precises what variables are assigned in the loop body.

As an example, you are provided with loop1 function below. This function is complete. Play with it to understand what it does and try to see what happens when you remove for example the loop invariant or the loop variant.

 ```c
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

 ```

Complete the second function loop2 with the loop annotations.

 ```c
/*@ requires x<100 ; 
@ensures \result==100 ;
*/
int loop2(int x){
  int  n=x;
  /*@  
      loop invariant ... ;
      loop assigns .. ;
      loop variant ...;

  */
  while (n<100) n++;
  return n;
}

 ```
Complete the third function loop3 with the postcondition and the loop annotations. In this case no precondition is required (x may be any integer). Remember the invariant must be verified before entering the loop.
 ```c
/*@ ensures .....  ;
*/
int loop3(int x){
  int  n=x;
  if (n>=100) 
  return 100;
  else {
  /*@  
      loop invariant ... ;
      loop assigns ... ;
      loop variant .... ;

  */
  while (n<100) n++;
  return n;
  }
}
 ```
### Task 5: Absolute value - file abs.c
Complete the contract of the following program and verify that at the end of its execution a points to the absolute value of its initial value.

 ```c
 /*@
    ....
  */
int abs (int  a){
int aux = a;
if (aux < 0){
 aux = - aux;
}
return a;
}
 ```
Pay attention to overflows!! Check potential runtime errors with the rte plugin: frama-c -wp -wp-rte abs.c. If it fails, complete the contract by adding the right precondition. From now on, use both wp and rte pluggins.

### Task 6: Sum of odds - file sum.c

We want to show that the sum of the first n odd numbers is equal to n^2. In a sum.c file, we consider the function:
 ```c
/*@ ensures \result == n * n; */
int f(int n) {
  int i = 0;
  int s = 0;
  while (i != n) {
    i++;
    s += 2 * i - 1;
  };
  return s;
}
 ```
As its name suggests, \result corresponds to the result returned by the function. In Frama-C, note that it is not possible to prove the correctness of the function. To be able to show this correction, you must add an annotation to the loop, in particular by indicating the loop invariant. We must also indicate which variables are modified in the body of the loop. To do this, we add the following annotations just before the loop:
 ```c
 /*@ loop invariant i * i == s;
@ loop assigns i, s; */

 ```
Relaunch Frama-C, we can now prove the assignment and correction of the function and the invariant. Please do it.
### Task 7: Guess what foo does - file foo.c
 ```c
int foo(int n) {
  int x = 0;
  int y = x;
  while (x != n) {
    x = x + 1;
    y = y - 1;
  }
  return x - y;
}
 ```
What does the above function do when n is a positive number n>=0? Write its contract (with a precondition specifying n>=0) and prove its correctness w.r.t. this contract.
### Task 8: Rest of Euclidean division - file reminder.c
We consider the following function, which must return the remainder of the Euclidean division of a by b
 ```c
int rem(int a, int b) {
  while (a >= b){
    a = a - b;
 }
  return a;
}
 ```
Give the specification of rem; To make the proof easier, use integer and not int as the type for the quotient
Find a loop invariant
Show that the function contract is valid assuming that the invariant is verified
Try to prove the loop invariant. Alt-ergo can't do it. We will use Coq to achieve our goals.
The use of Coq with Frama-C is deprecated, but it is possible to enable it by passing the -wp-prover=native:coq option to frama-c-gui. In the “WP Goals” tab, we see that Alt-Ergo failed for the proof of the preservation of the invariant. Looking at the formula to be demonstrated, this is not surprising since there is an existential quantifier. We will therefore use Coq to demonstrate this sub-goal, by double-clicking in the box in the Coq column and the Invariant (established) row. A window of the Coq proof graphical environment opens

### Task 9: Index of the minimum of an array - file getIndexMax.c

Adapt the program getMin (given in the introduction) in order to compute the index of the minimum of a non-empty array (n is the length of the array). Write its contract and then its code. Then prove its correctness.

### Task 10: Is an array full of 0 ? - file allZeros.c

We consider a function all_zeros that takes as arguments an array and its length and determines whether all its elements are zero or not. The source and its specification are as follows:
 ```c
/*@ requires \valid(t+(0..n-1));
    ensures \result <==> \forall integer i; 0 <= i < n ==> t[i]==0; 
  @*/
int all_zeros(int t[], int n) {
    /*@ loop invariant ...; 
        loop assigns .... ;
        loop variant   ...;

      @*/
    for (int k = 0; k < n; k++) if (t[k]!=0) return 0;
    return 1;
}
 ```

Give the invariant loop and the variant in order to prove the correctness of this programme.

### Task 11: Are two arrays equal ? - file equal.c

We consider that 2 arrays are equal if they contain the same values in the same order. The arrays are expected to have the same length.
 ```c
/*@ requires \valid(t+(0..n-1)) && \valid(u+(0..n-1));
   ensures \result <==> \forall integer i; 0 <= i < n ==> t[i]==u[i]; 
  @*/
int equal(int t[], int u[], int n) {
    /*@ loop invariant ...;
        loop assigns .... ;
        loop variant   ...; 
      @*/
    for (int k = 0; k < n; k++) if (t[k]!=u[k]) return 0;
    return 1;
}

 ```
Give the invariant loop and the variant in order to prove the correctness of this programme.

### Task 12: Fill an array - file fill.c

Here is an example of program that fills an array with a given value. The pre-condition explains that the resulting array must have been allocated before the call. The assign clause precises what will be modified in this array by the function.
 ```c
/*@
requires \valid(a+(0..(n-1))) && n>=0;
assigns a[0..n-1];
ensures ....
 */
void fill( int* a, int n, int val)
 {
 /*@
 loop invariant ....
 loop assigns i, a[0..n-1];
 loop variant .... ;
 */
 for (int i = 0; i < n; i++)
   a[i] = val;
 }
 ```
Complete the post-condition, the invariant and variant. Prove the correctness of the program with respect to its specification.

### Task 13 : Factorial - file fact.c

 ```c
int fact (int n) {
  int y = 1;
  int x = n;
  while (x > 1) {
    y = y * x;
    x = x - 1;
  }; 
  return y;
}
 ```
We need to express the specification of the function, thus we need a definition of the notion of factorial. In mathematics, the factorial of a non-negative integer n, denoted by n!, is the product of all positive integers less than or equal to n. For example, 5! = 5 * 4 * 3 * 2 * 1 = 120. The value of 0! is 1. This definition can also be expressed with the help of a recurrence relation: n! = 1 if n=0, n! = (n-1)! * n if n > 0. We add a similar definition in the file fact.c as a comment:
 ```c
/*@ axiomatic Fact {
  @   logic integer Fact(integer n);
  @   axiom Fact_1: Fact(0) == 1;
  @   axiom Fact_rec: \forall integer n; n > 0 ==> Fact(n) == n * Fact(n-1);
  @}*/
 ```
We declare a logical function Fact, it is only used in the contract and in the annotations. This function is defined with 2 axioms (2 facts), Fact1 and Fact2. These 2 facts are logical first order predicates. Then we can define the contract of the function:
 ```c
/*@ requires n >= 0;
  @ ensures \result == Fact(n);
*/
 ```
Prove the correctness of the annotated function fact.
