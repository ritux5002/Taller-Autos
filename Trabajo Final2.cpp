#include <stdio.h>

#define MAX_AUTOS 5
#define MAX_CLIENTES 2

struct venta {
    char autos[MAX_AUTOS][20]; 
    int precio[MAX_AUTOS];
};

struct cliente {
    char nombre[20];
    int dni;
    float precio;  
    char detalle[500];
};
//funcion para buscas clientes

void buscardatos(struct cliente clientes[], int totalClientes) {
    int dni;
    
    printf("--MENU DE BUSQUEDA--\n");
    printf("Ingrese el documento del cliente: ");
    scanf("%d", &dni);
    
    int found = 0; 
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].dni == dni) {
            found = 1;
            printf("Nombre: %s\n", clientes[i].nombre);
            printf("Precio: %.2f\n", clientes[i].precio);
            printf("Detalle: %s\n", clientes[i].detalle);
            break;
        }
    }
    
    if (!found) {
        printf("No hay entregas con ese DNI\n");
    }
}
//funcion para cargar clientes
void cargarCliente(struct cliente clientes[], int i) {
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", clientes[i].nombre);
    
    printf("Ingrese el DNI del cliente: ");
    scanf("%d", &clientes[i].dni);
    
    printf("Ingrese el precio del trabajo a realizar: ");
    scanf("%f", &clientes[i].precio);
    
    printf("Ingrese el detalle del arreglo: ");
    scanf(" %[^\n]", clientes[i].detalle);  
}
//Menu principal

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
        printf("2. Buscar clientes\n");
        printf("3. Cargar autos en venta\n");
        printf("4. Menu de Compra\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                if (totalClientes < MAX_CLIENTES) {
                    cargarCliente(clientes, totalClientes);
                    totalClientes++;
                } else {
                    printf("No se pueden cargar más clientes.\n");
                }
                break;
            case 2:
                buscardatos(clientes, totalClientes);
                break;
            case 3:    
                for (int i = 0; i < MAX_AUTOS; i++) {
                    printf("Ingrese el nombre del auto a la venta: ");
                    scanf("%s", ventas.autos[i]); 
                    
                    printf("Ingrese el precio del auto: ");
                    scanf("%d", &ventas.precio[i]); 
                    totalAutos++;  ]
                }
                break;
            case 4:
                {
                    int opA;
                    printf("--MENU DE COMPRA--\n");
                    printf("1. Ver autos a la venta\n");
                    printf("2. Generar Comprobante de Compra\n");
                    printf("Seleccione una opción: ");
                    scanf("%d", &opA);

                    switch(opA) {
                        case 1:
                            if (totalAutos == 0) {
                                printf("No hay autos a la venta\n");
                            } else {
                                printf("--- Autos en venta ---\n");
                                for (int i = 0; i < totalAutos; i++) {
                                    printf("Auto: %s, Precio: %d\n", ventas.autos[i], ventas.precio[i]);
                                }
                            }
                            break;
                        case 2:
                            {
                                char autocom[20], nomVen[20];
                                float precio;

                                printf("Ingrese el auto que desea comprar: ");
                                scanf("%s", autocom);
                                printf("Ingrese Nombre de Vendedor: ");
                                scanf("%s", nomVen);
                                printf("Ingrese el precio del vehículo: ");
                                scanf("%f", &precio);

                                fptr = fopen("COMPRA.txt", "w");
                                if (fptr == NULL) {
                                    printf("Error al abrir el archivo.\n");
                                    return 1; 
                                }
                                fprintf(fptr, "----FACTURA DE COMPRA----\n");
                                fprintf(fptr, "----Auto a vender: %s\n", autocom);
                                fprintf(fptr, "Se recibió el pago de %.2f en pesos\n", precio);    
                                fprintf(fptr, "Nombre del vendedor: %s\n", nomVen); 
                                fclose(fptr);
                                printf("Comprobante generado exitosamente.\n");
                            }
                            break;
                        default:
                            printf("Opción no válida.\n");
                            break;
                    }
                }
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }

    } while (op != 5);

    return 0;
}
