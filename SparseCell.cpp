//
// Created by A671988 on 2017-10-19.
//

#include "SparseCell.h"

SparseCell::SparseCell(int numberOfDimensions, int *coordinates, int value) {
    cerr << CELL_CONSTRUCTOR_MESSAGE;
    dimensions = numberOfDimensions;
    this->coordinates = coordinates;
    this->value = value;
}

SparseCell::SparseCell(SparseCell &cell) {
    this->dimensions = cell.dimensions;
    this->coordinates = new int[dimensions];
    for (int i = 0; i < dimensions; ++i) {
        coordinates[i] = cell.coordinates[i];
    }
    this->value = cell.value;
}

SparseCell::~SparseCell() {
    cerr << CELL_DESTRUCTOR_MESSAGE;
    delete[] coordinates;
}

int SparseCell::compareCoordinates(int *coordinates) {
    for (int i = 0; i < dimensions; ++i) {
        if (coordinates[i] > this->coordinates[i]) return 1;
        else if (coordinates[i] < this->coordinates[i]) return -1;
    }
    return 0;
}

string SparseCell::toString() {
    stringstream stream;
    stream << "[";
    for (int i = 0; i < dimensions; ++i) {
        stream << coordinates[i];
        if (i != dimensions - 1) {
            stream << ";";
        }
    }
    stream << "] " << this->value;
    return stream.str();
}


