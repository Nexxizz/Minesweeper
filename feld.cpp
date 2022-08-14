#include "feld.h"

void Feld::initialisieren(int anzahlMinen)
{
    srand(time(NULL));

    int anzMinen = anzahlMinen;

    for(size_t i = 0; i < breite; i++) {
        for(size_t j = 0; j < hoehe; j++) {
            spielfeld.at(i).at(j).belegung = Belegung::offen;
            spielfeld.at(i).at(j).mineNachbarfeld = 0;
        }
    }

    for(size_t i = 0; i < breite; i++) {
        for(size_t j = 0; j < hoehe; j++) {
            zaehleMineNachbar(i,j);
        }
    }

    for(size_t i = 0; i < anzMinen; i++) {
        int reihe = rand() % breite;
        int spalte = rand() % hoehe;
        if(spielfeld.at(reihe).at(spalte).belegung == Belegung::offen) {
            spielfeld.at(reihe).at(spalte).belegung = Belegung::mine;
            anzMinen--;
        }
        if(spielfeld.at(reihe).at(spalte).belegung == Belegung::mine) {
            anzMinen++;
        }
    }
    for(size_t i = 0; i < breite; i++) {
        for(size_t j = 0; j < hoehe; j++) {
            zaehleMineNachbar(i, j);
        }
    }
}

void Feld::darstellen(bool debug, bool ende)
{
    for(size_t i = 0; i < breite; i++) {
        cout << setfill('0') << setw(2) << i + 1 << "| ";
        for(size_t j = 0; j < hoehe; j++) {
            if (debug == false) {
                if(ende == false) {
                    if(spielfeld.at(i).at(j).belegung == Belegung::offen || spielfeld.at(i).at(j).belegung == Belegung::mine) {
                        cout << "*" << " ";
                    }
                    if(spielfeld.at(i).at(j).belegung == Belegung::aufgedeckt && spielfeld.at(i).at(j).belegung != Belegung::mine
                            && spielfeld.at(i).at(j).mineNachbarfeld == 0) {
                        cout << "." << " ";
                    }
                    if(spielfeld.at(i).at(j).belegung == Belegung::aufgedeckt && spielfeld.at(i).at(j).belegung != Belegung::mine
                            && spielfeld.at(i).at(j).mineNachbarfeld != 0) {
                        cout << spielfeld.at(i).at(j).mineNachbarfeld << " ";
                    }
                }
                // Wenn Mine getroffen
                else {
                    if(spielfeld.at(i).at(j).belegung == Belegung::offen) {
                        cout << "*" << " ";
                    }
                    if(spielfeld.at(i).at(j).belegung == Belegung::mine) {
                        cout << "X" << " ";
                    }
                    if(spielfeld.at(i).at(j).belegung == Belegung::aufgedeckt && spielfeld.at(i).at(j).belegung != Belegung::mine
                            && spielfeld.at(i).at(j).mineNachbarfeld == 0) {
                        cout << "." << " ";
                    }
                    if(spielfeld.at(i).at(j).belegung == Belegung::aufgedeckt && spielfeld.at(i).at(j).belegung != Belegung::mine
                            && spielfeld.at(i).at(j).mineNachbarfeld != 0) {
                        cout << spielfeld.at(i).at(j).mineNachbarfeld << " ";
                    }
                }
            }
            // Nur für Debug Modus
            else {
                if(spielfeld.at(i).at(j).belegung == Belegung::offen) {
                    cout << "*" << " ";
                }
                if(spielfeld.at(i).at(j).belegung == Belegung::mine) {
                    cout << "X" << " ";
                }
                if(spielfeld.at(i).at(j).belegung == Belegung::aufgedeckt && spielfeld.at(i).at(j).belegung != Belegung::mine
                        && spielfeld.at(i).at(j).mineNachbarfeld == 0) {
                    cout << "." << " ";
                }
                if(spielfeld.at(i).at(j).belegung == Belegung::aufgedeckt && spielfeld.at(i).at(j).belegung != Belegung::mine
                        && spielfeld.at(i).at(j).mineNachbarfeld != 0) {
                    cout << spielfeld.at(i).at(j).mineNachbarfeld << " ";
                }
            }

        }
        cout << endl;
    }
    cout << "  ";
    for(size_t i = 0; i < breite; i++) {
        cout << "__";
    }
    cout << "_";
    cout << endl;
    cout << "  ";
    for(size_t i = 0; i < breite; i++) {
        cout << i + 1 << " ";
    }
    cout << endl;
}

