#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct math_node {
        char *op;
        struct math_node *left;
        struct math_node *right;
};

struct math_node **stackify(char *string, int *stack_size)
{
        char *tmp;
        char delim[2] = " ";
        struct math_node **stack;
        stack = 0;
        *stack_size = 0;
        tmp = strtok(string, delim);
        if ((!tmp) || *tmp == 10 || *tmp == 13) {
                *stack_size = 0;
                return 0;
        }
        while (tmp) {
                stack = realloc(stack, (*stack_size+1)*sizeof(*stack));
                *(stack + *stack_size) = malloc(sizeof(**stack));
                (*(stack + *stack_size))->op =
                        calloc(strlen(tmp) + 1, sizeof(char));
                strcpy((*(stack + *stack_size))->op, tmp);
                (*(stack + *stack_size))->left = 0;
                (*(stack + *stack_size))->right = 0;
                (*stack_size)++;
                tmp = strtok(0, delim);
                if (*stack_size>9) { break; }
        }
        return stack;
}

int isOperator(char *string)
{
        int i;
        int found;
        found = 0;
        char operator[6];
        operator[0] = '+';
        operator[1] = '-';
        operator[2] = '%';
        operator[3] = '/';
        operator[4] = '&';
        operator[5] = '^';
        for (i=0; i<6; i++) {
                if (*string == operator[i]) { found = 1; }
        }
        return found;
}

struct math_node *treeify(struct math_node **stack, int *size)
{
        if (!stack || !size) { return 0; }
        struct math_node *parent;
        (*size)--;
        parent = *(stack + *size);
        if (*(parent->op) == '-' &&
                *(parent->op + 1) >= 48 &&
                *(parent->op + 1) <= 57) {
                return parent;
        }
        if (isOperator(parent->op)) {
                parent->right = treeify(stack, size);
                parent->left = treeify(stack, size);
        }
        return parent;
}

int evaluate_tree(struct math_node *tree)
{
        if (!tree) { return 0; }
        int value;
        switch (*(tree->op)) {
        case '+':
                value = evaluate_tree(tree->left) +
                        evaluate_tree(tree->right);
                break;
        case '-':       // special; numbers can start with -!
                if (*(tree->op + 1) >= 48 && *(tree->op + 1) <= 57) {
                        value = atoi(tree->op);
                } else {
                        value = evaluate_tree(tree->left) -
                                evaluate_tree(tree->right);
                }
                break;
        case '%':
                value = evaluate_tree(tree->left) %
                        evaluate_tree(tree->right);
                break;
        case '/':
                value = evaluate_tree(tree->left) /
                        evaluate_tree(tree->right);
                break;
        case '&':
                value = evaluate_tree(tree->left) &
                        evaluate_tree(tree->right);
                break;
        case '^':
                value = evaluate_tree(tree->left) ^
                        evaluate_tree(tree->right);
                break;
        default:
                value = atoi(tree->op);
                break;
        }
        return value;
}

char *getexp_prefix(struct math_node *tree, int *length)
{
        int i;
        if (!tree) { return 0; }
        char *expr;
        char *exprleft;
        char *exprright;
        switch (*(tree->op)) {
        case '-':
                if (*(tree->op + 1) >= 48 &&
                        *(tree->op + 1) <= 57) {
                        expr = malloc((strlen(tree->op) + 2)*sizeof(*expr));
                        strcpy(expr, tree->op);
                        *(expr + strlen(tree->op)) = 32;
                        *(expr + strlen(tree->op) + 1) = 0;
                        (*length)+=strlen(expr);
                        break;
                }
        case '+':
        case '%':
        case '/':
        case '&':
        case '^':
                *(tree->op + 1) = 0;
                exprleft = getexp_prefix(tree->left, length);
                exprright = getexp_prefix(tree->right, length);
                (*length)+=(strlen(tree->op) + 1);
                expr = calloc((*length + 1), sizeof(*expr));
                strcat(expr, tree->op);
                *(expr + strlen(expr)) = 32;
                strcat(expr, exprleft);
                strcat(expr, exprright);
                *(expr + strlen(expr) + 1) = 0;
                free(exprleft);
                exprleft = 0;
                free(exprright);
                exprright = 0;
                break;
        default:
                expr = malloc((strlen(tree->op) + 2)*sizeof(*expr));
                strcpy(expr, tree->op);
                *(expr + strlen(tree->op)) = 32;
                *(expr + strlen(tree->op) + 1) = 0;
                (*length)+=strlen(expr);
                break;
        }
        return expr;
}

