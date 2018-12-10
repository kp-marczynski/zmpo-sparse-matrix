//
// Created by A671988 on 2017-10-19.
//

#include "SparseMatrixRepository.h"

SparseMatrixRepository::SparseMatrixRepository() {
    cerr << REPOSITORY_CONSTRUCTOR_MESSAGE;
    matricesRepository = new SparseMatrix*[10];
    sizeOfRepository = 10;
    currentNumberOfStoredMatrices = 0;
}
SparseMatrixRepository::~SparseMatrixRepository() {
    cerr << REPOSITORY_DESTRUCTOR_MESSAGE;
    for(int i=0; i<currentNumberOfStoredMatrices;++i){
        delete[] matricesRepository[i];
    }
}

void SparseMatrixRepository::addSparseMatrix(int numberOfDimensions, int *dimensions, int defaultValue, string name){
    resizeRepositoryTable();
    if(!name.empty()){
        matricesRepository[currentNumberOfStoredMatrices] = new SparseMatrix(numberOfDimensions, dimensions,defaultValue,name);
    } else{
        matricesRepository[currentNumberOfStoredMatrices] = new SparseMatrix(numberOfDimensions, dimensions,defaultValue);
    }
//    matricesRepository[currentNumberOfStoredMatrices]->setDimensions(numberOfDimensions, dimensions);
//    matricesRepository[currentNumberOfStoredMatrices]->setDefaultValue(defaultValue);
//    if(!name.empty()) matricesRepository[currentNumberOfStoredMatrices]->setName(name);
    ++currentNumberOfStoredMatrices;
}

SparseMatrix & SparseMatrixRepository::getSparseMatrix(int offset) {
    if (offset < currentNumberOfStoredMatrices && offset >= 0) {
        return *matricesRepository[offset];
    }
    cerr << INDEX_OUT_OF_BOUND_TEXT;
}

int SparseMatrixRepository::deleteOne(int offset) {
    if (offset < currentNumberOfStoredMatrices && offset >= 0) {
//        matricesRepository.erase(matricesRepository.begin() + offset);
        delete matricesRepository[offset];
        --currentNumberOfStoredMatrices;
        for(int i=offset; i<currentNumberOfStoredMatrices;++i){
            matricesRepository[i] = matricesRepository[i+1];
        }
        return true;
    } else {
        cerr << INDEX_OUT_OF_BOUND_TEXT;
        return false;
    }
}

void SparseMatrixRepository::deleteAll() {
    for(int i=0; i<currentNumberOfStoredMatrices;++i){
        delete matricesRepository[i];
    }
    currentNumberOfStoredMatrices = 0;
//    return matricesRepository.clear();
}

string SparseMatrixRepository::toString() {
    stringstream stream;
    stream << MATRICES_TEXT << currentNumberOfStoredMatrices << "\n";
    for (int i = 0; i < currentNumberOfStoredMatrices; ++i) {
        stream << "[" << i << "] - " << matricesRepository[i]->toStringHeader() << "\n";
    }
    return stream.str();
}

bool SparseMatrixRepository::setDimensions(int offset, int numberOfDimensions, int *specificDimensionsSizes) {
    if (offset < currentNumberOfStoredMatrices && offset >= 0) {
        matricesRepository[offset]->setDimensions(numberOfDimensions, specificDimensionsSizes);
        return true;
    } else {
        cerr << INDEX_OUT_OF_BOUND_TEXT;
        return false;
    }
}

bool SparseMatrixRepository::setDefaultValue(int offset, int defaultValue) {
    if (offset < currentNumberOfStoredMatrices && offset >= 0) {
        matricesRepository[offset]->setDefaultValue(defaultValue);
        return true;
    } else {
        cerr << INDEX_OUT_OF_BOUND_TEXT;
        return false;
    }
}

int SparseMatrixRepository::getValue(int offset, int *coordinates) {
    if (offset < currentNumberOfStoredMatrices && offset >= 0) {
        return matricesRepository[offset]->getValue(coordinates);
    } else {
        cerr << INDEX_OUT_OF_BOUND_TEXT;
        return false;
    }
}

int SparseMatrixRepository::setValue(int offset, int *coordinates, int value) {
    if (offset < currentNumberOfStoredMatrices && offset >= 0) {
        return matricesRepository[offset]->setValue(coordinates, value);
    } else {
        cerr << INDEX_OUT_OF_BOUND_TEXT;
        return false;
    }
}

bool SparseMatrixRepository::cloneOne(int offset) {
    if (offset < currentNumberOfStoredMatrices && offset >= 0) {
        resizeRepositoryTable();
        matricesRepository[currentNumberOfStoredMatrices++] = &matricesRepository[offset]->clone();
        return true;
    } else {
        cerr << INDEX_OUT_OF_BOUND_TEXT;
        return false;
    }
}

bool SparseMatrixRepository::setName(int offset, string name) {
    if (offset < currentNumberOfStoredMatrices && offset >= 0){
        matricesRepository[offset]->setName(name);
        return true;
    } else{
        cerr << INDEX_OUT_OF_BOUND_TEXT;
        return false;
    }
}

string SparseMatrixRepository::getName(int offset) {
    if (offset < currentNumberOfStoredMatrices && offset >= 0){
        return matricesRepository[offset]->getName();
    } else{
        cerr << INDEX_OUT_OF_BOUND_TEXT;
        return "";
    }
}

string SparseMatrixRepository::toStringOne(int offset) {
    if (offset < currentNumberOfStoredMatrices && offset >= 0){
        return matricesRepository[offset]->toString();
    } else{
        cerr << INDEX_OUT_OF_BOUND_TEXT;
        return "";
    }
}

void SparseMatrixRepository::resizeRepositoryTable() {
    int newSize = (int) (sizeOfRepository * 1.5);
    SparseMatrix **newMatrixRepo = new SparseMatrix *[newSize];

    for (int i = 0; i < newSize; i++) {
        if (i < sizeOfRepository)
            newMatrixRepo[i] = matricesRepository[i];
        else
            newMatrixRepo[i] = nullptr;
    }

    for (int i = 0; i < currentNumberOfStoredMatrices; ++i) {
        delete matricesRepository[i];
    }
    sizeOfRepository = newSize;
    matricesRepository = newMatrixRepo;
}


