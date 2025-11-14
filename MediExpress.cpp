#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "MediExpress.h"
// Se asume la inclusión de "PaMedicamentos.h", "Laboratorios.h", "VecDin.h", y "listasEnlazadas.h" dentro de "MediExpress.h"

// --- IMPLEMENTACIÓN DE MediExpress ---

/**
 * @brief Constructor por defecto. Inicializa los contenedores de medicamentos y laboratorios vacíos.
 */
MediExpress::MediExpress() : medication(), labs(), pharmacy() {}

/**
 * @brief Constructor que carga datos desde ficheros CSV.
 *
 * Carga los medicamentos y laboratorios, y luego realiza la asignación 2:1:
 * cada dos medicamentos consecutivos se asignan al mismo laboratorio.
 *
 * @param nomFichPaMed Ruta y nombre del fichero de Principios Activos de Medicamentos (CSV).
 * @param nomFichLab Ruta y nombre del fichero de Laboratorios (CSV).
 * @post Los contenedores \c medication y \c labs quedan cargados con los datos.
 */
MediExpress::MediExpress(const std::string &nomFichPaMed, const std::string &nomFichLab,
                         const std::string &nomFichFar){
    std::ifstream is;
    std::stringstream columnas;
    std::string fila;
    int contador = 0;

    // --- 1. Carga de MEDICAMENTOS (a std::map) ---

    int id_num = 0;
    std::string nombre = "";
    std::string num = "";

    is.open(nomFichPaMed);
    if (is.good()) {

        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);

                // Leemos solo 2 columnas
                getline(columnas, num, ';');      // Columna 1: ID
                getline(columnas, nombre, '\r');  // Columna 2: Nombre (hasta el fin de línea)

                // Si el archivo CSV no tiene '\r' (es formato Unix),
                // usa solo: getline(columnas, nombre);

                if (num.empty()) continue; // saltar líneas vacías o corruptas

                try {
                    id_num = stoi(num);
                } catch (const std::invalid_argument& e) {
                    std::cout << "Advertencia: Saltando linea invalida. " << e.what() << std::endl;
                    continue; // Saltar esta línea si 'num' no es un número
                }


                fila = "";
                columnas.clear();

                // Asignamos el nombre a las dos variables (id_alpha y nombre)
                // ya que la clase PaMedicamentos pide 3 argumentos
                PaMedicamentos dato(id_num, nombre, nombre);

                medication.insert(std::make_pair(id_num, dato)); // Usamos make_pair (C++98)
            }
        }
        is.close();
    } else {
        // Lanzamos una excepción si el archivo no se abre
        throw std::runtime_error("Error de apertura en archivo: " + nomFichPaMed);
    }

    // --- 2. Carga de LABORATORIOS (a std::list) ---

    int id = 0;
    std::string nombrelab = "";
    std::string direccion = "";
    std::string cp = "";
    std::string localidad = "";

    is.open(nomFichLab);
    if (is.good()) {

        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);
                getline(columnas, num, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, nombre, ';');
                getline(columnas, direccion, ';');
                getline(columnas, cp, ';');
                getline(columnas, localidad, '\r');
                id_num = stoi(num);

                fila = "";
                columnas.clear();

                Laboratorios dato(id_num,nombre,direccion,cp,localidad);

                labs.push_back(dato);
            }
        }
        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


