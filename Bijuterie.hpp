#ifndef BIJUTERIE_HPP
#define BIJUTERIE_HPP

#include "PiesaVestimentara.hpp"

class Bijuterie : public PiesaVestimentara {
private:
    std::string metal;
    double cantitate;

    void afisareDetalii(std::ostream& os) const;

public:
    Bijuterie(const std::string& den, const std::string& brd, double prt, int pct, const std::string& met, double cant);

    PiesaVestimentara* clone() const;
    const std::string& getMetal() const { return metal; }
    double getCantitate() const { return cantitate; }
    double calculeazaImpact() const;
    std::string getTip() const;
};

#endif
