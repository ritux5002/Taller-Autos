#include <stdio.h>
#include <string.h>

#define MAX_AUTOS 5
#define MAX_CLIENTES 2

// Enumeracion para el tipo de auto
typedef enum {
    SEDAN,
    SUV,
    HATCHBACK,
    PICKUP,
    TIPO_INVALIDO
} TipoAuto;

// Estructura para la venta
struct venta {
    char autos[MAX_AUTOS][20]; 
    int precio[MAX_AUTOS];
    TipoAuto tipo[MAX_AUTOS]; // Agregar tipo de auto
};

// Estructura para el cliente
struct cliente {
    char nombre[20];
    int dni;
    float precio;  
    char detalle[500];
    char telefono[15]; // Agregar numero de telefono
};

// Funcion para buscar clientes
void buscardatos(struct cliente clientes[], int totalClientes) {
    int dni;

    printf("--MENU DE BUSQUEDA--\n");
    printf("Ingrese el documento del cliente: ");
    while (scanf("%d", &dni) != 1) {
        printf("Entrada invalida. Ingrese un numero valido para el DNI: ");
        while (getchar() != '\n');
    }

    int found = 0; 
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].dni == dni) {
            found = 1;
            printf("Nombre: %s\n", clientes[i].nombre);
            printf("Telefono: %s\n", clientes[i].telefono);
            printf("Precio: %.2f\n", clientes[i].precio);
            printf("Detalle: %s\n", clientes[i].detalle);
            break;
        }
    }

    if (!found) {
        printf("No hay entregas con ese DNI\n");
    }
}

// Funcion para cargar clientes
void cargarCliente(struct cliente clientes[], int i) {
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", clientes[i].nombre);

    printf("Ingrese el DNI del cliente: ");
    while (scanf("%d", &clientes[i].dni) != 1) {
        printf("Entrada invalida. Ingrese un numero valido para el DNI: ");
        while (getchar() != '\n'); 
    }

    printf("Ingrese el numero de telefono del cliente: ");
    scanf("%s", clientes[i].telefono); // Solicitar numero de telefono

    printf("Ingrese el precio del trabajo a realizar: ");
    while (scanf("%f", &clientes[i].precio) != 1) {
        printf("Entrada invalida. Ingrese un numero valido para el precio: ");
        while (getchar() != '\n'); 
    }

    printf("Ingrese el detalle del arreglo: ");
    scanf(" %[^\n]", clientes[i].detalle);  
}

// Funcion para mostrar la lista de clientes
void mostrarClientes(struct cliente clientes[], int totalClientes) {
    printf("Lista de Clientes:\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("%d. Nombre: %s, DNI: %d, Telefono: %s, Precio: %.2f, Detalle: %s\n", 
               i + 1, clientes[i].nombre, clientes[i].dni, clientes[i].telefono, clientes[i].precio, clientes[i].detalle);
    }
}

// Funcion para cargar autos
TipoAuto seleccionarTipoAuto() {
    int tipo;
    printf("Seleccione el tipo de auto:\n");
    printf("0: Sedan\n");
    printf("1: SUV\n");
    printf("2: Hatchback\n");
    printf("3: Pickup\n");
    printf("Ingrese su opcion: ");
    while (scanf("%d", &tipo) != 1 || tipo < 0 || tipo > 3) {
        printf("Entrada invalida. Ingrese un numero valido (0-3): ");
        while (getchar() != '\n');
    }
    return (TipoAuto)tipo;
}

// Funcion para cargar autos en venta
void cargarAutos(struct venta *ventas, int *totalAutos) {
    for (int i = 0; i < MAX_AUTOS; i++) {
        printf("Ingrese el nombre del auto a la venta: ");
        scanf("%s", ventas->autos[i]);

        printf("Ingrese el precio del auto: ");
        while (scanf("%d", &ventas->precio[i]) != 1) {
            printf("Entrada invalida. Ingrese un numero valido para el precio: ");
            while (getchar() != '\n'); 
        }

        ventas->tipo[i] = seleccionarTipoAuto(); // Seleccionar el tipo de auto

        (*totalAutos)++;  

        // Preguntar si se desea continuar cargando autos
        if (i < MAX_AUTOS - 1) {
            char continuar;
            printf("Desea cargar otro auto? (s/n): ");
            while (getchar() != '\n');
            scanf("%c", &continuar);
            if (continuar != 's' && continuar != 'S') {
                break; 
            }
        }
    }
}

