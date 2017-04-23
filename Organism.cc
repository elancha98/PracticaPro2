//
// Created by ernesto on 23/04/17.
//

#include "Organism.hh"

void Organism::write() const {
    cout << 'X';
    if (male) cout << 'Y';
    else cout << 'X';
    cout << " (" << father << "," << mother << ")" << endl;
}

void Organism::write_genotype() const {
    cout << "X:";
    ADN[0].first.write();
    if (male) cout << "Y:";
    else cout << "X:";
    ADN[0].second.write();
    for (int i = 1; i < ADN.size(); i++) {
        cout << i << ".1:";
        ADN[i].first.write();
        cout << i << ".2:";
        ADN[i].second.write();
    }
}

Organism Organism::reproduce(const Organism& o1, const Organism& o2, string o1_,
                             string o2_, const vector<int>& l) {
    Organism o;
    o.mother = o1_;
    o.father = o2_;

    Chromosome c1, c2;
    bool a1, a2;
    int cross_point;

    for (unsigned i = 0; i < o1.ADN.size(); i++) {
        cin >> a1 >> a2 >> cross_point;
        if (i == 0 and a2 == 0) o.male = false;
        if (a1) c1 = o1.ADN[i].second;
        else c1 = o1.ADN[i].first;
        if (a2) c2 = o2.ADN[i].second;
        else c2 = o2.ADN[i].first;

        o.ADN.push_back(Chromosome::crossover(c1, c2, cross_point, l[i]));
    }
    return o;
}