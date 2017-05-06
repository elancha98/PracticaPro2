//
// Created by ernesto on 23/04/17.
//

#include "Specie.hh"

void Specie::write() const {
    for (map<string, Relation>::const_iterator it = relations.begin(); it != relations.end(); it++) {
        cout << "  " << it->first << " X";
        if ((*it->second.org).is_male())
            cout << "Y";
        else
            cout << "X";
        cout << " (";
        if (it->second.father != relations.end())
            cout << it->second.father->first;
        else
            cout << "$";
        cout << ",";
        if (it->second.mother != relations.end())
            cout << it->second.mother->first;
        else
            cout << "$";
        cout << ")" << endl;
    }
}

Organism Specie::get(string name) const {
    map<string, Relation>::const_iterator it = relations.find(name);
    if (it == relations.end())
        throw exceptions::ElementNotFoundException(name + " does not exist");
    return *it->second.org;
}

Organism Specie::read_organism() const {
    bool male = true;
    vector<pair<Chromosome, Chromosome> > v(N+1);
    char c;
    cin >> c;
    Chromosome c1, c2;
    c1 = Chromosome::read(lx);
    if (c == 'X') {
        c2 = Chromosome::read(lx);
        male = false;
    } else if (c == 'Y')
        c2 = Chromosome::read(ly);
    else
        throw exceptions::IllegalArgumentException("Sexual cromosome can't be " + c);

    v[0] = make_pair(c1, c2);
    for (int i = 1; i <= N; i++) {
        c1 = Chromosome::read(l[i]);
        c2 = Chromosome::read(l[i]);
        v[i] = make_pair(c1, c2);
    }
    return Organism(male, v);
}

bool Specie::add_organism(string name, const Organism& o, const Relation& r) {
    pair<map<string, Relation>::iterator, bool> res = relations.insert(make_pair(name, r));
    if (not res.second)
        return false;
    res.first->second.org = population.insert(population.end(), o);
    return true;
}

bool Specie::reproduce(string o1, string o2, string name) {
    map<string, Relation>::const_iterator it1, it2;

    it1 = relations.find(o1);
    if (it1 == relations.end()) {
        for (int j, i = 0; i < (N+1)*3; i++)
            cin >> j;
        throw exceptions::ElementNotFoundException(o1 + " not found");
    }

    it2 = relations.find(o2);
    if (it2 == relations.end()) {
        for (int j, i = 0; i < (N+1)*3; i++)
            cin >> j;
        throw exceptions::ElementNotFoundException(o2 + " not found");
    }

    Organism result = Organism::reproduce(*it1->second.org, *it2->second.org, l);

    if ((*it1->second.org).is_male() or (not (*it2->second.org).is_male()))
        return false;
    if (!can_reproduce(it1, it2))
        return false;
    Relation r;
    r.father = it2;
    r.mother = it1;
    add_organism(name, result, r);
    return true;
}

void Specie::write_genealogical_tree(string root) const {
    queue<map<string, Relation>::const_iterator> to_check;
    map<string, Relation>::const_iterator it = relations.find(root);
    if (it == relations.end())
        throw exceptions::ElementNotFoundException(root + " does not exist");
    to_check.push(it);
    int count = 0, added = 0, adding = 1, level = 0;
    while (!to_check.empty()) {
        if (count == added) {
            count = 0;
            added = adding;
            adding = 0;
            cout << endl << "  Nivel " << level++ << ":";
        } else {
            Relation r = to_check.front()->second;
            if (r.father != relations.end()) {
                to_check.push(r.father);
                adding++;
            }
            if (r.mother != relations.end()) {
                to_check.push(r.mother);
                adding++;
            }
            cout << " " << to_check.front()->first;
            to_check.pop();
            count++;
        }
    }
    cout << endl;
}

string Specie::check_genealogical_tree(map<string, Relation>::const_iterator root, bool& success) const {
    string mother, father, res = "";
    cin >> father;
    if (father == "$") {
        if (success and root->second.father != relations.end())
            res += " *" + root->second.father->first + "* $ $";
        else
            res += " $";
    } else {
        if (success and root->second.father != relations.end() and root->second.father->first == father) {
            res += " " + father;
            res += check_genealogical_tree(root->second.father, success);
        } else {
            success = false;
            check_genealogical_tree(relations.end(), success);
        }
    }
    cin >> mother;
    if (mother == "$"){
        if (success and root->second.mother != relations.end())
            res += " *" + root->second.mother->first + "* $ $";
        else
            res += " $";
    } else {
        if (success and root->second.mother != relations.end() and root->second.mother->first == mother) {
            res += " " + mother;
            res += check_genealogical_tree(root->second.mother, success);
        } else {
            success = false;
            check_genealogical_tree(relations.end(), success);
        }
    }
    return res;
}

Specie Specie::read() {
    Specie s;
    cin >> s.N;
    s.l = vector<int>(s.N+1);
    for (int i = 0; i <= s.N; i++)
        cin >> s.l[i];
    cin >> s.lx >> s.ly;
    int m;
    string name;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> name;
        s.add_organism(name, s.read_organism());
    }
    return s;
}

bool Specie::can_reproduce(map<string, Relation>::const_iterator it1, map<string, Relation>::const_iterator it2) {
    queue<map<string, Relation>::const_iterator> to_check;
    to_check.push(it1);
    to_check.push(it2);
    if (it1 == it2)
        return false;
    while (!to_check.empty()) {
        if (to_check.front()->second.father != relations.end()) {
            if (to_check.front()->second.father == it1 or to_check.front()->second.father == it2)
                return false;
            else
                to_check.push(to_check.front()->second.father);
        }
        if (to_check.front()->second.mother != relations.end()) {
            if (to_check.front()->second.mother == it1 or to_check.front()->second.mother == it2)
                return false;
            else
                to_check.push(to_check.front()->second.mother);
        }
        to_check.pop();
    }
    return true;
}
