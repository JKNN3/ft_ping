/*              PRINT BINARY

we need 2 loops, one iterating over the bytes of our data type (sizeof(data_type)),
and one iterating over every 8 bit of each byte
bitshift (ex:   1101 >> 1; == 110) décale de un vers la droite
                1101 & 0001 == 0001
                0110 & 0001 == 0000
        binary operator & met un 1 là ou il y a un 1 dans les deux nombres comparés uniquement
        en bitshiftant et comparant avec l'opérateur & le résultat correspond à notre bit (0 ou 1)
*/
#include <stdio.h>
# define SET_DF_BIT_TRUE         (1 << 14) 

int main(int argc, char **argv){
    int nb = 111111234 & 0xFFFF;
    // nb = SET_DF_BIT_TRUE;
    long long i, j;
    for (i = sizeof(int) - 1; i >= 0; i--){
//        char byte = *(((char*)&nb) + i);     // because char == 1 byte, adding i moove the ptr to iterate over every byte
        char byte = ((char*)&nb)[i]; // the same thing but shorter
        for (j = 7; j >= 0; j--){
            char tmp = (byte >> j); 
            printf("%d", tmp&1);
        }
        printf(" ");
    }
    return 0;
}