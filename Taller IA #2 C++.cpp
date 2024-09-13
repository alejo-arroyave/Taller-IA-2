#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// Función para verificar si un número es primo
bool esPrimo(int numero) {
    if (numero <= 1) return false;
    for (int i = 2; i * i <= numero; i++) {
        if (numero % i == 0) return false;
    }
    return true;
}

// Función para lanzar los dados
int lanzarDado() {
    return rand() % 6 + 1;
}

// Función para jugar una ronda con dos dados
int jugarRonda() {
    int sumaTotal = 0;
    char opcion;
    bool primerLanzamiento = true; // Bandera para controlar si es el primer lanzamiento

    do {
        int dado1 = lanzarDado();
        int dado2 = lanzarDado();

        cout << "Lanzaste: " << dado1 << " y " << dado2 << endl;

        int suma = dado1 + dado2;
        sumaTotal += suma;

        // Si el jugador se pasa de 23, el turno termina inmediatamente
        if (sumaTotal > 23) {
            cout << "Te pasaste de 23. Tu turno ha terminado.\n";
            return sumaTotal;
        }

        // Si es el primer lanzamiento y sacas dobles, se pregunta si el jugador desea abrir el juego
        if (primerLanzamiento && dado1 == dado2) {
            cout << "Sacaste dobles en el primer lanzamiento, ¿quieres abrir el juego y lanzar 3 dados para cada línea? (s/n): ";
            cin >> opcion;
            cin.ignore(); // Evitar problemas de buffer de entrada

            if (opcion == 's' || opcion == 'S') {
                // Creamos dos líneas de juego adicionales
                vector<int> lanzamientosLinea1, lanzamientosLinea2;

                // Lanzamos 3 dados para cada línea
                for (int i = 0; i < 3; i++) {
                    lanzamientosLinea1.push_back(lanzarDado());
                    lanzamientosLinea2.push_back(lanzarDado());
                }

                // Mostramos los resultados
                cout << "Línea 1: ";
                for (int dado : lanzamientosLinea1) cout << dado << " ";
                cout << endl;

                cout << "Línea 2: ";
                for (int dado : lanzamientosLinea2) cout << dado << " ";
                cout << endl;

                // Calculamos la suma de cada línea
                int sumaLinea1 = 0, sumaLinea2 = 0;
                for (int val : lanzamientosLinea1) sumaLinea1 += val;
                for (int val : lanzamientosLinea2) sumaLinea2 += val;

                cout << "Suma Línea 1: " << sumaLinea1 << endl;
                cout << "Suma Línea 2: " << sumaLinea2 << endl;

                // El jugador ahora debe elegir con qué línea continuar
                char eleccion;
                cout << "Elige con qué línea continuar (1/2): ";
                cin >> eleccion;
                cin.ignore(); // Evitar problemas de buffer de entrada

                // Actualizamos la suma con base en la línea elegida
                if (eleccion == '1') {
                    sumaTotal += sumaLinea1;
                } else {
                    sumaTotal += sumaLinea2;
                }

                cout << "Suma final elegida: " << sumaTotal << endl;

                // Si el jugador se pasa de 23, el turno termina inmediatamente
                if (sumaTotal > 23) {
                    cout << "Te pasaste de 23. Tu turno ha terminado.\n";
                    return sumaTotal;
                }
            }
        }

        // Si se saca un 12, se puede lanzar un solo dado opcionalmente
        if (suma == 12) {
            cout << "Sacaste un 12, puedes elegir lanzar un dado adicional." << endl;
            cout << "¿Quieres lanzar un dado más? (s/n): ";
            cin >> opcion;
            cin.ignore(); // Evitar problemas de buffer de entrada
            if (opcion == 's' || opcion == 'S') {
                int nuevoDado = lanzarDado();
                cout << "Nuevo dado: " << nuevoDado << endl;
                sumaTotal += nuevoDado;

                // Si el jugador se pasa de 23, el turno termina inmediatamente
                if (sumaTotal > 23) {
                    cout << "Te pasaste de 23. Tu turno ha terminado.\n";
                    return sumaTotal;
                }
            }
        }

        cout << "Tu suma total hasta ahora es: " << sumaTotal << endl;

        // Preguntamos si el jugador desea continuar lanzando
        cout << "¿Quieres lanzar de nuevo? (s/n): ";
        cin >> opcion;
        cin.ignore(); // Evitar problemas de buffer de entrada

        // Después del primer lanzamiento, la división ya no es posible
        primerLanzamiento = false;

    } while (opcion == 's' || opcion == 'S');

    return sumaTotal;
}

// Función para determinar el ganador
void determinarGanador(int puntajeJugador1, int puntajeJugador2) {
    cout << "\nPuntaje Jugador 1: " << puntajeJugador1 << endl;
    cout << "Puntaje Jugador 2: " << puntajeJugador2 << endl;

    // Si ambos puntajes son mayores a 23, el juego se anula
    if (puntajeJugador1 > 23 && puntajeJugador2 > 23) {
        cout << "Ambos jugadores superaron 23. No hay ganador." << endl;
        return;
    }

    // Verificar si alguno de los dos tiene un número primo
    bool jugador1Primo = esPrimo(puntajeJugador1);
    bool jugador2Primo = esPrimo(puntajeJugador2);

    if (jugador1Primo && jugador2Primo) {
        // Si ambos tienen primos, gana el mayor
        if (puntajeJugador1 > puntajeJugador2 && puntajeJugador1 < 23) {
            cout << "Jugador 1 tiene un número primo mayor. ¡Jugador 1 gana!" << endl;
        } else if (puntajeJugador1 < puntajeJugador2 && puntajeJugador2 < 23) {
            cout << "Jugador 2 tiene un número primo mayor. ¡Jugador 2 gana!" << endl;
        } else {
            cout << "Ambos tienen el mismo número primo. Empate." << endl;
        }
    } else if (jugador1Primo) {
        cout << "Jugador 1 tiene un número primo. ¡Jugador 1 gana!" << endl;
    } else if (jugador2Primo) {
        cout << "Jugador 2 tiene un número primo. ¡Jugador 2 gana!" << endl;
    } else {
        // Si ninguno tiene un primo, gana el más cercano a 23 sin pasarse
        if ((puntajeJugador1 <= 23 && puntajeJugador1 > puntajeJugador2) || puntajeJugador2 > 23) {
            cout << "Jugador 1 está más cerca de 23. ¡Jugador 1 gana!" << endl;
        } else {
            cout << "Jugador 2 está más cerca de 23. ¡Jugador 2 gana!" << endl;
        }
    }
}

int main() {
    srand(time(0));

    cout << "Bienvenidos a Prime Jack o 23\n";

    // Jugador 1 juega su ronda
    cout << "Turno del Jugador 1:\n";
    int puntajeJugador1 = jugarRonda();

    // Jugador 2 juega su ronda
    cout << "\nTurno del Jugador 2:\n";
    int puntajeJugador2 = jugarRonda();

    // Determinar quién ganó
    determinarGanador(puntajeJugador1, puntajeJugador2);

    return 0;
}
