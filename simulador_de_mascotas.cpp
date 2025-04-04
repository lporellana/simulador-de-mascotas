#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;
/**
 * @class Mascota
 * @brief Representa una mascota virtual con atributos de energía, hambre y felicidad.
 */
class Mascota {
    
    private:
        string nombre; ///< Nombre de la mascota
        int energia; ///< Nivel de energía de la mascota
        int hambre; ///< Nivel de hambre de la mascota
        int felicidad; ///< Nivel de felicidad de la mascota
        
    public:
        /**
         * @brief Constructor por defecto.
         */

        Mascota(); 
        /**
         * 
         * @brief Constructor con parámetros.
         * @param _nombre Nombre de la mascota.
         * @param _energia Nivel inicial de energía.
         * @param _hambre Nivel inicial de hambre.
         * @param _felicidad Nivel inicial de felicidad.
         */        
        Mascota(string, int, int, int);

        /**
         * @brief Permite que la mascota coma, reduciendo hambre y aumentando energía.
         */
        void comer(){
            if (hambre > 0) {
                hambre --;
                energia ++;
                cout << nombre << " ha comido (^o^)" << endl;
            }
            else {
                cout << nombre << " no tiene hambre (^-^)" << endl;
            }
        }

        /**
         * @brief Permite que la mascota juegue, aumentando su felicidad y su hambre.
         */      
        void jugar(){
            if (energia > 0 && felicidad < 5) {
                energia --;
                felicidad ++;
                hambre ++;
                cout << nombre << " ha jugado (^-^)" << endl;
            }
            else {
                cout << nombre << " no tiene energía." << endl;
            }
        }

        /**
         * @brief Permite que la mascota duerma y recupere energía.
         */
        void dormir(){
            if (energia < 5) {
                energia ++;
                cout << nombre << " ha dormido (-_-)" << endl;
            }
            else {
                cout << nombre << " no tiene sueño (^-^)" << endl;
            }
        }

        /**
         * @brief Muestra el estado actual de la mascota en pantalla.
         */        
        void mostrar_estado(){
            cout << " " << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Energia: " << energia << endl;
            cout << "Hambre: " << hambre << endl;
            cout << "Felicidad: " << felicidad << endl;
            expresion();
        }

        /**
         * @brief Muestra la expresión de la mascota en base a su felicidad.
         */        
        void expresion(){
            if (felicidad > 3) {
                cout << ">(^..^)<" << endl;
                cout << "  (  )_ " << endl;
            }
            else {
              cout << "꒰(˶◞ ‸ ◟˶)꒱" << endl;
            }
        }

        /**
         * @brief Reduce progresivamente los atributos de la mascota con el tiempo.
         */
        void degradar() {
            while (true) {
                this_thread::sleep_for(chrono::seconds(20));
                if (hambre < 10) hambre++;
                if (felicidad > 0) felicidad--;
                if (energia > 0) energia--;
                cout << "Estado actualizado: ";
                mostrar_estado();
            }
        }

        //setters
        void set_nombre(string _nombre){
            nombre = _nombre;
        }
        void set_energia(int _energia){
            energia = _energia;
        }
        void set_hambre(int _hambre){
            hambre = _hambre;
        }
        void set_felicidad(int _felicidad){
            felicidad = _felicidad;
        } 
        
        //getters
        string get_nombre(){
            return nombre;
        }
        int get_energia(){
            return energia;
        }
        int get_hambre(){
            return hambre;
        }
        int get_felicidad(){
            return felicidad;
        }
};
    // Constructor inicialiado
    Mascota::Mascota(){
        nombre = "";
        energia = 0;
        hambre = 0;
        felicidad = 0;
    }
    
    // Constructor con parámetros
    Mascota::Mascota(string _nombre, int _energia, int _hambre, int _felicidad){
        nombre = _nombre;
        energia = _energia;
        hambre = _hambre;
        felicidad = _felicidad;
    }

/**
 * @brief Limpia la pantalla de la consola.
 */
void limpiar_pantalla() { cout << "\033[2J\033[H"; }

/**
 * @brief Pausa la ejecución por un tiempo determinado.
 * @param ms Milisegundos a esperar.
 */
void esperar(int ms) { for(clock_t t=clock(); (clock()-t)*1000/CLOCKS_PER_SEC < ms;); }

int main() {
    limpiar_pantalla();
    cout << "Bienvenido al simulador de mascotas!" << endl;

    cout << "Por favor, ingrese el nombre de su mascota: ";
    string nombre;
    cin >> nombre;

    Mascota ajolote(nombre, 3 , 0, 2);
    ajolote.mostrar_estado();

    thread hilo_estado(&Mascota::degradar, &ajolote);
    hilo_estado.detach();

    while (ajolote.get_felicidad() > 0) {
        cout << "¿Qué desea hacer? 1. Comer 2. Jugar 3. Dormir: " << endl;
        int opcion;
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                ajolote.comer();
                break;
            case 2:
                ajolote.jugar();
                break;
            case 3:
                ajolote.dormir();
                break;
            default:
                cout << "Opción inválida!" << endl;
                break;  
        }

        ajolote.mostrar_estado();
        esperar(2000);
    }

    limpiar_pantalla();
    cout << "Tu mascota ha muerto (T_T)" << endl;
    ajolote.mostrar_estado();
    esperar(2000);

    return 0;
}