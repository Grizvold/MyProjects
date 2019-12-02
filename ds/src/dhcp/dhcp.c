#include <assert.h> /* assert   */
#include <stdint.h> /* int32_t  */

#include "trie.h" /* Trie API */
#include "dhcp.h" /* DHCP API */  

struct dhcp
{
    uint32_t net_add;
    uint32_t net_mask;
    binary_trie_t *pool;
};

typedef struct dhcp_data
{
    size_t free_nodes_beneath;
    void *data;
} dhcp_data_t;
