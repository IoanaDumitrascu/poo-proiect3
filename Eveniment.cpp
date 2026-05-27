#include "Eveniment.hpp"
#include "Exceptii.hpp"

TipEveniment parseTipEveniment(const std::string& str) {
    if (str == "Gala")         return TipEveniment::Gala;
    if (str == "Street-Style") return TipEveniment::StreetStyle;
    if (str == "Business")     return TipEveniment::Business;
    throw EvenimentInexistentException(str);
}

std::string tipToString(TipEveniment tip) {
    switch (tip) {
        case TipEveniment::Gala:        return "Gala";
        case TipEveniment::StreetStyle: return "Street-Style";
        case TipEveniment::Business:    return "Business";
    }
    return "Necunoscut";
}

Eveniment::Eveniment(const std::string& n, TipEveniment t) : nume(n), tip(t) {
    switch (tip) {
        case TipEveniment::Gala:
            tipuriRecomandate = {"Haina", "Bijuterie", "Accesoriu"};
            break;
        case TipEveniment::StreetStyle:
            tipuriRecomandate = {"Haina", "Incaltaminte", "Accesoriu"};
            break;
        case TipEveniment::Business:
            tipuriRecomandate = {"Haina", "Incaltaminte", "Bijuterie"};
            break;
    }
}

double Eveniment::calculeazaMultiplicator(const std::string& tipPiesa) const {
    for (const auto& t : tipuriRecomandate)
        if (t == tipPiesa) return 1.5;
    return 1.0;
}

std::ostream& operator<<(std::ostream& os, const Eveniment& e) {
    os << "Eveniment: " << e.nume << " [" << tipToString(e.tip) << "]";
    return os;
}
