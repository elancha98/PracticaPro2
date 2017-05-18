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
     * @brief Default constructor
     * \pre true
     * \post returns an empty Chromosome
     */
    Chromosome() : genes(0) {};
    /**
     * @brief Constructor given number of genes
     * \pre \e n_genes > 0
     * \post returns an empty Chromosome with \e n_genes genes
     */
    Chromosome(int n_genes) : genes(n_genes) {};
    /**
     * @brief Default destructor
     * \pre true
     * \post destruct this Chromosome
     */
    ~Chromosome() {};

    /**
     * @brief Writes this Chromosome to the console
     * \pre true
     * \post Writes this Chromosome to the console
     */
    void write() const;

    /**
     * @brief reads a Chromosome from the console
     * \pre there is a Chromosome ready to be read in the console and \e n_genes > 0
     * \post returns a Chromosome with \e n_genes read from the console
     */
    static Chromosome read(int n_genes);
    /**
     * @brief Performs the crossover between two Chromosomes
     * \pre \e cross_point and \e size less than number of Chromosome of \e c1 and \e c2
     * \post the result of the crossover of \e c1 and \e c2, where \e cross_point indicates where the first
     *     cross point is and \e size indicates where the second cross point is
     */
    static pair<Chromosome, Chromosome> crossover(const Chromosome& c1, const Chromosome& c2,
                                                  int cross_point, int size);
private:
    vector<gene> genes; /**< Stores the genes in this Chromosome */
};

#endif /* CHROMOSOME_HH_ */
