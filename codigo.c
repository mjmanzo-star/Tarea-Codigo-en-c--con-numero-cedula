#include <iostream>
#include <string>
#include <windows.h>  
#include <stdlib.h>

using namespace std;

struct Persona {
    string cedula;
    string nombre;
    string apellido;
    float sueldo;
};

void gotoxy(int x, int y);
void titulos();
string pedirYValidar(int x, int y, string mensajeError, int tipoValidacion);
void insertar(Persona &per);
void impresion(Persona &per);

void gotoxy(int x, int y) {  
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y = y;  
    SetConsoleCursorPosition(hcon, dwPos);  
} 
void titulos() {
    system("cls");
    gotoxy(20, 4); cout << "INGRESO DE DATOS EN UNA ESTRUCTURA";
    gotoxy(10, 7); cout << "Cedula   : ";
    gotoxy(10, 8); cout << "Nombre   : ";
    gotoxy(10, 9); cout << "Apellido : ";
    gotoxy(10, 10);cout << "Sueldo   : ";
}

string pedirYValidar(int x, int y, string mensajeError, int tipoValidacion) {
    string entrada;
    bool error;

    do {
        error = false;
        gotoxy(x, y);
        cout << "        "; 
        gotoxy(x, y);
        getline(cin, entrada);

        if (entrada.empty()) {
            error = true;
        } 
  
        else if (tipoValidacion == 1) { 
            for (int i = 0; i < entrada.length(); i++) {
                if (isdigit(entrada[i])) { 
                    error = true;
                    break;
                }
            }
        } 
       
        else if (tipoValidacion == 2) {
            if (entrada.length() != 10) {
                error = true;
            } else {
                for (int i = 0; i < 10; i++) {
                    if (!isdigit(entrada[i])) error = true;
                }
            }
            if (!error) {
                int provincia = (entrada[0] - '0') * 10 + (entrada[1] - '0');
                if (provincia < 1 || provincia > 24) {
                    error = true;
                } else {
                    int coef[9] = {2, 1, 2, 1, 2, 1, 2, 1, 2};
                    int suma = 0;

                    for (int i = 0; i < 9; i++) {
                        int d = entrada[i] - '0';
                        int prod = d * coef[i];
                        
                        if (prod > 9) {
                            prod -= 9;
                        }
                        suma += prod;
                    }

                    int digitoOriginal = entrada[9] - '0';
                    int decenaSuperior = ((suma + 9) / 10) * 10;
                    int digitoCalculado = decenaSuperior - suma;

                    if (digitoCalculado == 10) {
                        digitoCalculado = 0;
                    }

                    if (digitoCalculado != digitoOriginal) {
                        error = true; 
                    }
                }
            }
        } 

        else if (tipoValidacion == 3) { 
            int puntos = 0;
            for (int i = 0; i < entrada.length(); i++) {
                if (entrada[i] == '.') {
                    puntos++;
                } else if (!isdigit(entrada[i])) {
                    error = true;
                }
            }
            if (puntos > 1) error = true; 
        }

        if (error) {
            gotoxy(10, 13); cout << "         ";
            gotoxy(10, 13); cout << "Error: " << mensajeError;
        } else {
            gotoxy(10, 13); cout << "         ";
        

    } while (error); 

    return entrada;
}
void insertar(Persona &per) {
    titulos();
    
    per.cedula   = pedirYValidar(22, 7, "Solo se aceptan numeros y una cedula valida. Intente de nuevo.", 2);
    per.nombre   = pedirYValidar(22, 8, "Solo se aceptan letras. Intente de nuevo.", 1);
    per.apellido = pedirYValidar(22, 9, "Solo se aceptan letras. Intente de nuevo.", 1);
    
    string sueldoStr = pedirYValidar(22, 10, "Solo se aceptan numeros enteros o decimales. Intente de nuevo.", 3);
    per.sueldo = atof(sueldoStr.c_str()); 
}

void impresion(Persona &per) {
    system("cls");
    gotoxy(20, 4); cout << "DATOS GUARDADOS EN LA ESTRUCTURA";
    gotoxy(10, 7); cout << "Cedula   : " << per.cedula;
    gotoxy(10, 8); cout << "Nombre   : " << per.nombre;
    gotoxy(10, 9); cout << "Apellido : " << per.apellido;
    gotoxy(10, 10);cout << "Sueldo   : $" << per.sueldo;
    gotoxy(10, 13);cout << "Presione ENTER para salir...";
    cin.get();
}

int main() {
    Persona persona;
    insertar(persona);
    impresion(persona);
    return 0;
}
