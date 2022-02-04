#include <iostream>
#include <map>

int getSubmissionTime(const std::multimap<int, int>::iterator& submissionIterator)
{
    return (*submissionIterator).second;
}

int getSubmissionLinesOfCode(const std::multimap<int, int>::iterator& submissionIterator)
{
    return (*submissionIterator).first;
}

int getFirstSubmission(const std::multimap<int, int>& submissionTimes)
{
    return (*submissionTimes.begin()).first;
}

void checkSubmissions(std::multimap<int, int>& submissions, std::multimap<int, int>& submissionTimes, const int N, long& averageWaitingTime)
{
    long totalTimeWaited = 0;
    long currentTime = 0;
    while (!submissions.empty())
    {
        currentTime = currentTime < getFirstSubmission(submissionTimes) ? getFirstSubmission(submissionTimes) : currentTime;
        auto top = submissions.begin();

        auto current = top;
        while (current != submissions.end() && getSubmissionTime(current) > currentTime)
        {
            ++current;
        }
        top = current;

        currentTime += getSubmissionLinesOfCode(top);
        totalTimeWaited += currentTime - getSubmissionTime(top);
        submissionTimes.erase(getSubmissionTime(top));
        submissions.erase(top);        
    }

    averageWaitingTime = totalTimeWaited / N;
}

void getSubmission(std::multimap<int, int>& submissions, std::multimap<int, int>& submissionTimes, const int N)
{
    for (int i = 0; i < N; ++i)
    {
        int submissionTime, linesOfCode;
        std::cin >> submissionTime >> linesOfCode;

        submissions.insert({ linesOfCode, submissionTime });
        submissionTimes.insert({ submissionTime, i });
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::multimap<int, int> submissions;
    std::multimap<int, int> submissionTimes;
    long averageWaitingTime;

    getSubmission(submissions, submissionTimes, N);
    checkSubmissions(submissions, submissionTimes, N, averageWaitingTime);

    std::cout << averageWaitingTime;

    return 0;
}