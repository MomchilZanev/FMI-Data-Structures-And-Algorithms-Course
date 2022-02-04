#include <iostream>
#include <algorithm>
#include <vector>

class Operator
{
public:
    Operator()
        :index(this->id++), customersServed(0), busyUntil(0)
    {}

    void serveCustomer(const unsigned callTime, const unsigned serviceDuration)
    {
        this->busyUntil = callTime + serviceDuration;
        ++this->customersServed;
    }

    unsigned getIndex() const
    {
        return this->index;
    }

    unsigned getCustomersServed() const
    {
        return this->customersServed;
    }

    bool isFree(const unsigned currentTime) const
    {
        return currentTime >= busyUntil;
    }

    bool operator<(const Operator& rhs) const
    {
        if (this->customersServed < rhs.customersServed)
        {
            return true;
        }
        else if (this->customersServed == rhs.customersServed)
        {
            return this->index > rhs.index;
        }

        return false;
    }

private:
    static unsigned id;
    unsigned index;
    unsigned customersServed;
    unsigned busyUntil;
};

unsigned Operator::id = 0;

bool findFreeOperator(const std::vector<Operator>& operators, int& servicingOperator, const int K, const int callerIndex, const int callTime)
{
    servicingOperator = callerIndex % K;
    int currentOperator = servicingOperator;
    while (currentOperator < K && !operators[currentOperator].isFree(callTime))
    {
        ++currentOperator;
    }
    currentOperator = currentOperator == K ? currentOperator - 1 : currentOperator;

    if (servicingOperator > 0 && !operators[currentOperator].isFree(callTime))
    {
        currentOperator = 0;
        while (currentOperator < servicingOperator && !operators[currentOperator].isFree(callTime))
        {
            ++currentOperator;
        }
    }
    currentOperator = currentOperator == K ? currentOperator - 1 : currentOperator;

    servicingOperator = currentOperator;
    return operators[currentOperator].isFree(callTime);
}

void serveCallers(std::vector<Operator>& operators, const int N, const int K)
{
    for (int i = 0; i < N; ++i)
    {
        int callTime, serviceDuration;
        std::cin >> callTime >> serviceDuration;
        int servicingOperator;
        
        if (findFreeOperator(operators, servicingOperator, K, i, callTime))
        {
            operators[servicingOperator].serveCustomer(callTime, serviceDuration);
        }
    }
}

void printBestOperators(const std::vector<Operator>& operators, const int K)
{
    int bestIndex = K - 1;
    unsigned maxCustomersServed = operators[bestIndex].getCustomersServed();
    while (bestIndex >= 0 && operators[bestIndex].getCustomersServed() == maxCustomersServed)
    {
        std::cout << operators[bestIndex].getIndex() << ' ';
        --bestIndex;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, K;
    std::cin >> N >> K;

    std::vector<Operator> operators(K);

    serveCallers(operators, N, K);
    std::sort(operators.begin(), operators.end());
    printBestOperators(operators, K);

    return 0;
}