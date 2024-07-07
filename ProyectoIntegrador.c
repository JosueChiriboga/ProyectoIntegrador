/*Universidad De Las Américas
Integrantes: Josue Chiriboga
             Nicole Yepez
             Gustavo Zarate
Semana: 15
Actividad: Proyecto Integrador (Sistema de Inventario)
Fecha: 07/07/2024 */
#include <stdio.h>    // Biblioteca estándar de entrada/salida.
#include <string.h>   // Biblioteca para operaciones con cadenas.
#include <stdbool.h>  // Biblioteca para utilizar el tipo de datos booleano.
#include <time.h>     // Biblioteca para funciones relacionadas con el tiempo.

#include "lecturas.h"
#include "operaciones.h"

int main() {
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE]; // Arreglo para nombres de productos
    int cantidades[MAX_PRODUCTOS]; // Arreglo para cantidades de productos
    float precios[MAX_PRODUCTOS]; // Arreglo para precios de productos
    int numProductos = 0; // Numero actual de productos

    char clientesNombres[MAX_CLIENTES][MAX_NOMBRE];
    char clientesApellidos[MAX_CLIENTES][MAX_NOMBRE];
    char clientesCedulas[MAX_CLIENTES][11];
    int numClientes = 0;

    char facturasNombres[MAX_FACTURAS][MAX_NOMBRE];
    char facturasApellidos[MAX_FACTURAS][MAX_NOMBRE];
    char facturasCedulas[MAX_FACTURAS][11];
    float facturasValores[MAX_FACTURAS];
    int facturasCantidades[MAX_FACTURAS];
    int numFacturas = 0;

    int opcion; // Opcion seleccionada por el usuario

    FILE *archivo; // Puntero a archivo

    // Abre el archivo de productos
    archivo = fopen("Productos.txt", "a+");
    if (archivo == NULL) { // Verifica si se abrio el archivo
        printf("No fue posible abrir el archivo de productos\n");
        return 1;
    }

    // Lee los datos del archivo de productos y los carga en memoria
    rewind(archivo); // Coloca el cursor al inicio del archivo
    while (fscanf(archivo, "Nombre:%s\nCantidad:%d\nPrecio:%f\n\n", nombres[numProductos], &cantidades[numProductos], &precios[numProductos]) != EOF) {
        numProductos++;
    }
    fclose(archivo);

    // Abre el archivo de clientes
    archivo = fopen("Clientes.txt", "a+");
    if (archivo == NULL) { // Verifica si se abrio el archivo
        printf("No fue posible abrir el archivo de clientes\n");
        return 1;
    }

    // Lee los datos del archivo de clientes y los carga en memoria
    rewind(archivo); // Coloca el cursor al inicio del archivo
    while (fscanf(archivo, "Cedula:%s\nNombre:%s\nApellido:%s\n\n", clientesCedulas[numClientes], clientesNombres[numClientes], clientesApellidos[numClientes]) != EOF) {
        numClientes++;
    }
    fclose(archivo);

    // Abre el archivo de facturas
    archivo = fopen("Facturas.txt", "a+");
    if (archivo == NULL) { // Verifica si se abrio el archivo
        printf("No fue posible abrir el archivo de facturas\n");
        return 1;
    }

    // Lee los datos del archivo de facturas y los carga en memoria
    rewind(archivo); // Coloca el cursor al inicio del archivo
    while (fscanf(archivo, "Cedula:%s\nNombre:%s\nApellido:%s\nValor:%f\nCantidad:%d\n\n", facturasCedulas[numFacturas], facturasNombres[numFacturas], facturasApellidos[numFacturas], &facturasValores[numFacturas], &facturasCantidades[numFacturas]) != EOF) {
        numFacturas++;
    }
    fclose(archivo);

    do {
        mostrarMenu();
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarProducto(nombres, cantidades, precios, &numProductos);
                break;
            case 2:
                imprimirProductos(nombres, cantidades, precios, numProductos);
                break;
            case 3:
                buscarProducto(nombres, cantidades, precios, numProductos);
                break;
            case 4:
                modificarProducto(nombres, cantidades, precios, numProductos);
                break;
            case 5:
                eliminarProducto(nombres, cantidades, precios, &numProductos);
                break;
            case 6:
                adicionarStock(nombres, cantidades, precios, numProductos);
                break;
            case 7:
                agregarCliente(clientesNombres, clientesApellidos, clientesCedulas, &numClientes);
                break;
            case 8:
                modificarCliente(clientesNombres, clientesApellidos, clientesCedulas, numClientes);
                break;
            case 9:
                buscarCliente(clientesNombres, clientesApellidos, clientesCedulas, numClientes);
                break;
            case 10:
                imprimirClientes(clientesNombres, clientesApellidos, clientesCedulas, numClientes);
                break;
            case 11:
                facturar(nombres, cantidades, precios, numProductos, clientesNombres, clientesApellidos, clientesCedulas, numClientes, facturasNombres, facturasApellidos, facturasCedulas, facturasValores, facturasCantidades, &numFacturas);
                break;
            case 12:
                buscarFactura(facturasNombres, facturasApellidos, facturasCedulas, facturasValores, facturasCantidades, numFacturas);
                break;
            case 13:
                imprimirFacturas(facturasNombres, facturasApellidos, facturasCedulas, facturasValores, facturasCantidades, numFacturas);
                break;
            case 14:
                printf("\nCerrando Sistema de Inventario\n");
                break;
            default:
                printf("\nOpcion incorrecta. Ingrese nuevamente.\n");
        }
    } while (opcion != 14);

    return 0;
}

void mostrarMenu() {
    printf("\n-----------------SISTEMA DE INVENTARIO-----------------\n");
    printf("1. Ingresar producto\n");
    printf("2. Imprimir productos\n");
    printf("3. Buscar producto\n");
    printf("4. Modificar producto\n");
    printf("5. Eliminar producto\n");
    printf("6. Adicionar compra Producto (aumentar stock)\n");
    printf("7. Ingresar cliente\n");
    printf("8. Modificar cliente\n");
    printf("9. Consultar cliente\n");
    printf("10. Ver listado de clientes\n");
    printf("11. Facturar\n");
    printf("12. Buscar factura\n");
    printf("13. Ver listado de facturas\n");
    printf("14. Salir\n");
}