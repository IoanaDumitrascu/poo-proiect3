#ifndef PIESAFACTORY_HPP
#define PIESAFACTORY_HPP

#include "PiesaVestimentara.hpp"
#include "Haina.hpp"
#include "Incaltaminte.hpp"
#include "Accesoriu.hpp"
#include "Bijuterie.hpp"
#include "Exceptii.hpp"
#include <memory>
#include <string>



class PiesaFactory {
public:

    static std::unique_ptr<PiesaVestimentara> creeaza(
        const std::string& tip,
        const std::string& denumire,
        const std::string& brand,
        double pret,
        int stil,
        const std::string& param1 = "",
        const std::string& param2 = "0"
    ) {
        if (tip == "Haina") {
            bool imp = (param2 == "1");
            return std::make_unique<Haina>(denumire, brand, pret, stil, param1, imp);
        }
        if (tip == "Incaltaminte") {
            int marime  = param1.empty() ? 40 : std::stoi(param1);
            int confort = std::stoi(param2);
            return std::make_unique<Incaltaminte>(denumire, brand, pret, stil, marime, confort);
        }
        if (tip == "Accesoriu") {
            bool lux = (param2 == "1");
            return std::make_unique<Accesoriu>(denumire, brand, pret, stil, param1, lux);
        }
        if (tip == "Bijuterie") {
            double cantitate = std::stod(param2);
            return std::make_unique<Bijuterie>(denumire, brand, pret, stil, param1, cantitate);
        }
        throw PiesaInvalidaException("Tip necunoscut: " + tip);
    }



    static std::unique_ptr<PiesaVestimentara> rochieDeGala() {
        return std::make_unique<Haina>("Rochie Gala", "Versace", 1200.0, 95, "Matase", false);
    }

    static std::unique_ptr<PiesaVestimentara> sacouBusiness() {
        return std::make_unique<Haina>("Sacou Business", "Hugo Boss", 800.0, 80, "Lana", false);
    }

    static std::unique_ptr<PiesaVestimentara> sneakersCasual() {
        return std::make_unique<Incaltaminte>("Sneakers", "Nike", 350.0, 65, 42, 9);
    }

    static std::unique_ptr<PiesaVestimentara> pantofiFormali() {
        return std::make_unique<Incaltaminte>("Pantofi Oxford", "Gucci", 700.0, 88, 43, 7);
    }

    static std::unique_ptr<PiesaVestimentara> geantaLux() {
        return std::make_unique<Accesoriu>("Geanta Quilted", "Chanel", 2500.0, 92, "Geanta", true);
    }

    static std::unique_ptr<PiesaVestimentara> colierAur() {
        return std::make_unique<Bijuterie>("Colier Aur", "Cartier", 3000.0, 90, "Aur", 18.0);
    }
};

#endif
