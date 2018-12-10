//
// Created by A671988 on 2017-10-19.
//

#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <regex>

#include "SparseMatrixRepository.h"

const char *ADDMAT_INSTRUCTION = "addmat";
const char *LIST_INSTRUCTION = "list";
const char *DEL_INSTRUCTION = "del";
const char *DELALL_INSTRUCTION = "delall";
const char *DEF_INSTRUCTION = "def";
const char *CLONE_INSTRUCTION = "clone";
const char *RENAME_INSTRUCTION = "rename";
const char *PRINT_INSTRUCTION = "print";
const char *QUIT_INSTRUCTION = "quit";

const char *REGEX_TEMPLATE = "^-?\\d+";

const char *HELLO_MESSAGE = "***** Witaj w programie do obslugi wektora rzadkiego! *****\n"
        "Dostepne polecenia:\n"
        "1) mvec <len> <def>\n"
        "       wykonanie polecenia usuwa istniejacy wektor rzadki(jesli jakis istnieje)\n"
        "       i tworzy nowy wektor o dlugosci <len>\n"
        "       i wartosci domyslnej wektora rzadkiego <def>\n"
        "2) len <len>\n"
        "       zmiana dlugosci wektora rzadkiego. Jesli zostaje zmniejszona to, to te\n"
        "       pozycje, ktore inne niż domyslna, a nie mieszcza sie w nowym zakresie\n"
        "       powinny zostac usuniete z tablicy wartosci i tablicy offsetow.\n"
        "3) def <off> <val>\n"
        "       ustalenie wartosci <val> dla offsetu <off> wektora\n"
        "4) def2 <off 0> <val 0> <off 1> <val 1>\n"
        "       ustalenie wartosci jak w 3) dla 2 par wartosci\n"
        "5) print\n"
        "       wykonanie polecenia wypisuje na ekran aktualny stan wektora\n"
        "6) del\n"
        "       usuwa wszystkie dynamicznie alokowane zmienne dla wektor rzadkiego,\n"
        "       jesli wektor obecnie istnieje.\n"
        "7) quit\n"
        "       konczy wykonywanie programu\n"
        "***********************************************************";

const char *OPERATION_PROMPT = "\nPodaj polecenie: ";

const char *WRONG_COMMAND_TEXT = "polecenie nie istnieje";
const char *WRONG_ARGUMENT_TEXT = "pierwszy argument nie byl liczba";

class Interface{
public:
    static void showInterface();
    static int getNumberFromUserInput(stringstream &stream, bool &hasGettingArgumentFailed);

    static int *getMultipleNumbersFromUserInput(stringstream &stream, int number, bool &hasFailed);

    static string getStringFromUserInput(stringstream &stream);
};


#endif //INTERFACE_H
