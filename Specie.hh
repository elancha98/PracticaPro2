//
// Created by ernesto on 23/04/17.
//

#ifndef SPECIE_HH_
#define SPECIE_HH_

#include "Organism.hh"
#include "Exceptions.hh"
#include <iostream>
#include <vector>
#include <list>
#include <queue>
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
     * \post If it can, it adds the Organism \e o to the population with name \e name and returns true,
     *     If there's already an Organism with name \e name, it just returns false
     */
    bool add_organism(string name, const Organism& o) {
            Individual r;
            r.father = population.end();
            r.mother = population.end();
            r.org = o;
            return add_organism(name, r);
    };
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

    pair<string, bool> check_genealogical_tree(string root) const {
        bool b = true;
        map<string, Individual>::const_iterator it = population.find(root);
        if (it == population.end())
            b = false;
        return make_pair(root + check_genealogical_tree(it, b), b);
    };
    /**
     * @brief Reads a Specie from the console
     * \pre there is Specie information and a initial population in the console ready to be read
     * \post Reads a Specie and it's initial population from the console and then returns it
     */
    static Specie read();
private:
    int N; /**< The  number of non sexual Chromosome of the organisms of the specie */
    int lx; /**< The number of genes of the X Chromosome of the specie */
    int ly; /**< The number of genes of the Y Chromosome of the specie */
    vector<int> l; /**< The number of genes of the non-sexual Chromosome of this Specie */

    struct Individual {
        map<string, Individual>::const_iterator father;
        map<string, Individual>::const_iterator mother;
        Organism org;
    };
    map<string, Individual> population; /**< The population of this Specie */

    /**
     * \pre true
     * \post returns whether \e o1 and \e o2 can reproduce, that is, they are not brothers and
     *     one is not the other's predecessor
     */
    bool can_reproduce(map<string, Individual>::const_iterator it1, map<string, Individual>::const_iterator it2);

    bool add_organism(string name, const Individual& ind);

    /**
     * @brief Reads and checks genealogical tree of Organism \e root
     * \pre there's a genealogical tree in the console ready to be read
     * \post Reads and checks a genealogical tree from the console.
     *     if \e success is true then assumes that the root of the tree is correct and checks it's parents recursively.
     *     Otherwise it reads the tree.
     *     Then returns the tree that was read completed (if possible, non-sense string otherwise)
     */
    string check_genealogical_tree(map<string, Individual>::const_iterator root, bool& success) const;
    string get_genealogical_tree(map<string, Individual>::const_iterator root) const;
};

#endif /* SPECIE_HH_ */
