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
     * Default constructor
     */
    Specie() : N(0), lx(0), ly(0), l(0), population() {};
    /**
     * Default destructor
     */
    ~Specie() {};

    /**
     * Writes the population of this Specie to the console
     */
    void write() const;
    /**
     * @return a Organism read from the console (of this Specie)
     */
    Organism read_organism() const;
    /**
     * @return the Organism of name \b name in the population.
     * @throws exception::ElementNotFoundException if there's no Organism with name \b name
     * @param name the name of the Organism to be returned
     */
    Organism get(string name) const;
    /**
     * Adds a Organism to the population.
     * @throws exception::DuplicatedElementException if an Organism with name \b name already exist
     * @param name the name of the Organism to be added
     * @param o the Organism to be added
     */
    void add_organism(string name, Organism o);
    /**
     * Reproduces the Organism with name \b mother and the Organism with name \b father
     * and adds the result Organism in the population (if the reproduction can be performed)
     * @throws exception::ElementNotFoundException if there's no Organism with name \b mother or
     * there's no Organism with name \b father
     * @param mother the name of the mother
     * @param father the name of the father
     * @param name the name of the new Organism
     * @returns true if the reproduction succeeded, false otherwise
     */
    bool reproduce(string mother, string father, string name);
    /**
     * Writes genealogical tree of the Organism with name \b root
     * @throws exception::ElementNotFoundException if there's no Organism with name \b root
     * @param root the name of the Organism whose genealogical tree we want to know
     */
    void write_genealogical_tree(string root) const;
    /**
     * Reads and checks a genealogical tree from the console.
     * if success is true then assumes that the root of the tree is correct and checks it's parents recursively.
     * Otherwise it reads the tree
     * @return the tree that was read completed (if possible, no-sense \ref std::string otherwise)
     * @param root the root of the tree
     * @param success stores whether the tree read is a partial tree or not
     */
    string check_genealogical_tree(Organism root, bool& success) const;

    /**
     * Reads a Specie and it's initial population from the console
     * @return a Specie read from the console
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
     * @throws exceptions::ElementNotFoundException if there's no Organism with name \b o1 or
     *     there's no Organism with name \b o2
     * @return whether \b o1 and \b o2 are family, that is, they are brothers or one is the other's predecessor
     * @param o1 the first Organism to be checked
     * @param o2 the second Organism to be checked
     */
    bool are_family(string o1, string o2);
};

#endif /* SPECIE_HH_ */
