//
// Created by ernesto on 23/04/17.
//

#ifndef CHROMOSOME_HH_
#define CHROMOSOME_HH_

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Chromosome {
public:

    /**
     * gene instead of bool
     */
    typedef bool gene;

    /**
     * Default constructor
     */
    Chromosome() : genes(0) {};
    /**
     * Constructor given the number of genes in the new Chromosome
     * @param n_genes number of genes of the new Chromosome
     */
    Chromosome(int n_genes) : genes(n_genes) {};
    /**
     * Default destructor
     */
    ~Chromosome() {};

    /**
     * Writes this Chromosome to the console
     */
    void write() const;

    /**
     * @return a Chromosome read from the console
     * @param n_genes number of genes of the returned Chromosome
     */
    static Chromosome read(int n_genes);
    /**
     * @return the result of the crossover of \b c1 and \b c2
     * @param c1 the first Chromosome of the crossover
     * @param c2 the second Chromosome of the crossover
     * @param cross_point indicates the first cross point in the crossover
     * @param size indicates the second cross point in the crossover
     */
    static pair<Chromosome, Chromosome> crossover(const Chromosome& c1, const Chromosome& c2,
                                                  int cross_point, int size);
private:
    /**
     * Stores the genes in this Chromosome
     */
    vector<gene> genes;
};

#endif /* CHROMOSOME_HH_ */