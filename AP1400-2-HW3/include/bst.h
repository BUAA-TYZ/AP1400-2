#ifndef BST_H
#define BST_H

#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using std::cout;    using std::endl;
using std::queue;


class BST {
public:
    class Node {
    public:
        Node(int value = 0, Node* left = nullptr, Node* right = nullptr)
                : value(value), left(left), right(right) {}
        Node(const Node& node)
                : value(node.value), left(node.left), right(node.right) {}
        friend std::ostream& operator<<(std::ostream& os, const Node& node);
        bool operator==(int val) { return value == val; }
        friend bool operator==(int val, Node& node) { return node == val; }
        bool operator!=(int val) { return value != val; }
        friend bool operator!=(int val, Node& node) { return node != val; }
        bool operator<(int val) { return value < val; }
        friend bool operator<(int val, Node& node) { return node > val; }
        bool operator>(int val) { return value > val; }
        friend bool operator>(int val, Node& node) { return node < val; }
        bool operator<=(int val) { return value <= val; }
        friend bool operator<=(int val, Node& node) { return node >= val; }
        bool operator>=(int val) { return value >= val; }
        friend bool operator>=(int val, Node& node) { return node <= val; }

        int value;
        Node* left;
        Node* right;
    };

public:
    BST() = default;
    BST(std::initializer_list<int> list);
    BST(const BST& tree);
    BST(BST&& tree) noexcept : root(tree.root) {
        tree.root = nullptr;
    }
    BST& operator=(const BST& tree);
    BST& operator=(BST&& tree) noexcept {
        if (this != &tree) {
            root = tree.root;
            tree.root = nullptr;
        }
        return *this;
    }
    ~BST();

    BST& operator++();
    BST operator++(int);
    Node*& get_root() { return root; }
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& os, BST& tree);

private:
    Node* root = nullptr;
    void initiate(Node* tmp, Node*& node);
};
/*
                25
        10              50
    7       15              53
        8
            9
            */
#endif //BST_H