void Feld::zaehleMineNachbar(int reihe, int spalte)
{
    // Obere Reihe
    if (reihe != 0) {
        if (spalte != 0) {
            if(spielfeld.at(reihe-1).at(spalte-1).belegung == Belegung::mine) {
                spielfeld.at(reihe).at(spalte).mineNachbarfeld++;
            }
        }
        if(spielfeld.at(reihe-1).at(spalte).belegung == Belegung::mine) {
            spielfeld.at(reihe).at(spalte).mineNachbarfeld++;
        }
        if(spalte != hoehe - 1) {
            if(spielfeld.at(reihe-1).at(spalte+1).belegung == Belegung::mine) {
                spielfeld.at(reihe).at(spalte).mineNachbarfeld++;
            }
        }
    }
    //Untere Reihe
    if(reihe != hoehe - 1) {
        if (spalte != 0) {
            if(spielfeld.at(reihe+1).at(spalte-1).belegung == Belegung::mine) {
                spielfeld.at(reihe).at(spalte).mineNachbarfeld++;
            }
        }
        if(spielfeld.at(reihe+1).at(spalte).belegung == Belegung::mine) {
            spielfeld.at(reihe).at(spalte).mineNachbarfeld++;
        }
        if(spalte != hoehe - 1) {
            if(spielfeld.at(reihe+1).at(spalte+1).belegung == Belegung::mine) {
                spielfeld.at(reihe).at(spalte).mineNachbarfeld++;
            }
        }
    }
    //Seitlich
    if(spalte != 0) {
        if(spielfeld.at(reihe).at(spalte-1).belegung == Belegung::mine) {
            spielfeld.at(reihe).at(spalte).mineNachbarfeld++;
        }
    }
    if(spalte != breite - 1) {
        if(spielfeld.at(reihe).at(spalte+1).belegung == Belegung::mine) {
            spielfeld.at(reihe).at(spalte).mineNachbarfeld++;
        }
    }
}

bool Feld::spielen()
{
    string eingabe{};
    int x{-1};
    int y{-1};

    bool debug = true;

    while (true) {
        darstellen(debug, false);
        cout << "Bitte Koordinaten (z.B. 1 enter 3) eingeben, auf der Stelle das Sie aufdecken moechten (-2 um abzubrechen):" << endl;
        cin >> x;
        cin >> y;
        if (x == -2 || y == -2) {
            break;
        }
        x--;
        y--;
        cout << x << "\t" << y << endl;
        if(x > breite - 1 || x < 0 || y > hoehe - 1 || y < 0) {
            cout << "Bitte im Bereich 1 - 12 eingeben" << endl;
            continue;
        }
        if (spielfeld.at(x).at(y).belegung != Belegung::mine) {
            oeffneNachbarn(x, y);
//            spielfeld.at(x).at(y).belegung = Belegung::aufgedeckt;
        }
        else {
            cout << "Sie haben eine Mine getroffen und somit das Spiel verloren" << endl;
            darstellen(false, true);
            return false;
        }
    }
    return true;
}

bool Feld::oeffneNachbarn(int x, int y)
{
//    bool zahlGefunden = false;
//    while (zahlGefunden == false) {
//        for(size_t i = x; i < breite; i++) {
//            for(size_t j = y; j < hoehe; j++) {
//                if(spielfeld.at(i).at(j).mineNachbarfeld > 0) {
//                    spielfeld.at(i).at(j).belegung = Belegung::aufgedeckt;
//                    zahlGefunden = true;
//                    break;
//                }
//                if(spielfeld.at(i).at(j).mineNachbarfeld == 0) {
//                    spielfeld.at(i).at(j).belegung = Belegung::aufgedeckt;
//                }
//            }
//            if(zahlGefunden == true){
//                break;
//            }
//        }
//    }

    int erweitern = 1;
    bool zahlGefunden = false;
    //    int i = x;
    //    int j = y;
    while (x + erweitern < breite && x - erweitern >= 0 && y + erweitern < breite && y - erweitern >= 0) {
        cout << erweitern << endl;
        cout << "x + erweitern: " << x + erweitern << " x - erweitern: " << x - erweitern << endl;
        cout << "y + erweitern: " << y + erweitern << " y - erweitern: " << y - erweitern << endl;
        erweitern++;
        for (size_t i = x; i < breite; i++) {
            if (spielfeld.at(i).at(y + erweitern).mineNachbarfeld > 0) {
                zahlGefunden = true;
                break;
            } else {
                spielfeld.at(i).at(y + erweitern).belegung = Belegung::aufgedeckt;
            }
        }
        for (size_t i = y; i < hoehe; i++) {
            if (spielfeld.at(x + erweitern).at(i).mineNachbarfeld > 0) {
                zahlGefunden = true;
                break;
            } else {
                spielfeld.at(x + erweitern).at(i).belegung = Belegung::aufgedeckt;
            }
        }
        for (size_t i = x; i >= 0; i--) {
            if (spielfeld.at(i).at(y - erweitern).mineNachbarfeld > 0) {
                zahlGefunden = true;
                break;
            } else {
                spielfeld.at(i).at(y - erweitern).belegung = Belegung::aufgedeckt;
            }
        }
        for (size_t i = y; i >= 0; i--) {
            if (spielfeld.at(x - erweitern).at(i).mineNachbarfeld > 0) {
                zahlGefunden = true;
                break;
            } else {
                spielfeld.at(x - erweitern).at(i).belegung = Belegung::aufgedeckt;
            }
        }
        if(zahlGefunden == true) {
            break;
        }
//         for(int i = x; i < breite; i++) {
//             for(int j = y; j < hoehe; j++) {
//                 if (spielfeld.at(i).at(j).belegung == Belegung::mine) {
//                     zahlGefunden = true;
//                 }
//                 spielfeld.at(i).at(j).belegung = Belegung::aufgedeckt;
//             }
//         }
//         while (zahlGefunden == false) {
//             while (zahlGefunden == false) {
//                 if (spielfeld.at(x + erweitern).at(y + erweitern).belegung == Belegung::mine) {
//                     zahlGefunden = true;
//                 }
//                 spielfeld.at(x + erweitern).at(y + erweitern).belegung = Belegung::aufgedeckt;
//             }
//         }
    }
    return true;
}
