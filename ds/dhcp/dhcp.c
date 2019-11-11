
#include <stdio.h>     /* size_t, printf */
#include <string.h>     /* memset */
#include <stdlib.h>     /* mallo c       */
#include <assert.h>     /* assert        */
#include <arpa/inet.h>  /*inet_pton      */

#include "dhcp.h" 
#define UNUSED(x)     (void)(x)

typedef struct trie
{
    struct trie *left;  /*0 - go there by default                                 */
    struct trie *right; /*1 - go there if left is occupied                        */
    int occ;            /*0 = there is a free path a head. 1 = no free path a head*/
}trie_t;

struct dhcp
{
    struct trie *trie;
    size_t height;
    uint32_t mask;
    uint32_t net_addr;
};

#ifndef NDEBUG
void PrintDhcp(dhcp_t *dhcp);
#endif

static size_t CountBitsOff(uint32_t num);
static int IsLittleEndian();
static uint32_t RotateToLittle(uint32_t num);
static void DestroyTree(trie_t *trie);
static uint32_t GetAddTree(trie_t *trie, size_t height, uint32_t ip, uint32_t net_addr);
static trie_t *CreateNode(trie_t *current);
static int CreateMostRightNode(trie_t *trie, size_t height);
static void PrintTrie(trie_t *trie);
static int ReleaseAdd(trie_t *trie, uint32_t ip, size_t height);
static void UpdeateParents(trie_t *current);

const uint32_t INT_LEN = 32;
const size_t BYTE = 8;


dhcp_t *DHCPCreate(const char *net_addr, uint32_t net_mask)
{
    dhcp_t *dhcp = NULL;
    trie_t *trie = NULL;
    uint32_t addr = 0;

    assert(net_mask);

    dhcp = malloc(sizeof(dhcp_t));
    trie = malloc(sizeof(trie_t));

    if (NULL == dhcp || NULL == trie)
    {
        free(dhcp);
        free(trie);
        return NULL;
    }

    if (1 != inet_pton(AF_INET, net_addr, &addr))
    {
        free(dhcp);
        free(trie);
        return NULL;
    }

    if (IsLittleEndian())
    {
        addr = RotateToLittle(addr);
    }

    dhcp->trie = trie;
    dhcp->height = CountBitsOff(net_mask);
    dhcp->net_addr = addr;
    dhcp->mask = net_mask;

    memset(trie, 0, sizeof(trie_t));

    /* alloc saved ip's - most right one and both first allocated ones in left*/
    if (0 == CreateMostRightNode(dhcp->trie, dhcp->height) || 0 == DHCPGetAdd(dhcp) || 0 == DHCPGetAdd(dhcp))
    {
        DHCPDestroy(dhcp);

        return NULL;
    }

    return dhcp;
}

/* returns 0 in failure and 1 in success */
static int CreateMostRightNode(trie_t *trie, size_t height)
{
    if (0 == height)
    {
        trie->occ = 1;
        return 1;
    }

    trie->right = CreateNode(trie->right);
    if (NULL == trie->right)
    {
        return 0;
    }

    return CreateMostRightNode(trie->right, height - 1);
}


/*When didn't succeed to find & alloc a new ip - return 0*/
uint32_t DHCPGetAdd(dhcp_t *dhcp)
{
    assert(dhcp);

    if (1 == dhcp->trie->occ)
    {
        return 0;
    }

    return GetAddTree(dhcp->trie, dhcp->height, 0, dhcp->net_addr);
}

/* returns a full ip address or zero if didn't succeed */
static uint32_t GetAddTree(trie_t *current, size_t height, uint32_t ip, uint32_t net_addr)
{
    if (0 == height)
    {
        current->occ = 1;
        
        return (ip | net_addr);
    }

    if (current->left == NULL)
    {
        current->left = CreateNode(current->left);
    }
    /*malloc hasn't failed and the node exised but was free */
    if (NULL != current->left && current->left->occ == 0)
    {
        ip = GetAddTree(current->left, height - 1, ip << 1, net_addr);
        UpdeateParents(current);

        return ip;
    }

    else if (current->right == NULL)
    {
        current->right = CreateNode(current->right);
    }
    /*malloc hasn't failed or the node exised but was free */
    if (NULL != current->right && current->right->occ == 0)
    {
        ip = GetAddTree(current->right, height - 1, (ip << 1) | 1, net_addr);
        UpdeateParents(current);

        return ip;
    }
    /* for mallocs that failed */
    return 0;
}
 
uint32_t DHCPReleaseAdd(dhcp_t *dhcp, uint32_t ip)
{    
    uint32_t path = 0;

    assert(dhcp);

    path = (ip & ~(dhcp->mask));

    if ((0 == path) || (1 == path) || (0 == CountBitsOff(ip | dhcp->mask)))
    {
        return 0;
    }

    return ReleaseAdd(dhcp->trie, ip, dhcp->height);
}

/* returns 1 for success and 0 for failure */
static int ReleaseAdd(trie_t *trie, uint32_t ip, size_t height)
{
    if (0 == height)
    {
        trie->occ = 0;
        return ip;
    }
    /*for 0 digit go to the left */
    if (0 == (ip & (1 << (height - 1))))
    {
        ReleaseAdd(trie->left, ip, height - 1);
        trie->occ = 0;
        return ip;
    }
    /*for 1 digit go to the right */
    ReleaseAdd(trie->right, ip, height - 1);
    trie->occ = 0;
    return ip;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(dhcp);

    DestroyTree(dhcp->trie);

    free(dhcp);
}

static void DestroyTree(trie_t *trie)
{
    if (NULL != trie)
    {
        DestroyTree(trie->left);
        DestroyTree(trie->right);
        free(trie);
    }
}

static size_t CountBitsOff(uint32_t num)
{
    int bits_off = INT_LEN;

	while (0 != num)
	{
		num &= (num-1);
		--bits_off;
	}
	
	return bits_off;
}


static int IsLittleEndian()
{
	short num = 1;
	char *ptr = (char*)&num;	/*point at the left digit*/

	return *ptr;	/*return the value of left digit 0 OR 1*/
	
}

static uint32_t RotateToLittle(uint32_t num)
{
    uint32_t swapped = ((num >> (BYTE * 3)) & 0xFF) |      /* move byte 3 to byte 0 */
                       ((num << BYTE) & 0xFF0000) |        /* move byte 1 to byte 2 */
                       ((num >> BYTE) & 0xFF00) |          /* move byte 2 to byte 1 */
                       ((num << (BYTE * 3)) & 0xFF000000); /* byte 0 to byte 3      */
    return swapped;
}

static trie_t *CreateNode(trie_t *current)
{
    current = (trie_t*)malloc(sizeof(trie_t));

    if (NULL == current)
    {
        return NULL;
    }

    current->left = NULL;
    current->right = NULL;
    current->occ = 0;

    return current;
}

void PrintDhcp(dhcp_t *dhcp)
{
    assert(dhcp);

    PrintTrie(dhcp->trie);
    puts("");
} 

 /* when returning from recursive calls check and update the parent nodes */
static void UpdeateParents(trie_t *current)
{
    if ((current->right != NULL) && (current->right->occ == 1) && (current->left->occ == 1))
    {
        current->occ = 1;
    } 
}
    

#ifndef NDEBUG
static void PrintTrie(trie_t *trie)
{
    if (NULL != trie)
    {
        PrintTrie(trie->left);
        printf("%d ", trie->occ);
        PrintTrie(trie->right);
    }
}
#endif
