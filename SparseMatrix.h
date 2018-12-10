//
// Created by A671988 on 2017-10-19.
//

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <sstream>
#include <iostream>
using namespace std;

const string INDEX_OUT_OF_BOUND_TEXT = "Podany offset jest poza dopuszczalnymi granicami\n";
const string COORDINATES_OUT_OF_BOUNDS_TEXT = "Podane koordynaty są poza dopuszczalnymi granicami\n";

const char *MATRIX_CONSTRUCTOR_MESSAGE = "Tworzenie obiektu SparseMatrix: ";
const char *MATRIX_DESTRUCTOR_MESSAGE = "Niszczenie obiektu SparseMatrix: ";

const string DEFAULT_NAME = "Default name";
const string COPY_TEXT = "_copy";

#define SUCCESS_CODE (0)
#define VECTOR_NOT_EXIST (-1)
#define NEGATIVE_NUMBER (-2)
#define SAME_LENGTH_AS_CURRENT (-3)
#define INDEX_OUT_OF_BOUNDS (-4)


const string SIZE_TEXT = " size: ";
const string VALUE_TEXT = " values: ";
const string SEPARATOR = ";";

const float RESIZE_FACTOR = 1.5;
const int INITIAL_SIZE = 10;


#include "SparseCell.h"

class SparseMatrix {
private:
    string name;
    int numberOfDimensions;
    int *specificDimensionsSizes;
    int defaultValue;

    SparseCell **sparseCells = new SparseCell *[10];
    int numberOfStoredValues;
    int sizeOfSparseCellsTable;

    void init(string name);

    void resizeCellsTable();

    bool checkIfCoordinatesWithinBounds(int *coordinates);

public:
    SparseMatrix();

    SparseMatrix(int numberOfDimensions, int *specificDimensionsSizes, int defaultValue);

    SparseMatrix(int numberOfDimensions, int *specificDimensionsSizes, int defaultValue, string name);

    SparseMatrix(const SparseMatrix &anotherMatrix);

    ~SparseMatrix();

    void setDimensions(int numberOfDimensions, int *specificDimensionsSizes);

    int getNumberOfDimensions();

    void setDefaultValue(int defaultValue);

    int getValue(int *coordinates);

    int setValue(int *coordinates, int value);

    SparseMatrix &clone();

    void copyData(const SparseMatrix &sparseMatrix);

    void setName(string name);

    string getName();

    string toString();

    string toStringHeader();
};


#endif //SPARSEMATRIX_H
