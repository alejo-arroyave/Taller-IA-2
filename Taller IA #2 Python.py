import random

# Función para verificar si un número es primo
def es_primo(numero):
    if numero <= 1:
        return False
    for i in range(2, int(numero**0.5) + 1):
        if numero % i == 0:
            return False
    return True

# Función para lanzar los dados
def lanzar_dado():
    return random.randint(1, 6)

# Función para jugar una ronda con dos dados
def jugar_ronda():
    suma_total = 0
    primer_lanzamiento = True  # Bandera para controlar si es el primer lanzamiento

    while True:
        dado1 = lanzar_dado()
        dado2 = lanzar_dado()

        print(f"Lanzaste: {dado1} y {dado2}")

        suma = dado1 + dado2
        suma_total += suma

        # Si el jugador se pasa de 23, el turno termina inmediatamente
        if suma_total > 23:
            print("Te pasaste de 23. Tu turno ha terminado.")
            return suma_total

        # Si es el primer lanzamiento y sacas dobles, se pregunta si el jugador desea abrir el juego
        if primer_lanzamiento and dado1 == dado2:
            opcion = input("Sacaste dobles en el primer lanzamiento, ¿quieres abrir el juego y lanzar 3 dados para cada línea? (s/n): ").lower()
            if opcion == 's':
                # Creamos dos líneas de juego adicionales
                lanzamientos_linea1 = [lanzar_dado() for _ in range(3)]
                lanzamientos_linea2 = [lanzar_dado() for _ in range(3)]

                # Mostramos los resultados
                print(f"Línea 1: {' '.join(map(str, lanzamientos_linea1))}")
                print(f"Línea 2: {' '.join(map(str, lanzamientos_linea2))}")

                suma_linea1 = sum(lanzamientos_linea1)
                suma_linea2 = sum(lanzamientos_linea2)

                print(f"Suma Línea 1: {suma_linea1}")
                print(f"Suma Línea 2: {suma_linea2}")

                # El jugador ahora debe elegir con qué línea continuar
                eleccion = input("Elige con qué línea continuar (1/2): ").strip()
                if eleccion == '1':
                    suma_total += suma_linea1
                else:
                    suma_total += suma_linea2

                print(f"Suma final elegida: {suma_total}")

                # Si el jugador se pasa de 23, el turno termina inmediatamente
                if suma_total > 23:
                    print("Te pasaste de 23. Tu turno ha terminado.")
                    return suma_total

        # Si se saca un 12, se puede lanzar un solo dado opcionalmente
        if suma == 12:
            opcion = input("Sacaste un 12, ¿quieres lanzar un dado adicional? (s/n): ").lower()
            if opcion == 's':
                nuevo_dado = lanzar_dado()
                print(f"Nuevo dado: {nuevo_dado}")
                suma_total += nuevo_dado

                # Si el jugador se pasa de 23, el turno termina inmediatamente
                if suma_total > 23:
                    print("Te pasaste de 23. Tu turno ha terminado.")
                    return suma_total

        print(f"Tu suma total hasta ahora es: {suma_total}")

        # Preguntamos si el jugador desea continuar lanzando
        opcion = input("¿Quieres lanzar de nuevo? (s/n): ").lower()

        # Después del primer lanzamiento, la división ya no es posible
        primer_lanzamiento = False

        if opcion != 's':
            break

    return suma_total

# Función para determinar el ganador
def determinar_ganador(puntaje_jugador1, puntaje_jugador2):
    print(f"\nPuntaje Jugador 1: {puntaje_jugador1}")
    print(f"Puntaje Jugador 2: {puntaje_jugador2}")

    # Si ambos puntajes son mayores a 23, el juego se anula
    if puntaje_jugador1 > 23 and puntaje_jugador2 > 23:
        print("Ambos jugadores superaron 23. No hay ganador.")
        return

    # Verificar si alguno de los dos tiene un número primo
    jugador1_primo = es_primo(puntaje_jugador1)
    jugador2_primo = es_primo(puntaje_jugador2)

    if jugador1_primo and jugador2_primo:
        # Si ambos tienen primos, gana el mayor
        if puntaje_jugador1 > puntaje_jugador2 and puntaje_jugador1 <= 23:
            print("Jugador 1 tiene un número primo mayor. ¡Jugador 1 gana!")
        elif puntaje_jugador1 < puntaje_jugador2 and puntaje_jugador2 <= 23:
            print("Jugador 2 tiene un número primo mayor. ¡Jugador 2 gana!")
        else:
            print("Ambos tienen el mismo número primo. Empate.")
    elif jugador1_primo:
        print("Jugador 1 tiene un número primo. ¡Jugador 1 gana!")
    elif jugador2_primo:
        print("Jugador 2 tiene un número primo. ¡Jugador 2 gana!")
    else:
        # Si ninguno tiene un primo, gana el más cercano a 23 sin pasarse
        if (puntaje_jugador1 <= 23 and puntaje_jugador1 > puntaje_jugador2) or puntaje_jugador2 > 23:
            print("Jugador 1 está más cerca de 23. ¡Jugador 1 gana!")
        else:
            print("Jugador 2 está más cerca de 23. ¡Jugador 2 gana!")

# Función principal
def main():
    random.seed()

    print("Bienvenidos a Prime Jack o 23")

    # Jugador 1 juega su ronda
    print("\nTurno del Jugador 1:")
    puntaje_jugador1 = jugar_ronda()

    # Jugador 2 juega su ronda
    print("\nTurno del Jugador 2:")
    puntaje_jugador2 = jugar_ronda()

    # Determinar quién ganó
    determinar_ganador(puntaje_jugador1, puntaje_jugador2)

if __name__ == "__main__":
    main()
