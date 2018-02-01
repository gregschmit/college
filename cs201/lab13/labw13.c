#include <stdio.h>
#include <stdlib.h>
#include "vec.h"
#include "solver.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//=================================================================================================


void printStats(stats* stats, int cpu_time)
{

    printf("restarts          : %12d\n", stats->starts);

    printf("conflict literals : %12.0f           (%9.2f %% deleted  )\n", (double)stats->tot_literals, (double)(stats->max_literals - stats->tot_literals) * 100.0 / (double)stats->max_literals);

}

int main(int argc, char *argv[]) {

    solver* s = solver_new();
    lbool   st;
    veci lits;
    lit* begin;
    int clk = clock();
/**** Do not change anything above this line ***/

// 1) (!x1 + !x2)(x1 + x2 + x3)(x1)
// 2) 3 clauses
// 3) Solution returns true

/* Put your code here */
veci_new(&lits);
veci_resize(&lits, 0);
veci_push(&lits, lit_neg(toLit(0)));
veci_push(&lits, lit_neg(toLit(1)));
begin = veci_begin(&lits);
solver_addclause(s, begin, begin+veci_size(&lits));
veci_delete(&lits);

veci_new(&lits);
veci_resize(&lits, 0);
veci_push(&lits, toLit(0));
veci_push(&lits, toLit(1));
veci_push(&lits, toLit(2));
begin = veci_begin(&lits);
solver_addclause(s, begin, begin+veci_size(&lits));
veci_delete(&lits);

veci_new(&lits);
veci_resize(&lits, 0);
veci_push(&lits, toLit(0));
begin = veci_begin(&lits);
solver_addclause(s, begin, begin+veci_size(&lits));
veci_delete(&lits);

/* Don't need to change anything below this line, for lab */
/* Here is where we ask minisat to find a solution that causes our
collection of clauses to be true */

 st = solver_solve(s,0,0);
 printStats(&s->stats, clock() - clk);
 printf("\n");
 printf("%d",st);
 printf("model size %d\n",s->model.size);
 // print the sat assignment
    if ( st == l_True )
    {
        int k;
        printf( "\nSatisfying solution: " );
        for ( k = 0; k < s->model.size; k++ )
            printf( "x%d=%d ", k, s->model.ptr[k] == l_True );
        printf( "\n" );
    }



	return 0;
}
