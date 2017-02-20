#include <fstream>
#include <iostream>
#include "table.h"

double func(double *vars)
{
    return vars[0]*vars[0];
}

int testgrid(int num, std::vector<double> &result)
{
    Table storage;
    storage.initialize(1);

    storage.setfunction(func);

    double lowerlimit[1] = {-10, };
    double upperlimit[1] = {10.0, };
    int p[1] = {num,};
    storage.setlimit(lowerlimit, upperlimit, p);
    double x = -9.9;
    double dx = 0.1;
    double dy = 0.1;

    while(x < 9.9)
    {
        double vars[1] = {x, };
        double value = 0.0;

        storage.query(vars, value);
        result.push_back(value);
        x += dx;
    }

}

int main()
{
    std::ofstream outfile;
    outfile.open("temp.dat", std::ios::binary);

    for(int i=1; i<=20; ++i)
    {
        std::vector<double> result;
        testgrid(10*i, result);
        size_t Nx = result.size();
        outfile.write(reinterpret_cast<char*>(&Nx), sizeof(int));
        outfile.write(reinterpret_cast<char*>(&result[0]), sizeof(double)*Nx);
    }

    outfile.close();
    return 1;
}