// Funcion para mostrar autos en venta
void mostrarAutos(struct venta *ventas, int totalAutos) {
    printf("--- Autos en venta ---\n");
    for (int i = 0; i < totalAutos; i++) {
        printf("Auto: %s, Precio: %d, Tipo: ", ventas->autos[i], ventas->precio[i]);
        switch (ventas->tipo[i]) {
            case SEDAN: printf("Sedan\n"); break;
            case SUV: printf("SUV\n"); break;
            case HATCHBACK: printf("Hatchback\n"); break;
            case PICKUP: printf("Pickup\n"); break;
            default: printf("Tipo desconocido\n"); break;
        }
    }
}

// Menu principal
int main() {
    struct venta ventas;
    struct cliente clientes[MAX_CLIENTES];
    int op;
    int totalClientes = 0;
    int totalAutos = 0;  

    FILE *fptr;

    do {
        printf("---MENU PRINCIPAL---\n");
        printf("1. Cargar cliente\n");
        printf("2. Buscar cliente\n");
        printf("3. Mostrar lista de clientes\n");
        printf("4. Cargar autos en venta\n");
        printf("5. Menu de compra\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");

        while (scanf("%d", &op) != 1) {
            printf("Entrada invalida. Seleccione un numero valido: ");
            while (getchar() != '\n'); 
        }

        switch (op) {
            case 1:
                if (totalClientes < MAX_CLIENTES) {
                    cargarCliente(clientes, totalClientes);
                    totalClientes++;
                } else {
                    printf("No se pueden cargar mas clientes.\n");
                }
                break;
            case 2:
                buscardatos(clientes, totalClientes);
                break;
            case 3:
                mostrarClientes(clientes, totalClientes);
                break;
            case 4:    
                cargarAutos(&ventas, &totalAutos); // Cargar autos
                break;
            case 5: {
                int opA;
                printf("--MENU DE COMPRA--\n");
                printf("1. Ver autos a la venta\n");
                printf("2. Generar comprobante de compra\n");
                printf("Seleccione una opcion: ");

                while (scanf("%d", &opA) != 1) {
                    printf("Entrada invalida. Seleccione un numero valido: ");
                    while (getchar() != '\n'); 
                }

                switch(opA) {
                    case 1:
                        if (totalAutos == 0) {
                            printf("No hay autos a la venta\n");
                        } else {
                            mostrarAutos(&ventas, totalAutos); // Mostrar autos
                        }
                        break;
                    case 2: {
                        char autocom[20], nomVen[20];
                        float precio;

                        printf("Ingrese el auto que desea comprar: ");
                        scanf("%s", autocom);
                        printf("Ingrese nombre de vendedor: ");
                        scanf("%s", nomVen);
                        printf("Ingrese el precio del vehiculo: ");
                        while (scanf("%f", &precio) != 1) {
                            printf("Entrada invalida. Ingrese un numero valido para el precio: ");
                            while (getchar() != '\n'); 
                        }

                        fptr = fopen("COMPRA.txt", "w");
                        if (fptr == NULL) {
                            printf("Error al abrir el archivo.\n");
                            return 1; 
                        }
                        fprintf(fptr, "----FACTURA DE COMPRA----\n");
                        fprintf(fptr, "----Auto a vender: %s\n", autocom);
                        fprintf(fptr, "Se recibio el pago de %.2f en pesos\n", precio);    
                        fprintf(fptr, "Nombre del vendedor: %s\n", nomVen); 
                        fclose(fptr);
                        printf("Comprobante generado exitosamente.\n");
                    }
                    break;
                    default:
                        printf("Opcion no valida.\n");
                        break;
                }
            }
            break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida.\n");
                break;
        }
    } while (op != 6);

    return 0;
}

