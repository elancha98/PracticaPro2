//
// Created by ernesto on 23/04/17.
//

#ifndef SPECIE_HH_
#define SPECIE_HH_

#include "Organism.hh"
#include "Exceptions.hh"
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

class Specie {
public:
    /**
     * @brief Default constructor
     * \pre true
     * \post an empty Specie
     */
    Specie() : N(0), lx(0), ly(0), l(0), population() {};
    /**
     * @brief Default destructor
     * \pre true
     * \post destruct this Specie
     */
    ~Specie() {};

    /**
     * @brief writes the population of this Specie
     * \pre true
     * \post Writes the population of this Specie to the console
     */
    void write() const;
    /**
     * @brief Reads an Organism from the console
     * \pre there is an Organism ready to be read in the console
     * \post returns an Organism read from the console (of this Specie)
     */
    Organism read_organism() const;
    /**
     * @brief Get Organism with name \e name
     * \pre true
     * \post returns the Organism of name \e name in the population (if it exists)
     * @throws exception::ElementNotFoundException if there's no Organism with name \e name
     */
    Organism get(string name) const;
    /**
     * @brief Add Organism with name \e name
     * \pre true
     * \post Adds a Organism \e o to the population with name \e name.
     * @throws exception::DuplicatedElementException if an Organism with name \e name already exist
     */
    void add_organism(string name, Organism o);
    /**
     * @brief Reproduce two Organism
     * \pre true
     * \post Reproduces the Organism with name \e mother and the Organism with name \e father
     *     and adds the result Organism in the population with name \e name (if the reproduction can be performed).
     *     Returns true if the reproduction can be performed
     * @throws exception::ElementNotFoundException if there's no Organism with name \e mother or
     *     there's no Organism with name \e father
     */
    bool reproduce(string mother, string father, string name);
    /**
     * @brief Write genealogical tree of Organism \e name
     * \pre true
     * \post Writes genealogical tree of the Organism with name \e root
     * @throws exception::ElementNotFoundException if there's no Organism with name \e root
     */
    void write_genealogical_tree(string root) const;
    /**
     * @brief Reads and checks genealogical tree of Organism \e root
     * \pre there's a genealogical tree in the console ready to be read
     * \post Reads and checks a genealogical tree from the console.
     *     if \e success is true then assumes that the root of the tree is correct and checks it's parents recursively.
     *     Otherwise it reads the tree.
     *     Then returns the tree that was read completed (if possible, non-sense string otherwise)
     */
    string check_genealogical_tree(const Organism& root, bool& success) const;

    /**
     * @brief Reads a Specie from the console
     * \pre there is Specie information and a initial population in the console ready to be read
     * \post Reads a Specie and it's initial population from the console and then returns it
     */
    static Specie read();

    /**
     * An empty Organism used to call functions that need an Organism parameter,
     * but parameter doesn't matter anymore
     */
    static Organism empty;
private:
    int N; /**< The  number of non sexual Chromosome of the organisms of the specie */
    int lx; /**< The number of genes of the X Chromosome of the specie */
    int ly; /**< The number of genes of the Y Chromosome of the specie */
    vector<int> l; /**< The number of genes of the non-sexual Chromosome of this Specie */
    map<string, Organism> population; /**< The population of this Specie */

    /**
     * \pre true
     * \post returns whether \e o1 and \e o2 can reproduce, that is, they are not brothers and
     *     one is not the other's predecessor
     * @throws exceptions::ElementNotFoundException if there's no Organism with name \b o1 or
     *     there's no Organism with name \b o2
     */
    bool can_reproduce(string o1, string o2);
};

#endif /* SPECIE_HH_ */
