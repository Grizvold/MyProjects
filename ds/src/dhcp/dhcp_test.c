#include <stdio.h>

#include "dhcp.h"

/* colors */
#define RED "\033[1;31m"
#define GRN "\033[1;32m"
#define YEL "\033[1;33m"
#define PRP "\033[1;35m"
#define BLU "\033[1;36m"
#define NRM "\033[0m"

dhcp_t *DHCPCreateTest(uint32_t net_add, uint32_t net_mask);
void DHCPAllocTest(dhcp_t *dhcp);
void DHCPReleaseTest(dhcp_t *dhcp);
void DHCPDestroyTest(dhcp_t *dhcp);


int main()
{
    dhcp_t *dhcp = NULL;

	dhcp = DHCPCreateTest(0x26B8B400, 0xFFFFF000);
    DHCPAllocTest(dhcp);
    DHCPReleaseTest(dhcp);
	DHCPDestroyTest(dhcp);

	printf("%s", NRM);
	
	return 0;
}


dhcp_t *DHCPCreateTest(uint32_t net_add, uint32_t net_mask)
{
	dhcp_t* dhcp = NULL;

	printf("%sCreate Test\n", PRP);

	dhcp = DHCPCreate(net_add, net_mask);

	dhcp != NULL ? printf("%s Success\n", GRN) : printf("%s Failure\n", RED);

	return dhcp;
}


void DHCPAllocTest(dhcp_t *dhcp)
{
	uint32_t addr = 0;
	int status = 0;
	size_t i = 0;

	printf("%sAlloc Test\n", PRP);

    status = DHCPAllocIp(dhcp, &addr);

	status == 0 && addr == 0x26B8B401 ? printf("%s Success\n", GRN) : printf("%s Failure\n", RED);

	for(i = 0; i < (2<<12) - 3; ++i)
	{
		DHCPAllocIp(dhcp, &addr);
	}

	status = DHCPAllocIp(dhcp, &addr);

	status == 1  ? printf("%s Success\n", GRN) : printf("%s Failure\n", RED);
}

void DHCPReleaseTest(dhcp_t *dhcp)
{
	int status = 0;
	uint32_t addr = 0x26B8B403;

	printf("%sRelease Test\n", PRP);

	DHCPRelease(dhcp, addr);

	status = DHCPAllocIp(dhcp, &addr);
	status == 0 && addr == 0x26B8B403 ? printf("%s Success\n", GRN) : printf("%s Failure\n", RED);


}

void DHCPDestroyTest(dhcp_t *dhcp)
{
	printf("%sDestroy Test\n", PRP);
	
	DHCPDestroy(dhcp);

	printf("%scheck valgrind\n", NRM);

}
