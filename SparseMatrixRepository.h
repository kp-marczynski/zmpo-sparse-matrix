//
// Created by A671988 on 2017-10-19.
//

#ifndef SPARSEMATRIXREPOSITORY_H
#define SPARSEMATRIXREPOSITORY_H

#include <vector>
#include <sstream>

#include "SparseMatrix.h"
const char *REPOSITORY_CONSTRUCTOR_MESSAGE = "Tworzenie obiektu SparseMatrixRepository";
const char *REPOSITORY_DESTRUCTOR_MESSAGE = "Niszczenie obiektu SparseMatrixRepository";

const string MATRICES_TEXT = "Matryce rzadkie: ";

using namespace std;

class SparseMatrixRepository {
private:
    SparseMatrix **matricesRepository;
    int sizeOfRepository;
    int currentNumberOfStoredMatrices;

    void resizeRepositoryTable();
public:
    SparseMatrixRepository();

    ~SparseMatrixRepository();

    void addSparseMatrix(int numberOfDimensions, int *dimensions, int defaultValue, string name);

    SparseMatrix &getSparseMatrix(int offset);

    int deleteOne(int offset);

    void deleteAll();

    string toString();

    bool setDimensions(int offset, int numberOfDimensions, int *specificDimensionsSizes);

    bool setDefaultValue(int offset, int defaultValue);

    int getValue(int offset, int *coordinates);

    int setValue(int offset, int *coordinates, int value);

    bool cloneOne(int offset);

    bool setName(int offset, string name);

    string getName(int offset);

    string toStringOne(int offset);
};


#endif //SPARSEMATRIXREPOSITORY_H
