#include "Haina.hpp"

Haina::Haina(const std::string& den, const std::string& brd, double prt, int pct, const std::string& mat, bool imp)
    : PiesaVestimentara(den, brd, prt, pct), material(mat), esteImpermeabila(imp) {}

PiesaVestimentara* Haina::clone() const {
    return new Haina(*this);
}

double Haina::calculeazaImpact() const {
    double imp = punctajStil;
    if (material == "Matase") imp *= 1.5;
    if (esteImpermeabila) imp += 10;
    return imp;
}

std::string Haina::getTip() const { return "Haina"; }

void Haina::afisareDetalii(std::ostream& os) const {
    os << " | Material: " << material << (esteImpermeabila ? " [Impermeabil]" : "");
}
