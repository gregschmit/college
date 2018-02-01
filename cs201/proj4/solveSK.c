#include "solveSK.h"
#include "solver.h"
#include <stdio.h>
#include <time.h>

int prop(int n, int r, int c, int value)
{
    return n*n*value + n*r + c;
}

int *boxvalues(int n, int r, int c)
{
    int *answerlist;
    answerlist = malloc(n*sizeof(*answerlist));
    int i;
    // scale back

    // figure out position

    return answerlist;
}

void solveSK(char ** board, int n){
    solver* s = solver_new();
    lbool   st;
    veci lits;
    lit* begin;
    int clk = clock(), r, c, i, j, k;
    int v, rowspace, colspace;

    for (v=0; v<n; v++) {
        for (r=0; r<n; r++) {
            for (c=0; c<n; c++) {
                // no duplicate values in each cell
                if (v == 0) {
                    for (i=0; i<n; i++) {
                        for (j=i+1; j<n; j++) {
                            veci_new(&lits);
                            veci_resize(&lits, 0);
                            veci_push(&lits, lit_neg(toLit(prop(n, r, c, i))));
                            veci_push(&lits, lit_neg(toLit(prop(n, r, c, j))));
                            begin = veci_begin(&lits);
                            solver_addclause(s, begin, begin+veci_size(&lits));
                            veci_delete(&lits);
                        }
                    }
                }
                // must be one of each v in each row
                if (c == 0) {
                    veci_new(&lits);
                    veci_resize(&lits, 0);
                    for (i=c; i<n; i++) {
                        veci_push(&lits, toLit(prop(n, r, i, v)));
                    }
                    begin = veci_begin(&lits);
                    solver_addclause(s, begin, begin+veci_size(&lits));
                    veci_delete(&lits);
                }
                // unique v within rowspace (redundant)
                for (rowspace=c+1; rowspace<n; rowspace++) {
                    veci_new(&lits);
                    veci_resize(&lits, 0);
                    veci_push(&lits, lit_neg(toLit(prop(n, r, c, v))));
                    veci_push(&lits, lit_neg(toLit(prop(n, r, rowspace, v))));
                    begin = veci_begin(&lits);
                    solver_addclause(s, begin, begin+veci_size(&lits));
                    veci_delete(&lits);
                }
                // must be one of each v in each column
                if (r == 0) {
                    veci_new(&lits);
                    veci_resize(&lits, 0);
                    for (i=r; i<n; i++) {
                        veci_push(&lits, toLit(prop(n, i, c, v)));
                    }
                    begin = veci_begin(&lits);
                    solver_addclause(s, begin, begin+veci_size(&lits));
                    veci_delete(&lits);
                }
                // unique v within colspace
                for (colspace=r+1; colspace<n; colspace++) {
                    veci_new(&lits);
                    veci_resize(&lits, 0);
                    veci_push(&lits, lit_neg(toLit(prop(n, r, c, v))));
                    veci_push(&lits, lit_neg(toLit(prop(n, colspace, c, v))));
                    begin = veci_begin(&lits);
                    solver_addclause(s, begin, begin+veci_size(&lits));
                    veci_delete(&lits);
                }
                // still gotta do box rules!
                // int *boxes = boxvalues(n, r, c);
                // for (i=1; i<n; i++) {
                //     veci_new(&lits);
                //     veci_resize(&lits, 0);
                //     veci_push(&lits, lit_neg(toLit(*(boxes))));
                //     veci_push(&lits, lit_neg(toLit(*(boxes + i)));
                //     begin = veci_begin(&lits);
                //     solver_addclause(s, begin, begin+veci_size(&lits));
                //     veci_delete(&lits);
                // }
                // known
                if (board[r][c] != '-') {
                    veci_new(&lits);
                    veci_resize(&lits, 0);
                    veci_push(&lits, toLit(prop(n, r, c, board[r][c] - 'a')));
                    begin = veci_begin(&lits);
                    solver_addclause(s, begin, begin+veci_size(&lits));
                    veci_delete(&lits);
                }
            }
        }
    }

    st = solver_solve(s,0,0);

    if (st) {
        for (v=0; v<n; v++) {
            for (r=0; r<n; r++) {
                for (c=0; c<n; c++) {
                    if (s->model.ptr[prop(n, r, c, v)] == l_True) {
                        board[r][c] = 'a' + v;
                    }
                }
            }
        }
    }

    return;
}
