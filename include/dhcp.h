
#ifndef __DHCP_H__
#define __DHCP_H__

#include <stdint.h>    /* size_t  */

typedef struct dhcp dhcp_t;

/*Creates a new ds dhcp. returns pointer to it for success and NULL for failure*/
dhcp_t *DHCPCreate(const char *net_addr, uint32_t net_mask);

/*Gets a free ip dynamically. for success returns the ip allocaed, for failure returns 0*/
uint32_t DHCPGetAdd(dhcp_t *dhcp);

/*Releases ip. returns the ip released if found or 0 when addr eleagle */
uint32_t DHCPReleaseAdd(dhcp_t *dhcp, uint32_t ip);

/*frees the dhcp*/
void DHCPDestroy(dhcp_t *dhcp);

#endif          /* __DHCP_H__  */

