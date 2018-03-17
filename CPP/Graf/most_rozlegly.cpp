#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

void dfs(int v, int verAmo, std::vector<int> edges[], bool* visited)
{
    int i;
    visited[v] = true;

    for(i = 0; i < verAmo; ++i)
    {
        if(i != v)
        {
            int x = (i > v) ? i : v;
            int y = (i < v) ? i : v;
            if(edges[x][y] == 1 && !visited[i]) dfs(i, verAmo, edges, visited);
        }
    }
}

int main()
{
    int verAmount;
    std::string sign1="", sign2="";
    int firstVer, secondVer;
    std::cin >> verAmount;

    if(verAmount < 4) return 0;

    std::vector<int> edges[verAmount];

    for(int i = 0; i < verAmount; ++i)
    {
        for(int j = 0; j < i+1; ++j)
        {
            edges[i].push_back(0);
        }
    }


    while(true)
    {
        std::cin >> sign1;
        if(sign1 == "q") break;
        std::cin >> sign2;

        firstVer = (sign1 > sign2) ? atoi(sign1.c_str()) : atoi(sign2.c_str());
        secondVer = (sign1 < sign2) ? atoi(sign1.c_str()) : atoi(sign2.c_str());

        edges[firstVer][secondVer] = 1;
    }

    for(int i = 0; i < verAmount; ++i)
    {
        std::vector<int> erasedEdgesFirst;
        int j;

        for(j = 0; j < i; ++j)
        {
            if(edges[i][j] == 1)
            {
                erasedEdgesFirst.push_back(j);
                edges[i][j] = 0;
            }
        }
        for(++j; j < verAmount; ++j)
        {
            if(edges[j][i] == 1)
            {
                erasedEdgesFirst.push_back(j);
                edges[j][i] = 0;
            }
        }

        for(int k = 0; k < erasedEdgesFirst.size(); ++k)
        {
            if(erasedEdgesFirst[k] > i){
                std::vector<int> erasedEdgesSecond;

                for(j = 0; j < erasedEdgesFirst[k]; ++j)
                {
                    if(edges[erasedEdgesFirst[k]][j] == 1)
                    {
                        erasedEdgesSecond.push_back(j);
                        edges[erasedEdgesFirst[k]][j] = 0;
                    }
                }
                for(++j; j < verAmount; ++j)
                {
                    if(edges[j][erasedEdgesFirst[k]] == 1)
                    {
                        erasedEdgesSecond.push_back(j);
                        edges[j][erasedEdgesFirst[k]] = 0;
                    }
                }

     //           bool visited[verAmount] = {};
		bool visited[verAmount];
		for(j = 0; j < verAmount; ++j) visited[j] = false;
                int x;
                if(verAmount-1 != i && verAmount-1 != erasedEdgesFirst[k]) x = verAmount-1;
                else if(verAmount-2 != i && verAmount-2 != erasedEdgesFirst[k]) x = verAmount-2;
                else x = verAmount-3;

                dfs(x, verAmount, edges, visited);

                int check = 0;

                for(j = 0; j < verAmount; ++j) check += visited[j];

                if(check < verAmount-2) std::cout << i << " " << erasedEdgesFirst[k] << "\n";

                for(j = 0; j < erasedEdgesSecond.size(); ++j)
                {
                    firstVer = (erasedEdgesFirst[k] > erasedEdgesSecond[j]) ? erasedEdgesFirst[k] : erasedEdgesSecond[j];
                    secondVer = (erasedEdgesFirst[k] < erasedEdgesSecond[j]) ? erasedEdgesFirst[k] : erasedEdgesSecond[j];
                    edges[firstVer][secondVer] = 1;
                }
            }
        }

        for(j = 0; j < erasedEdgesFirst.size(); ++j)
        {
            firstVer = (i > erasedEdgesFirst[j]) ? i : erasedEdgesFirst[j];
            secondVer = (i < erasedEdgesFirst[j]) ? i : erasedEdgesFirst[j];
            edges[firstVer][secondVer] = 1;
        }
    }
}
