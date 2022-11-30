#include <iostream>
#include <memory>

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
  auto new_node = std::make_unique<Node>(data, std::move(head));
  head = std::move(new_node);
}

// g++ -std=c++17 -Wall -O2 not_leaky.cpp && ./a.out
// valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out
int main(int argc, char *argv[]) {
  std::unique_ptr<Node> head{nullptr};
  for (int i = 0; i < 5; ++i) {
    insert(head, i);
  }
  print_list(head.get());
  return 0;
}
