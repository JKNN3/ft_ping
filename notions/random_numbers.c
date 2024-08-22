/*              RANDOM NUMBERS

rand() give the same sequence of numbers unless we specify a seed
    -> srand(), if i put 0 or 1, the rand() result is still the same (must be the
    random seed) but if i put others, it changes.
we can use the time to make it pseudo random changing

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){
    srand(time(NULL));
    printf("random nb: %d\n", rand());
    printf("random nb: %d\n", rand());
    printf("random nb: %d\n", rand());

    return 0;
}