#include <climits>
#include <iostream>
#include <iterator>
#include <memory>
#include <pstl/glue_algorithm_defs.h>
#include <pstl/glue_algorithm_impl.h>
#include <queue>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void bubbleSort(int arr[], int size) {
  for (int i = size - 1; i > 0; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void selectionSort(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    int minIndex = i;
    for (int j = i + 1; j < size; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }
    if (i != minIndex) {
      int temp = arr[i];
      arr[i] = arr[minIndex];
      arr[minIndex] = temp;
    }
  }
}

void insertionSort(int arr[], int size) {
  for (int i = 1; i < size; i++) {
    int temp = arr[i];
    int j = i - 1;
    while (j > -1 && temp < arr[j]) {
      arr[j + 1] = arr[j];
      arr[j] = temp;
    }
  }
}

void merge(int arr[], int leftIndex, int midIndex, int rightIndex) {
  int leftArraySize = midIndex - leftIndex + 1;
  int rightArraySize = rightIndex - midIndex;

  int leftArray[leftArraySize];
  int rightArray[rightArraySize];

  for (int i = 0; i < leftArraySize; i++) {
    leftArray[i] = arr[leftIndex + i];
  }
  for (int j = 0; j < rightArraySize; j++) {
    rightArray[j] = arr[midIndex + j + 1];
  }

  int index = leftIndex;
  int i = 0, j = 0;
  while (i < leftArraySize && j < rightArraySize) {
    if (leftArray[i] < rightArray[j]) {
      arr[index] = leftArray[i];
      index++;
      i++;
    }
    arr[index] = rightArray[j];
    j++;
    index++;
  }
  while (i < leftArraySize) {
    arr[index] = leftArray[i];
    index++;
    i++;
  }
  while (j < rightArraySize) {
    arr[index] = rightArray[j];
    index++;
    j++;
  }
}

void mergeSort(int arr[], int leftIndex, int rightIndex) {
  if (leftIndex >= rightIndex)
    return;

  int midIndex = leftIndex + (rightIndex - leftIndex) / 2;
  mergeSort(arr, leftIndex, midIndex);
  mergeSort(arr, midIndex + 1, rightIndex);

  merge(arr, leftIndex, midIndex, rightIndex);
}

void swap(int arr[], int firstIndex, int secondIndex) {
  int temp = arr[firstIndex];
  arr[firstIndex] = arr[secondIndex];
  arr[secondIndex] = temp;
}

int pivot(int arr[], int pivotIndex, int endIndex) {
  int swapIndex = pivotIndex;
  for (int i = pivotIndex + 1; i <= endIndex; i++) {
    if (arr[i] < arr[pivotIndex]) {
      swapIndex++;
      swap(arr, i, swapIndex);
    }
  }
  swap(arr, pivotIndex, swapIndex);
  return swapIndex;
}

void quickSort(int arr[], int leftIndex, int rightIndex) {
  if (leftIndex >= rightIndex)
    return;

  int pivotIndex = pivot(arr, leftIndex, rightIndex);
  quickSort(arr, leftIndex, pivotIndex - 1);
  quickSort(arr, pivotIndex + 1, rightIndex);
}

class Graph {
private:
  unordered_map<string, unordered_set<string>> adjList;

public:
  bool addVertex(string vertex) {
    if (adjList.count(vertex) == 0) {
      adjList[vertex];
      return true;
    }
    return false;
  }
  bool addEdge(string vertex1, string vertex2) {
    if (adjList.count(vertex1) != 0 && adjList.count(vertex2) != 0) {
      adjList.at(vertex1).insert(vertex2);
      adjList.at(vertex2).insert(vertex1);
      return true;
    }
    return false;
  }
  bool removeEdge(string vertex1, string vertex2) {
    if (adjList.count(vertex1) != 0 && adjList.count(vertex2) != 0) {
      adjList.at(vertex1).erase(vertex2);
      adjList.at(vertex2).erase(vertex1);
      return true;
    }
    return false;
  }
  bool removeVertex(string vertex) {
    if (adjList.count(vertex) == 0)
      return false;
    for (auto otherVertex : adjList.at(vertex)) {
      adjList.at(otherVertex).erase(vertex);
    }
    adjList.erase(vertex);
    return true;
  }
};

