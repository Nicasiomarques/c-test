#define MAX_ITEMS 50

typedef short unsigned int shortInt;

typedef enum { false, true } bool;

typedef int Key;

typedef struct {
  Key key;
} Item;

typedef struct {
  Item items[MAX_ITEMS + 1];
  shortInt length;
} List;

void initialize(List* list);
bool addItem(List* list, shortInt index, Item item);
shortInt length(List *list);
bool removeItem(List* list, Key key);
int sequentialSearch(List* list, Key key);
int sentinelSearch(List* list, Key key);
int binarySearch(List* list, Key key);
void showList(List* list);
bool isFull(List *list);
void reset(List *list);
void unitTestsListLinearSequential(List* list);
