#include <stdio.h>
#include <stdlib.h>

typedef struct _list
{
    int radix;
    struct _list* next;
}List;

typedef struct _map
{
    int radix;
    struct _list* list;
    struct _list* tail;
    struct _map* next;
} Map;

int _map_insert(Map** map, List* x)
{
    if (!*map || (*map)->radix > x->radix)
    {
        Map* znew = (Map*) malloc(sizeof(Map));
        *znew = (Map) {x->radix, x, x, *map};
        *map = znew;
    }
    else if ((*map)->radix == x->radix)
        (*map)->tail = (*map)->tail->next = x;
    else
        return _map_insert(&(*map)->next, x);
    return 0;
}

int map_insert(Map** map, List* x)
{
    if (!x) return 0;
    _map_insert(map, x);
    return map_insert(map, x->next);
}

int map_merge(List** x, Map* map)
{
    if (!map) return (*x = NULL, 0);
    *x = map->list;
    map->list = NULL;
    return map_merge(&map->tail->next, map->next);
}

int radix_sort(List** x)
{
    Map* map = NULL;
    map_insert(&map, *x);
    map_merge(x, map);
    free(map);
}

void list_free(List* lst)
{
    if (!lst) return;
    List* n = lst-> next;
    free(lst);
    list_free(n);
}

void map_free(Map* map)
{
    if (!map) return;
    Map* n = map->next;
    list_free(map->list);
    free(map);
    map_free(n);

}
int main()
{
    List* lst = NULL;
    List* x;
    int a;
    while (scanf("%d", &a) == 1)
    {
        List* znew = (List*)malloc(sizeof(List));
        *znew = (List) {a, lst};
        lst = znew;
    }
    radix_sort(&lst);
    for (x = lst; x != NULL; x = x->next)
    {
        printf("%d\n", x->radix);
    }
    list_free(lst);
    return 0;
}
