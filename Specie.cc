//
// Created by ernesto on 23/04/17.
//

#include "Specie.hh"

void Specie::write() const {
    for (map<string, Individual>::const_iterator it = population.begin(); it != population.end(); it++) {
        cout << "  " << it->first << " X";
        if (it->second.org.is_male())
            cout << "Y";
        else
            cout << "X";
        cout << " (";
        if (it->second.father != population.end())
            cout << it->second.father->first;
        else
            cout << "$";
        cout << ",";
        if (it->second.mother != population.end())
            cout << it->second.mother->first;
        else
            cout << "$";
        cout << ")" << endl;
    }
}

Organism Specie::get(string name) const {
    map<string, Individual>::const_iterator it = population.find(name);
    if (it == population.end())
        throw invalid_argument(name + " does not exist");
    return it->second.org;
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
        throw invalid_argument("Sexual cromosome can't be " + c);

    v[0] = make_pair(c1, c2);
    for (int i = 1; i <= N; i++) {
        c1 = Chromosome::read(l[i]);
        c2 = Chromosome::read(l[i]);
        v[i] = make_pair(c1, c2);
    }
    return Organism(male, v);
}

bool Specie::add_organism(string name, const Individual& ind) {
    pair<map<string, Individual>::iterator, bool> res = population.insert(make_pair(name, ind));
    return res.second;
}

bool Specie::reproduce(string o1, string o2, string name) {
    map<string, Individual>::const_iterator it1, it2;

    it1 = population.find(o1);
    if (it1 == population.end()) {
        for (int j, i = 0; i < (N+1)*3; i++)
            cin >> j;
        throw invalid_argument(o1 + " not found");
    }

    it2 = population.find(o2);
    if (it2 == population.end()) {
        for (int j, i = 0; i < (N+1)*3; i++)
            cin >> j;
        throw invalid_argument(o2 + " not found");
    }
    Individual ind;
    ind.father = it2;
    ind.mother = it1;
    ind.org = Organism::reproduce(it1->second.org, it2->second.org, l);

    if (population.find(name) != population.end()) {
        throw invalid_argument(name + " found in the population");
    }
    if (it1->second.org.is_male() or (not it2->second.org.is_male()))
        return false;
    if (it1->second.father != population.end() and (it1->second.father == it2->second.father or it1->second.mother == it2->second.mother))
        return false;
    if (are_family(it1, it2))
        return false;

    add_organism(name, ind);
    return true;
}

void Specie::write_genealogical_tree(string root) const {
    queue<map<string, Individual>::const_iterator> to_check;
    map<string, Individual>::const_iterator it = population.find(root);
    if (it == population.end())
        throw invalid_argument(root + " does not exist");
    to_check.push(it);
    int count = 0, added = 0, adding = 1, level = 0;
    while (!to_check.empty()) {
        if (count == added) {
            count = 0;
            added = adding;
            adding = 0;
            cout << endl << "  Nivel " << level++ << ":";
        } else {
            if (to_check.front()->second.father != population.end()) {
                to_check.push(to_check.front()->second.father);
                to_check.push(to_check.front()->second.mother);
                adding += 2;
            }
            cout << " " << to_check.front()->first;
            to_check.pop();
            count++;
        }
    }
    cout << endl;
}

bool Specie::check_genealogical_tree(map<string, Individual>::const_iterator root, queue<string>& res) const {
    string o;
    bool success = true;
    cin >> o;
    if (o == "$") {
        if (root->second.father != population.end()) {
            add_genealogical_tree(root->second.father, res);
        } else {
            res.push(" $");
        }
    } else {
        if (root->second.father != population.end() and root->second.father->first == o) {
            res.push(" ");
            res.push(o);
            success &= check_genealogical_tree(root->second.father, res);
        } else {
            success = false;
            read_useless_tree();
            read_useless_tree();
        }
    }
    cin >> o;
    if (o == "$"){
        if (root->second.mother != population.end()) {
            add_genealogical_tree(root->second.mother, res);
        } else {
            res.push(" $");
        }
    } else {
        if (root->second.mother != population.end() and root->second.mother->first == o) {
            res.push(" ");
            res.push(o);
            success &= check_genealogical_tree(root->second.mother, res);
        } else {
            success = false;
            read_useless_tree();
            read_useless_tree();
            return false;
        }
    }
    return success;
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

bool Specie::are_family(map<string, Individual>::const_iterator it1, map<string, Individual>::const_iterator it2) {
    queue<map<string, Individual>::const_iterator> to_check;
    to_check.push(it1);
    to_check.push(it2);
    if (it1 == it2)
        return true;
    while (!to_check.empty()) {
        if (to_check.front()->second.father == it1 or to_check.front()->second.father == it2 or
            to_check.front()->second.mother == it1 or to_check.front()->second.mother == it2)
            return true;
        if (to_check.front()->second.father != population.end()) {
            to_check.push(to_check.front()->second.father);
            to_check.push(to_check.front()->second.mother);
        }
        to_check.pop();
    }
    return false;
}

void Specie::add_genealogical_tree(map<string, Individual>::const_iterator root, queue<string>& res) const {
    res.push(" *");
    res.push(root->first);
    res.push("*");
    if (root->second.father != population.end()) {
        add_genealogical_tree(root->second.father, res);
        add_genealogical_tree(root->second.mother, res);
    } else {
        res.push(" $ $");
    }
}

void Specie::read_useless_tree() {
    string r;
    cin >> r;
    if (r != "$") {
        read_useless_tree();
        read_useless_tree();
    }
}