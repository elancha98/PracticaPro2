//
// Created by ernesto on 23/04/17.
//

/**
 * @mainpage Main program. Reads commands from the console and executes them
 * @brief Reads commands from the console and executes them
 */

#include <iostream>
#include "Specie.hh"
#include "Exceptions.hh"

using namespace std;

int main() {
    // SETUP
    Specie specie = Specie::read();
    string name, n1, n2, n3;
    // MAIN LOOP
    while (cin >> name and name != "acabar") {
        if (name == "anadir_individuo") {
            cin >> n1;
            cout << name << " " << n1 << endl;
            try {
                specie.add_organism(n1, specie.read_organism());
            } catch (exceptions::DuplicatedElementException& e) {cout << "error" << endl;}
        } else if (name == "reproduccion_sexual") {
            cin >> n1 >> n2 >> n3;
            cout << name << " " << n1 << " " << n2 << " " << n3 << endl;
            try {
                if (not specie.reproduce(n1, n2, n3))
                    cout << "no es posible reproduccion" << endl;
            } catch (exceptions::ElementNotFoundException& e) {
                cout << "error" << endl;
            } catch (exceptions::DuplicatedElementException& e) { cout << "error" << endl;
            }
        } else if (name == "escribir_arbol_genealogico") {
            cin >> n1;
            cout << name << " " << n1 << endl;
            try {
                specie.write_genealogical_tree(n1);
            } catch (exceptions::ElementNotFoundException& e) { cout << "error" << endl; }
        } else if (name == "completar_arbol_genealogico") {
            cin >> n1;
            cout << name << " " << n1 << endl;
            bool success = true;
            try {
                n2 = "";
                Organism o = specie.get(n1);
                string res = specie.check_genealogical_tree(o, success);
                if (success)
                    cout << n1 << res << endl;
                else
                    cout << "no es arbol parcial" << endl;
            } catch (exceptions::ElementNotFoundException& e) {
                success = false;
                specie.check_genealogical_tree(Specie::empty, success);
                cout << "no es arbol parcial" << endl;
            }
        } else if (name == "escribir_poblacion") {
            cout << name << endl;
            specie.write();
        } else if (name == "escribir_genotipo") {
            cin >> n1;
            cout << name << " " << n1 << endl;
            try {
                specie.get(n1).write_genotype();
            } catch (exceptions::ElementNotFoundException& e) { cout << "error" << endl; }
        } else {
            throw exceptions::IllegalArgumentException("Invalid command");
        }
    }
    cout << name << endl;
}
