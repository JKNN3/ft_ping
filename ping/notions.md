




    ** define and strings tabs **

we cannot make a macro (# define) of an array of strings because macros replace text and are not complex dynamic objects. But, we can use a macro containing a list of strings to initialize an array of strings.

  ex:

#define INGREDIENTS_PATES AU GRUYERE_LIST {"pates", "beurre", "sel", "gruyère"}

int main(int ac, char ** av){
  const char *ingredients[] = INGREDIENTS_PATES_AU_GRUYERE;

  //  en l'assignant comme ça, j'ai mon tableau d'ingrédients

  return 0;
}


    **  stddev = stability of the conenxion  **

It shows how much variation there is from the average, or mean. A low deviation value indicates that the data points tend to be very close to the mean, whereas a high deviation value indicates that the data are spread out over a large range of values. A low standard deviation implies that there is a more stable, or consistent, performance within the system.


ho to compute stddev:
Step 1: Calculate the mean. The mean is simply the average of all the response times. This is calculated by adding all the response times together and divide by the total number of transactions.

Step 2: Calculate variance. Variance is calculated by taking each response time and subtracting it from the mean. Note that this may end up with a negative number, but each result is squared, so it will become a positive number. The last piece is to add up each of the squared values.

Step 3: Calculate standard deviation. This last step is fairly straightforward. Simply take the total of all the squared values from the previous step and find the square root of that value. That will be your standard deviation.

link : https://www.dotcom-monitor.com/wiki/knowledge-base/standard-deviation/


The inet_ntoa() function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation. The string is returned in a statically allocated buffer, which subsequent calls will overwrite. WHICH SUBSEQUENT CALLS WILL OVERWRITE.