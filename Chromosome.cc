//
// Created by ernesto on 23/04/17.
//

#include "Chromosome.hh"

void Chromosome::write() const {
    for (int i = 0; i < genes.size(); i++)
        cout << " " << genes[i];
    cout << endl;
}

Chromosome Chromosome::read(int n_genes) {
    Chromosome c(n_genes);
    gene g;
    for (int i = 0; i < n_genes; i++) {
        cin >> g;
        c.genes[i] = g;
    }
    return c;
}

pair<Chromosome, Chromosome> Chromosome::crossover(const Chromosome& c1, const Chromosome& c2,
                                                   int cross_point, int size) {
    Chromosome c1_(c1.genes.size()), c2_(c2.genes.size());

    for (int i = 0; i < cross_point; i++) {
        c1_.genes[i] = c1.genes[i];
        c2_.genes[i] = c2.genes[i];
    }
    for (int i = cross_point; i < size; i++) {
        c1_.genes[i] = c2.genes[i];
        c2_.genes[i] = c1.genes[i];
    }
    for (int i = size; i < c1.genes.size(); i++)
        c1_.genes[i] = c1.genes[i];
    for (int i = size; i < c2.genes.size(); i++)
        c2_.genes[i] = c2.genes[i];
    return make_pair(c1_, c2_);
}