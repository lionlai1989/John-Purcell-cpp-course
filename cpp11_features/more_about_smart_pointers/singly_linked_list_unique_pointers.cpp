#include <iostream>
#include <memory>
#include <random>
#include <unordered_map>

struct Node {
  int data = 0;
  std::unique_ptr<Node> next = nullptr;
  Node(int data = 0, std::unique_ptr<Node> &&next = nullptr)
      : data{data}, next{std::move(next)} {}
  ~Node() { std::cout << "Destroy node with data: " << data << '\n'; }
};

void print_list(Node *head) {
  while (head) {
    std::cout << head->data << " --> ";
    head = head->next.get();
  }
  std::cout << "nullptr" << std::endl;
}

void insert(std::unique_ptr<Node> &head, int data) {
  // Use `auto` to avoid typing `std::unique_ptr<Node>` twice
  auto new_node = std::make_unique<Node>(data, std::move(head));
  // std::move unconditionally casts its argument to an rvalue.
  head = std::move(new_node);
}

// g++ -std=c++17 -Wall -O2 2_1_unique_ptr.cpp && ./a.out
int main(int argc, char *argv[]) {
  // head is a unique_ptr which points to Node() but initialized as nullptr.
  std::unique_ptr<Node> head{nullptr};
  for (int i = 0; i < 5; ++i) {
    insert(head, i);
  }
  print_list(head.get());

  return 0;
}
