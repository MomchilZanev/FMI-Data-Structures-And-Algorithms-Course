#include <iostream>
#include <vector>
#include <list>

class DoublyLinkedListNode
{
public:
    int data;
    DoublyLinkedListNode* prev;
    DoublyLinkedListNode* next;

    DoublyLinkedListNode(int data, DoublyLinkedListNode* prev = nullptr, DoublyLinkedListNode* next = nullptr)
    {
        this->data = data;
        this->prev = prev;
        this->next = next;
    }
};

class DoublyLinkedList
{
public:
    DoublyLinkedListNode* head;
    DoublyLinkedListNode* tail;

    DoublyLinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
    }

    DoublyLinkedListNode* pushBack(int data)
    {
        DoublyLinkedListNode* node = new DoublyLinkedListNode(data);

        if (this->head == nullptr)
        {
            this->head = node;
        }
        else
        {
            this->tail->next = node;
            node->prev = this->tail;
        }

        this->tail = node;
        return node;
    }

    void printDoublyLinkedList(const std::string& separator, std::ostream& out)
    {
        DoublyLinkedListNode* current = this->head;
        while (current != nullptr)
        {
            out << current->data;

            current = current->next;

            if (current != nullptr)
            {
                out << separator;
            }
        }
    }

    int getSize()
    {
        int size = 0;
        DoublyLinkedListNode* current = this->head;
        while (current != nullptr)
        {
            current = current->next;
            ++size;
        }

        return size;
    }
};

DoublyLinkedListNode* getLeftmostBallWithSameColor(DoublyLinkedListNode* aimedBall)
{
    int color = aimedBall->data;
    while (aimedBall->prev != nullptr && aimedBall->prev->data == color)
    {
        aimedBall = aimedBall->prev;
    }

    return aimedBall;
}

DoublyLinkedListNode* getRightmostBallWithSameColor(DoublyLinkedListNode* aimedBall)
{
    int color = aimedBall->data;
    while (aimedBall->next != nullptr && aimedBall->next->data == color)
    {
        aimedBall = aimedBall->next;
    }

    return aimedBall;
}

int getNumberOfBallsWithSameColorBetween(DoublyLinkedListNode* leftBall, DoublyLinkedListNode* rightBall)
{
    if (leftBall == rightBall)
    {
        return 1;
    }

    int count = 1;
    while (leftBall->next != nullptr && leftBall != rightBall)
    {
        leftBall = leftBall->next;
        ++count;
    }

    return count;
}

bool threeBallsWithSameColorExistNear(DoublyLinkedListNode* ball)
{
    if (ball->prev != nullptr && ball->next != nullptr && ball->prev->data == ball->data && ball->data == ball->next->data)
    {
        return true;
    }
    if (ball->prev != nullptr && ball->prev->prev != nullptr && ball->prev->prev->data == ball->prev->data && ball->prev->data == ball->data)
    {
        return true;
    }
    if (ball->next != nullptr && ball->next->next != nullptr && ball->next->next->data == ball->next->data && ball->next->data == ball->data)
    {
        return true;
    }

    return false;
}

void playGame(std::vector<DoublyLinkedListNode*>& nodeIndexes, DoublyLinkedList& coloredBalls, const std::list<std::pair<int, int>>& shots)
{
    for (const auto& shot : shots)
    {
        if (coloredBalls.getSize() <= 0)
        {
            std::cout << "Game Over" << '\n';
            continue;
        }

        int position = shot.first, color = shot.second;

        DoublyLinkedListNode* aimedBall = nodeIndexes[position];
        DoublyLinkedListNode* tmp = aimedBall->next;
        DoublyLinkedListNode* newBall = new DoublyLinkedListNode(color);
        nodeIndexes.push_back(newBall);
        aimedBall->next = newBall;
        newBall->prev = aimedBall;
        newBall->next = tmp;
        if (tmp != nullptr)
        {
            tmp->prev = newBall;
        }

        int totalBallsRemoved = 0;
        if (threeBallsWithSameColorExistNear(newBall))
        {
            DoublyLinkedListNode* leftBall = newBall;
            DoublyLinkedListNode* rightBall = newBall;

            while (leftBall != nullptr && rightBall != nullptr && leftBall->data == rightBall->data)
            {
                leftBall = getLeftmostBallWithSameColor(leftBall);
                rightBall = getRightmostBallWithSameColor(rightBall);

                int ballsToRemove = getNumberOfBallsWithSameColorBetween(leftBall, rightBall);

                if (ballsToRemove < 3)
                {
                    break;
                }

                totalBallsRemoved += ballsToRemove;

                if (leftBall->prev == nullptr && rightBall->next == nullptr)
                {
                    coloredBalls.head = nullptr;
                    coloredBalls.tail = nullptr;
                    break;
                }

                if (rightBall->next == nullptr)
                {
                    coloredBalls.tail = leftBall->prev;
                    coloredBalls.tail->next = nullptr;
                    break;
                }

                if (leftBall->prev == nullptr)
                {
                    coloredBalls.head = rightBall->next;
                    coloredBalls.head->prev = nullptr;
                    break;
                }

                leftBall = leftBall->prev;
                rightBall = rightBall->next;

                leftBall->next = rightBall;
                rightBall->prev = leftBall;
            }
        }

        std::cout << totalBallsRemoved << '\n';
    }
}

void gatherInput(std::vector<DoublyLinkedListNode*>& nodeIndexes, DoublyLinkedList& coloredBalls, std::list<std::pair<int, int>>& shots)
{
    int N;
    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int ballColor;
        std::cin >> ballColor;
        nodeIndexes.push_back(coloredBalls.pushBack(ballColor));
    }

    int Q;
    std::cin >> Q;
    for (int i = 0; i < Q; ++i)
    {
        int position, color;
        std::cin >> position >> color;
        shots.push_back(std::pair<int, int>(position, color));
    }
}

int main()
{
    std::vector<DoublyLinkedListNode*> nodeIndexes;
    DoublyLinkedList coloredBalls;
    std::list<std::pair<int, int>> shots;

    gatherInput(nodeIndexes, coloredBalls, shots);

    playGame(nodeIndexes, coloredBalls, shots);

    if (coloredBalls.getSize() > 0)
    {
        coloredBalls.printDoublyLinkedList(" ", std::cout);
    }
    else
    {
        std::cout << -1;
    }

    return 0;
}