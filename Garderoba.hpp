#ifndef GARDEROBA_HPP
#define GARDEROBA_HPP

#include "PiesaVestimentara.hpp"
#include "Eveniment.hpp"
#include "ScoreStrategy.hpp"
#include <vector>
#include <memory>
#include <string>

class Garderoba {
private:
    std::string numeInfluencer;
    double buget;

    std::vector<std::unique_ptr<PiesaVestimentara>> piese;

    std::unique_ptr<ScoreStrategy> scoreStrategy;


    std::vector<PiesaVestimentara*> getRawPiese() const;

public:
    Garderoba(const std::string& nume, double buget,
              std::unique_ptr<ScoreStrategy> strategy = nullptr);


    Garderoba(const Garderoba& sursa);
    Garderoba& operator=(Garderoba sursa);
    ~Garderoba() = default;

    friend void swap(Garderoba& a, Garderoba& b) noexcept;

    void adaugaPiesa(PiesaVestimentara* p);
    void setStrategy(std::unique_ptr<ScoreStrategy> s) { scoreStrategy = std::move(s); }

    void afiseazaScorEveniment(const Eveniment& ev) const;
    double calculeazaScorPentruEveniment(const Eveniment& ev) const;
    void afiseazaTopPiese(int n) const;
    void eliminaPieseSub(double prag);
    void afiseazaHaineImpermeabile() const;

    void incarcaDinFisier(const std::string& numeFisier);
    void salveazaInFisier(const std::string& numeFisier) const;

    double getBuget() const            { return buget; }
    const std::string& getNume() const { return numeInfluencer; }
    int getNrPiese() const             { return static_cast<int>(piese.size()); }

    friend std::ostream& operator<<(std::ostream& os, const Garderoba& g);
};

#endif
