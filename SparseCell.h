//
// Created by A671988 on 2017-10-19.
//

#ifndef SPARSECELL_H
#define SPARSECELL_H

#include <iostream>
#include <sstream>
const char *CELL_CONSTRUCTOR_MESSAGE = "Tworzenie obiektu SparseCell\n";
const char *CELL_DESTRUCTOR_MESSAGE = "Niszczenie obiektu SparseCell\n";


using namespace std;

class SparseCell {
private:
    int dimensions;
    int *coordinates;
    int value;

    int compareCoordinates(int *coordinates);

    friend class SparseMatrix;

    SparseCell(int numberOfDimensions, int *coordinates, int value);

    SparseCell(SparseCell &cell);

    ~SparseCell();

    string toString();
};


#endif //SPARSECELL_H
