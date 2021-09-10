#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "list-linear-sequential.h"
#include "testing-library.h"

void initialize(List *list) {
  list->length = 0;
}

void reset(List *list) {
  initialize(list);
}

shortInt length(List *list) {
  return list->length;
}

void showList(List *list) {
  shortInt c = 0;
  printf("   All List Items: ");
  printf("[");
  while(c < list->length) {
    printf("%d ", list->items[c].key);
    c++;
  }
  printf("]\n");
}

bool isFull(List *list) {
  return list->length == MAX_ITEMS;
}

bool indexIsInvalid(List *list, shortInt index) {
  return index < 0 || index > list->length;
}

bool canNotAdd(List *list, shortInt index) {
  return isFull(list) || indexIsInvalid(list, index);
}

bool addItem(List* list, shortInt index, Item item) {
  if(canNotAdd(list, index)) return false;
  for(shortInt i = list->length; i <= index; i++) {
    list->items[i+1] = list->items[i];
  }
  list->items[index] = item;
  list->length++;
  return true;
}

bool addItemSort(List* list, Item item) {
  if(isFull(list)) return false;
  shortInt lastItemIndex = list->length;
  while(lastItemIndex > 0 && list->items[lastItemIndex -1].key > item.key) {
    list->items[lastItemIndex] = list->items[lastItemIndex-1];
    lastItemIndex--; 
  }
  list->items[lastItemIndex] = item;
  list->length++;
  return true;
}

int sequentialSearch(List* list, Key key) {
  for(int i = 0; i < list->length; i++) {
    if(list->items[i].key == key) return i;
  }
  return -1;
}

int sentinelSearch(List* list, Key key) {
  int c = 0;
  list->items[list->length].key = key;
  while(list->items[c].key != key) c++;
  return c == list->length ? -1 : c;
}

int binarySearch(List* list, Key key) {
  int start = 0, middle,
  end = list->length -1;
  while(start <= end) { 
    middle = (start + end) / 2;
    if(list->items[middle].key == key) return middle;
    if(list->items[middle].key < key) start = middle + 1;
    else end = middle - 1;
  }
  return -1;
}

bool removeItem(List* list, Key key) {
  shortInt index = sentinelSearch(list, key);
  if(indexIsInvalid(list, index)) return false;
  for(shortInt i = index; i < list->length; i++) {
    list->items[i] = list->items[i+1];
  }
  list->length--;
  return true;
}

void unitTestsListLinearSequential(List* list) {
   Item items[3] = {{.key=23}, {.key=43}, {.key=73}};

  describe("Initialize List");
  initialize(list);
  it("Should had 0 items after initialize list", length(list) == 0);

  describe("addItemSort");
  addItemSort(list, items[0]);
  addItemSort(list, items[1]);
  addItemSort(list, items[2]);
  it("Should add items incrementally", list->items[0].key < list->items[1].key < list->items[2].key);
  it("Should have 3 elements after add 3 items", length(list) == 3);
  
  describe("reset");
  reset(list);
  it("Should reset list correctly", list->length == 0);

  describe("addItem");
  addItem(list, 0, items[0]);
  addItem(list, 1, items[1]);
  addItem(list, 2, items[2]);
  it("Should add item with key 23 to first element", list->items[0].key == 23);
  it("Should add item with key 43 to second element", list->items[1].key == 43);
  it("Should add item with key 73 to treed element", list->items[2].key == 73);
  it("Should have 3 elements after add 3 items", length(list) == 3);

  describe("sequentialSearch");
  shortInt indexSequential = sequentialSearch(list, 43);
  it("Should return correct index of element when search with key", list->items[indexSequential].key == 43);
  it("Should return -1 when there is no element with id a searched", sequentialSearch(list, 143) == -1);

  describe("setinelSearch");
  shortInt indexSentinel = sentinelSearch(list, 23);
  it("Should return correct index of element when search with key", list->items[indexSentinel].key == 23);
  it("Should return -1 when there is no element with id a searched", sentinelSearch(list, 143) == -1);

  describe("binarySearch");
  shortInt indexBinary = binarySearch(list, 43);
  it("Should return correct index of element when search with key", list->items[indexBinary].key == 43);
  it("Should return -1 when there is no element with id a searched", binarySearch(list, 143) == -1);

  describe("removeItem");
  it("Should return return true when element is removed", removeItem(list, 43));
  it("Should have 2 elements after remove one", length(list) == 2);

  describe("showList");
  it("Should render list correctly", 1);
  showList(list);

  describe("isFull");
  srand(time(NULL));  
  for(shortInt i = 0; i < MAX_ITEMS; i++) {
    items[0].key = rand();
    addItem(list, i, items[0]);
  }

  it("Should return true when list is full", isFull(list));
  removeItem(list, list->items[0].key);
  it("Should return false when list isn't full", !isFull(list));
}
