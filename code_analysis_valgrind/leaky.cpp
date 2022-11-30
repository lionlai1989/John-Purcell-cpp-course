#include <iostream>

struct Node {
  int data = 0;
  Node *next = nullptr;
  Node(int data = 0, Node *next = nullptr) : data{data}, next{next} {}
  ~Node() { std::cout << "Destroy node with data: " << data << '\n'; }
};

void insert(Node *&head, int data) {
  Node *new_node = new Node{data, head};
  head = new_node;
}

void print_list(Node *head) {
  while (head != nullptr) {
    std::cout << head->data << " --> ";
    head = head->next;
  }
  std::cout << "nullptr" << std::endl;
}

// g++ -std=c++17 -Wall -O2 leaky.cpp && ./a.out
// valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out
int main(int argc, char *argv[]) {
  Node *head{nullptr};
  for (int i = 0; i < 5; ++i) {
    insert(head, i);
  }
  print_list(head);
  return 0;
}
