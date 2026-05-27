#pragma once
#include <string>
#include <vector>
#include <iostream>

enum class TipEveniment { Gala, StreetStyle, Business };

TipEveniment parseTipEveniment(const std::string& str);
std::string tipToString(TipEveniment tip);

class Eveniment {
private:
    std::string nume;
    TipEveniment tip;
    std::vector<std::string> tipuriRecomandate;

public:
    Eveniment(const std::string& nume, TipEveniment tip);

    double calculeazaMultiplicator(const std::string& tipPiesa) const;

    const std::string& getNume() const { return nume; }
    TipEveniment getTip() const        { return tip; }

    friend std::ostream& operator<<(std::ostream& os, const Eveniment& e);
};
