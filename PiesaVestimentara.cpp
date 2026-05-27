#include "PiesaVestimentara.hpp"
#include "Exceptii.hpp"

int PiesaVestimentara::nrPieseCreate = 0;

PiesaVestimentara::PiesaVestimentara() : denumire("Necunoscut"), brand("Generic"), pretBaza(0), punctajStil(0) {
    nrPieseCreate++;
}

PiesaVestimentara::PiesaVestimentara(const std::string& den, const std::string& brd, double pret, int punctaj)
    : denumire(den), brand(brd), pretBaza(pret), punctajStil(punctaj) {
    if (pret < 0) throw PiesaInvalidaException("pret negativ");
    nrPieseCreate++;
}

PiesaVestimentara::PiesaVestimentara(const PiesaVestimentara& sursa)
    : denumire(sursa.denumire), brand(sursa.brand), pretBaza(sursa.pretBaza), punctajStil(sursa.punctajStil) {
    nrPieseCreate++;
}

PiesaVestimentara& PiesaVestimentara::operator=(const PiesaVestimentara& sursa) {
    if (this != &sursa) {
        denumire = sursa.denumire;
        brand = sursa.brand;
        pretBaza = sursa.pretBaza;
        punctajStil = sursa.punctajStil;
    }
    return *this;
}

PiesaVestimentara::~PiesaVestimentara() {
    nrPieseCreate--;
}

std::ostream& operator<<(std::ostream& os, const PiesaVestimentara& p) {
    os << "[" << p.getTip() << "] " << p.denumire << " | Brand: " << p.brand << " | Pret: " << p.pretBaza << " RON";
    p.afisareDetalii(os);
    return os;
}
