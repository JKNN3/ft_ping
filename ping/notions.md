




    ** define and strings tabs **

we cannot make a macro (# define) of an array of strings because macros replace text and are not complex dynamic objects. But, we can use a macro containing a list of strings to initialize an array of strings.

  ex:

#define INGREDIENTS_PATES AU GRUYERE_LIST {"pates", "beurre", "sel", "gruyère"}

int main(int ac, char ** av){
  const char *ingredients[] = INGREDIENTS_PATES_AU_GRUYERE;

  //  en l'assignant comme ça, j'ai mon tableau d'ingrédients

  return 0;
}



