/*
 * ============================================================
 *  Leyes de Newton — Calculadora en C++
 *  Karina Reyes | 0910-25-2515
 * ============================================================
 *
 *  Compila con:
 *      g++ -std=c++17 -o leyes_newton leyes_newton.cpp
 *  Ejecuta con:
 *      ./leyes_newton
 * ============================================================
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits>

using namespace std;

// ── Constante gravitacional ─────────────────────────────────
const double G = 9.8; // m/s²

// ── Utilidades de formato ───────────────────────────────────

// Imprime una línea decorativa
void linea(char c = '-', int ancho = 55) {
    cout << string(ancho, c) << "\n";
}

// Encabezado de sección
void titulo(const string& texto) {
    linea('=');
    cout << "  " << texto << "\n";
    linea('=');
}

// Imprime un resultado con etiqueta, ecuación y valor
void resultado(const string& nombre, const string& formula,
               double valor, const string& unidad) {
    cout << fixed << setprecision(4);
    cout << "  " << left << setw(20) << nombre
         << "  " << setw(14) << formula
         << "  = " << right << setw(10) << valor
         << "  " << unidad << "\n";
}

// ── Lectura segura de doubles ───────────────────────────────
double leerDouble(const string& prompt, bool soloPositivo = false) {
    double valor;
    while (true) {
        cout << prompt;
        if (cin >> valor) {
            if (soloPositivo && valor <= 0) {
                cout << "  ⚠  El valor debe ser mayor a cero. Intenta de nuevo.\n";
                continue;
            }
            return valor;
        }
        // Entrada inválida
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  ⚠  Entrada inválida. Ingresa un número.\n";
    }
}

double leerDoubleRango(const string& prompt, double minVal, double maxVal) {
    double valor;
    while (true) {
        cout << prompt;
        if (cin >> valor) {
            if (valor < minVal || valor > maxVal) {
                cout << "  ⚠  El valor debe estar entre " << minVal
                     << " y " << maxVal << ". Intenta de nuevo.\n";
                continue;
            }
            return valor;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  ⚠  Entrada inválida. Ingresa un número.\n";
    }
}

// ── Interpretación de la 2da Ley ───────────────────────────
void interpretarSegunda(double m, double F, double N,
                        double f, double Fn, double a, double mu) {
    cout << "\n  [ Interpretacion ]\n";
    cout << fixed << setprecision(4);

    if (a <= 0)
        cout << "  -> La friccion (" << f << " N) >= fuerza aplicada ("
             << F << " N).\n"
             << "     El objeto NO SE MUEVE. Necesitas aplicar mas de "
             << f << " N.\n";
    else if (a < 1)
        cout << "  -> El objeto se mueve con aceleracion baja (" << a
             << " m/s²). La friccion consume gran parte de la fuerza.\n";
    else if (a < 5)
        cout << "  -> Aceleracion moderada (" << a
             << " m/s²). Buen balance fuerza-friccion.\n";
    else
        cout << "  -> Aceleracion elevada (" << a
             << " m/s²). La fuerza supera ampliamente la friccion.\n";

    if (mu >= 0.6)
        cout << "  -> Coef. de friccion alto (u=" << mu
             << "): superficie muy rugosa. Friccion = " << f << " N.\n";
    else if (mu <= 0.1)
        cout << "  -> Superficie casi lisa (u=" << mu
             << "). El objeto se desliza con facilidad.\n";

    cout << "  -> Fuerza normal = " << N
         << " N (igual al peso — equilibrio vertical).\n";
}

// ── Segunda Ley de Newton ───────────────────────────────────
void segundaLey() {
    titulo("2da Ley de Newton   F = m * a");

    cout << "\n  Enunciado: La aceleracion de un objeto es directamente\n"
         << "  proporcional a la fuerza neta e inversamente proporcional\n"
         << "  a su masa.\n\n";

    double m  = leerDouble("  Masa  m  [kg]              : ", true);
    double F  = leerDouble("  Fuerza aplicada F [N]      : ");
    if (F < 0) F = 0; // por diseño
    double mu = leerDoubleRango("  Coef. de friccion u [0-1]  : ", 0.0, 1.0);

    // Calculos
    double N  = m * G;       // Fuerza Normal
    double f  = mu * N;      // Friccion cinetica
    double Fn = F - f;       // Fuerza neta
    double a  = Fn / m;      // Aceleracion

    // Resultados
    cout << "\n";
    linea();
    cout << "  RESULTADOS\n";
    linea();
    resultado("Fuerza Normal",   "N = m*g",   N,  "N  [arriba]");
    resultado("Friccion cinetica","f = u*N",   f,  "N  [izquierda]");
    resultado("Fuerza neta",     "Fn = F-f",  Fn, "N");
    resultado("Aceleracion",     "a = Fn/m",  a,  "m/s²");
    linea();

    // Pasos detallados
    cout << "\n  [ Pasos ]\n";
    cout << fixed << setprecision(4);
    cout << "    N  = " << m  << " kg  x  9.8  =  " << N  << " N\n";
    cout << "    f  = " << mu << "  x  " << N  << " N  =  " << f  << " N\n";
    cout << "    Fn = " << F  << " N  -  " << f  << " N  =  " << Fn << " N\n";
    cout << "    a  = " << Fn << " N  /  " << m  << " kg =  " << a  << " m/s²\n";

    interpretarSegunda(m, F, N, f, Fn, a, mu);
}

// ── Interpretación de la 3ra Ley ───────────────────────────
void interpretarTercera(double m, double a, double F1) {
    cout << "\n  [ Interpretacion ]\n";
    cout << fixed << setprecision(4);
    cout << "  -> A ejerce " << F1 << " N sobre B; B ejerce "
         << -F1 << " N sobre A.\n";

    double absF = fabs(F1);
    if (absF < 10)
        cout << "  -> Fuerza pequeña: como dos personas empujandose suavemente.\n";
    else if (absF < 50)
        cout << "  -> Fuerza moderada: similar al retroceso de una pelota.\n";
    else
        cout << "  -> Fuerza considerable: similar al empuje de un motor.\n";

    cout << "  -> Las fuerzas actuan en objetos distintos: no se cancelan.\n";
}

// ── Tercera Ley de Newton ───────────────────────────────────
void terceraLey() {
    titulo("3ra Ley de Newton   F1 = -F2");

    cout << "\n  Enunciado: Por cada fuerza de accion existe una fuerza de\n"
         << "  reaccion igual en magnitud pero opuesta en direccion.\n\n";

    double m = leerDouble("  Masa del objeto m [kg] : ", true);
    double a = leerDouble("  Aceleracion a [m/s²]   : ");

    double F1 =  m * a;   // Fuerza de accion
    double F2 = -F1;      // Fuerza de reaccion

    // Resultados
    cout << "\n";
    linea();
    cout << "  RESULTADOS\n";
    linea();
    resultado("Fuerza de accion",   "F1 = m*a", F1,          "N  [->]");
    resultado("Fuerza de reaccion", "F2 = -F1", F2,          "N  [<-]");
    resultado("Magnitud (igual)",   "|F1|=|F2|",fabs(F1),    "N");
    resultado("Aceleracion",        "a = F/m",  a,           "m/s²");
    linea();

    // Pasos
    cout << "\n  [ Pasos ]\n";
    cout << fixed << setprecision(4);
    cout << "    F1 = " << m  << " kg  x  " << a  << " m/s²  =  " << F1 << " N\n";
    cout << "    F2 = -(" << F1 << ")  =  " << F2 << " N\n";
    cout << "    |F1| = |F2| = " << fabs(F1) << " N\n";

    interpretarTercera(m, a, F1);
}

// ── Menú principal ──────────────────────────────────────────
void menu() {
    linea('*');
    cout << "  LEYES DE NEWTON — Calculadora\n";
    cout << "  Karina Reyes | 0910-25-2515\n";
    linea('*');
    cout << "\n  1. Segunda Ley de Newton  (F = m*a, con friccion)\n";
    cout << "  2. Tercera Ley de Newton  (Accion y Reaccion)\n";
    cout << "  0. Salir\n\n";
}

// ── Punto de entrada ────────────────────────────────────────
int main() {
    cout << fixed << setprecision(4);

    int opcion;
    do {
        menu();
        cout << "  Selecciona una opcion: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = -1;
        }
        cout << "\n";

        switch (opcion) {
            case 1:
                segundaLey();
                break;
            case 2:
                terceraLey();
                break;
            case 0:
                cout << "  Hasta luego!\n";
                break;
            default:
                cout << "  Opcion no valida.\n";
        }
        cout << "\n";

    } while (opcion != 0);

    return 0;
}
