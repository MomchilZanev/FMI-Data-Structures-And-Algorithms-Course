#include <iostream>
#include <vector>
#include <map>

class Node
{
public:
    Node(const int index, const int x = -1, const int y = -1);

    int x, y;
    int index;
    Node* left;
    Node* right;
};

Node::Node(const int index, const int x, const int y)
    : index(index), x(x), y(y), left(nullptr), right(nullptr)
{}

class BinaryTree
{
public:
    BinaryTree(const int size);

    void addLeft(Node* node, const int index);
    void addRight(Node* node, const int index);

    std::vector<Node*> nodes;
};

BinaryTree::BinaryTree(const int size)
    :nodes(size)
{}

void BinaryTree::addLeft(Node* currentNode, const int newNodeindex)
{
    if (this->nodes[newNodeindex] != nullptr || currentNode->left != nullptr)
    {
        return;
    }
    this->nodes[newNodeindex] = new Node(newNodeindex, currentNode->x - 1, currentNode->y - 1);
    currentNode->left = this->nodes[newNodeindex];
}

void BinaryTree::addRight(Node* currentNode, const int newNodeindex)
{
    if (this->nodes[newNodeindex] != nullptr || currentNode->right != nullptr)
    {
        return;
    }
    this->nodes[newNodeindex] = new Node(newNodeindex, currentNode->x + 1, currentNode->y - 1);
    currentNode->right = this->nodes[newNodeindex];
}

void fillBinaryTree(BinaryTree& tree, const int N)
{
    tree.nodes[0] = new Node(0, 0, 0);
    for (int i = 0; i < N; ++i)
    {
        int leftIndex, rightIndex;
        std::cin >> leftIndex >> rightIndex;

        if (leftIndex != -1)
        {
            tree.addLeft(tree.nodes[i], leftIndex);
        }
        if (rightIndex != -1)
        {
            tree.addRight(tree.nodes[i], rightIndex);
        }
    }
}

void fillDistanceMap(std::map<int, std::pair<int, int>>& distanceMap, Node* root, int distanceX, int distanceY)
{
    if (root == nullptr)
    {
        return;
    }

    if (distanceMap.count(distanceX) == 0)
    {
        std::pair<int, int> NodeWithDistanceY(distanceY, root->index);
        distanceMap[distanceX] = NodeWithDistanceY;
    }
    else if (distanceMap[distanceX].first < distanceY)
    {
        std::pair<int, int> NodeWithDistanceY(distanceY, root->index);
        distanceMap[distanceX] = NodeWithDistanceY;
    }

    fillDistanceMap(distanceMap, root->left, distanceX - 1, distanceY - 1);
    fillDistanceMap(distanceMap, root->right, distanceX + 1, distanceY - 1);
}

void printDistanceMap(const std::map<int, std::pair<int, int>>& distanceMap)
{
    for (const auto& xPos : distanceMap)
    {
        std::cout << xPos.second.second << " ";
    }
}

int main()
{
    int N;
    std::cin >> N;

    BinaryTree tree(N);
    fillBinaryTree(tree, N);

    std::map<int, std::pair<int, int>> distanceMap;
    fillDistanceMap(distanceMap, tree.nodes[0], 0, 0);
    printDistanceMap(distanceMap);

    return 0;
}