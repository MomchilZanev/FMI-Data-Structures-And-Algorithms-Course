#include <iostream>
#include <vector>

class Employee
{
public:
    Employee(const int index);

    int getSubordinatesCount() const;

    void addSubordinate(Employee* subordinate);
    void increaseSubordinatesCount();
private:
    int index;

    Employee* supervisor;

    int subordinatesCount;
};

Employee::Employee(const int index)
    :index(index), supervisor(nullptr), subordinatesCount(0)
{}

int Employee::getSubordinatesCount() const
{
    return this->subordinatesCount;
}

void Employee::addSubordinate(Employee* subordinate)
{
    subordinate->supervisor = this;
    this->increaseSubordinatesCount();
}

void Employee::increaseSubordinatesCount()
{
    ++this->subordinatesCount;
    if (this->supervisor != nullptr)
    {
        supervisor->increaseSubordinatesCount();
    }
}

void getEmployees(std::vector<Employee*>& employees)
{
    const int maxEmployees = employees.size();

    int employeesCount = 0;
    while (employeesCount < maxEmployees)
    {
        int supervisor, subordinate;
        std::cin >> supervisor >> subordinate;

        if (employees[supervisor] == nullptr)
        {
            employees[supervisor] = new Employee(supervisor);
            ++employeesCount;
        }

        if (employees[subordinate] == nullptr)
        {
            employees[subordinate] = new Employee(supervisor);
            ++employeesCount;
        }

        employees[supervisor]->addSubordinate(employees[subordinate]);
    }
}

void printSubordinatesCount(const std::vector<Employee*>& employees)
{
    int employeesCount = employees.size();
    for (int i = 0; i < employeesCount; ++i)
    {
        std::cout << employees[i]->getSubordinatesCount() << ' ';
    }
}

int main()
{
    int N;
    std::cin >> N;

    std::vector<Employee*> employees(N, nullptr);
    getEmployees(employees);

    printSubordinatesCount(employees);

    return 0;
}