//
// Created by A671988 on 2017-10-19.
//

#include "SparseMatrix.h"

void SparseMatrix::setDimensions(int numberOfDimensions, int *specificDimensionsSizes) {
    delete[] SparseMatrix::specificDimensionsSizes;
    SparseMatrix::specificDimensionsSizes = specificDimensionsSizes;
    if (numberOfDimensions != SparseMatrix::numberOfDimensions) {
        for (int i = 0; i < numberOfStoredValues; ++i) {
            delete sparseCells[i];
        }
        SparseMatrix::numberOfDimensions = numberOfDimensions;
    } else {
        for (int i = 0; i < numberOfStoredValues; ++i) {
            if (!checkIfCoordinatesWithinBounds(sparseCells[i]->coordinates)) {
                delete sparseCells[i];
                for (int j = i; j < numberOfStoredValues - 1; j++) {
                    sparseCells[j] = sparseCells[j + 1];
                }
                --numberOfStoredValues;
                --i;
            }
        }
    }
}

void SparseMatrix::setDefaultValue(int defaultValue) {
    SparseMatrix::defaultValue = defaultValue;
}

int SparseMatrix::getValue(int *coordinates) {
    if (checkIfCoordinatesWithinBounds(coordinates)) {
        for (int i = 0; i < numberOfStoredValues; ++i) {
            if (sparseCells[i]->compareCoordinates(coordinates) == 0) {
                return sparseCells[i]->value;
            }
        }
    }
    cerr << COORDINATES_OUT_OF_BOUNDS_TEXT;
    return false;
}

int SparseMatrix::setValue(int *coordinates, int value) {
    if (checkIfCoordinatesWithinBounds(coordinates)) {
        bool valueInserted = false;
        for (int i = 0; i < numberOfStoredValues && !valueInserted; ++i) {
            int comparationResult = sparseCells[i]->compareCoordinates(coordinates);
            if (comparationResult == 0) {
                if (value == defaultValue) {
                    delete sparseCells[i];
                    for (int j = i; j < numberOfStoredValues - 1; ++i) {
                        sparseCells[j] = sparseCells[j + 1];
                    }
                    --numberOfStoredValues;
                    valueInserted = true;
                } else {
                    sparseCells[i]->value = value;
                    valueInserted = true;
                }
            } else if (comparationResult < 0) {
                if (sizeOfSparseCellsTable == numberOfStoredValues) {
                    resizeCellsTable();
                }
                for (int j = numberOfStoredValues; j > i; --j) {
                    sparseCells[j] = sparseCells[j - 1];
                }
                sparseCells[i] = new SparseCell(numberOfDimensions, coordinates, value);
                ++numberOfStoredValues;
                valueInserted = true;
            }
        }
        if (!valueInserted) {
            if (sizeOfSparseCellsTable == numberOfStoredValues) {
                resizeCellsTable();
            }
            SparseCell *cell = new SparseCell(numberOfDimensions, coordinates, value);
            sparseCells[numberOfStoredValues++] = cell;
        }
        return true;
    }
    cerr << COORDINATES_OUT_OF_BOUNDS_TEXT;
    return false;
}

SparseMatrix &SparseMatrix::clone() {
    SparseMatrix *sparseMatrix = new SparseMatrix(*this);
    return *sparseMatrix;
}

void SparseMatrix::copyData(const SparseMatrix &sparseMatrix) {
    if (this->numberOfDimensions != 0) {
        delete[] this->specificDimensionsSizes;
    }
    for (int i = 0; i < numberOfStoredValues; ++i) {
        delete sparseCells[i];
    }

    this->numberOfStoredValues = sparseMatrix.numberOfStoredValues;
    this->numberOfDimensions = sparseMatrix.numberOfDimensions;
    this->defaultValue = sparseMatrix.defaultValue;
    this->sizeOfSparseCellsTable = sparseMatrix.sizeOfSparseCellsTable;
    this->specificDimensionsSizes = new int[this->numberOfDimensions];
    for (int i = 0; i < numberOfDimensions; ++i) {
        this->specificDimensionsSizes[i] = sparseMatrix.specificDimensionsSizes[i];
    }
    this->sparseCells = new SparseCell *[sizeOfSparseCellsTable];
    for (int i = 0; i < numberOfStoredValues; ++i) {
        this->sparseCells[i] = new SparseCell(*sparseMatrix.sparseCells[i]);
    }
}

