#include "Garderoba.hpp"
#include "Eveniment.hpp"
#include "Exceptii.hpp"
#include "PiesaFactory.hpp"
#include "ScoreStrategy.hpp"
#include "Colectie.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <string>

static void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


template <typename T>
void afiseazaDenumiri(const std::vector<T*>& v) {
    std::cout << "[ ";
    for (const auto& p : v)
        std::cout << p->getDenumire() << " | ";
    std::cout << "]\n";
}

static void adaugaHaina(Garderoba& g) {
    std::string den, brd, mat;
    double pret; int stil; bool imp;
    std::cout << "Denumire: ";  std::getline(std::cin, den);
    std::cout << "Brand: ";     std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Material (Bumbac/Matase/Piele/Casmir): "; std::getline(std::cin, mat);
    std::cout << "Impermeabila? (1=Da, 0=Nu): "; std::cin >> imp; clearInput();

    g.adaugaPiesa(PiesaFactory::creeaza("Haina", den, brd, pret, stil,
                                        mat, imp ? "1" : "0").release());
    std::cout << "Haina adaugata!\n";
}

static void adaugaIncaltaminte(Garderoba& g) {
    std::string den, brd;
    double pret; int stil, marime, confort;
    std::cout << "Denumire: ";  std::getline(std::cin, den);
    std::cout << "Brand: ";     std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Marime: ";    std::cin >> marime; clearInput();
    std::cout << "Confort (1-10): "; std::cin >> confort; clearInput();
    g.adaugaPiesa(PiesaFactory::creeaza("Incaltaminte", den, brd, pret, stil,
                                        std::to_string(marime),
                                        std::to_string(confort)).release());
    std::cout << "Incaltaminte adaugata!\n";
}

static void adaugaAccesoriu(Garderoba& g) {
    std::string den, brd, tip;
    double pret; int stil; bool lux;
    std::cout << "Denumire: ";  std::getline(std::cin, den);
    std::cout << "Brand: ";     std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Tip (Geanta/Esarfa/Ochelari): "; std::getline(std::cin, tip);
    std::cout << "De lux? (1=Da, 0=Nu): "; std::cin >> lux; clearInput();
    g.adaugaPiesa(PiesaFactory::creeaza("Accesoriu", den, brd, pret, stil,
                                        tip, lux ? "1" : "0").release());
    std::cout << "Accesoriu adaugat!\n";
}

static void adaugaBijuterie(Garderoba& g) {
    std::string den, brd, metal;
    double pret, cantitate; int stil;
    std::cout << "Denumire: ";  std::getline(std::cin, den);
    std::cout << "Brand: ";     std::getline(std::cin, brd);
    std::cout << "Pret (RON): "; std::cin >> pret; clearInput();
    std::cout << "Stil (0-100): "; std::cin >> stil; clearInput();
    std::cout << "Metal (Aur/Argint/Platina): "; std::getline(std::cin, metal);
    std::cout << "Cantitate (grame): "; std::cin >> cantitate; clearInput();
    g.adaugaPiesa(PiesaFactory::creeaza("Bijuterie", den, brd, pret, stil,
                                        metal, std::to_string(cantitate)).release());
    std::cout << "Bijuterie adaugata!\n";
}

static void meniuEveniment(Garderoba& g) {
    std::string numeEv, tipStr;
    double prag;
    std::cout << "Nume eveniment: ";  std::getline(std::cin, numeEv);
    std::cout << "Tip (Gala/Street-Style/Business): "; std::getline(std::cin, tipStr);
    std::cout << "Prag pentru VIRAL: "; std::cin >> prag; clearInput();

    Eveniment ev(numeEv, parseTipEveniment(tipStr));
    double scor = g.calculeazaScorPentruEveniment(ev);

    std::cout << "\n REZULTAT EVENIMENT \n"
              << "Scor realizat: " << scor << "\n"
              << "Prag necesar:  " << prag << "\n";
    if (scor >= prag)
        std::cout << "FELICITARI! Ai devenit VIRAL! \n";
    else
        std::cout << " Tinuta nu a impresionat. Mai lucreaza la garderoba! \n";

    g.afiseazaScorEveniment(ev);
}

static void meniuSchimbaStrategie(Garderoba& g) {
    std::cout << "Strategii disponibile:\n"
              << "  1. simplu  - suma totala a impacturilor\n"
              << "  2. medie   - media impacturilor\n"
              << "  3. top3    - suma celor mai bune 3 piese\n"
              << "Alegere: ";
    std::string s; std::getline(std::cin, s);
    std::string tip = (s == "1") ? "simplu" : (s == "2") ? "medie" : "top3";
    g.setStrategy(ScoreStrategyFactory::creeaza(tip));
    std::cout << "Strategie schimbata!\n";
}


