
#include <stdio.h>
#include "dhcp.h"

int main()
{
    dhcp_t *dhcp = DHCPCreate("1.0.0.0", 0xFFFFFFF8);

	uint32_t ip1 = 0;
	uint32_t ip2 = 0;
	uint32_t ip3 = 0;
	uint32_t ip4 = 0;
	uint32_t ip5 = 0;

    uint32_t illeagel_ip1 = 0;
    uint32_t illeagel_ip2 = 0;
    uint32_t illeagel_ip3 = 0;
    uint32_t illeagel_ip4 = 0;

    if (NULL == dhcp)
    {
        printf("failed DHCPCreate\n");
    }

	/*Alloc all ip's */
    ip1 = DHCPGetAdd(dhcp);
    ip2 = DHCPGetAdd(dhcp);
    ip3 = DHCPGetAdd(dhcp);
    ip4 = DHCPGetAdd(dhcp);
    ip5 = DHCPGetAdd(dhcp);

	if (ip1 == 0)
	{
		printf("failed GetAdd %d\n", __LINE__);
	}

	if (ip2 == 0)
	{
		printf("failed GetAdd %d\n", __LINE__);
	}

	if (ip3 == 0)
	{
		printf("failed GetAdd %d\n", __LINE__);
	}

	if (ip4 == 0)
	{
		printf("failed GetAdd %d\n", __LINE__);
	}

	if (ip5 == 0)
	{
		printf("failed GetAdd %d\n", __LINE__);
	}	

	/* Release all ip's */
	if (0 == DHCPReleaseAdd(dhcp, ip1))
	{
		printf("failed release %d\n", __LINE__);
	}

	if (0 == DHCPReleaseAdd(dhcp, ip2))
	{
		printf("failed release %d\n", __LINE__);
	}

	if (0 == DHCPReleaseAdd(dhcp, ip3))
	{
		printf("failed release %d\n", __LINE__);
	}

	if (0 == DHCPReleaseAdd(dhcp, ip4))
	{
		printf("failed release %d\n", __LINE__);
	}

	if (0 == DHCPReleaseAdd(dhcp, ip5))
	{
		printf("failed release %d\n", __LINE__);
	}


	/*Try to release "stubs" */
    if (0 != DHCPReleaseAdd(dhcp, illeagel_ip1))
	{
		printf("failed release %d\n", __LINE__);
	}
	if (0 != DHCPReleaseAdd(dhcp, illeagel_ip2))
	{
		printf("failed release %d\n", __LINE__);
	}
	if (0 != DHCPReleaseAdd(dhcp, illeagel_ip3))
	{
		printf("failed release %d\n", __LINE__);
	}
	if (0 != DHCPReleaseAdd(dhcp, illeagel_ip4))
	{
		printf("failed release %d\n", __LINE__);
	}
	
    DHCPDestroy(dhcp);

    return 0;
}







