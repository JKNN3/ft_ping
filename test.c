#include <stdio.h>
#include <string.h>


short first_ping_cksum(short *addr, int len)
{
	int nleft = len;
	short *w = addr;
	int sum = 0;
	short answer = 0;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
	 */
	while( nleft > 1 )  {
		sum += *w++;
		nleft -= 2;
		printf("sum: %d\n", sum);
		unsigned int sumprint = sum;
   		for(int bit=0;bit < 8; bit++)
   		{
      		printf("%i ", sumprint & 0x01 ? 1 : 0);
      		sumprint = sumprint >> 1;
   		}
	}

	/* mop up an odd byte, if necessary */
	if( nleft == 1 ) {
		*(char *)(&answer) = *(char *)w ;
		sum += answer;
	}

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	printf("sum: %u\n", sum);
	sum += (sum >> 16);			/* add possible carry */
	printf("sum: %u\n", sum);
	answer = ~sum;		/* ones complement & truncate to 16 bits */
	printf("answer: %u\n", answer);
	return (answer);
}



int main (int argc, char **argv){

	if (!argv[1])
		return (0);
	first_ping_cksum(argv[1], strlen(argv[1]));
	return (0);
}
