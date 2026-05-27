#ifndef INCALTAMINTE_HPP
#define INCALTAMINTE_HPP

#include "PiesaVestimentara.hpp"

class Incaltaminte : public PiesaVestimentara {
private:
    int marime;
    int nivelConfort;

    void afisareDetalii(std::ostream& os) const;

public:
    Incaltaminte(const std::string& den, const std::string& brd, double prt, int pct, int marime, int confort);

    PiesaVestimentara* clone() const;
    double calculeazaImpact() const;
    std::string getTip() const;

    int getMarime() const { return marime; }
    int getConfort() const { return nivelConfort; }
};

#endif
