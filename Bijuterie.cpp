#include "Bijuterie.hpp"

Bijuterie::Bijuterie(const std::string& den, const std::string& brd, double prt, int pct, const std::string& met, double cant)
    : PiesaVestimentara(den, brd, prt, pct), metal(met), cantitate(cant) {}

PiesaVestimentara* Bijuterie::clone() const {
    return new Bijuterie(*this);
}

double Bijuterie::calculeazaImpact() const {
    double mult = 1.0;
    if (metal == "Platina") mult = 3.0;
    else if (metal == "Aur") mult = 2.5;
    return punctajStil * mult;
}

std::string Bijuterie::getTip() const {
    return "Bijuterie";
}

void Bijuterie::afisareDetalii(std::ostream& os) const {
    os << " | Metal: " << metal << " | Cantitate: " << cantitate << "g";
}