// --- 3. Carga de FARMACIAS (a std::vector) ---

    std::string ciff = "";
    std::string provinciaf = "";
    std::string localidadf = "";
    std::string nombref = "";
    std::string direccionf= "";
    std::string codpostalf= "";

    contador=0;

    is.open(nomFichFar);
    if (is.good()) {

        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);

                getline(columnas, ciff, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provinciaf, ';');
                getline(columnas, localidadf, ';');
                getline(columnas, nombref, ';');
                getline(columnas, direccionf, ';');
                getline(columnas, codpostalf, '\r');

                fila = "";
                columnas.clear();

                Farmacia datof(ciff,provinciaf,localidadf,nombref,direccionf,codpostalf, this);

                pharmacy.push_back(datof);

            }
        }
        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    //ENLAZAMOS CADA 2 PAMEDIC. CON UN LABORATORIO

    auto itl = labs.begin(); // Iterador de laboratorios (std::list)
    auto itm = medication.begin(); // Iterador de medicamentos (std::map)

    while (itm != medication.end() && itl != labs.end()) {
        // Suministrar al primer medicamento
        suministrarMed(&(itm->second), &(*itl)); // itm->second es el PaMedicamentos

        itm++; // Avanzar medicamento
        if (itm == medication.end()) break; // Salir si se acaba

        // Suministrar al segundo medicamento
        itm->second.servidoPor(&(*itl)); // (forma 2 original)

        itm++; // Avanzar medicamento
        itl++; // Avanzar laboratorio
    }

    //laboratorios madrid
    vector<Laboratorios*> madrid= buscarLabCiudad("Madrid");
    //Medicamentos sin laboratorio
    vector<PaMedicamentos*> sin= PaMedSinLab();

    for (size_t i=0; i<madrid.size() && i<sin.size(); i++){
        suministrarMed(sin[i],madrid[i]);
    }

    //MOSTRAR PARA COMPROBAR (CORREGIDO SIN AUTO)
    int cont = 0;

    // 1. Declaramos el iterador con su tipo completo
    // Usamos 'const_iterator' porque solo vamos a leer datos (es más seguro)
    std::map<int, PaMedicamentos>::const_iterator it;

    // 2. Bucle 'for' clásico con iteradores
    for (it = medication.begin(); it != medication.end(); ++it) {

        // 'it->second' es el objeto PaMedicamentos.
        // Lo guardamos en una referencia constante para que sea más claro.
        const PaMedicamentos& med = it->second;


    }

// --- 6. Lectura de CIFs y Suministro a Farmacias (Vector y Map) ---

    // Volver a leer el CSV solo para los CIFs (como en el original)
    std::vector<std::string> cif_Farma;
    contador = 0;
    is.open(nomFichFar);
    if (!is.good()) {
        throw std::runtime_error("Error abriendo farmacias.csv por segunda vez");
    }

    while (getline(is, fila)) {
        if (fila.empty()) continue;
        columnas.str(fila);
        getline(columnas, ciff, ';');
        columnas.clear();
        cif_Farma.push_back(ciff);
    }
    is.close();

    // Necesitamos una lista de IDs de medicamentos para simular el acceso medication[j]
    std::vector<int> med_ids;
    for(auto const& [id, med] : medication) {
        med_ids.push_back(id);
    }

    if (med_ids.empty()) {
        std::cout << "Advertencia: No hay medicamentos cargados, no se puede suministrar a farmacias." << std::endl;
        return;
    }

    // Suministrar 100 medicamentos a cada farmacia (reemplaza buscaIt por buscarFarmacia)
    int j = 0;
    for (size_t i = 0; i < cif_Farma.size(); i++) {
        // Usamos la nueva búsqueda O(N) en el vector de farmacias
        Farmacia* f = buscarFarmacia(cif_Farma[i]);

        if (f) { // Si la farmacia se encontró
            int c = 0;
            while (c < 100) {
                // Suministramos 1 unidad (o la cantidad 'n' que queramos)
                suministrarFarmacia(f, med_ids[j], 1);

                j = (j + 1) % med_ids.size(); // Ciclar por los IDs de medicamentos
                c++;
            }
        }
    }

    std::cout << "--- [FIN DE CONSTRUCTOR MEDIEXPRESS] ---" << std::endl;
    std::cout << "Total Medicamentos cargados (Map): " << medication.size() << std::endl;
    std::cout << "Total Laboratorios cargados (List): " << labs.size() << std::endl;
    std::cout << "Total Farmacias cargadas (Vector): " << pharmacy.size() << std::endl;
    std::cout << "------------------------------------------" << std::endl;
}

/**
 * @brief Constructor de copia.
 * @param orig Objeto MediExpress constante para copiar.
 */
MediExpress::MediExpress(const MediExpress &orig) : medication(orig.medication), labs(orig.labs) {
    // La copia profunda se maneja a través de los constructores de copia de VecDin y listasEnlazadas.
}

/**
 * @brief Destructor de la clase MediExpress.
 * @post Libera la memoria de los contenedores \c medication y \c labs.
 */
MediExpress::~MediExpress() {
}

