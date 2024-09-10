import random


with open('numeros_aleatorios3.txt', 'w') as f:
    for _ in range(30001):
        numero = random.randint(1, 30001)
        f.write(f"{numero} ")

with open('numeros_ascendentes3.txt', 'w') as f:
    numero = 1
    for _ in range(1, 30001):

        f.write(f"{numero} ")
        numero += 1

with open('numeros_descebdebtes3.txt', 'w') as f:
    numero = 30000
    for _ in range(1, 30001):
        f.write(f"{numero} ")
        numero -= 1

with open('numeros_ordenado_parcial3.txt', 'w') as f:
    numero = 1 
    for i in range(1, 30001):  
        if i % 700 == 0:  # Cada 700 números
            numero_r = random.randint(1, 30001) 
            f.write(f"{numero_r} ")  
        else:
            f.write(f"{numero} ")  
            numero += 1  



