#ifndef HAINA_HPP
#define HAINA_HPP

#include "PiesaVestimentara.hpp"

class Haina : public PiesaVestimentara {
private:
    std::string material;
    bool esteImpermeabila;

    void afisareDetalii(std::ostream& os) const;

public:
    Haina(const std::string& den, const std::string& brd, double prt, int pct, const std::string& mat, bool imp);

    PiesaVestimentara* clone() const;
    const std::string& getMaterial() const { return material; }
    bool eImpermeabila() const { return esteImpermeabila; }
    double calculeazaImpact() const;
    std::string getTip() const;
};

#endif
