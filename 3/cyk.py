class Gramatica:
    def __init__(self):
        self.reguli = {}

    def adauga_regula(self, variabila, productie):
        if variabila in self.reguli:
            self.reguli[variabila].append(productie)
        else:
            self.reguli[variabila] = [productie]

    def get_reguli(self, variabila):
        return self.reguli.get(variabila, [])


def CYK(grammar, cuvant):
    n = len(cuvant)
    neterm = list(grammar.reguli.keys())

    # Matricea de rezultate
    rezultate = [[[] for _ in range(n)] for _ in range(n)]

    # Inițializarea matricei
    for i in range(n):
        for variabila in neterm:
            if cuvant[i] in grammar.get_reguli(variabila):
                rezultate[i][i].append(variabila)

    # Calcularea matricei
    for l in range(1, n):
        for i in range(n - l):
            j = i + l
            for k in range(i, j):
                for variabila in neterm:
                    for productie in grammar.get_reguli(variabila):
                        if len(productie) == 2:
                            if productie[0] in rezultate[i][k] and productie[1] in rezultate[k + 1][j]:
                                rezultate[i][j].append(variabila)

    # Verificarea dacă cuvântul este acceptat
    return 'DA' if 'S' in rezultate[0][n - 1] else 'NU'


def main():
    grammar = Gramatica()

    # Citirea gramaticii dintr-un fișier
    with open('gramatica.txt', 'r') as file:
        for line in file:
            variabila, productie = line.strip().split('->')
            productii = productie.split('|')
            for productie in productii:
                grammar.adauga_regula(variabila, productie)

    # Citirea cuvintelor dintr-un fișier
    cuvinte = []
    with open('cuvinte.txt', 'r') as file:
        for line in file:
            cuvant = line.strip()
            cuvinte.append(cuvant)

    rezultate = []

    # Verificarea fiecărui cuvânt
    for cuvant in cuvinte:
        rezultat = CYK(grammar, cuvant)
        rezultate.append((cuvant, rezultat))

    # Scrierea rezultatelor într-un fișier
    with open('rezultate.txt', 'w') as file:
        for cuvant, rezultat in rezultate:
            file.write(f'{cuvant}: {rezultat}\n')


if __name__ == '__main__':
    main()