/**
 * @brief Asigna un laboratorio para que suministre un medicamento.
 * @param pa Puntero al medicamento (\c PaMedicamentos) que será suministrado.
 * @param l Puntero al laboratorio (\c Laboratorios) que suministra.
 */
void MediExpress::suministrarMed(PaMedicamentos *pa, Laboratorios *l){
    if (l && pa){
        pa->servidoPor(l);
    }
}

void MediExpress::suministrarFarmacia(Farmacia* f, int id_num, int n) {
    if (f == nullptr) return;

    // Usamos la búsqueda rápida O(log N) del map
    PaMedicamentos* med_a_suministrar = this->buscarCompuesto(id_num);

    if (med_a_suministrar != nullptr) {
        // Usamos la función corregida de Farmacia
        f->nuevoStock(med_a_suministrar, n);
    }
}

/**
 * @brief Busca un laboratorio por su nombre (búsqueda parcial).
 * @param nombreLab Nombre (parcial) del laboratorio a buscar.
 * @return Puntero al Laboratorio encontrado, o \c nullptr si no se encuentra.
 */
Laboratorios* MediExpress::buscarLab(std::string nombreLab){
    list<Laboratorios>::iterator it=labs.begin();
    while (it!= labs.end()){
        if (it->getNombreLab().find(nombreLab) != string::npos)
            return &(*it);
        it++;
    }
    return nullptr;
}


/**
 * @brief Busca laboratorios ubicados en una ciudad específica.
 * @param nombreCiudad Nombre de la ciudad.
 * @return Vector dinámico de punteros a los Laboratorios encontrados.
 */
vector<Laboratorios*> MediExpress::buscarLabCiudad(const std::string &nombreCiudad) {
    vector<Laboratorios*> labor;
    list<Laboratorios>::iterator it=labs.begin();
    while (it!=labs.end()){
        if (it->getLocalidad().find(nombreCiudad) != string::npos)
            labor.push_back(&(*it));
        it++;
    }
    return labor;
}

vector<Laboratorios*> MediExpress::buscarLabs(const std::string &nombrePA) {

    vector<Laboratorios*> laboratorios;
    for (map<int,PaMedicamentos>::iterator it=medication.begin(); it!=medication.end(); it++){
        if (it->second.getNombre().find(nombrePA)!=string::npos)
            if (it->second.servidoPor())
                laboratorios.push_back(it->second.servidoPor());
    }
    return laboratorios;
}

/**
 * @brief Busca medicamentos que contengan un compuesto activo específico.
 * @param nombrePA Nombre (parcial) del compuesto activo.
 * @return Vector dinámico de punteros a los PaMedicamentos coincidentes.
 */
vector<PaMedicamentos*> MediExpress::buscarCompuesto(const std::string &nombrePA) {
    vector<PaMedicamentos*> compu;
    map<int,PaMedicamentos>::iterator it= medication.begin();
    for (; it!=medication.end(); it++) {
        if (it->second.getNombre().find(nombrePA) != string::npos) {
            compu.push_back(&(it->second));
        }
    }
    return compu;
}


/**
     * @brief Busca un medicamento por su ID numérico.
     * @param id_num ID a buscar.
     * @return Puntero al medicamento o nullptr si no se encuentra.
     */
PaMedicamentos* MediExpress::buscarCompuesto(int id_num) {
    map<int,PaMedicamentos>::iterator it = medication.find(id_num);
    if (it != medication.end()) {
        return &(it->second); // Devolver la dirección del valor encontrado
    }
    return nullptr; // No se encontró
}

/**
 * @brief Identifica los medicamentos que no tienen un laboratorio asignado.
 * @return Vector dinámico de punteros a los PaMedicamentos sin laboratorio (el puntero es \c nullptr).
 */
vector<PaMedicamentos*> MediExpress::PaMedSinLab() {
    vector<PaMedicamentos*> sin;
    map<int,PaMedicamentos>::iterator it= medication.begin();
    while (it!=medication.end()) {
        if (!it->second.servidoPor())
            sin.push_back(&(it->second));

        it++;
    }
    return sin;
}


