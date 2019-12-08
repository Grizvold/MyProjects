#include <stdlib.h> /* malloc,free  */
#include <assert.h> /* assert       */
#include <stdint.h> /* int32_t      */
#include <stdio.h>  /* perror       */

#include "trie.h" /* Trie API */
#include "dhcp.h" /* DHCP API */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

typedef enum
{
    SUCCESS = 0,
    FAILURE
} status_t;

struct dhcp
{
    uint32_t network_address;
    uint32_t subnet_mask;
    trie_t *trie;
};
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Declaration                    */
/******************************************************************************/

/* -Get number of '0' that signifies tree height. */
static size_t CalculateHeight(uint32_t subnet_mask);
/******************************************************************************/

/******************************************************************************/
/*                          DHCP Functions Definition                         */
/******************************************************************************/

dhcp_t *DHCPCreate(uint32_t net_add, uint32_t subnet_mask)
{
    dhcp_t *new_DHCP = NULL;
    size_t trie_height = 0;

    while (1)
    {
        new_DHCP = (dhcp_t *)malloc(sizeof(*new_DHCP));
        if (NULL == new_DHCP)
        {
            perror("Malloc in DHCPCreate of new_DHCP failed\n");
            return NULL;
        }

        trie_height = CalculateHeight(subnet_mask);

        new_DHCP->trie = TrieCreate(trie_height);
        if (NULL == new_DHCP->trie)
        {
            perror("Malloc in DHCPCreate of new_DHCP->trie failed\n");
            break;
        }

        new_DHCP->network_address = net_add;
        new_DHCP->subnet_mask = subnet_mask;

        /* save 3 addresses aside   */
        /*      network address     */
        TrieInsert(new_DHCP->trie, 0, NULL);
        /*      broadcast address     */
        TrieInsert(new_DHCP->trie, (1U << trie_height) - 1, NULL);
        /*      server address     */
        TrieInsert(new_DHCP->trie, (1U << trie_height) - 2, NULL);
    }

    free(new_DHCP->trie);
    new_DHCP->trie = NULL;

    free(new_DHCP);
    new_DHCP = NULL;

    return new_DHCP;
}

int DHCPAllocIp(dhcp_t *dhcp, uint32_t *addr)
{
    uint32_t new_ip = 0;
    status_t status = SUCCESS;

    assert(NULL != dhcp);
    assert(NULL != addr);

    /* find next free <node> */
    status = TrieFindNextFree(dhcp->trie, &new_ip);
    if (FAILURE == status)
    {
        return FAILURE;
    }

    /* if free node was found -> create and insert */
    status = TrieInsert(dhcp->trie, new_ip, NULL);
    if (FAILURE == status)
    {
        return FAILURE;
    }

    *addr = dhcp->network_address | new_ip;

    return SUCCESS;
}

void DHCPRelease(dhcp_t *dhcp, uint32_t addr)
{
    assert(NULL != dhcp);

    addr = addr - dhcp->network_address;

    TrieRemove(dhcp->trie, addr);
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);

    TrieDestroy(dhcp->trie);

    free(dhcp);
    dhcp = NULL;
}
/******************************************************************************/

/******************************************************************************/
/*                          Internal Component Definition                    */
/******************************************************************************/

static size_t CalculateHeight(uint32_t subnet_mask)
{
    size_t i = 0;

    for (i = 0; i < sizeof(uint32_t) * 8; i++)
    {
        if (subnet_mask & (1U))
        {
            break;
        }

        subnet_mask >>= 1;
    }

    return i;
}
/******************************************************************************/