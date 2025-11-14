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

int main() {
    try {
        std::string rutaMedicamentos = "C:/Users/mario/Desktop/estructuras/practica4/pa_medicamentos.csv";
        std::string rutaLaboratorios = "C:/Users/mario/Desktop/estructuras/practica4/lab2.csv";
        std::string rutaFarmacias    = "C:/Users/mario/Desktop/estructuras/practica4/farmacias.csv";

        // 1. Carga de datos
        std::cout << "Iniciando carga de MediExpress..." << std::endl;
        MediExpress medi(rutaMedicamentos, rutaLaboratorios, rutaFarmacias);
        std::cout << "Carga completada." << std::endl;


        // --- EJERCICIO 1 ---
        std::cout << "\nEjercicio 1: Comprar magnesio en Sevilla" << std::endl;
        std::cout << "=========================================" << std::endl;

        std::vector<Farmacia*> farmaciasSevilla = medi.buscarFarmacias("SEVILLA");
        std::cout << "Numero de farmacias en Sevilla: " << farmaciasSevilla.size() << std::endl << std::endl;

        // IDs específicos del enunciado
        int ID_OXIDO = 3640;
        int ID_CARBONATO = 3632;
        int ID_CLORURO = 3633;

        PaMedicamentos* medInfo = 0;
        PaMedicamentos* dummy = 0; // Puntero de salida no usado
        int comprados = 0;

        // Iteramos por cada farmacia de Sevilla (bucle C++98)
        for (size_t i = 0; i < farmaciasSevilla.size(); ++i) {
            Farmacia* farmacia = farmaciasSevilla[i];

            std::cout << "=== Farmacia: " << farmacia->getNombre() << " ===" << std::endl;

            // 12 "personas" intentan comprar
            for (int persona = 1; persona <= 12; ++persona) {

                comprados = 0; // Reseteamos 'comprados' para cada persona

                // 1. Intentar OXIDO (3640)
                comprados = farmacia->comprarMedicamento(ID_OXIDO, 1, dummy);
                if (comprados > 0) {
                    medInfo = medi.buscarCompuesto(ID_OXIDO);
                    std::cout << "La persona " << persona << " ha comprado una unidad de " << medInfo->getNombre() << std::endl;

                } else {
                    // 2. Si falla Óxido, intentar CARBONATO (3632)
                    comprados = farmacia->comprarMedicamento(ID_CARBONATO, 1, dummy);
                    if (comprados > 0) {
                        medInfo = medi.buscarCompuesto(ID_CARBONATO);
                        std::cout << "La persona " << persona << " ha comprado una unidad de " << medInfo->getNombre() << std::endl;

                    } else {
                        // 3. Si falla Carbonato, intentar CLORURO (3633)
                        comprados = farmacia->comprarMedicamento(ID_CLORURO, 1, dummy);
                        if (comprados > 0) {
                            medInfo = medi.buscarCompuesto(ID_CLORURO);
                            std::cout << "La persona " << persona << " ha comprado una unidad de " << medInfo->getNombre() << std::endl;

                        } else {
                            // 4. Si fallan los tres
                            std::cout << "La persona " << persona << " no ha podido comprar ningun magnesio" << std::endl;
                        }
                    }
                }
            } // Fin 12 personas

            // Requisito: Mostrar stock final
            std::cout << "--- Stock final de Magnesio ---" << std::endl;
            std::cout << "Stock (ID 3640) OXIDO: " << farmacia->buscaMedicamID(ID_OXIDO) << std::endl;
            std::cout << "Stock (ID 3632) CARBONATO: " << farmacia->buscaMedicamID(ID_CARBONATO) << std::endl;
            std::cout << "Stock (ID 3633) CLORURO: " << farmacia->buscaMedicamID(ID_CLORURO) << std::endl;
            std::cout << std::endl; // Espacio entre farmacias

        } // Fin farmacias


        // --- EJERCICIO 2 ---
        std::cout << "\nEjercicio 2: Farmacias en Madrid con VIRUS" << std::endl;
        std::cout << "==========================================" << std::endl;

        std::vector<Farmacia*> farmaciasMadrid = medi.buscarFarmacias("MADRID");
        std::cout << "Numero de farmacias en MADRID: " << farmaciasMadrid.size() << std::endl << std::endl;

        for (size_t i = 0; i < farmaciasMadrid.size(); ++i) {
            Farmacia* farmacia = farmaciasMadrid[i];

            std::cout << "=== Farmacia: " << farmacia->getNombre() << " ===" << std::endl;

            // La farmacia busca en su stock (usando a MediExpress para los nombres)
            std::vector<PaMedicamentos*> virusMeds = farmacia->buscaMedicamentoNombre("VIRUS");

            std::cout << "Numero de VIRUS: " << virusMeds.size() << std::endl;
            for (size_t j = 0; j < virusMeds.size(); ++j) {
                std::cout << virusMeds[j]->getNombre() << std::endl;
            }
            std::cout << std::endl; // Espacio entre farmacias
        }


        // --- EJERCICIO 3 ---
        std::cout << "\nEjercicio 3: Eliminar CIANURO" << std::endl;
        std::cout << "=========================================" << std::endl;

        int cianuroID = 9355; // ID de CIANURO DE SODIO (13C)

        if (medi.eliminaMedicamento(cianuroID)) {
            std::cout << "Se ha eliminado el CIANURO" << std::endl;
        } else {
            std::cout << "Error: El CIANURO (ID " << cianuroID << ") no se pudo eliminar o no existia." << std::endl;
        }

        std::cout << "Procedemos a buscar el CIANURO..." << std::endl;
        PaMedicamentos* medBuscado = medi.buscarCompuesto(cianuroID);

        if (medBuscado == 0) { // Comprobamos si es 0 (NULL)
            std::cout << "El CIANURO se ha eliminado correctamente" << std::endl;
        } else {
            std::cout << "ERROR: El CIANURO todavia se encuentra en el sistema." << std::endl;
        }

        if (medi.eliminaMedicamento(3244)) {
            std::cout << "Se ha eliminado el CIANURO" << std::endl;
        } else {
            std::cout << "Error: El CIANURO (ID " << cianuroID << ") no se pudo eliminar o no existia." << std::endl;
        }

        // --- EJERCICIO 4 ---
        std::cout << "\nEjercicio 4: Gripe en Madrid" << std::endl;
        std::cout << "=========================================" << std::endl;

        // Reutilizamos el vector de farmacias de Madrid del Ejercicio 2
        for (size_t i = 0; i < farmaciasMadrid.size(); ++i) {
            Farmacia* farmacia = farmaciasMadrid[i];

            // Buscamos si la farmacia tiene algún medicamento para la GRIPE
            std::vector<PaMedicamentos*> gripeMeds = farmacia->buscaMedicamentoNombre("GRIPE");

            if (!gripeMeds.empty()) {
                // Si el vector no está vacío, significa que tiene al menos uno
                std::cout << farmacia->getNombre() << std::endl;
            }
        }

    } catch (const std::exception &e) { // Captura errores (ej. apertura de archivo)
        std::cerr << "EXCEPCIÓN GRAVE: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "EXCEPCIÓN DESCONOCIDA. El programa terminará." << std::endl;
        return 2;
    }

    std::cout << "\n--- FIN DE LA DEMOSTRACIÓN ---" << std::endl;
    return 0;
}