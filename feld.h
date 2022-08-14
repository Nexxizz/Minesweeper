#ifndef FELD_H
#define FELD_H

#include <iostream>
#include <array>
#include <random>
#include <iomanip>
#include <string>

using namespace std;

enum Belegung {offen, mine, aufgedeckt};

struct Feld {
    Belegung belegung;
    int mineNachbarfeld = 0;

    void initialisieren(int anzahlMinen);
    void darstellen(bool debug, bool ende);
    void zaehleMineNachbar(int reihe, int spalte);
    bool spielen();
    bool oeffneNachbarn(int x, int y);
};

const int breite = 12;
const int hoehe = 12;

static array<array<Feld, breite>, hoehe> spielfeld = {};

//class Feld
//{
//public:
//    Feld();
//};



#endif // FELD_H
