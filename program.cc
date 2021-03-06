//
// Created by ernesto on 23/04/17.
//

/**
 * @mainpage Reads commands from the console and executes them.
 *     It reads a Specie, a initial population and then performs operations over
 *     that population. Operations like adding a new Organism, reproduce two members
 *     or print the genotype of an Organism.
 * @brief Reads commands from the console and executes them
 */

#include <iostream>
#include "Specie.hh"

using namespace std;

int main() {
    // SETUP |
    Specie specie = Specie::read();
    string name, n1, n2, n3;
    // MAIN LOOP
    while (cin >> name and name != "acabar") {
        if (name == "anadir_individuo") {
            cin >> n1;
            cout << name << " " << n1 << endl;
            Organism o = specie.read_organism();
            bool b = specie.add_organism(n1, o);
            if (b == false)
                cout << "  error" << endl;
        } else if (name == "reproduccion_sexual") {
            cin >> n1 >> n2 >> n3;
            cout << name << " " << n1 << " " << n2 << " " << n3 << endl;
            try {
                if (not specie.reproduce(n1, n2, n3))
                    cout << "  no es posible reproduccion" << endl;
            } catch (invalid_argument& e) {
                cout << "  error" << endl;
            }
        } else if (name == "escribir_arbol_genealogico") {
            cin >> n1;
            cout << name << " " << n1;
            try {
                specie.write_genealogical_tree(n1);
            } catch (invalid_argument& e) { cout << endl << "  error" << endl; }
        } else if (name == "completar_arbol_genealogico") {
            cin >> n1;
            cout << name << " " << n1 << endl;
            pair<queue<string>, bool> s = specie.check_genealogical_tree(n1);
            if (s.second) {
                cout << "  ";
                while (!s.first.empty()) {
                    cout << s.first.front();
                    s.first.pop();
                }
                cout << endl;
            } else
                cout << "  no es arbol parcial" << endl;
        } else if (name == "escribir_poblacion") {
            cout << name << endl;
            specie.write();
        } else if (name == "escribir_genotipo") {
            cin >> n1;
            cout << name << " " << n1 << endl;
            try {
                specie.get(n1).write_genotype();
            } catch (invalid_argument& e) { cout << "  error" << endl; }
        } else {
            throw invalid_argument("  Invalid command");
        }
    }
    cout << name << endl;
}
