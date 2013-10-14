#include "acm_api.h"
#include <string.h>
#define MAXLENGTH 1000

void a1002()
{
	int counter=0, i, j, carry=0;;
	char a[MAXLENGTH]={0}, b[MAXLENGTH]={0}, c[MAXLENGTH];
	int len_a, len_b;
	scanf("%d",&counter);

	for(i=0; i<counter; i++){
		scanf("%s %s",a, b);
		len_a = strlen(a);
		len_b = strlen(b);
		for(j=0; j<len_a || j<len_b; j++){
			c[j] = a[len_a - j - 1] + b[len_b - j - 1] - '0' + carry;
			carry = 0;
			if(c[j] > '9'){
				carry = 1;
				c[j] -= 10;
			}
		}
		if(carry = 1){
			c[j+1] = '1';
		}
		printf("case %d:\n", i);
		printf("%s + %s = %s", a, b, c);
		
	}
}