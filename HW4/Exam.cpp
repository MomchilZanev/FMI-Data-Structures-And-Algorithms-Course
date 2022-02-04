#include <iostream>

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
    DoublyLinkedListNode* middle;
    DoublyLinkedListNode* tail;
    int size;
    int middleIndex;

    DoublyLinkedList()
    {
        this->head = nullptr;
        this->middle = nullptr;
        this->tail = nullptr;
        size = 0;
        middleIndex = 0;
    }

    void pushBack(int data)
    {
        DoublyLinkedListNode* node = new DoublyLinkedListNode(data);

        if (this->head == nullptr)
        {
            this->head = node;
            node->prev = nullptr;
        }
        else
        {
            this->tail->next = node;
            node->prev = this->tail;
        }
        
        this->tail = node;
        ++this->size;
        this->updateMiddle();
    }

    void popBack()
    {
        if (this->head == nullptr)
        {
            return;
        }
        if (this->size == 1)
        {
            delete this->head;
            this->head = nullptr;
            this->middle = nullptr;
            this->tail = nullptr;

            this->middleIndex = 0;
            this->size = 0;
            return;
        }

        this->tail = this->tail->prev;
        delete this->tail->next;
        this->tail->next = nullptr;

        --this->size;
        this->updateMiddle();
    }

    void moveFirstHalfToBack()
    {
        if (this->size <= 1)
        {
            return;
        }

        DoublyLinkedListNode* current = this->middle;
        DoublyLinkedListNode* newHead = current->next;
        DoublyLinkedListNode* newMiddle = this->tail;
        DoublyLinkedListNode* newTail = current;
        if (this->size % 2 != 0)
        {
            newMiddle = this->tail->prev;
        }

        current->next = nullptr;
        this->head->prev = this->tail;
        this->tail->next = this->head;

        this->head = newHead;
        this->middle = newMiddle;
        this->tail = newTail;
    }

    void updateMiddle()
    {
        if (this->size <= 1)
        {
            this->middle = this->head;
            this->middleIndex = 0;
            return;
        }

        int trueMiddle = (this->size / 2) - 1;
        while (this->middleIndex < trueMiddle)
        {
            this->middle = this->middle->next;
            ++this->middleIndex;
        }

        while (this->middleIndex > trueMiddle)
        {
            this->middle = this->middle->prev;
            --this->middleIndex;
        }
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
};

void parseCommand(DoublyLinkedList& cheatSheets, const std::string& command)
{
    if (command == "add")
    {
        int x;
        std::cin >> x;
        cheatSheets.pushBack(x);
    }
    else if (command == "gun")
    {
        cheatSheets.popBack();
    }
    else // (command == "milen")
    {
        cheatSheets.moveFirstHalfToBack();
    }
}

int main()
{
    int N;
    std::cin >> N;

    DoublyLinkedList cheatSheets;
    for (int i = 0; i < N; ++i)
    {
        std::string command;
        std::cin >> command;
        parseCommand(cheatSheets, command);
    }

    std::cout << cheatSheets.size << '\n';
    cheatSheets.printDoublyLinkedList(" ", std::cout);

    return 0;
}