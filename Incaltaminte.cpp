#include "Incaltaminte.hpp"

Incaltaminte::Incaltaminte(const std::string& den, const std::string& brd, double prt, int pct, int m, int c)
    : PiesaVestimentara(den, brd, prt, pct), marime(m), nivelConfort(c) {}

PiesaVestimentara* Incaltaminte::clone() const {
    return new Incaltaminte(*this);
}

double Incaltaminte::calculeazaImpact() const {
    return (double)punctajStil + (nivelConfort * 2.0);
}

std::string Incaltaminte::getTip() const {
    return "Incaltaminte";
}

void Incaltaminte::afisareDetalii(std::ostream& os) const {
    os << " | Marime: " << marime << " | Confort: " << nivelConfort << "/10";
}
