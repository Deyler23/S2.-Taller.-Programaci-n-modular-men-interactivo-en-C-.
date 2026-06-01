#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <array>
#include <numeric>   // std::accumulate
#include <algorithm> // std::minmax_element, std::count_if, std::for_each
using namespace std;

int leerEnteroSeguro(const string& mensaje) {
    int valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Ingrese un número entero: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

bool validarRangoCalificacion(int nota) {
    return nota >= 0 && nota <= 100;
}

char convertirNotaALetra(int nota) {
    switch (nota / 10) {
        case 10: case 9: return 'A';
        case 8: return 'B';
        case 7: return 'C';
        case 6: return 'D';
        default: return 'F';
    }
}

struct DesgloseTiempo {
    long long dias;
    long long horas;
    long long minutos;
};

DesgloseTiempo calcularDesgloseMinutos(long long minutosTotales) {
    if (minutosTotales < 0) return {-1, 0, 0}; 

    const long long MIN_POR_DIA = 24 * 60;
    return {
        minutosTotales / MIN_POR_DIA,
        (minutosTotales % MIN_POR_DIA) / 60,
        (minutosTotales % MIN_POR_DIA) % 60
    };
}

int solicitarOpcionMenu() {
    int opcion = leerEnteroSeguro("Seleccione una opción: ");
    if (opcion < 1 || opcion > 8) {
        cout << "Error: Ingrese un valor entre 1 y 8.\n";
        return solicitarOpcionMenu();
    }
    return opcion;
}

void resolverPromedioFijo() {
    cout << "\nPROBLEMA 1: Promedio de 10 números\n";
    int contadorIteraciones = 0;
    double sumaAcumulada = 0.0;

    cout << "Ingrese 10 números enteros:\n";
    while (contadorIteraciones < 10) {
        sumaAcumulada += leerEnteroSeguro("Número " + to_string(contadorIteraciones + 1) + ": ");
        contadorIteraciones++;
    }
    cout << fixed << setprecision(2);
    cout << "Promedio calculado: " << sumaAcumulada / 10.0 << "\n";
}

void resolverPromedioCentinela() {
    cout << "\nPROBLEMA 2: Promedio hasta centinela (-1)\n";
    vector<int> bufferNumeros;
    cout << "Ingrese números positivos (-1 para terminar):\n";

    while (true) {
        int entradaUsuario = leerEnteroSeguro("Valor: ");
        if (entradaUsuario == -1) break;

        if (entradaUsuario < 0) {
            cout << "Solo se aceptan positivos o -1.\n";
            continue;
        }
        bufferNumeros.push_back(entradaUsuario);
    }
    
    if (bufferNumeros.empty()) {
        cout << "No se ingresaron números válidos.\n";
        return;
    }

    double sumaTotal = accumulate(bufferNumeros.begin(), bufferNumeros.end(), 0.0);
    cout << fixed << setprecision(2);
    cout << " Promedio calculado: " << sumaTotal / bufferNumeros.size() << "\n";
}

void resolverCalificacionLetra() {
    cout << "\nPROBLEMA 3: Calificación a letra\n";
    int calificacionIngresada = leerEnteroSeguro("Ingrese calificación (0-100): ");

    if (!validarRangoCalificacion(calificacionIngresada)) {
        cout << "Error: Calificación fuera de rango.\n";
        return; 
    }

    cout << "Calificación en letra: " << convertirNotaALetra(calificacionIngresada) << "\n";
}

void resolverPotenciasDe4() {
    cout << "\nPROBLEMA 4: Potencias de 4 (1 a 20)\n";
    unsigned long long potenciaActual = 4;
    for (int exponente = 1; exponente <= 20; ++exponente) {
        cout << "4^" << exponente << " = " << potenciaActual << "\n";
        potenciaActual *= 4;
    }
}

void resolverMayorMenor() {
    cout << "\nPROBLEMA 5: Mayor y menor de 100 números\n";
    array<int, 100> serieNumeros;

    for (size_t indice = 0; indice < serieNumeros.size(); ++indice) {
        serieNumeros[indice] = leerEnteroSeguro("Número " + to_string(indice + 1) + ": ");
    }

    auto [iterMinimo, iterMaximo] = minmax_element(serieNumeros.begin(), serieNumeros.end());
    cout << "Número mayor: " << *iterMaximo << "\n";
    cout << "Número menor: " << *iterMinimo << "\n";
}

void resolverConversionMinutos() {
    cout << "\nPROBLEMA 6: Conversión de minutos\n";
    long long entradaMinutos = leerEnteroSeguro("Ingrese cantidad de minutos: ");

    DesgloseTiempo tiempoCalculado = calcularDesgloseMinutos(entradaMinutos);
    if (tiempoCalculado.dias == -1) {
        cout << "El tiempo no puede ser negativo.\n";
        return;
    }

    cout << "Equivale a: " << tiempoCalculado.dias << " días, "
         << tiempoCalculado.horas << " horas y "
         << tiempoCalculado.minutos << " minutos.\n";
}

void resolverAnalisisPares() {
    cout << "\nPROBLEMA 7: Análisis de pares (20 a 400)\n";
    vector<int> numerosPares;
    for (int valor = 20; valor <= 400; valor += 2) {
        numerosPares.push_back(valor);
    }

    double sumaPares = accumulate(numerosPares.begin(), numerosPares.end(), 0.0);
    double promedioPares = sumaPares / numerosPares.size();

    long double productoPares = 1.0;
    for_each(numerosPares.begin(), numerosPares.end(), [&](int num) {
        productoPares *= num;
    });

    int cantidadMayoresPromedio = count_if(numerosPares.begin(), numerosPares.end(),
        [&](int num) { return num > promedioPares; });

    cout << fixed << setprecision(2);
    cout << "Suma:                  " << sumaPares << "\n";
    cout << "Promedio:              " << promedioPares << "\n";
    cout << "Cantidad > Promedio:   " << cantidadMayoresPromedio << "\n";
    cout << "Producto (long double): " << scientific << setprecision(4) << productoPares << "\n";
}

//MENÚ Y PROGRAMA PRINCIPAL
void mostrarMenuPrincipal() {
    cout << "\nMENÚ PRINCIPAL\n";
    cout << "1. Promedio de 10 números\n";
    cout << "2. Promedio hasta centinela (-1)\n";
    cout << "3. Calificación a letra\n";
    cout << "4. Potencias de 4 (1-20)\n";
    cout << "5. Mayor y menor de 100 números\n";
    cout << "6. Conversión de minutos\n";
    cout << "7. Análisis de pares (20-400)\n";
    cout << "8. Salir\n";
}

int main() {
    int opcionSeleccionada;
    do {
        mostrarMenuPrincipal();
        opcionSeleccionada = solicitarOpcionMenu();

        switch (opcionSeleccionada) {
            case 1: resolverPromedioFijo(); break;
            case 2: resolverPromedioCentinela(); break;
            case 3: resolverCalificacionLetra(); break;
            case 4: resolverPotenciasDe4(); break;
            case 5: resolverMayorMenor(); break;
            case 6: resolverConversionMinutos(); break;
            case 7: resolverAnalisisPares(); break;
            case 8: cout << "Saliendo del sistema...\n"; break;
        }
    } while (opcionSeleccionada != 8);

    return 0;
}