/*class Node {
public:
  string key;
  int value;
  Node *next;

  Node(string key, int value) {
    this->key = key;
    this->value = value;
    next = nullptr;
  }
};

class HashTable {
private:
  static const int size = 7;
  Node *dataMap[size];

  int hash(string key) {
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
      int asciiValue = int(key[i]);
      hash = (hash + asciiValue * 23) % size;
    }
    return hash;
  }

public:
  void set(string key, int value) {
    Node *newNode = new Node(key, value);
    int index = hash(key);
    if (dataMap[index] == nullptr) {
      dataMap[index] = newNode;
    } else {
      Node *temp = dataMap[index];
      while (temp->next) {
        temp = temp->next;
      }
      temp->next = newNode;
    }
  }
  int get(string key) {
    int index = hash(key);
    Node *temp = dataMap[index];
    while (temp) {
      if (temp->key == key)
        return temp->value;
      temp = temp->next;
    }
    return 0;
  }
  vector<string> keys() {
    vector<string> allKeys;
    for (int i = 0; i < size; i++) {
      Node *temp = dataMap[i];
      while (temp) {
        allKeys.push_back(temp->key);
        temp = temp->next;
      }
    }
    return allKeys;
  }
};*/

/*class Node {
public:
  int value;
  Node *left;
  Node *right;

  Node(int value) {
    this->value = value;
    left = nullptr;
    right = nullptr;
  }
};

class BinarySearchTree {
private:
  Node *root;

public:
  BinarySearchTree() { root = nullptr; }

  bool insert(int value) {
    Node *newNode = new Node(value);
    if (root == nullptr) {
      root = newNode;
      return true;
    } else {
      Node *temp = root;
      while (true) {
        if (newNode->value == temp->value)
          return false;
        if (newNode->value < temp->value) {
          if (temp->left == nullptr) {
            temp->left = newNode;
            return true;
          }
          temp = temp->left;
        } else {
          if (temp->right == nullptr) {
            temp->right = newNode;
            return true;
          }
          temp = temp->right;
        }
      }
    }
  }
  bool contains(int value) {
    Node *temp = root;
    while (temp) {
      if (value < temp->value) {
        temp = temp->left;
      } else if (value > temp->value) {
        temp = temp->right;
      } else {
        return true;
      }
    }
    return false;
  }
};*/

