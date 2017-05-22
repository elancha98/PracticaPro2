//
// Created by ernesto on 23/04/17.
//

#ifndef SPECIE_HH_
#define SPECIE_HH_

#include "Organism.hh"
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
     * @throws invalid_argument if there's no Organism with name \e name
     */
    Organism get(string name) const;
    /**
     * @brief Add Organism with name \e name
     * \pre true
     * \post If it can, it adds the Organism \e o to the population with name \e name (and no parents)
     *     and returns true, If there's already an Individual with name \e name, it just returns false
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
     * @throws invalid_argument if there's no Organism with name \e mother or
     *     there's no Organism with name \e father
     */
    bool reproduce(string mother, string father, string name);
    /**
     * @brief Write genealogical tree of Organism \e name
     * \pre true
     * \post Writes genealogical tree of the Organism with name \e root
     * @throws invalid_argument if there's no Organism with name \e root
     */
    void write_genealogical_tree(string root) const;
    /**
     * @brief Read and check the genealogical tree of \e root
     * \pre there is a tree ready to be read in the console
     * \post returns a string queue where the completed tree is stored (the completed tree is
     *     obtained by joining all the string together) and a boolean
     *     that is true if the read tree is actually a parcial tree and false otherwise
     */
    pair<queue<string>, bool> check_genealogical_tree(string root) const {
        queue<string> a;
        a.push(root);
        map<string, Individual>::const_iterator it = population.find(root);
        if (it == population.end()) {
            read_useless_tree();
            read_useless_tree();
            return make_pair(a, false);
        }
        bool b = check_genealogical_tree(it, a);
        return make_pair(a, b);
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

    /**
     * @brief Individual, social part of the population, stores an Organism and a
     *     reference to it's parents
     */
    struct Individual {
        map<string, Individual>::const_iterator father;
        map<string, Individual>::const_iterator mother;
        Organism org;
    };
    map<string, Individual> population; /**< The population of this Specie */

    /**
     * \pre \e it1 and \e it2 point to an element in population
     * \post returns whether \e it1 and \e it2 can reproduce, that is, they are not brothers and
     *     one is not the other's predecessor
     */
    bool are_family(map<string, Individual>::const_iterator it1, map<string, Individual>::const_iterator it2);

    /**
     * \pre true
     * \post If it cans, it adds the Individual \e o to the population with name \e name and
     *     returns true, If there's already an Individual with name \e name, it just returns false
     */
    bool add_organism(string name, const Individual& ind);

    /**
     * \pre \e root points to an element in population and there's a genealogical_tree ready to be
     *     read in the console
     * \post Reads a genealogical tree with root \e root. Returns true if the read tree was a
     *     partial tree, in that case the completed read tree is added to \e res. If the read tree
     *     was not a partial tree returns false (but adds things to \e res)
     */
    bool check_genealogical_tree(map<string, Individual>::const_iterator root, queue<string>& res) const;
    /**
     * \pre \e root points to an element in population
     * \post Adds the complete genealogical tree of \e root to \e res
     */
    void add_genealogical_tree(map<string, Individual>::const_iterator root, queue<string>& res) const;
    /**
     * \pre there's a genealogical tree ready to be read in the console
     * \post reads the tree (leaving the cin cursor at the end of the tree)
     */
    static void read_useless_tree();
};

#endif /* SPECIE_HH_ */
