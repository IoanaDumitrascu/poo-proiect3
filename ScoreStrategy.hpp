#ifndef SCORESTRATEGY_HPP
#define SCORESTRATEGY_HPP

#include "PiesaVestimentara.hpp"
#include "Eveniment.hpp"
#include <memory>
#include <vector>
#include <numeric>
#include <algorithm>

class ScoreStrategy {
public:
    virtual ~ScoreStrategy() = default;
    virtual double calculeaza(
        const std::vector<PiesaVestimentara*>& piese,
        const Eveniment& ev
    ) const = 0;
    virtual std::string nume() const = 0;
};

class ScoreSimple : public ScoreStrategy {
public:
    double calculeaza(
        const std::vector<PiesaVestimentara*>& piese,
        const Eveniment& ev
    ) const override {
        double total = 0;
        for (auto p : piese)
            total += p->calculeazaImpact() * ev.calculeazaMultiplicator(p->getTip());
        return total;
    }
    std::string nume() const override { return "Scor Simplu"; }
};

class ScoreMedie : public ScoreStrategy {
public:
    double calculeaza(
        const std::vector<PiesaVestimentara*>& piese,
        const Eveniment& ev
    ) const override {
        if (piese.empty()) return 0.0;
        double total = 0;
        for (auto p : piese)
            total += p->calculeazaImpact() * ev.calculeazaMultiplicator(p->getTip());
        return total / piese.size();
    }
    std::string nume() const override { return "Scor Medie"; }
};


class ScoreTop3 : public ScoreStrategy {
public:
    double calculeaza(
        const std::vector<PiesaVestimentara*>& piese,
        const Eveniment& ev
    ) const override {
        std::vector<double> scoruri;
        for (auto p : piese)
            scoruri.push_back(p->calculeazaImpact() * ev.calculeazaMultiplicator(p->getTip()));
        std::sort(scoruri.rbegin(), scoruri.rend());
        double total = 0;
        int limita = std::min(3, static_cast<int>(scoruri.size()));
        for (int i = 0; i < limita; i++) total += scoruri[i];
        return total;
    }
    std::string nume() const override { return "Scor Top-3"; }
};


class ScoreStrategyFactory {
public:
    static std::unique_ptr<ScoreStrategy> creeaza(const std::string& tip) {
        if (tip == "simplu") return std::make_unique<ScoreSimple>();
        if (tip == "medie")  return std::make_unique<ScoreMedie>();
        if (tip == "top3")   return std::make_unique<ScoreTop3>();
        return std::make_unique<ScoreSimple>(); // default
    }
};

#endif
