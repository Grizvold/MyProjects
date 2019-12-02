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

dhcp_t *DHCPCreate(uint32_t net_add, uint32_t net_mask);

int DHCPAllocIp(dhcp_t *dhcp, uint32_t *addr);

void DHCPRelease(dhcp_t *dhcp, uint32_t addr);

void DHCPDestroy(dhcp_t *dhcp);
/******************************************************************************/

#endif /* __DHCP_H__ */
