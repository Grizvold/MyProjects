#ifndef __DHCP_H__
#define __DHCP_H__

#include <stdint.h> /* uint32_t */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

typedef struct dhcp dhcp_t;
/******************************************************************************/

/******************************************************************************/
/*                          DHCP Functions Declaration                        */
/******************************************************************************/

/*  -Create DHCP.
    -Return pointer to created new DHCP. */
dhcp_t *DHCPCreate(uint32_t net_add, uint32_t net_mask);

/*  -Allocate new IP. 
    -Returns status:
                0 SUCCESS.
                1 FAILURE.  */
int DHCPAllocIp(dhcp_t *dhcp, uint32_t *addr);

void DHCPRelease(dhcp_t *dhcp, uint32_t addr);

void DHCPDestroy(dhcp_t *dhcp);
/******************************************************************************/
#endif /* __DHCP_H__ */