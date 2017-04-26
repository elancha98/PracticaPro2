//
// Created by ernesto on 23/04/17.
//

#ifndef ORGANISM_HH_
#define ORGANISM_HH_

#include <iostream>
#include <vector>
#include <utility>
#include "Chromosome.hh"

using namespace std;

class Organism {
public:
    /**
     * @brief Default constructor
     * \pre true
     * \post returns an empty male Organism
     */
    Organism() : male(true), father("$"), mother("$"), ADN(0) {};
    /**
     * @brief Constructor given sex and ADN
     * \pre true
     * \post returns an Organism that is male if \e m is true and it's ADN is \e v
     */
    Organism(bool m, const vector<pair<Chromosome, Chromosome> >& v) : male(m), father("$"), mother("$"), ADN(v) {};
    /**
     * @brief Default destructor
     * \pre true
     * \post destruct this Organism
     */
    ~Organism() {};

    /**
     * @brief \b male getter
     * \pre true
     * \post returns whether this Organism is male or not
     */
    inline bool is_male() const { return male; };
    /**
     * \brief \b father getter
     * \pre true
     * \post returns the name of the father of this Organism
     */
    inline string get_father() const { return father; };
    /**
     * @brief \b mother getter
     * \pre true
     * \post returns the name of the mother of this Organism
     */
    inline string get_mother() const { return mother; };

    /**
     * @brief Writes sex and parents to the console
     * \pre true
     * \post Writes the sex and the parents of this Organism to the console
     */
    void write() const;
    /**
     * \pre true
     * \post Writes the genotype of this Organism to the console
     */
    void write_genotype() const;

    /**
     * @brief reproduces two Organism
     * \pre \e o1 and \e o2 can reproduce
     * \post returns an Organism result of the reproduction of \e o1 and \e o2. Note: \e o1_ is the name of \e o1,
     *     |e o2_ is the name of \e o2 and \e l is a vector that contains l0..ln
     */
    static Organism reproduce(const Organism& o1, const Organism& o2, string o1_,
                              string o2_, const vector<int>& l);
private:
    bool male; /**< Keeps track of the sex of this Organism */
    string father; /**< Name of the father */
    string mother; /**< Name of the mother */
    vector<pair<Chromosome, Chromosome> > ADN; /**< The ADN of this Organism */
};

#endif /* ORGANISM_HH_ */