/**
* @brief Elimina todos los laboratorios de una localidad dada.
*
* Desasigna (\c nullptr) el laboratorio de los medicamentos que dependían de él, y luego
* elimina los nodos de la lista enlazada que contienen dichos laboratorios.
*
* @param localidad Nombre de la localidad a eliminar.
* @post Los medicamentos que dependían de laboratorios en esa localidad quedan sin asignar.
* @post Los nodos de laboratorios de esa localidad son eliminados de la lista \c labs.
*/
void MediExpress::eliminaLaboratorio(const std::string &localidad){
    int contador_eliminados = 0;

    // 1. Desasignación de Laboratorios en los PaMedicamentos.
    // 1. Desasignación de Laboratorios en los PaMedicamentos (CORREGIDO SIN AUTO)

    // Usamos un iterador NO-constante, porque vamos a modificar los medicamentos
    std::map<int, PaMedicamentos>::iterator it;

    for (it = medication.begin(); it != medication.end(); ++it) {

        // it->second es el PaMedicamentos (NO es const)
        PaMedicamentos& med = it->second;

        if (med.servidoPor() &&
            med.servidoPor()->getLocalidad().find(localidad) != std::string::npos) {

            med.servidoPor(nullptr); // Desasignar con nullptr
        }
    }

    // 2. Eliminación de nodos en la lista de laboratorios.
    list<Laboratorios>::iterator it_lab = labs.begin();
    list<Laboratorios>::iterator aux;

    while (it_lab!=labs.end()) {
        if (it_lab->getLocalidad().find(localidad) != std::string::npos) {
            it_lab = labs.erase(it_lab);
            contador_eliminados++;
        } else {
            it++; // Si no se borra, se avanza normalmente.
        }
    }
    std::cout << "Total de laboratorios de '" << localidad << "' eliminados: " << contador_eliminados << std::endl;
}

    /**
     * @brief Busca una farmacia por su CIF.
     * @param cif CIF a buscar.
     * @return Puntero a la farmacia o nullptr si no se encuentra.
     */
     Farmacia* MediExpress::buscarFarmacia(const string &cif){
        for (int i=0; i<pharmacy.size(); i++){
            if (pharmacy[i].getCif()==cif)
                return &pharmacy[i];
        }
        return 0;
    }

    vector<Farmacia*> MediExpress::buscarFarmacias(const std::string &provincia) {
         vector<Farmacia*> v_resultados;

         for (auto& farma : pharmacy) {
             if (farma.getProvincia()==provincia){
                 v_resultados.push_back(&farma);
             }
         }
         return v_resultados;
     }

    /**
     * @brief Suministra un medicamento (por ID) a una farmacia.
     * @param f Puntero a la farmacia que recibe.
     * @param id_num ID del medicamento a suministrar.
     */


    /**
     * @brief Busca laboratorios que suministren un medicamento (por nombre P.A.).
     * @param nombrePA Nombre (o parte) del principio activo.
     * @return Vector de punteros a laboratorios únicos.
     */
/**
 * @brief Busca medicamentos por nombre en el stock GLOBAL de MediExpress.
 */
std::vector<PaMedicamentos*> MediExpress::buscarMedicamentoNombre(const std::string &nombre) {
    std::vector<PaMedicamentos*> v_resultados;

    // Iteramos sobre el std::map 'medication'
    // (it->first es el ID, it->second es el PaMedicamentos)
    for (std::map<int, PaMedicamentos>::iterator it = medication.begin(); it != medication.end(); it++) {

        // Comparamos el nombre del medicamento (it->second)
        if (it->second.getNombre().find(nombre) != std::string::npos) {
            // Si coincide, añadimos un puntero a ese medicamento
            v_resultados.push_back(&(it->second));
        }
    }

    return v_resultados;
}

/**
 * @brief Elimina un medicamento del sistema central y del stock de todas las farmacias.
 * @param id_num ID del medicamento a eliminar.
 * @return true si se encontró y eliminó, false en caso contrario.
 */
bool MediExpress::eliminaMedicamento(int id_num) {
    // 1. Eliminarlo del stock de todas las farmacias
    for (Farmacia &farma : pharmacy) {
        farma.eliminarStock(id_num);
    }

    // 2. Eliminarlo del map principal de MediExpress
    // .erase(key) devuelve el número de elementos eliminados (0 o 1 en un map)
    size_t borrados = medication.erase(id_num);

    return (borrados > 0);
}