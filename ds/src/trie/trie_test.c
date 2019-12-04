#include <stdio.h>
#include "trie.h"

int main()
{
    trie_t* trie = NULL;
    uint32_t path = 0;

    trie = TrieCreate(5);

    TrieInsert(trie, 0, NULL);
    TrieInsert(trie, 1, NULL);
    TrieInsert(trie, 2, NULL);
    TrieInsert(trie, 3, NULL);

    TrieFindNextFree(trie, &path);
    printf("%d\n", path);

    TrieRemove(trie, 2);

    path = 0;
    TrieFindNextFree(trie, &path);
    printf("%d\n", path);

    TrieDestroy(trie);

    return 0;
}