/*class Node {
public:
  int value;
  Node *next;

  Node(int value) {
    this->value = value;
    next = nullptr;
  }
};

class LinkedList {
private:
  Node *head;
  Node *tail;
  int length;

public:
  LinkedList(int value) {
    Node *newNode = new Node(value);
    head = newNode;
    tail = newNode;
    length = 1;
  }
  ~LinkedList() {
    Node *temp = head;
    while (head) {
      head = head->next;
      delete temp;
      temp = head;
    }
  }
  void printList() {
    Node *temp = head;
    while (temp) {
      cout << temp->value << endl;
      temp = temp->next;
    }
  }
  void append(int value) {
    Node *newNode = new Node(value);
    if (length == 0) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    length++;
  }
  void prepend(int value) {
    Node *newNode = new Node(value);
    if (length == 0) {
      head = newNode;
      tail = newNode;
    } else {
      newNode->next = head;
      head = newNode;
    }
    length++;
  }
  void deleteLast() {
    if (length == 0)
      return;
    Node *temp = head;
    if (length == 1) {
      head = nullptr;
      tail = nullptr;
    } else {
      Node *pre = head;
      while (temp->next) {
        pre = temp;
        temp = temp->next;
      }
      tail = pre;
      tail->next = nullptr;
    }
    delete temp;
    length--;
  }
  void deleteFirst() {
    if (length == 0)
      return;
    Node *temp = head;
    if (length == 1) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = head->next;
    }
    delete temp;
    length--;
  }
  Node *get(int index) {
    if (index < 0 || index >= length)
      return nullptr;
    Node *temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp;
  }
  bool set(int index, int value) {
    Node *temp = get(index);
    if (temp) {
      temp->value = value;
      return true;
    }
    return false;
  }
  bool insert(int index, int value) {
    if (index < 0 || index > length)
      return false;
    if (index == 0) {
      prepend(value);
      return true;
    }
    if (index == length) {
      append(value);
      return true;
    }
    Node *newNode = new Node(value);
    Node *temp = get(index - 1);
    newNode->next = temp->next;
    temp->next = newNode;
    length++;
    return true;
  }
  void deleteNode(int index) {
    if (index < 0 || index >= length)
      return;
    if (index == 0)
      return deleteFirst();
    if (index == length - 1)
      return deleteLast();
    Node *before = get(index - 1);
    Node *temp = before->next;
    temp->next = before->next;
    delete temp;
    length--;
  }
  void reverse() {
    Node *temp = head;
    head = tail;
    tail = temp;
    Node *after = temp->next;
    Node *before = nullptr;
    for (int i = 0; i < length; i++) {
      after = temp->next;
      temp->next = before;
      before = temp;
      temp = after;
    }
  }
};

class Stack {
private:
  Node *top;
  int height;

public:
  Stack(int value) {
    Node *newNode = new Node(value);
    top = newNode;
    height = 1;
  }
  void push(int value) {
    Node *newNode = new Node(value);
    newNode->next = top;
    top = newNode;
    height++;
  }
  int pop() {
    if (height == 0)
      return INT_MIN;
    Node *temp = top;
    int poppedValue = top->value;
    top = top->next;
    delete temp;
    height--;
    return poppedValue;
  }
};

class Queue {
private:
  Node *first;
  Node *last;
  int length;

public:
  Queue(int value) {
    Node *newNode = new Node(value);
    first = newNode;
    last = newNode;
    length = 1;
  }
  void enqueue(int value) {
    Node *newNode = new Node(value);
    if (length == 0) {
      first = newNode;
      last = newNode;
    } else {
      last->next = newNode;
      last = newNode;
    }
    length++;
  }
  int dequeue() {
    if (length == 0)
      return INT_MIN;
    Node *temp = first;
    int removedValue = first->value;
    first = first->next;
    delete temp;
    length--;
    return removedValue;
  }
};*/

class Node {
public:
  int value;
  Node *prev;
  Node *next;

  Node(int value) {
    this->value = value;
    prev = nullptr;
    next = nullptr;
  }
};

class DoublyLinkedList {
private:
  Node *head;
  Node *tail;
  int length;

public:
  DoublyLinkedList(int value) {
    Node *newNode = new Node(value);
    head = newNode;
    tail = newNode;
    length = 1;
  }
  void append(int value) {
    Node *newNode = new Node(value);
    if (length == 0) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    length++;
  }
  void prepend(int value) {
    Node *newNode = new Node(value);
    if (length == 0) {
      head = newNode;
      tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
    length++;
  }
  void deleteLast() {
    if (length == 0)
      return;
    Node *temp = tail;
    if (length == 1) {
      head = nullptr;
      tail = nullptr;
    } else {
      tail = tail->prev;
      tail->next = nullptr;
    }
    delete temp;
    length--;
  }
  void deleteFirst() {
    if (length == 0)
      return;
    Node *temp = head;
    if (length == 1) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = head->next;
      head->prev = nullptr;
    }
    delete temp;
    length--;
  }
  Node *get(int index) {
    if (index < 0 || index >= length)
      return nullptr;
    Node *temp = head;
    if (index < length / 2) {
      for (int i = 0; i < index; i++) {
        temp = temp->next;
      }
    } else {
      temp = tail;
      for (int i = length - 1; i > index; i--) {
        temp = temp->prev;
      }
    }
    return temp;
  }
  bool insert(int index, int value) {
    if (index < 0 || index > length)
      return false;
    if (index == 0) {
      prepend(value);
      return true;
    }
    if (index == length) {
      append(value);
      return true;
    }
    Node *newNode = new Node(value);
    Node *before = get(index - 1);
    Node *after = before->next;
    newNode->next = after;
    newNode->prev = before;
    before->next = newNode;
    after->prev = newNode;
    length++;
    return true;
  }
  void deleteNode(int index) {
    if (index < 0 || index >= length)
      return;
    if (index == 0)
      return deleteFirst();
    if (index == length - 1)
      return deleteLast();
    Node *temp = get(index);
    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;
    delete temp;
    length--;
  }
};
