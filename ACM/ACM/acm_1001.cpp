#include "acm_api.h"

void a1001()
{
	unsigned int n;
	while(scanf("%d",&n)!=EOF)
		printf("%ld\n\n", n*(n+1)>>1);
}