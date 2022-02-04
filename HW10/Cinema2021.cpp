#include <iostream>
#include <vector>

bool** allocateCinema(const long N, const long M)
{
    bool** cinema = new bool* [N];
    for (long i = 0; i < N; ++i)
    {
        cinema[i] = new bool[M]();
    }

    return cinema;
}

void clearCinema(bool** cinema, const long N, const long M)
{
    for (long i = 0; i < N; ++i)
    {
        delete[] cinema[i];
    }
    delete[] cinema;
}

void getInitialSickPeople(bool** cinema, std::vector<std::pair<long, long>>& sickPeople, const int K)
{
    for (long k = 0; k < K; ++k)
    {
        long i, j;
        std::cin >> i >> j;
        cinema[i - 1][j - 1] = true;
        sickPeople.push_back({ i - 1, j - 1 });
    }
}

bool isValidSeat(const long N, const long M, const long i, const long j)
{
    if (i < 0 || j < 0)
    {
        return false;
    }
    if (i >= N || j >= M)
    {
        return false;
    }

    return true;
}

void infectPerson(bool** cinema, const long N, const long M, std::vector<std::pair<long, long>>& newlyInfected, long& sickPeopleCount, const long i, const long j)
{
    if (isValidSeat(N, M, i, j))
    {
        if (!cinema[i][j])
        {
            ++sickPeopleCount;
            cinema[i][j] = true;
            newlyInfected.push_back({ i, j });
        }
    }
}

void playMovie(bool** cinema, const long N, const long M, const long T, std::vector<std::pair<long, long>>& sickPeople, long& sickPeopleCount)
{
    for (long i = 0; i < T; ++i)
    {
        std::vector<std::pair<long, long>> newlyInfected;

        while (!sickPeople.empty())
        {
            std::pair<long, long> currentInfected = sickPeople.back();
            sickPeople.pop_back();

            long currentI = currentInfected.first;
            long currentJ = currentInfected.second;

            infectPerson(cinema, N, M, newlyInfected, sickPeopleCount, currentI + 1, currentJ);
            infectPerson(cinema, N, M, newlyInfected, sickPeopleCount, currentI - 1, currentJ);
            infectPerson(cinema, N, M, newlyInfected, sickPeopleCount, currentI, currentJ + 1);
            infectPerson(cinema, N, M, newlyInfected, sickPeopleCount, currentI, currentJ - 1);
        }

        sickPeople = newlyInfected;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long N, M;
    std::cin >> N >> M;
    long T, K;
    std::cin >> T >> K;

    bool** cinema = allocateCinema(N, M);
    std::vector<std::pair<long, long>> sickPeople;
    getInitialSickPeople(cinema, sickPeople, K);

    long totalPeopleCount = N * M;
    long sickPeopleCount = K;

    playMovie(cinema, N, M, T, sickPeople, sickPeopleCount);

    long healthyPeopleCount = totalPeopleCount - sickPeopleCount;
    std::cout << healthyPeopleCount;

    clearCinema(cinema, N, M);

    return 0;
}