class PDA:
    def __init__(self):
        self.states = set()  # Stări
        self.input_alphabet = set()  # Alfabetul de intrare
        self.stack_alphabet = set()  # Alfabetul stivei
        self.transitions = dict()  # Tranzitii
        self.start_state = None  # Starea initiala
        self.accept_state = None  # Starea de accept
        self.final_states = set()  # Starile finale
        self.stack = []  # Stiva

    def load_from_file(self, file_name):
        with open(file_name, 'r') as file:
            # Citeste tranzitiile automatei cu stiva
            for line in file:
                line = line.strip()
                if line == '#':
                    break
                source, symbol, stack_top, dest, stack_push = line.split(',')
                self.states.add(source)
                self.states.add(dest)
                self.input_alphabet.add(symbol)
                self.stack_alphabet.add(stack_top)
                self.stack_alphabet.add(stack_push)
                if source not in self.transitions:
                    self.transitions[source] = dict()
                if symbol not in self.transitions[source]:
                    self.transitions[source][symbol] = dict()
                self.transitions[source][symbol][stack_top] = (dest, stack_push)

            # Citeste starea initiala, starea de accept si starile finale
            self.start_state = file.readline().strip()
            self.accept_state = file.readline().strip()
            self.final_states = set(file.readline().strip().split(','))

    def accepts_word(self, word):
        self.stack = []  # Resetam stiva la fiecare verificare
        return self._accepts_word_from_state(word, self.start_state)

    def _accepts_word_from_state(self, word, state):
        if len(word) == 0:
            # Verificam daca suntem intr-o stare finala
            if state in self.final_states:
                return True
            else:
                # Verificam daca putem face o tranzitie fara consum de simbol
                if '' in self.transitions[state]:
                    stack_top = self.stack.pop() if len(self.stack) > 0 else ''
                    dest, stack_push = self.transitions[state]['']['']
                    self.stack.append(stack_push)
                    return self._accepts_word_from_state(word, dest)
                else:
                    return False

        symbol = word[0]
        rest_of_word = word[1:]

        if symbol in self.transitions[state]:
            stack_top = self.stack.pop() if len(self.stack) > 0 else ''
            if stack_top in self.transitions[state][symbol]:
                dest, stack_push = self.transitions[state][symbol][stack_top]
                new_stack = self.stack + list(stack_push[::-1])
                if self._accepts_word_from_state(rest_of_word, dest):
                    return True
                self.stack = new_stack
            if '' in self.transitions[state][symbol]:
                stack_top = self.stack.pop() if len(self.stack) > 0 else ''
                dest, stack_push = self.transitions[state][symbol]['']
                new_stack = self.stack + list(stack_push[::-1])
                if self._accepts_word_from_state(word, dest):
                    return True
                self.stack = new_stack

        return False


def main():
    # Citim automatul cu stiva din fisier
    automaton = PDA()
    automaton.load_from_file('automaton.txt')

    # Citim cuvantul din fisier
    with open('word.txt', 'r') as file:
        word = file.readline().strip()

    # Verificam daca cuvantul apartine limbajului definit de automat
    if automaton.accepts_word(word):
        print(f"Cuvantul '{word}' apartine limbajului definit de automat.")
    else:
        print(f"Cuvantul '{word}' nu apartine limbajului definit de automat.")

if __name__ == '__main__':
    main()