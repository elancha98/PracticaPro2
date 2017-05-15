import random
from random import randint
import string
import os

cases = input("Casos de prueba: ")
filename = raw_input("Nombre de la salida: ")
gen = 0

while (gen < cases):
    N = randint(1,10)
    l = []
    l0 = randint(1,10)
    for i in range(N):
        l.append(randint(1,10))
    lx = randint(l0,10)
    ly = randint(l0,10)

    individuals = string.lowercase
    sex = {"X" : lx,"Y" : ly}

    def anadir_individuo():
        res = "anadir_individuo " + random.choice(individuals)
        sexe = random.choice(sex.keys())
        res += "\n" + sexe + "\n"
        for i in range(lx):
            res += str(randint(0,1)) + " "
        res += "\n"
        for i in range(sex[sexe]):
            res += str(randint(0,1)) + " "
        res += "\n"
        for i in range(N):
            for j in range(l[i]):
                res += str(randint(0,1)) + " "
            res += "\n"
            for j in range(l[i]):
                res += str(randint(0,1)) + " "
            res += "\n"
        return res + "\n"

    def reproduccion_sexual():
        res = "reproduccion_sexual\n" + random.choice(individuals)
        res += " " + random.choice(individuals) + " " + random.choice(individuals) + "\n"
        res += str(randint(0,1)) + " " + str(randint(0,1)) + " " + str(randint(1,l0)) + "\n"
        for i in range(N):
            res += str(randint(0,1)) + " " + str(randint(0,1)) + " " + str(randint(1,l[i])) + "\n"
        return res + "\n"
        
    def escribir_arbol_genealogico():
        res = "escribir_arbol_genealogico\n" + random.choice(individuals)
        return res + "\n"

    def escribir_poblacion():
        return "escribir_poblacion\n"

    def escribir_genotipo():
        res = "escribir_genotipo\n" + random.choice(individuals)
        return res + "\n"

    cmds = [anadir_individuo, reproduccion_sexual, escribir_arbol_genealogico, escribir_poblacion, escribir_genotipo]
    
    end = False
    f = open(filename + "-" + str(gen) + ".in", "w")
    
    f.write(str(N) + "\n" + str(l0) + " ")
    for i in range(N):
        f.write(str(l[i]) + " ")
    f.write("\n" + str(lx) + " " + str(ly) + "\n0\n")

    while (not end):
        end = random.random() < 0.10
        if (not end):
            f.write(random.choice(cmds)() + "\n")
        else:
            f.write("acabar")
            f.close()
    f = open(filename + "-" + str(gen) + ".out", "w")
    f.write(os.popen("./program.exe < " + filename + "-" + str(gen) + ".in").read())
    f.close()
    gen += 1
    if (gen % 10 == 0):
        print gen
print "=====ENDED====="
