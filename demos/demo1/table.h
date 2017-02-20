#ifndef Table_H
#define Table_H

#include "hashtable.h"
typedef double (*Function)(double *vars);

class Table
{
public:
    Table();
    Table(int _dimension);
    ~Table();
    void initialize(int _dimension);
    void setfunction(Function _function);
    void setlimit(double *_lowerlimit, double *_upperlimit, int *_p);
    bool query(int *index, double &value);
    bool query(double *vars, double &value);
    #ifdef DEBUG
    void display();
    #endif
private:
    // storage table
    hashTable<double> SPM;
    int dimension;
    // lower limit of the variables.
    double *lowerlimit;
    // upper limit of the variables.
    double *upperlimit;
    // spacing of the grid space.
    double *interval;
    // number of points of grid space.
    int *p;

    Function function;
};

Table::Table(){;}
Table::Table(int _dimension) { initialize(_dimension);}
Table::~Table()
{
    delete []p;
    delete []lowerlimit;
    delete []upperlimit;
    delete []interval;
}
void Table::initialize(int _dimension)
{
    dimension = _dimension;
    lowerlimit = new double[dimension];
    upperlimit = new double[dimension];
    p = new int[dimension];
    interval = new double[dimension];
    SPM.initialize(dimension);
}

void Table::setfunction(Function _function) {function = _function;}

void Table::setlimit(double *_lowerlimit, double *_upperlimit, int *_p)
{
    for(int i=0; i!=dimension; ++i)
    {
        lowerlimit[i] = _lowerlimit[i];
        upperlimit[i] = _upperlimit[i];
        p[i] = _p[i];
        interval[i] = (upperlimit[i] - lowerlimit[i])/double(p[i]);
    }
}
bool Table::query(int *index, double &value)
{
    bool flag = SPM.query(index, value);

    if(!flag)
    {
        double tvalue;
        double *vars = new double[dimension];
        double s = 0.0;
        for(int i=0; i<dimension; ++i)
        {
            vars[i] = lowerlimit[i] + interval[i]*index[i];
            s += vars[i];
        }

        tvalue = function(vars);
        value = tvalue;

        SPM.insert(index, tvalue);
    }
    return flag;
}
bool Table::query(double *vars, double &value)
{
    int *index = new int[dimension];
    for(int i=0; i!=dimension; ++i)
    {
        // perform the bounary check
        if(vars[i] > upperlimit[i]) vars[i] = upperlimit[i];
        else if(vars[i] < lowerlimit[i]) vars[i] = lowerlimit[i];
        index[i] = int((vars[i] - lowerlimit[i])/interval[i]);
    }

    double current = 0.0;
    query(index, current);
    double result = 0.0;
    int *tindex = new int[dimension];

    // interpolate the a point with the storage record.
    for(int i=0; i<dimension; ++i)
    {
        for(int j=0; j<dimension; ++j) tindex[j] = index[j];

        tindex[i] += 1;

        double tvalue;
        query(tindex, tvalue);

        double grad = (tvalue - current)/interval[i];
        double dx = vars[i] - index[i]*interval[i] - lowerlimit[i];
        result = result - grad*dx;

    }
    value = result + current;

    delete []tindex;
    delete []index;
    return false;
}
#ifdef DEBUG
void Table::display()
{
    SPM.stat();
}
#endif
#endif
