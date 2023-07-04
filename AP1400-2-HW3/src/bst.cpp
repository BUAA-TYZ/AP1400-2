#include "bst.h"

// 0x188dee70       => value:25        left:0x188dedd0      right:0x188dedf0
std::ostream& operator<<(std::ostream& os, const BST::Node& node) {
    os << &node << "\t\t=> value:" << node.value << "\t\tleft:";
    if (node.left) {
        cout << &node.left;
    } else {
        cout << "0\t\t";
    }
    cout << "\t\tright:";
    if (node.right) {
        cout << &node.right;
    } else {
        cout << "0\t\t";
    }
    return os;
}

void BST::initiate(Node* tmp, Node*& node) {
    if (!tmp) {
        node = tmp;
    } else {
        node = new Node(tmp->value);
        initiate(tmp->left, node->left);
        initiate(tmp->right, node->right);
    }
}

BST::BST(std::initializer_list<int> list) {
    for (auto x : list) {
        add_node(x);
    }
}

BST::BST(const BST& tree) {
    Node*& tmp = const_cast<BST&>(tree).get_root();
    if (!tmp) { root = nullptr; }
    else {
        root = new Node(tmp->value);
        initiate(tmp->left, root->left);
        initiate(tmp->right, root->right);
    }
}

BST& BST::operator=(const BST& tree) {
    if (this != &tree) {
        this->~BST();
        auto res = new BST(tree);
        root = res->root;
    }
    return *this;
}

BST::~BST()
{
	std::vector<Node*> nodes;
	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
	for(auto& node: nodes)
		delete node;
}

BST& BST::operator++() {
    this->bfs([](Node*& node) { ++node->value;});
    return *this;
}

BST BST::operator++(int) {
    BST res = *this;
    this->bfs([](Node*& node) { ++node->value;});
    return res;
}

void BST::bfs(std::function<void(Node*& node)> func) {
    if (!root) { return; }
    queue<Node*> order;
    order.push(root);
    while (!order.empty()) {
        Node* tmp = order.front();
        order.pop();
        func(tmp);
        if (tmp->left) { order.push(tmp->left); }
        if (tmp->right) { order.push(tmp->right); }
    }
}

size_t BST::length() {
    int res = 0;
    bfs([&res](Node*& node){ ++res; });
    return res;
}

bool BST::add_node(int value) {
    Node* tmp = root;
    if (!tmp) {
        root = new Node(value);
        return true;
    }
    while (tmp) {
        if (*tmp > value) {
            if (!tmp->left) {
                tmp->left = new Node(value);
                return true;
            }
            tmp = tmp->left;
        } else if (*tmp < value){
            if (!tmp->right) {
                tmp->right = new Node(value);
                return true;
            }
            tmp = tmp->right;
        } else {
            return false;
        }
    }
    return false;
}

BST::Node** BST::find_node(int value) {
    Node** tmp = &root;
    while (*tmp) {
        if (**tmp > value) {
            if ((*tmp)->left) {
                tmp = &(*tmp)->left;
            } else { break; }
        } else if (**tmp < value) {
            if ((*tmp)->right) {
                tmp = &(*tmp)->right;
            } else { break; }
        } else {
            return tmp;
        }
    }
    return nullptr;
}

BST::Node** BST::find_parrent(int value) {
    Node** tmp = &root;
    if (!*tmp) { return nullptr; }
    if (**tmp == value) { return tmp; }
    while (*tmp) {
        if ((*tmp)->left) {
            // Node is at left side of tmp.
            if (**tmp > value) {
                if (*((*tmp)->left) == value) { return tmp; }
                tmp = &(*tmp)->left;
                continue;
            }
        }
        if ((*tmp)->right) {
            if (**tmp < value) {
                if (*((*tmp)->right) == value) { return tmp; }
                tmp = &(*tmp)->right;
                continue;
            }
        }
        // situation 1 : tmp->left && !tmp->right && *tmp < value => nullptr
        // situation 2 : !tmp->left && tmp->right && *tmp > value => nullptr
        // situation 3 : !tmp->left && !tmp->right => nullptr
        break;
    }
    return nullptr;
}

// Caution: Successor of 5 is 4 in this programme. (weird)
BST::Node** BST::find_successor(int value) {
    Node **tmp = find_node(value);
    if (!tmp) { return nullptr; }
    // Successor is at left side or the node has not the parent node.
    auto max_left = [](Node** node) {
        Node** res = node;
        if (!*res) { return res; }
        if (!(*res)->right) { return &((*res)->right); }
        while (true) {
            if (!(*res)->right) {
                return res;
            }
            res = &(*res)->right;
        }
    };
    Node** res = max_left(&(*tmp)->left);
    if (!*res) {
        auto pre = find_parrent(value);
        if (pre) {
            if ((*pre)->left == *tmp) { return res; }
            return max_left(pre);
        }
        return pre;
    }
    return res;
}

// Caution: we must not delete tmp
// tmp is a pointer of a pointer of a node, it'll change when BST changes
bool BST::delete_node(int value) {
    Node** tmp = find_node(value);
    if (!tmp) { return false; }
    // Situation 1 : no child node
    if (!(*tmp)->left && !(*tmp)->right) {
        Node** pre = find_parrent(value);
        // Only one child
        if (pre) {
            if ((*pre)->left == *tmp) {
                (*pre)->left = nullptr;
            } else {
                (*pre)->right = nullptr;
            }
        }
    } else if ((*tmp)->left && (*tmp)->right) {
        // Situation 2 : two child nodes => Success
        Node** pre = find_successor(value);
        Node** pre_par = find_parrent((*pre)->value);
        std::swap((*tmp)->value, (*pre)->value);
        if ((*pre_par)->left == *pre) {
            (*pre_par)->left = nullptr;
        } else {
            (*pre_par)->right = nullptr;
        }
    } else {
        // Situation : one child node
        Node** pre = find_parrent(value);
        if (!pre) {
            root = ((*tmp)->left == nullptr) ? (*tmp)->right : (*tmp)->left;
        } else {
            if ((*tmp)->left) {
                (*pre)->left = (*tmp)->left;
            } else {
                (*pre)->right = (*tmp)->right;
            }
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, BST& tree) {
    auto line = []() {
        for (size_t i = 0; i < 20; ++i)
            cout << '*';
        cout <<endl;
    };
    line();
    tree.bfs([](BST::Node*& node) { cout << *node << endl; });
    line();
    return os;
}