char *getexp_infix(struct math_node *tree, int *length)
{
        int i;
        if (!tree) { return 0; }
        char *expr;
        char *exprleft;
        char *exprright;
        switch (*(tree->op)) {
        case '-':
                if (*(tree->op + 1) >= 48 &&
                        *(tree->op + 1) <= 57) {
                        expr = malloc((strlen(tree->op) + 2)*sizeof(*expr));
                        strcpy(expr, tree->op);
                        *(expr + strlen(tree->op)) = 32;
                        *(expr + strlen(tree->op) + 1) = 0;
                        (*length)+=strlen(expr);
                        break;
                }
        case '+':
        case '%':
        case '/':
        case '&':
        case '^':
                *(tree->op + 1) = 0;
                exprleft = getexp_infix(tree->left, length);
                exprright = getexp_infix(tree->right, length);
                (*length)+=(strlen(tree->op) + 1);
                expr = calloc((*length + 1), sizeof(*expr));
                strcat(expr, exprleft);
                strcat(expr, tree->op);
                *(expr + strlen(expr)) = 32;
                strcat(expr, exprright);
                *(expr + strlen(expr) + 1) = 0;
                free(exprleft);
                exprleft = 0;
                free(exprright);
                exprright = 0;
                break;
        default:
                expr = malloc((strlen(tree->op) + 2)*sizeof(*expr));
                strcpy(expr, tree->op);
                *(expr + strlen(tree->op)) = 32;
                *(expr + strlen(tree->op) + 1) = 0;
                (*length)+=strlen(expr);
                break;
        }
        return expr;
}

char *getexp_postfix(struct math_node *tree, int *length)
{
        int i;
        if (!tree) { return 0; }
        char *expr;
        char *exprleft;
        char *exprright;
        switch (*(tree->op)) {
        case '-':
                if (*(tree->op + 1) >= 48 &&
                        *(tree->op + 1) <= 57) {
                        expr = malloc((strlen(tree->op) + 2)*sizeof(*expr));
                        strcpy(expr, tree->op);
                        *(expr + strlen(tree->op)) = 32;
                        *(expr + strlen(tree->op) + 1) = 0;
                        (*length)+=strlen(expr);
                        break;
                }
        case '+':
        case '%':
        case '/':
        case '&':
        case '^':
                *(tree->op + 1) = 0;
                exprleft = getexp_postfix(tree->left, length);
                exprright = getexp_postfix(tree->right, length);
                (*length)+=(strlen(tree->op) + 1);
                expr = calloc((*length + 1), sizeof(*expr));
                strcat(expr, exprleft);
                strcat(expr, exprright);
                strcat(expr, tree->op);
                *(expr + strlen(expr)) = 32;
                *(expr + strlen(expr) + 1) = 0;
                free(exprleft);
                exprleft = 0;
                free(exprright);
                exprright = 0;
                break;
        default:
                expr = malloc((strlen(tree->op) + 2)*sizeof(*expr));
                strcpy(expr, tree->op);
                *(expr + strlen(tree->op)) = 32;
                *(expr + strlen(tree->op) + 1) = 0;
                (*length)+=strlen(expr);
                break;
        }
        return expr;
}

void tree_destructor(struct math_node *tree)
{
        if (!tree) { return; }
        if (tree->left) {
                tree_destructor(tree->left);
        }
        if (tree->right) {
                tree_destructor(tree->right);
        }
        free(tree->op);
        tree->op = 0;
        free(tree);
        tree = 0;
}

int main()
{
        int i;
        char buffer[101];
        struct math_node **stack;
        int stack_size;
        struct math_node *tree;

        // get string
        printf("Enter the postfix expression to be evaluated: ");
        fgets(buffer, 100, stdin);

        // stackify
        stack = stackify(buffer, &stack_size);
        // test stackify:
        // printf("stack_size:%i\n", stack_size);
        // for (i=0; i<stack_size; i++) {
        //         printf("%s\n", (*(stack + i))->op);
        // }

        // treeify
        tree = treeify(stack, &stack_size);

        // evaluate the tree
        int value;
        value = evaluate_tree(tree);
        printf("The tree evaluates to: %d\n", value);

        // print various forms
        char* exp;
        int length;
        length = 0;
        exp = getexp_prefix(tree, &length);
        printf("Prefix Notation:   %s\n", exp);
        free(exp);
        exp = 0;
        length = 0;
        exp = getexp_infix(tree, &length);
        printf("Infix Notation:    %s\n", exp);
        free(exp);
        exp = 0;
        length = 0;
        exp = getexp_postfix(tree, &length);
        printf("Postfix Notation:  %s\n", exp);
        free(exp);
        exp = 0;

        // cleanup
        tree_destructor(tree);
        free(stack);
        stack = 0;
        return 0;
}
