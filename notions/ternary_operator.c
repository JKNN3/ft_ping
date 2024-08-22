/*              TERNARY OPERATOR

    (ternary operator bcs it's the only operator that takes 3 operands)
int variable = [condition] ? [value if condition is true] :(else) [value if condition is false]

misuses:
do something else than just give a value ( ex: x>y ? write(1, &x, 1) : write(1, &y, 1);)
using it without the else statement

*/
#include <stdio.h>

int main(int argc, char **argv){
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);
    int max = x>y ? x : y;
    printf("the max is: %d\n", max);
    return 0;
}