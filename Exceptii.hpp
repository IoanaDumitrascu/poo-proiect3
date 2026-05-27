#ifndef EXCEPTII_HPP
#define EXCEPTII_HPP

#include <exception>
#include <string>

class TrendsetterException : public std::exception {
protected:
    std::string mesaj;
public:
    TrendsetterException(const std::string& msg) : mesaj(msg) {}
    virtual ~TrendsetterException() throw() {}
    virtual const char* what() const throw() { return mesaj.c_str(); }
};

class BugetInsuficientException : public TrendsetterException {
public:
    BugetInsuficientException(const std::string& numePiesa, double pret, double buget)
        : TrendsetterException("Fonduri insuficiente pentru '" + numePiesa +
                               "'. Pret: " + std::to_string(pret) +
                               " RON, Buget: " + std::to_string(buget) + " RON.") {}
};

class PiesaInvalidaException : public TrendsetterException {
public:
    PiesaInvalidaException(const std::string& detaliu) : TrendsetterException(detaliu) {}
};

class EvenimentInexistentException : public TrendsetterException {
public:
    EvenimentInexistentException(const std::string& nume)
        : TrendsetterException("Evenimentul '" + nume + "' nu este recunoscut!") {}
};

class FisierException : public TrendsetterException {
public:
    FisierException(const std::string& nume)
        : TrendsetterException("Eroare la deschiderea fisierului: " + nume) {}
};

#endif
