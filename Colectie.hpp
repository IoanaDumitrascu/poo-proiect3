#ifndef COLECTIE_HPP
#define COLECTIE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Colectie {
private:
    std::vector<T> elemente;

public:
    Colectie() = default;


    void adauga(T elem) {
        elemente.push_back(std::move(elem));
    }


    template <typename Predicat>
    int elimina(Predicat p) {
        auto it = std::remove_if(elemente.begin(), elemente.end(), p);
        int nr = static_cast<int>(std::distance(it, elemente.end()));
        elemente.erase(it, elemente.end());
        return nr;
    }


    template <typename Comparator>
    void sorteaza(Comparator cmp) {
        std::sort(elemente.begin(), elemente.end(), cmp);
    }


    template <typename Predicat>
    Colectie<T> filtreaza(Predicat p) const {
        Colectie<T> rezultat;
        for (const auto& e : elemente)
            if (p(e)) rezultat.adauga(e);
        return rezultat;
    }


    T& operator[](int idx) {
        if (idx < 0 || idx >= static_cast<int>(elemente.size()))
            throw std::out_of_range("Index invalid in Colectie");
        return elemente[idx];
    }

    const T& operator[](int idx) const {
        if (idx < 0 || idx >= static_cast<int>(elemente.size()))
            throw std::out_of_range("Index invalid in Colectie");
        return elemente[idx];
    }

    int dimensiune() const { return static_cast<int>(elemente.size()); }
    bool goala() const     { return elemente.empty(); }


    typename std::vector<T>::iterator begin()             { return elemente.begin(); }
    typename std::vector<T>::iterator end()               { return elemente.end(); }
    typename std::vector<T>::const_iterator begin() const { return elemente.begin(); }
    typename std::vector<T>::const_iterator end()   const { return elemente.end(); }


    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Colectie<U>& c);
};


template <typename U>
std::ostream& operator<<(std::ostream& os, const Colectie<U>& c) {
    os << "Colectie [" << c.dimensiune() << " elemente]:\n";
    for (const auto& e : c)
        os << "  " << e << "\n";
    return os;
}

// Functie sablon libera: filtreaza orice vector dupa un predicat
// (functie template normala/libera - cerinta T3)
template <typename T, typename Predicat>
std::vector<T> filtrareVecotr(const std::vector<T>& sursa, Predicat p) {
    std::vector<T> rezultat;
    std::copy_if(sursa.begin(), sursa.end(), std::back_inserter(rezultat), p);
    return rezultat;
}

#endif
