/**
 * @author Alba Piñero Henares      aph00028@red.ujaen.es
 * @author Mario Jaime Rojas        mjr00038@red.ujaen.es
 * @brief Programa principal para la demostración de MediExpress (STL).
 * Carga el sistema y ejecuta los 4 ejercicios de prueba.
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "MediExpress.h"
#include "Farmacia.h"
#include "Laboratorios.h"
#include "PaMedicamentos.h"

// Usamos el espacio de nombres estándar para simplificar
using namespace std;

int main() {

    cout << "Comienzo de lectura de ficheros y carga de DATOS..." << endl;

    try {
        // --- CARGA DE DATOS ---
        // El constructor de MediExpress carga todos los CSV y enlaza los datos
        MediExpress medi("../pa_medicamentos.csv", "../lab2.csv", "../farmacias.csv");
        cout << "Carga de datos finalizada." << endl << endl;


        // --- Ejercicio 1: Comprar magnesio en Sevilla ---
        cout << "Ejercicio 1: Comprar magnesio en Sevilla" << endl;
        cout << "=========================================" << endl;

        // Buscamos las farmacias de Sevilla
        vector<Farmacia*> sevilla2 = medi.buscarFarmacias("SEVILLA");
        cout << "Numero de farmacias en Sevilla: " << sevilla2.size() << endl << endl;

        // Obtenemos los punteros a los medicamentos para poder mostrar sus NOMBRES
        PaMedicamentos* med3640 = medi.buscarCompuesto(3640); // OXIDO DE MAGNESIO
        PaMedicamentos* med3632 = medi.buscarCompuesto(3632); // CARBONATO DE MAGNESIO
        PaMedicamentos* med3633 = medi.buscarCompuesto(3633); // MAGNESIO HIDROXIDO

        // Almacenamos los nombres para imprimirlos (o un ID si no se encuentra)
        string n3640, n3632, n3633;

        if (med3640) {
            n3640 = med3640->getNombre();
        } else {
            n3640 = "ID 3640";
        }

        if (med3632) {
            n3632 = med3632->getNombre();
        } else {
            n3632 = "ID 3632";
        }

        if (med3633) {
            n3633 = med3633->getNombre();
        } else {
            n3633 = "ID 3633";
        }

        // Declaramos el puntero (aunque no se usa, según Farmacia.cpp)
        PaMedicamentos* punt2 = nullptr;

        // Recorremos cada farmacia de Sevilla
        for (size_t i = 0; i < sevilla2.size(); ++i) {
            // Imprimimos el nombre de la farmacia, como pide el formato
            cout << "=== Farmacia: " << sevilla2[i]->getNombre() << " ===" << endl;

            // Simulamos las 12 personas (de 1 a 12)
            for (int j = 1; j <= 12; ++j) {

                // Intento 1: Comprar ID 3640
                int stock2 = sevilla2[i]->comprarMedicamento(3640, 1, punt2);

                // La función devuelve > 0 si tuvo éxito
                if (stock2 > 0) {
                    cout << "La persona " << j << " ha comprado una unidad de " << n3640 << endl;
                } else {
                    // Intento 2: Comprar ID 3632
                    stock2 = sevilla2[i]->comprarMedicamento(3632, 1, punt2);
                    if (stock2 > 0) {
                        cout << "La persona " << j << " ha comprado una unidad de " << n3632 << endl;
                    } else {
                        // Intento 3: Comprar ID 3633
                        stock2 = sevilla2[i]->comprarMedicamento(3633, 1, punt2);
                        if (stock2 > 0) {
                            cout << "La persona " << j << " ha comprado una unidad de " << n3633 << endl;
                        } else {
                            // Fracaso: Si no pudo comprar ninguno
                            cout << "La persona " << j << " no ha podido comprar ningun medicamento" << endl;
                        }
                    }
                }
            }
            cout << endl; // Espacio entre farmacias
        }


        // --- Ejercicio 2: Farmacias en Madrid con VIRUS ---
        cout << "Ejercicio 2: Farmacias en Madrid con VIRUS" << endl;
        cout << "=========================================" << endl;

        // Buscamos farmacias de MADRID (solo mayúsculas, como pide el PDF)
        vector<Farmacia*> madrid = medi.buscarFarmacias("MADRID");
        cout << "Numero de farmacias en MADRID: " << madrid.size() << " (solo he considerado \"MADRID\" todo con mayusculas)" << endl << endl;

        // Recorremos cada farmacia de Madrid
        for (size_t i = 0; i < madrid.size(); ++i) {
            cout << "=== Farmacia: " << madrid[i]->getNombre() << " ===" << endl;

            // Usamos el método de farmacia para buscar en su stock local
            vector<PaMedicamentos*> virus = madrid[i]->buscaMedicamentoNombre("VIRUS");

            cout << "Numero de VIRUS: " << virus.size() << endl;

            // Imprimimos los nombres de los medicamentos encontrados
            for (size_t j = 0; j < virus.size(); ++j) {
                if (virus[j]) { // Comprobamos que el puntero no sea nulo
                    cout << virus[j]->getNombre() << endl;
                }
            }
            cout << endl; // Espacio entre farmacias
        }


        // --- Ejercicio 3: Eliminar CIANURO (ID 9355) y med 3244 ---
        cout << "Ejercicio 3: Eliminar CIANURO" << endl;
        cout << "=========================================" << endl;

        // Eliminamos el CIANURO (ID 9355)
        if (medi.eliminaMedicamento(9355)) {
            cout << "Se ha eliminado el CIANURO" << endl;
        } else {
            cout << "NO se encontro el CIANURO 9355 !!!" << endl;
        }

        // Comprobamos que ya no existe en el sistema
        cout << "Procedemos a buscar el CIANURO..." << endl;
        if (!medi.buscarCompuesto(9355)) {
            cout << "El CIANURO se ha eliminado correctamente" << endl;
        } else {
            cout << "ERROR: El CIANURO 9355 sigue existiendo!!!" << endl;
        }

        // Eliminamos el ID 3244
        if (medi.eliminaMedicamento(3244)) {
            cout << "Se ha eliminado el medicamento con ID 3244" << endl;
        } else {
            cout << "No se ha encontrado el medicamento con ID 3244" << endl;
        }
        cout << endl;


        // --- Ejercicio 4: Añadir Gripe (ID 997) en Madrid ---
        cout << "Ejercicio 4: Gripe en Madrid" << endl;
        cout << "=========================================" << endl;

        // Reutilizamos el vector 'madrid' del Ejercicio 2
        PaMedicamentos* pam = medi.buscarCompuesto(997); // Gripe

        if (!pam) {
            cout << "Error: No se ha encontrado el medicamento de la Gripe (ID 997)." << endl;
        } else {
            // Añadimos 20 unidades a CADA farmacia de Madrid
            for (size_t i = 0; i < madrid.size(); i++) {
                madrid[i]->nuevoStock(pam, 20);
            }

            // Buscamos las que tienen exactamente 30 unidades
            // (Implica que ya tenían 10 unidades del proceso de carga inicial)
            for (size_t i = 0; i < madrid.size(); i++) {
                int cant = madrid[i]->buscaMedicamID(997);
                if (cant == 30) {
                    // La salida de ejemplo muestra el NOMBRE de la farmacia
                    cout << madrid[i]->getNombre() << endl;
                }
            }
        }
        cout << endl;


    } catch (const std::runtime_error &e) { // Excepción de apertura de ficheros
        cerr << "Excepcion en fichero: " << e.what() << endl;
    } catch (const std::out_of_range &e) {
        cerr << e.what() << endl;
    } catch (const std::bad_alloc &e) {
        cerr << "No hay memoria suficiente para el objeto dinamico: " << e.what() << endl;
    } catch (const std::exception& e) {
        cerr << "Ha ocurrido un error inesperado: " << e.what() << endl;
    }

    return 0;
}