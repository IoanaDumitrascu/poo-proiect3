#ifndef PIESAVESTIMENTARA_HPP
#define PIESAVESTIMENTARA_HPP

#include <iostream>
#include <string>

class PiesaVestimentara {
protected:
    std::string denumire;
    std::string brand;
    double pretBaza;
    int punctajStil;
    static int nrPieseCreate;

public:
    PiesaVestimentara();
    PiesaVestimentara(const std::string& den, const std::string& brd, double pret, int punctaj);


    PiesaVestimentara(const PiesaVestimentara& sursa);
    PiesaVestimentara& operator=(const PiesaVestimentara& sursa);
    virtual ~PiesaVestimentara();

    virtual PiesaVestimentara* clone() const = 0;
    virtual double calculeazaImpact() const = 0;
    virtual std::string getTip() const = 0;


    virtual void afisareDetalii(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const PiesaVestimentara& p);

    const std::string& getDenumire() const { return denumire; }
    double getPret() const { return pretBaza; }
    int getPunctajStil() const { return punctajStil; }
    const std::string& getBrand() const { return brand; }
    static int getNrPiese() { return nrPieseCreate; }
};

#endif
