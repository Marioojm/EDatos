/**
 * @author Alba Piñero Henares      aph00028@red.ujaen.es
 * @author Mario Jaime Rojas        mjr00038@red.ujaen.es
 * @brief Programa principal para la demostración de MediExpress (STL).
 * Carga el sistema y ejecuta una serie de pruebas predefinidas.
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
        // -----------------------------------------------------------------
        // FIXME: CAMBIA ESTAS RUTAS A LAS DE TU ORDENADOR
        // Se usan las rutas del main.cpp original
        // -----------------------------------------------------------------
        std::string rutaMedicamentos = "C:/Users/Mario/Desktop/Universidad/estructura de datos/practica_4/pa_medicamentos.csv";
        std::string rutaLaboratorios = "C:/Users/Mario/Desktop/Universidad/estructura de datos/practica_4/lab2.csv";
        std::string rutaFarmacias    = "C:/Users/Mario/Desktop/Universidad/estructura de datos/practica_4/farmacias.csv";

        // --- DATOS DE PRUEBA (Basados en los CSV y el main original) ---
        std::string PROVINCIA_PRUEBA = "ALICANTE"; //
        std::string CIUDAD_LAB_PRUEBA = "Madrid";  //
        std::string PA_PRUEBA_1 = "MAGNESIO";      //
        std::string PA_PRUEBA_2 = "VIRUS";         //
        std::string CIF_PRUEBA = "37656422V";     // (FARMACIA LAGUNA VENTOSA)
        int MED_ID_PRUEBA = 3640;                  // (OXIDO DE MAGNESIO)
        std::string LOCALIDAD_ELIMINAR = "Madrid"; //

        // Puntero dummy para la función 'comprarMedicamento'
        PaMedicamentos* med_comprado_dummy = nullptr;


        // 1. Carga de datos (Requisito de carga)
        std::cout << "Iniciando carga de MediExpress..." << std::endl;
        MediExpress medi(rutaMedicamentos, rutaLaboratorios, rutaFarmacias);
        std::cout << "\n--- CARGA COMPLETADA ---" << std::endl;
        std::cout << "=================================================" << std::endl;


        // 2. Buscar farmacias por provincia
        std::cout << "\n--- PRUEBA 1: BUSCAR FARMACIAS POR PROVINCIA (" << PROVINCIA_PRUEBA << ") ---" << std::endl;
        std::vector<Farmacia*> farmacias = medi.buscarFarmacias(PROVINCIA_PRUEBA);
        if (farmacias.empty()) {
            std::cout << "No se encontraron farmacias." << std::endl;
        } else {
            std::cout << "Encontradas " << farmacias.size() << " farmacias (mostrando max 10):" << std::endl;
            for (size_t i = 0; i < farmacias.size() && i < 10; ++i) {
                std::cout << "  - CIF: " << farmacias[i]->getCif() << ", Nombre: " << farmacias[i]->getNombre() << std::endl;
            }
        }
        std::cout << "=================================================" << std::endl;


        // 3. Buscar laboratorios por ciudad
        std::cout << "\n--- PRUEBA 2: BUSCAR LABORATORIOS POR CIUDAD (" << CIUDAD_LAB_PRUEBA << ") ---" << std::endl;
        std::vector<Laboratorios*> labs = medi.buscarLabCiudad(CIUDAD_LAB_PRUEBA);
        if (labs.empty()) {
            std::cout << "No se encontraron laboratorios." << std::endl;
        } else {
            std::cout << "Encontrados " << labs.size() << " laboratorios:" << std::endl;
            for (Laboratorios* l : labs) {
                std::cout << "  - ID: " << l->getId() << ", Nombre: " << l->getNombreLab() << std::endl;
            }
        }
        std::cout << "=================================================" << std::endl;


        // 4. Buscar medicamento por principio activo (en MediExpress)
        std::cout << "\n--- PRUEBA 3: BUSCAR MEDICAMENTO EN MEDIEXPRESS (P.A.: " << PA_PRUEBA_1 << ") ---" << std::endl;
        std::vector<PaMedicamentos*> meds = medi.buscarCompuesto(PA_PRUEBA_1);
        if (meds.empty()) {
            std::cout << "No se encontraron medicamentos." << std::endl;
        } else {
            std::cout << "Encontrados " << meds.size() << " medicamentos:" << std::endl;
            for (PaMedicamentos* m : meds) {
                std::cout << "  - ID: " << m->getIdNum() << ", Nombre: " << m->getNombre() << std::endl;
            }
        }
        std::cout << "=================================================" << std::endl;


        // 5. Buscar medicamento EN FARMACIA por nombre (P.A.)
        std::cout << "\n--- PRUEBA 4: BUSCAR MEDS EN FARMACIA (CIF: " << CIF_PRUEBA << ", P.A.: " << PA_PRUEBA_2 << ") ---" << std::endl;
        Farmacia* farmaciaPtr = medi.buscarFarmacia(CIF_PRUEBA); // Búsqueda O(N) en vector
        if (farmaciaPtr) {
            std::cout << "Farmacia encontrada: " << farmaciaPtr->getNombre() << std::endl;
            // Esta función usa el 'linkMedi'
            std::vector<PaMedicamentos*> meds_farm = farmaciaPtr->buscaMedicamentoNombre(PA_PRUEBA_2);

            if (meds_farm.empty()) {
                std::cout << "La farmacia NO tiene en stock medicamentos con '" << PA_PRUEBA_2 << "'." << std::endl;
            } else {
                std::cout << "La farmacia SÍ tiene " << meds_farm.size() << " medicamentos con '" << PA_PRUEBA_2 << "':" << std::endl;
                for (PaMedicamentos* m : meds_farm) {
                    int stock = farmaciaPtr->buscaMedicamID(m->getIdNum()); //
                    std::cout << "  - ID: " << m->getIdNum() << ", Nombre: " << m->getNombre() << " (Stock: " << stock << ")" << std::endl;
                }
            }
        } else {
            std::cout << "Error: Farmacia de prueba " << CIF_PRUEBA << " no encontrada." << std::endl;
        }
        std::cout << "=================================================" << std::endl;


        // 6. Consultar y Comprar medicamento en farmacia
        std::cout << "\n--- PRUEBA 5: CONSULTAR Y COMPRAR (CIF: " << CIF_PRUEBA << ", MedID: " << MED_ID_PRUEBA << ") ---" << std::endl;
        farmaciaPtr = medi.buscarFarmacia(CIF_PRUEBA); // Re-buscar por si acaso
        if (farmaciaPtr) {
            // Consultar
            int stock_inicial = farmaciaPtr->buscaMedicamID(MED_ID_PRUEBA);
            std::cout << "Stock INICIAL del med " << MED_ID_PRUEBA << ": " << stock_inicial << " unidades." << std::endl;

            // Comprar 2
            int cantidad_a_comprar = 2;
            std::cout << "Intentando comprar " << cantidad_a_comprar << " unidades..." << std::endl;
            int comprados = farmaciaPtr->comprarMedicamento(MED_ID_PRUEBA, cantidad_a_comprar, med_comprado_dummy); //
            std::cout << "Comprados realmente: " << comprados << std::endl;
            std::cout << "Stock RESTANTE: " << farmaciaPtr->buscaMedicamID(MED_ID_PRUEBA) << " unidades." << std::endl;

            // Comprar todo (para vaciar)
            std::cout << "Intentando comprar 999 unidades (vaciar stock)..." << std::endl;
            comprados = farmaciaPtr->comprarMedicamento(MED_ID_PRUEBA, 999, med_comprado_dummy);
            std::cout << "Comprados realmente: " << comprados << std::endl;
            std::cout << "Stock FINAL (tras vaciar): " << farmaciaPtr->buscaMedicamID(MED_ID_PRUEBA) << " unidades." << std::endl;

        } else {
            std::cout << "Farmacia de prueba " << CIF_PRUEBA << " no encontrada." << std::endl;
        }
        std::cout << "=================================================" << std::endl;


        // 7. Eliminar laboratorio por localidad
        std::cout << "\n--- PRUEBA 7: ELIMINAR LABORATORIOS (Localidad: " << LOCALIDAD_ELIMINAR << ") ---" << std::endl;
        std::vector<PaMedicamentos*> meds_antes = medi.PaMedSinLab();
        std::cout << "Medicamentos sin laboratorio ANTES: " << meds_antes.size() << std::endl;

        std::cout << "Eliminando laboratorios de '" << LOCALIDAD_ELIMINAR << "' y desasignando sus medicamentos..." << std::endl;
        medi.eliminaLaboratorio(LOCALIDAD_ELIMINAR); //

        std::vector<PaMedicamentos*> meds_despues = medi.PaMedSinLab();
        std::cout << "Medicamentos sin laboratorio DESPUÉS: " << meds_despues.size() << std::endl;
        std::cout << "Operación completada." << std::endl;
        std::cout << "=================================================" << std::endl;


    } catch (const std::exception &e) { // Captura errores de apertura de archivo
        std::cerr << "EXCEPCIÓN GRAVE: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "EXCEPCIÓN DESCONOCIDA. El programa terminará." << std::endl;
        return 2;
    }

    std::cout << "\n--- FIN DE LA DEMOSTRACIÓN ---" << std::endl;
    return 0;
}