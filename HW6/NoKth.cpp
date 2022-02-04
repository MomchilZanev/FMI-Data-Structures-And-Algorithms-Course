#include <iostream>
#include <vector>
#include <queue>

class Node
{
public:
    Node(const int value);

    int value;
    Node* parent;
    Node* left;
    Node* right;
};

Node::Node(const int value)
    : value(value), parent(nullptr), left(nullptr), right(nullptr)
{}

class BinaryTree
{
public:
    BinaryTree(const int size);

    void addLeft(Node* currentNode, const int newNodeIndex, const int newNodeValue);
    void addRight(Node* currentNode, const int newNodeIndex, const int newNodeValue);

    std::vector<Node*> nodes;
};

BinaryTree::BinaryTree(const int size)
    :nodes(size)
{}

void BinaryTree::addLeft(Node* currentNode, const int newNodeIndex, const int newNodeValue)
{
    if (this->nodes[newNodeIndex] != nullptr || currentNode->left != nullptr)
    {
        return;
    }
    this->nodes[newNodeIndex] = new Node(newNodeValue);
    this->nodes[newNodeIndex]->parent = currentNode;
    currentNode->left = this->nodes[newNodeIndex];
}

void BinaryTree::addRight(Node* currentNode, const int newNodeIndex, const int newNodeValue)
{
    if (this->nodes[newNodeIndex] != nullptr || currentNode->right != nullptr)
    {
        return;
    }
    this->nodes[newNodeIndex] = new Node(newNodeValue);
    this->nodes[newNodeIndex]->parent = currentNode;
    currentNode->right = this->nodes[newNodeIndex];
}

Node* getLeftmost(Node* node)
{
    Node* current = node;

    while (current->left != nullptr)
    {
        current = current->left;
    }

    return current;
}

void deleteNode(Node* nodeToDelete)
{
    if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr)
    {
        if (nodeToDelete->parent->left == nodeToDelete)
        {
            nodeToDelete->parent->left = nullptr;
        }
        else
        {
            nodeToDelete->parent->right = nullptr;
        }
        std::free(nodeToDelete);
    }
    else if (nodeToDelete->left == nullptr)
    {
        nodeToDelete->right->parent = nodeToDelete->parent;
        if (nodeToDelete->parent->left == nodeToDelete)
        {
            nodeToDelete->parent->left = nodeToDelete->right;
        }
        else
        {
            nodeToDelete->parent->right = nodeToDelete->right;
        }
        free(nodeToDelete);

    }
    else if (nodeToDelete->right == nullptr)
    {
        nodeToDelete->left->parent = nodeToDelete->parent;
        if (nodeToDelete->parent->left == nodeToDelete)
        {
            nodeToDelete->parent->left = nodeToDelete->left;
        }
        else
        {
            nodeToDelete->parent->right = nodeToDelete->left;
        }
        free(nodeToDelete);
    }
    else
    {
        Node* temp = getLeftmost(nodeToDelete->right);

        nodeToDelete->value = temp->value;

        deleteNode(temp);

    }
}

void getInput(BinaryTree& tree, std::vector<std::pair<Node*, int>>& elements, const int N)
{
    for (int i = 0; i < N; ++i)
    {
        int value;
        std::cin >> value;

        if (i == 0)
        {
            tree.nodes[0] = new Node(value);
        }
        else
        {
            if (i % 2 != 0)
            {
                int parentIndex = (i - 1) / 2;
                tree.addLeft(tree.nodes[parentIndex], i, value);
            }
            else
            {
                int parentIndex = (i - 2) / 2;
                tree.addRight(tree.nodes[parentIndex], i, value);
            }

        }
        elements.push_back(std::make_pair(tree.nodes[i], value));
    }
}

int partition(std::vector<std::pair<Node*, int>>& arr, int from, int to)
{
    int pivot = arr[to].second, index = from;
    for (int i = from; i < to; ++i)
    {
        if (arr[i].second >= pivot)
        {
            std::swap(arr[i], arr[index]);
            ++index;
        }
    }

    std::swap(arr[index], arr[to]);
    return index;

}

std::pair<Node*, int> quickSelectKthLargest(std::vector<std::pair<Node*, int>>& arr, int from, int to, int K)
{
    int index = partition(arr, from, to);

    if (index - from == K - 1)
    {
        return arr[index];
    }

    if (index - from > K - 1)
    {
        return quickSelectKthLargest(arr, from, index - 1, K);
    }
    else
    {
        return quickSelectKthLargest(arr, index + 1, to, K - index + from - 1);
    }
}

void printTreeTopToBottom(Node* root)
{
    if (root == nullptr)
    {
        return;
    }

    std::queue<Node*> queue;
    Node* current = root;

    queue.push(current);
    while (queue.size() != 0)
    {
        current = queue.front();
        queue.pop();

        std::cout << current->value << " ";

        if (current->left != nullptr)
        {
            queue.push(current->left);
        }
        if (current->right != nullptr)
        {
            queue.push(current->right);
        }
    }
}

int main()
{
    int N, K;
    std::cin >> N >> K;

    BinaryTree tree(N);
    std::vector<std::pair<Node*, int>> elements;
    getInput(tree, elements, N);

    std::pair<Node*, int> kthLargest = quickSelectKthLargest(elements, 0, N - 1, K);
    deleteNode(kthLargest.first);

    Node* root = tree.nodes[0];
    printTreeTopToBottom(root);

    return 0;
}