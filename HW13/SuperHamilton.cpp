#include <iostream>

char** allocateMaze(const int rows, const int cols)
{
    char** maze = new char* [rows];
    for (int i = 0; i < rows; ++i)
    {
        maze[i] = new char[cols];
    }

    return maze;
}

void clearMaze(char** maze, const int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] maze[i];
    }
    delete[] maze;
}

std::pair<std::pair<int, int>, std::pair<int, int>> defineMaze(char** maze, const int rows, const int cols, int& keys)
{
    std::pair<int, int> startingRoom;
    std::pair<int, int> targetRoom;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            char symbol;
            std::cin >> symbol;
            maze[i][j] = symbol;

            if (symbol == 's')
            {
                startingRoom.first = i;
                startingRoom.second = j;
            }
            else if (symbol == 'e')
            {
                targetRoom.first = i;
                targetRoom.second = j;
            }
            else if (symbol == '-')
            {
                ++keys;
            }
        }
    }

    return { startingRoom, targetRoom };
}

bool isValidMove(char** maze, const int rows, const int cols, const int row, const int col)
{
    if (row < 0 || col < 0)
    {
        return false;
    }
    if (row >= rows || col >= cols)
    {
        return false;
    }
    if (maze[row][col] == 'x')
    {
        return false;
    }

    return true;
}

void dfsBacktrack(char** maze, const int rows, const int cols, const std::pair<int, int> currentRoom, const std::pair<int, int> targetRoom, const int keysToGather, int keysGathered, int& pathsCount)
{
    int currentRoomRow = currentRoom.first;
    int currentRoomCol = currentRoom.second;

    if (maze[currentRoomRow][currentRoomCol] == '-')
    {
        ++keysGathered;
    }
    else if (currentRoom == targetRoom)
    {
        if (keysGathered == keysToGather)
        {
            ++pathsCount;
        }

        return;
    }

    char mem = maze[currentRoomRow][currentRoomCol];
    maze[currentRoomRow][currentRoomCol] = 'x';

    //up
    if (isValidMove(maze, rows, cols, currentRoomRow - 1, currentRoomCol))
    {
        dfsBacktrack(maze, rows, cols, { currentRoomRow - 1, currentRoomCol }, targetRoom, keysToGather, keysGathered, pathsCount);
    }

    //down
    if (isValidMove(maze, rows, cols, currentRoomRow + 1, currentRoomCol))
    {
        dfsBacktrack(maze, rows, cols, { currentRoomRow + 1, currentRoomCol }, targetRoom, keysToGather, keysGathered, pathsCount);
    }

    //left
    if (isValidMove(maze, rows, cols, currentRoomRow, currentRoomCol - 1))
    {
        dfsBacktrack(maze, rows, cols, { currentRoomRow, currentRoomCol - 1 }, targetRoom, keysToGather, keysGathered, pathsCount);
    }

    //right
    if (isValidMove(maze, rows, cols, currentRoomRow, currentRoomCol + 1))
    {
        dfsBacktrack(maze, rows, cols, { currentRoomRow, currentRoomCol + 1 }, targetRoom, keysToGather, keysGathered, pathsCount);
    }

    maze[currentRoomRow][currentRoomCol] = mem;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int rows, cols;
    std::cin >> rows >> cols;

    int keysToGather = 0;
    char** maze = allocateMaze(rows, cols);
    auto pair = defineMaze(maze, rows, cols, keysToGather);
    auto startingRoom = pair.first;
    auto targetRoom = pair.second;

    int pathsCount = 0;
    dfsBacktrack(maze, rows, cols, startingRoom, targetRoom, keysToGather, 0, pathsCount);
    std::cout << pathsCount;

    clearMaze(maze, rows);
    return 0;
}