static void demonstratieColectie() {
    std::cout << "\n DEMO Colectie<string> (clasa sablon)\n";
    Colectie<std::string> branduri;
    branduri.adauga("Gucci");
    branduri.adauga("Zara");
    branduri.adauga("Chanel");
    branduri.adauga("H&M");


    auto lux = branduri.filtreaza([](const std::string& b) { return b.size() > 4; });
    std::cout << "Branduri de lux (>4 litere): " << lux;

    branduri.sorteaza([](const std::string& a, const std::string& b) { return a < b; });
    std::cout << "Toate brandurile (sortate): " << branduri;
}

static void meniuCatalog(Garderoba& g) {
    std::cout << "\n CATALOG PIESE PREDEFINITE \n"
              << "1. Rochie de Gala (Versace, 1200 RON)\n"
              << "2. Sacou Business (Hugo Boss, 800 RON)\n"
              << "3. Sneakers (Nike, 350 RON)\n"
              << "4. Pantofi Oxford (Gucci, 700 RON)\n"
              << "5. Geanta Lux (Chanel, 2500 RON)\n"
              << "6. Colier Aur (Cartier, 3000 RON)\n"
              << "Alegere: ";
    int opt; std::cin >> opt; clearInput();

    std::unique_ptr<PiesaVestimentara> p;
    switch(opt) {
        case 1: p = PiesaFactory::rochieDeGala();  break;
        case 2: p = PiesaFactory::sacouBusiness(); break;
        case 3: p = PiesaFactory::sneakersCasual(); break;
        case 4: p = PiesaFactory::pantofiFormali(); break;
        case 5: p = PiesaFactory::geantaLux();     break;
        case 6: p = PiesaFactory::colierAur();     break;
        default: std::cout << "Optiune invalida.\n"; return;
    }
    g.adaugaPiesa(p.release());
    std::cout << "Piesa adaugata din catalog!\n";
}

int main() {
    std::cout << " TRENDSETTER: SIMULATOR DE INFLUENTA SI STIL \n\n";

    std::string numeIn;
    double bugetIn;
    std::cout << "Nume influencer: "; std::getline(std::cin, numeIn);
    std::cout << "Buget initial (RON): "; std::cin >> bugetIn; clearInput();


    Garderoba garderoba(numeIn, bugetIn);

    try {
        garderoba.incarcaDinFisier("garderoba.csv");
        std::cout << "[INFO] Garderoba incarcata din fisier.\n";
    } catch (const FisierException&) {
        std::cout << "[INFO] Fisier nou - garderoba goala.\n";
    }

    int opt = -1;
    while (opt != 0) {
        std::cout << "\n MENIU \n"
                  << "1.  Adauga Haina\n"
                  << "2.  Adauga Incaltaminte\n"
                  << "3.  Adauga Accesoriu\n"
                  << "4.  Adauga Bijuterie\n"
                  << "5.  Adauga din catalog (Factory)\n"
                  << "6.  Afiseaza garderoba\n"
                  << "7.  Scor eveniment\n"
                  << "8.  Schimba strategie scor\n"
                  << "9.  Top piese\n"
                  << "10. Elimina piese slabe\n"
                  << "11. Haine impermeabile\n"
                  << "12. Demo clasa sablon\n"
                  << "13. Salveaza\n"
                  << "0.  Iesire\n"
                  << "Alegere: ";
        std::cin >> opt; clearInput();

        try {
            switch (opt) {
                case 1:  adaugaHaina(garderoba);          break;
                case 2:  adaugaIncaltaminte(garderoba);   break;
                case 3:  adaugaAccesoriu(garderoba);      break;
                case 4:  adaugaBijuterie(garderoba);      break;
                case 5:  meniuCatalog(garderoba);         break;
                case 6:  std::cout << garderoba;          break;
                case 7:  meniuEveniment(garderoba);       break;
                case 8:  meniuSchimbaStrategie(garderoba); break;
                case 9: {
                    int n; std::cout << "Cate: "; std::cin >> n; clearInput();
                    garderoba.afiseazaTopPiese(n); break;
                }
                case 10: {
                    double prag; std::cout << "Prag: "; std::cin >> prag; clearInput();
                    garderoba.eliminaPieseSub(prag); break;
                }
                case 11: garderoba.afiseazaHaineImpermeabile();  break;
                case 12: demonstratieColectie();                  break;
                case 13:
                    garderoba.salveazaInFisier("garderoba.csv");
                    std::cout << "Salvat!\n"; break;
                case 0: std::cout << "La revedere!\n"; break;
                default: std::cout << "Optiune invalida.\n";
            }
        } catch (const BugetInsuficientException& e) {
            std::cerr << "[EROARE BUGET] " << e.what() << "\n";
        } catch (const PiesaInvalidaException& e) {
            std::cerr << "[EROARE PIESA] " << e.what() << "\n";
        } catch (const EvenimentInexistentException& e) {
            std::cerr << "[EROARE EVENIMENT] " << e.what() << "\n";
        } catch (const FisierException& e) {
            std::cerr << "[EROARE FISIER] " << e.what() << "\n";
        } catch (const TrendsetterException& e) {
            std::cerr << "[EROARE] " << e.what() << "\n";
        }
    }
    return 0;
}