void SparseMatrix::setName(string name) {
    SparseMatrix::name = name;
}

string SparseMatrix::getName() {
    return name;
}

string SparseMatrix::toString() {
    stringstream stream;
    stream << toStringHeader();
    stream << VALUE_TEXT;
    for (int i = 0; i < numberOfStoredValues; ++i) {
        stream << sparseCells[i]->toString();
    }
    return stream.str();
}

bool SparseMatrix::checkIfCoordinatesWithinBounds(int *coordinates) {
    for (int i = 0; i < numberOfDimensions; ++i) {
        if (coordinates[i] > specificDimensionsSizes[i])
            return false;
    }
    return true;
}

SparseMatrix::SparseMatrix() {
    this->numberOfDimensions = 0;
    this->specificDimensionsSizes = nullptr;
    this->defaultValue = 0;
    init(DEFAULT_NAME);
}

SparseMatrix::SparseMatrix(int numberOfDimensions, int *specificDimensionsSizes, int defaultValue) {
    this->numberOfDimensions = numberOfDimensions;
    this->specificDimensionsSizes = specificDimensionsSizes;
    this->defaultValue = defaultValue;
    init(DEFAULT_NAME);
}


SparseMatrix::SparseMatrix(const SparseMatrix &anotherMatrix) {
    this->name = (anotherMatrix).name + COPY_TEXT;
    copyData(anotherMatrix);
}

SparseMatrix::~SparseMatrix() {
    cerr << MATRIX_DESTRUCTOR_MESSAGE << name << "\n";
    delete[] specificDimensionsSizes;
    for (int i = 0; i < numberOfStoredValues; ++i) {
        delete sparseCells[i];
    }
}

SparseMatrix::SparseMatrix(int numberOfDimensions, int *specificDimensionsSizes, int defaultValue, string name) {
    this->numberOfDimensions = numberOfDimensions;
    this->specificDimensionsSizes = specificDimensionsSizes;
    this->defaultValue = defaultValue;
    init(name);
}

void SparseMatrix::resizeCellsTable() {
    int newSize = (int) (sizeOfSparseCellsTable * 1.5);
    SparseCell **newCells = new SparseCell *[newSize];

    for (int i = 0; i < newSize; i++) {
        if (i < sizeOfSparseCellsTable)
            newCells[i] = sparseCells[i];
        else
            newCells[i] = nullptr;
    }

    for (int i = 0; i < numberOfStoredValues; ++i) {
        delete sparseCells[i];
    }
    sizeOfSparseCellsTable = newSize;
    sparseCells = newCells;
}

int SparseMatrix::getNumberOfDimensions() {
    return numberOfDimensions;
}

void SparseMatrix::init(string name) {
    cerr << MATRIX_CONSTRUCTOR_MESSAGE << name << "\n";
    this->name = name;
    sizeOfSparseCellsTable = 10;
    sparseCells = new SparseCell *[sizeOfSparseCellsTable];
    for (int i = 0; i < sizeOfSparseCellsTable; ++i) {
        sparseCells[i] = nullptr;
    }
    numberOfStoredValues = 0;
}

string SparseMatrix::toStringHeader() {
    stringstream stream;
    stream << name << SIZE_TEXT << "[";
    for (int i = 0; i < numberOfDimensions; ++i) {
        stream << specificDimensionsSizes[i];
        if (i != numberOfDimensions - 1) {
            stream << SEPARATOR;
        }
    }
    stream << "]";
    return stream.str();
}

