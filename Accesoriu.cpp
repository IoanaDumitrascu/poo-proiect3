#include "Accesoriu.hpp"

Accesoriu::Accesoriu(const std::string& den, const std::string& brd, double prt, int pct, const std::string& t, bool lux)
    : PiesaVestimentara(den, brd, prt, pct), tip(t), deLux(lux) {}

PiesaVestimentara* Accesoriu::clone() const {
    return new Accesoriu(*this);
}

double Accesoriu::calculeazaImpact() const {
    return deLux ? (punctajStil * 2.2) : (double)punctajStil;
}

std::string Accesoriu::getTip() const {
    return "Accesoriu";
}

void Accesoriu::afisareDetalii(std::ostream& os) const {
    os << " | Tip: " << tip << (deLux ? " [LUX]" : " [Standard]");
}
