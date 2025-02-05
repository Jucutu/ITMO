#include <iostream>

bool check(int coordinates[], int seats, int people, int mid)
{
    int count = 1;
    int currPosition = coordinates[0]; //позиуия последнего посаженного = ненышняя пощиция

    for (int i = 1; i <= seats; i++)
    {
        if(coordinates[i] - currPosition >= mid)
        {
            count++;
            currPosition = coordinates[i];

            if (count == people)
            {
                return true;
            }
        }
    }
    return false;
}


int binSearch(int seats, int people, int coordinates[])
{
    int l = 0;
    int r = 1 + coordinates[seats - 1] - coordinates[0];
    while (l + 1 < r)
    {
        int m = (l + r) / 2;

        if (check(coordinates, seats, people, m))
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }
    std::cout << l;
    return 0;
}


int main()
{
    int seats, people;
    std::cin >> seats >> people;
    int coordinates[seats];

    for (int i = 0; i < seats; i++)
    {
        std::cin >> coordinates[i];
    }

    binSearch(seats, people, coordinates);
}

