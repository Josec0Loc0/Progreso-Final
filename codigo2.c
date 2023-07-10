#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de estructura estudiantes 
struct Estudiante {
    int num;
    char nombre[50];
    char carrera[50];
    float nota1;
    float nota2;
    float nota3;
    float promedio;
};

// Funciones
void calcularProm(struct Estudiante* estudiante);
void imprimirEstu(struct Estudiante* estudiantes, int numEstudiantes, FILE* archivo);
void liberarMemoria(struct Estudiante* estudiantes);

int main() {
    FILE* archivoEntrada;
    FILE* archivoSalida;
    struct Estudiante* estudiantes;
    int numEstudiantes;
    int i;

    // Abrir archivo de entrada 
    archivoEntrada = fopen("alumnos.txt", "r");
    if (archivoEntrada == NULL) {
        printf("No se pudo abrir el archivo de entrada.\n");
        return 1;
    }


    numEstudiantes = 0;
    char buffer[500];
    while (fgets(buffer, sizeof(buffer), archivoEntrada) != NULL) {
        numEstudiantes++;
    }


    fseek(archivoEntrada, 0, SEEK_SET);


    estudiantes = (struct Estudiante*)malloc(numEstudiantes * sizeof(struct Estudiante));
    for (i = 0; i < numEstudiantes; i++) {
        fscanf(archivoEntrada, "%d;%[^;];%[^;];%f;%f;%f\n", &estudiantes[i].num, estudiantes[i].nombre, estudiantes[i].carrera, &estudiantes[i].nota1, &estudiantes[i].nota2, &estudiantes[i].nota3);
        calcularProm(&estudiantes[i]);
    }

 
    fclose(archivoEntrada);


    archivoSalida = fopen("alumnos_ordenados.txt", "w");
    if (archivoSalida == NULL) {
        printf("No se pudo abrir el archivo de salida.\n");
        liberarMemoria(estudiantes);
        return 1;
    }

    
    imprimirEstu(estudiantes, numEstudiantes, archivoSalida);

    // Cerrar el archivo
    fclose(archivoSalida);

    // Liberar memoria estud
    liberarMemoria(estudiantes);

    printf("El archivo ha sido creado exitosamente.\n");

    return 0;
}

// Función para calcular el promedio
void calcularProm(struct Estudiante* estudiante) {
    estudiante->promedio = (estudiante->nota1 + estudiante->nota2 + estudiante->nota3) / 3;
}

// Función para imprimir los estudiantes de manera ordenada
void imprimirEstu(struct Estudiante* estudiantes, int numEstudiantes, FILE* archivo) {
    int i;
    for (i = numEstudiantes - 1; i >= 0; i--) {
        fprintf(archivo, "%d;%s;%s;%.2f;%.2f;%.2f;%.2f\n", estudiantes[i].num, estudiantes[i].nombre, estudiantes[i].carrera, estudiantes[i].nota1, estudiantes[i].nota2, estudiantes[i].nota3, estudiantes[i].promedio);
    }
}

// Función para liberar la memoria de estud
void liberarMemoria(struct Estudiante* estudiantes) {
    free(estudiantes);
}


