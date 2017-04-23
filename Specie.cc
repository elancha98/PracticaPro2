//
// Created by ernesto on 23/04/17.
//

#include "Specie.hh"

typedef map<string, Organism>::const_iterator iter;
Organism Specie::empty;

void Specie::write() const {
    for (iter it = population.begin(); it != population.end(); it++) {
        cout << it->first << " ";
        it->second.write();
    }
}

Organism Specie::get(string name) const {
    iter it = population.find(name);
    if (it == population.end())
        throw exceptions::ElementNotFoundException(name + " does not exist");
    return it->second;
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

void Specie::add_organism(string name, Organism o) {
    pair<map<string, Organism>::iterator, bool> res = population.insert(pair<string, Organism>(name, o));
    if (not res.second)
        throw exceptions::DuplicatedElementException(name + " already exists");
}

bool Specie::reproduce(string o1, string o2, string name) {
    map<string, Organism>::iterator it;

    it = population.find(o1);
    if (it == population.end()) {
        for (int j, i = 0; i < (N+1)*3; i++)
            cin >> j;
        throw exceptions::ElementNotFoundException("Organism " + o1 + " doesn't exist");
    }
    Organism org1 = it->second;

    it = population.find(o2);
    if (it == population.end()) {
        for (int j, i = 0; i < (N+1)*3; i++)
            cin >> j;
        throw exceptions::ElementNotFoundException("Organism " + o2 + " doesn't exist");
    }
    Organism org2 = it->second;

    Organism result = Organism::reproduce(org1, org2, o1, o2, l);

    if (org1.is_male() or (not org2.is_male()))
        return false;
    if (are_family(o1, o2))
        return false;

    add_organism(name, result);
    return true;
}

void Specie::write_genealogical_tree(string root) const {
    queue<string> to_check;
    to_check.push(root);
    int count = 0, added = 1, adding = 0, level = 0;
    string lvl = "";
    while (!to_check.empty()) {
        if (count == added) {
            count = 0;
            added = adding;
            adding = 0;
            cout << "Nivel " << level++ << ":" << lvl << endl;
            lvl = "";
        } else {
            Organism o = get(to_check.front());
            if (o.get_father() != "$") {
                to_check.push(o.get_father());
                adding++;
            }
            if (o.get_mother() != "$") {
                to_check.push(o.get_mother());
                adding++;
            }
            lvl += " " + to_check.front();
            to_check.pop();
            count++;
        }
    }
    cout << "Nivel " << level << ":" << lvl << endl;
}

string Specie::check_genealogical_tree(Organism root, bool& success) const {
    string mother, father, res = "";
    cin >> father;
    if (father == "$") {
        if (root.get_father() != "$")
            res += " *" + root.get_father() + "* $ $";
        else
            res += " $";
    } else {
        if (success and father == root.get_father()) {
            res += " " + father;
            res += check_genealogical_tree(get(root.get_father()), success);
        } else {
            success = false;
            check_genealogical_tree(empty, success);
        }
    }
    cin >> mother;
    if (mother == "$"){
        if (root.get_mother() != "$")
            res += " *" + root.get_mother() + "* $ $";
        else
            res += " $";
    } else {
        if (success and mother == root.get_mother()) {
            res += " " + mother;
            res += check_genealogical_tree(get(root.get_mother()), success);
        } else {
            success = false;
            check_genealogical_tree(empty, success);
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
    return s;
}

bool Specie::are_family(string o1, string o2) {
    queue<string> q1, q2;
    set<string> s1, s2;
    q1.push(o1);
    q2.push(o2);
    int added_1 = 1, added_2 = 1, adding = 0;
    bool b = true;
    while ( (not q1.empty()) or (not q2.empty()) ) {
        for (int i = 0; i < added_1; i++) {
            set<string>::const_iterator it = s2.find(q1.front());
            if (it != s2.end())
                return true;
            Organism org = get(q1.front());
            if (org.get_father() != "$") {
                q1.push(org.get_father());
                adding++;
            }
            if (org.get_mother() != "$") {
                q1.push(org.get_mother());
                adding++;
            }
            s1.insert(q1.front());
            q1.pop();
        }
        added_1 = adding;
        adding = 0;
        for (int i = 0; i < added_2; i++) {
            set<string>::const_iterator it = s1.find(q2.front());
            if (it != s1.end())
                return true;
            Organism org = get(q2.front());
            if (org.get_father() != "$") {
                q1.push(org.get_father());
                adding++;
            }
            if (org.get_mother() != "$") {
                q2.push(org.get_mother());
                adding++;
            }
            s2.insert(q2.front());
            q2.pop();
        }
        added_1 = adding;
        adding = 0;
    }
    return true;
}