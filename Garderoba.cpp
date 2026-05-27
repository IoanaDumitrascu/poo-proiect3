#include "Garderoba.hpp"
#include "Exceptii.hpp"
#include "Haina.hpp"
#include "Incaltaminte.hpp"
#include "Accesoriu.hpp"
#include "Bijuterie.hpp"
#include "PiesaFactory.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>

Garderoba::Garderoba(const std::string& nume, double b,
                     std::unique_ptr<ScoreStrategy> strategy)
    : numeInfluencer(nume), buget(b),
      scoreStrategy(strategy ? std::move(strategy) : std::make_unique<ScoreSimple>()) {}

Garderoba::Garderoba(const Garderoba& sursa)
    : numeInfluencer(sursa.numeInfluencer), buget(sursa.buget),
      scoreStrategy(std::make_unique<ScoreSimple>()) {
    for (const auto& p : sursa.piese)
        piese.emplace_back(p->clone());
}

Garderoba& Garderoba::operator=(Garderoba sursa) {
    swap(*this, sursa);
    return *this;
}

void swap(Garderoba& a, Garderoba& b) noexcept {
    using std::swap;
    swap(a.numeInfluencer, b.numeInfluencer);
    swap(a.buget, b.buget);
    swap(a.piese, b.piese);
    swap(a.scoreStrategy, b.scoreStrategy);
}

std::vector<PiesaVestimentara*> Garderoba::getRawPiese() const {
    std::vector<PiesaVestimentara*> raw;
    raw.reserve(piese.size());
    for (const auto& p : piese) raw.push_back(p.get());
    return raw;
}

void Garderoba::adaugaPiesa(PiesaVestimentara* p) {
    std::unique_ptr<PiesaVestimentara> up(p);
    if (buget < up->getPret())
        throw BugetInsuficientException(up->getDenumire(), up->getPret(), buget);
    buget -= up->getPret();
    piese.push_back(std::move(up));
}

double Garderoba::calculeazaScorPentruEveniment(const Eveniment& ev) const {
    return scoreStrategy->calculeaza(getRawPiese(), ev);
}

void Garderoba::afiseazaScorEveniment(const Eveniment& ev) const {
    std::cout << "\n SCOR [" << scoreStrategy->nume() << "] PENTRU: " << ev << " \n";
    auto raw = getRawPiese();
    for (auto p : raw) {
        double mult = ev.calculeazaMultiplicator(p->getTip());
        std::cout << *p << "\n"
                  << "   -> Scor: " << std::fixed << std::setprecision(1)
                  << p->calculeazaImpact() * mult << " (x" << mult << ")\n";
    }
    std::cout << "SCOR TOTAL: " << calculeazaScorPentruEveniment(ev)
              << " followeri potentiali\n";
}

void Garderoba::afiseazaTopPiese(int n) const {
    std::vector<PiesaVestimentara*> sortate = getRawPiese();
    std::sort(sortate.begin(), sortate.end(),
        [](PiesaVestimentara* a, PiesaVestimentara* b) {
            return a->calculeazaImpact() > b->calculeazaImpact();
        });
    int afisate = std::min(n, static_cast<int>(sortate.size()));
    std::cout << "\n TOP " << afisate << " PIESE \n";
    for (int i = 0; i < afisate; i++)
        std::cout << (i+1) << ". " << *sortate[i]
                  << " | Impact: " << sortate[i]->calculeazaImpact() << "\n";
}

void Garderoba::eliminaPieseSub(double prag) {
    auto it = std::remove_if(piese.begin(), piese.end(),
        [&](const std::unique_ptr<PiesaVestimentara>& p) {
            return p->calculeazaImpact() < prag;
        });
    int nr = static_cast<int>(std::distance(it, piese.end()));
    piese.erase(it, piese.end());
    std::cout << "Eliminate " << nr << " piese cu impact sub " << prag << ".\n";
}

void Garderoba::afiseazaHaineImpermeabile() const {
    std::cout << "\n HAINE IMPERMEABILE \n";
    bool gasit = false;
    for (const auto& p : piese) {
        const Haina* h = dynamic_cast<const Haina*>(p.get());
        if (h && h->eImpermeabila()) {
            std::cout << *h << "\n";
            gasit = true;
        }
    }
    if (!gasit) std::cout << "Nicio haina impermeabila.\n";
}

void Garderoba::incarcaDinFisier(const std::string& numeFisier) {
    std::ifstream fin(numeFisier);
    if (!fin.is_open()) throw FisierException(numeFisier);

    std::string linie;
    while (std::getline(fin, linie)) {
        if (linie.empty() || linie[0] == '#') continue;
        auto split = [](const std::string& s, char d) {
            std::vector<std::string> tok;
            std::string t;
            for (char c : s) { if (c == d) { tok.push_back(t); t.clear(); } else t += c; }
            tok.push_back(t);
            return tok;
        };
        auto tok = split(linie, '|');
        if (tok.size() < 7) continue;
        try {

            auto piesa = PiesaFactory::creeaza(
                tok[0], tok[1], tok[2],
                std::stod(tok[3]), std::stoi(tok[4]),
                tok[5], tok[6]
            );
            adaugaPiesa(piesa.release());
        } catch (const TrendsetterException& e) {
            std::cerr << "[FISIER] " << e.what() << "\n";
        }
    }
}

void Garderoba::salveazaInFisier(const std::string& numeFisier) const {
    std::ofstream fout(numeFisier);
    if (!fout.is_open()) throw FisierException(numeFisier);
    fout << "# TrendSetter - garderoba " << numeInfluencer << "\n";
    for (const auto& p : piese) {
        fout << p->getTip() << "|" << p->getDenumire() << "|"
             << p->getBrand() << "|" << p->getPret() << "|"
             << p->getPunctajStil() << "|";
        if (const Haina* h = dynamic_cast<const Haina*>(p.get()))
            fout << h->getMaterial() << "|" << (h->eImpermeabila() ? "1" : "0");
        else if (const Incaltaminte* i = dynamic_cast<const Incaltaminte*>(p.get()))
            fout << i->getMarime() << "|" << i->getConfort();
        else if (const Accesoriu* a = dynamic_cast<const Accesoriu*>(p.get()))
            fout << a->getTipAccesoriu() << "|" << (a->eDeLux() ? "1" : "0");
        else if (const Bijuterie* b = dynamic_cast<const Bijuterie*>(p.get()))
            fout << b->getMetal() << "|" << b->getCantitate();
        fout << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Garderoba& g) {
    os << "\n \n"
       << "  INFLUENCER: " << g.numeInfluencer << "\n"
       << "  BUGET RAMAS: " << std::fixed << std::setprecision(2) << g.buget << " RON\n"
       << "  PIESE: " << g.piese.size() << "\n"
       << "  STRATEGIE SCOR: " << g.scoreStrategy->nume() << "\n"
       << "  TOTAL PIESE CREATE (static): " << PiesaVestimentara::getNrPiese() << "\n"
       << "\n";
    for (const auto& p : g.piese)
        os << "  " << *p << "\n";
    return os;
}
