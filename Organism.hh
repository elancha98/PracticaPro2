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
     * Default Constructor
     */
    Organism() : male(true), father("$"), mother("$"), ADN(0) {};
    /**
     * Constructor given sex and ADN
     * @param m if true the new Organism will be male, otherwise the new Organism will be female
     * @param v the ADN of the new Organism
     */
    Organism(bool m, vector<pair<Chromosome, Chromosome> > v) : male(m), father("$"), mother("$"), ADN(v) {};
    /**
     * Default destructor
     */
    ~Organism() {};

    /**
     * @return whether this Organism is male or not
     */
    inline bool is_male() const { return male; };
    /**
     * @return the name of the father of this Organism
     */
    inline string get_father() const { return father; };
    /**
     * @return the name of the mother of this Organism
     */
    inline string get_mother() const { return mother; };

    /**
     * Writes the sex and the parents of this Organism to the console
     */
    void write() const;
    /**
     * Writes the genotype of this Organism to the console
     */
    void write_genotype() const;

    /**
     * Assumes that \b o1 and \b o2 can reproduce
     * @return an Organism result of the reproduction of \b o1 and \b o2
     * @param o1 the mother of the new Organism
     * @param o2 the father of the new Organism
     * @param o1_ name of \b o1
     * @param o2_ name of \b o2
     * @param l a vector that contains, in the ith position, the size of the ith Chromosome.
     *     except \b l[0] which contains the second cross point of the sexual Chromosome
     */
    static Organism reproduce(const Organism& o1, const Organism& o2, string o1_,
                              string o2_, const vector<int>& l);
private:
    bool male; /**< Keeps track of the sex of this Oorganism */
    string father; /**< Name of the father */
    string mother; /**< Name of the mother */
    vector<pair<Chromosome, Chromosome> > ADN; /**< The ADN of this Organism */
};

#endif /* ORGANISM_HH_ */
