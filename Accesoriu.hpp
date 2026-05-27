#ifndef ACCESORIU_HPP
#define ACCESORIU_HPP

#include "PiesaVestimentara.hpp"

class Accesoriu : public PiesaVestimentara {
private:
    std::string tip;
    bool deLux;

    void afisareDetalii(std::ostream& os) const;

public:
    Accesoriu(const std::string& den, const std::string& brd, double prt, int pct, const std::string& t, bool lux);

    PiesaVestimentara* clone() const;
    const std::string& getTipAccesoriu() const { return tip; }
    bool eDeLux() const { return deLux; }
    double calculeazaImpact() const;
    std::string getTip() const;
};

#endif
