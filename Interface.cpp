//
// Created by A671988 on 2017-10-19.
//

#include "Interface.h"

int main() {
    Interface::showInterface();
}

void Interface::showInterface() {
    SparseMatrixRepository matrixRepository;
    bool endOfProgram = false;
    cout << HELLO_MESSAGE;
    while (!endOfProgram) {
        cout << OPERATION_PROMPT;
        string lineFromUser;
        string command;
        getline(cin, lineFromUser);
        stringstream stream(lineFromUser);
        stream >> command;
        bool hasGettingArgumentFailed = false;
        if (command == ADDMAT_INSTRUCTION) {
            int numberOfDimensions = getNumberFromUserInput(stream, hasGettingArgumentFailed);
            if (!hasGettingArgumentFailed) {
                int *dimensions = getMultipleNumbersFromUserInput(stream, numberOfDimensions, hasGettingArgumentFailed);
                if (!hasGettingArgumentFailed) {
                    int defaultValue = getNumberFromUserInput(stream, hasGettingArgumentFailed);
                    string name = getStringFromUserInput(stream);
                    matrixRepository.addSparseMatrix(numberOfDimensions, dimensions, defaultValue, name);
                }
            }
        } else if (command == LIST_INSTRUCTION) {
            cout << matrixRepository.toString();
        } else if (command == PRINT_INSTRUCTION) {
            int offset = getNumberFromUserInput(stream, hasGettingArgumentFailed);
            if (!hasGettingArgumentFailed) {
                cout << matrixRepository.toStringOne(offset);
            }
        } else if (command == DEL_INSTRUCTION) {
            int offset = getNumberFromUserInput(stream, hasGettingArgumentFailed);
            if (!hasGettingArgumentFailed) {
                matrixRepository.deleteOne(offset);
            }
        } else if (command == DELALL_INSTRUCTION) {
            matrixRepository.deleteAll();
        } else if (command == DEF_INSTRUCTION) {
            int offset = getNumberFromUserInput(stream, hasGettingArgumentFailed);
            if (!hasGettingArgumentFailed) {
                int numberOfDimensions = matrixRepository.getSparseMatrix(offset).getNumberOfDimensions();
                int *specificDimensions = new int[numberOfDimensions];
                for (int i = 0; i < numberOfDimensions; ++i) {
                    specificDimensions[i] = getNumberFromUserInput(stream, hasGettingArgumentFailed);
                }
                if (!hasGettingArgumentFailed) {
                    int value = getNumberFromUserInput(stream, hasGettingArgumentFailed);
                    if (!hasGettingArgumentFailed) {
                        matrixRepository.setValue(offset, specificDimensions, value);
                    }
                }
            }
        } else if (command == CLONE_INSTRUCTION) {
            int offset = getNumberFromUserInput(stream, hasGettingArgumentFailed);
            if (!hasGettingArgumentFailed) {
                matrixRepository.cloneOne(offset);
            }
        } else if (command == RENAME_INSTRUCTION) {
            int offset = getNumberFromUserInput(stream, hasGettingArgumentFailed);
            if (!hasGettingArgumentFailed) {
                string newName = getStringFromUserInput(stream);
                if (!hasGettingArgumentFailed) {
                    matrixRepository.setName(offset, newName);
                }
            }
        } else if (command == QUIT_INSTRUCTION) {
            endOfProgram = true;
            matrixRepository.deleteAll();
        } else {
            cerr << WRONG_COMMAND_TEXT;
        }
    }
}

int Interface::getNumberFromUserInput(stringstream &stream, bool &hasGettingArgumentFailed) {
    string argumentFromStream;
    stream >> argumentFromStream;
    regex regexTemplate(REGEX_TEMPLATE);
    bool isNumber = regex_match(argumentFromStream, regexTemplate);
    if (isNumber) {
        hasGettingArgumentFailed = false;
        return stoi(argumentFromStream);
    }
    cerr << WRONG_ARGUMENT_TEXT;
    hasGettingArgumentFailed = true;
    return false;
}

int *Interface::getMultipleNumbersFromUserInput(stringstream &stream, int number, bool &hasGettingArumentFailed) {
    int *output = new int[number];
    hasGettingArumentFailed = false;
    for (int i = 0; i < number && !hasGettingArumentFailed; ++i) {
        output[i] = getNumberFromUserInput(stream, hasGettingArumentFailed);
    }
    return output;
}

string Interface::getStringFromUserInput(stringstream &stream) {
    string output;
    stream >> output;
    return output;
}


