#include <stdio.h>    // Biblioteca estándar de entrada/salida.
#include <string.h>   // Biblioteca para operaciones con cadenas.
#include <stdbool.h>  // Biblioteca para utilizar el tipo de datos booleano.
#include <time.h>     // Biblioteca para funciones relacionadas con el tiempo.

#include "operaciones.h"
#include "lecturas.h"

void agregarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int *numProductos) {
    
    // Verificar si el numero de productos actuales es menor que el maximo permitido
    if (*numProductos < MAX_PRODUCTOS) {
        char nombre[MAX_NOMBRE]; // Declara una variable para almacenar el nombre del nuevo producto

        // Solicitar al usuario que ingrese el nombre del producto
        printf("Ingrese el nombre del producto: ");
        scanf("%s", nombre);

        // Recorrer el arreglo de nombres para verificar si el nombre ya existe
        for (int i = 0; i < *numProductos; i++) {
            if (strcmp(nombres[i], nombre) == 0) { // Compara el nombre ingresado con los existentes
                printf("Producto con el mismo nombre ya existe.\n"); // Informa si el producto ya existe
                return; // Sale de la función si se encuentra un nombre duplicado
            }
        }

        // Copia el nombre del nuevo producto en el arreglo de nombres
        strcpy(nombres[*numProductos], nombre);

        // Solicita al usuario que ingrese la cantidad del producto
        printf("Ingrese la cantidad del producto: ");
        scanf("%d", &cantidades[*numProductos]);

        // Solicita al usuario que ingrese el precio del producto
        printf("Ingrese el precio del producto: ");
        scanf("%f", &precios[*numProductos]);

        // Abre el archivo "Productos.txt" en modo de añadir
        FILE *archivo = fopen("Productos.txt", "a+");
        // Escribe los detalles del nuevo producto en el archivo
        fprintf(archivo, "Nombre:%s\nCantidad:%d\nPrecio:%.2f\n\n", nombres[*numProductos], cantidades[*numProductos], precios[*numProductos]);
        fclose(archivo); // Cierra el archivo

        printf("Producto registrado exitosamente\n"); // Informa al usuario que el producto fue registrado

        (*numProductos)++; // Incrementa el contador de productos
    } else {
        // Informa al usuario que no se pueden agregar más productos
        printf("No se pueden agregar mas productos. Se ha alcanzado el limite.\n");
    }
}


void imprimirProductos(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int numProductos) {
    
    // Imprime un encabezado para la lista de productos registrados
    printf("\nProductos registrados:\n");
    
    // Recorre todos los productos registrados
    for (int i = 0; i < numProductos; i++) {
        // Imprime el nombre del producto en la posición actual
        printf("Nombre: %s\n", nombres[i]);
        // Imprime la cantidad del producto en la posición actual
        printf("Cantidad: %d\n", cantidades[i]);
        // Imprime el precio del producto en la posición actual
        printf("Precio: %.2f\n", precios[i]);
        // Imprime una línea en blanco para separar los productos
        printf("\n");
    }
}


void buscarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int numProductos) {
    
    // Solicita al usuario que ingrese el nombre del producto a buscar
    printf("\nIngrese el nombre del producto a buscar: ");
    char nombreBuscar[MAX_NOMBRE]; // Declara una variable para almacenar el nombre del producto a buscar
    scanf("%s", nombreBuscar); // Lee el nombre ingresado por el usuario
    int encontrado = 0; // Variable para indicar si el producto fue encontrado
    
    // Recorre todos los productos registrados
    for (int i = 0; i < numProductos; i++) {
        // Compara el nombre del producto actual con el nombre buscado
        if (strcmp(nombres[i], nombreBuscar) == 0) {
            // Si se encuentra el producto, imprime los detalles
            printf("Producto encontrado:\n");
            printf("Nombre: %s\n", nombres[i]);
            printf("Cantidad: %d\n", cantidades[i]);
            printf("Precio: %.2f\n", precios[i]);
            encontrado = 1; // Marca que el producto fue encontrado
            break; // Sale del ciclo porque el producto fue encontrado
        }
    }
    // Si el producto no fue encontrado, imprime un mensaje informando al usuario
    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}


void modificarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int numProductos) {
    
    // Solicita al usuario que ingrese el nombre del producto a modificar
    printf("\nIngrese el nombre del producto a modificar: ");
    char nombreModificar[MAX_NOMBRE]; // Declara una variable para almacenar el nombre del producto a modificar
    scanf("%s", nombreModificar); // Lee el nombre ingresado por el usuario
    int encontrado = 0; // Variable para indicar si el producto fue encontrado
    
    // Recorre todos los productos registrados
    for (int i = 0; i < numProductos; i++) {
        // Compara el nombre del producto actual con el nombre a modificar
        if (strcmp(nombres[i], nombreModificar) == 0) {
            // Si se encuentra el producto, solicita la nueva cantidad y precio
            printf("Producto encontrado. Ingrese la nueva cantidad: ");
            scanf("%d", &cantidades[i]);
            printf("Ingrese el nuevo precio: ");
            scanf("%f", &precios[i]);
            // Abre el archivo "Productos.txt" en modo de escritura (se sobrescribe el archivo)
            FILE *archivo = fopen("Productos.txt", "w");
            // Escribe los detalles de todos los productos en el archivo
            for (int j = 0; j < numProductos; j++) {
                fprintf(archivo, "Nombre:%s\nCantidad:%d\nPrecio:%.2f\n\n", nombres[j], cantidades[j], precios[j]);
            }
            fclose(archivo); // Cierra el archivo
            printf("Producto modificado exitosamente\n"); // Informa al usuario que el producto fue modificado
            encontrado = 1; // Marca que el producto fue encontrado
            break; // Sale del ciclo porque el producto fue encontrado y modificado
        }
    }
    // Si el producto no fue encontrado, imprime un mensaje informando al usuario
    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}


void eliminarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int *numProductos) {
    
    // Solicita al usuario que ingrese el nombre del producto a eliminar
    printf("\nIngrese el nombre del producto a eliminar: ");
    char nombreEliminar[MAX_NOMBRE]; // Declara una variable para almacenar el nombre del producto a eliminar
    scanf("%s", nombreEliminar); // Lee el nombre ingresado por el usuario
    int encontrado = 0; // Variable para indicar si el producto fue encontrado
    
    // Recorre todos los productos registrados
    for (int i = 0; i < *numProductos; i++) {
        // Compara el nombre del producto actual con el nombre a eliminar
        if (strcmp(nombres[i], nombreEliminar) == 0) {
            // Si se encuentra el producto, se procede a eliminarlo desplazando los elementos siguientes hacia atras
            for (int j = i; j < *numProductos - 1; j++) {
                // Copia el nombre, cantidad y precio del siguiente producto en la posicion actual
                strcpy(nombres[j], nombres[j + 1]);
                cantidades[j] = cantidades[j + 1];
                precios[j] = precios[j + 1];
            }
            (*numProductos)--; // Decrementa el numero total de productos
            
            // Abre el archivo "Productos.txt" en modo de escritura (se sobrescribe el archivo)
            FILE *archivo = fopen("Productos.txt", "w");
            
            // Escribe los detalles de todos los productos en el archivo actualizado
            for (int j = 0; j < *numProductos; j++) {
                fprintf(archivo, "Nombre:%s\nCantidad:%d\nPrecio:%.2f\n\n", nombres[j], cantidades[j], precios[j]);
            }
            fclose(archivo); // Cierra el archivo
            printf("Producto eliminado exitosamente\n"); // Informa al usuario que el producto fue eliminado
            encontrado = 1; // Marca que el producto fue encontrado
            break; // Sale del ciclo porque el producto fue encontrado y eliminado
        }
    }
    
    // Si el producto no fue encontrado, imprime un mensaje informando al usuario
    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}


void adicionarStock(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int numProductos) {
    
    // Solicita al usuario que ingrese el nombre del producto al cual desea aumentar el stock
    printf("\nIngrese el nombre del producto al cual desea aumentar el stock: ");
    char nombreStock[MAX_NOMBRE]; // Declara una variable para almacenar el nombre del producto
    scanf("%s", nombreStock); // Lee el nombre ingresado por el usuario

    int encontrado = 0; // Variable para indicar si el producto fue encontrado

    // Recorre todos los productos registrados
    for (int i = 0; i < numProductos; i++) {
        // Compara el nombre del producto actual con el nombre ingresado por el usuario
        if (strcmp(nombres[i], nombreStock) == 0) {
            // Si se encuentra el producto, solicita la cantidad adicional
            printf("Producto encontrado. Ingrese la cantidad adicional: ");
            int cantidadAdicional; // Declara una variable para almacenar la cantidad adicional
            scanf("%d", &cantidadAdicional); // Lee la cantidad ingresada por el usuario

            // Aumenta la cantidad del producto
            cantidades[i] += cantidadAdicional;

            // Abre el archivo "Productos.txt" en modo de escritura (se sobrescribe el archivo)
            FILE *archivo = fopen("Productos.txt", "w");
            
            // Escribe los detalles de todos los productos en el archivo actualizado
            for (int j = 0; j < numProductos; j++) {
                fprintf(archivo, "Nombre:%s\nCantidad:%d\nPrecio:%.2f\n\n", nombres[j], cantidades[j], precios[j]);
            }
            fclose(archivo); // Cierra el archivo

            printf("Stock del producto actualizado exitosamente\n"); // Informa al usuario que el stock fue actualizado
            encontrado = 1; // Marca que el producto fue encontrado
            break; // Sale del ciclo porque el producto fue encontrado y su stock actualizado
        }
    }
    // Si el producto no fue encontrado, imprime un mensaje informando al usuario
    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}


bool verificarCedula(int vect[]) {
    int i, r, s = 0, s1 = 0, st = 0;
    // Calcula la suma ponderada de los digitos segun el algoritmo de verificación de cedula
    for (i = 0; i < 10; i = i + 2) {
        r = vect[i] * 2;
        if (r > 9) r -= 9;
        s += r;
    }
    // Calcula la suma de los digitos no ponderados
    for (i = 1; i < 9; i = i + 2) {
        s1 += vect[i];
    }
    // Calcula el digito verificador
    st = 10 - ((s + s1) % 10);
    if (st == 10) st = 0;
    // Retorna verdadero si el digito verificador calculado coincide con el ultimo digito de la cedula
    return vect[9] == st;
}


void ingresarCedula(char *cedula) {
    printf("Ingrese la cedula: ");
    scanf("%s", cedula); // Lee la cedula ingresada por el usuario
}

int validarCedula(char *cedula) {
    int tam = strlen(cedula);
    if (tam != 10) return 1; // Verifica que la cedula tenga exactamente 10 caracteres
    int cedint[10];
    for (int i = 0; i < 10; i++) {
        if (cedula[i] >= '0' && cedula[i] <= '9') {
            cedint[i] = cedula[i] - '0'; // Convierte cada caracter numerico de la cedula a un entero
        } else {
            return 1; // Si algun caracter no es un digito, la cedula no es valida
        }
    }
    return verificarCedula(cedint) ? 0 : 1; // Llama a la funcion verificarCedula para validar la cedula
}


void agregarCliente(char nombres[][MAX_NOMBRE], char apellidos[][MAX_NOMBRE], char cedulas[][11], int *numClientes) {
    
    // Verifica si aún se pueden agregar mas clientes
    if (*numClientes < MAX_CLIENTES) {
        char cedula[11];
        ingresarCedula(cedula); // Solicita al usuario ingresar la cedula
        // Valida la cedula ingresada
        if (validarCedula(cedula) != 0) {
            printf("Cedula no valida.\n");
            return; // Si la cédula no es valida, termina la función
        }
        
        // Verifica si ya existe un cliente con la misma cedula
        for (int i = 0; i < *numClientes; i++) {
            if (strcmp(cedulas[i], cedula) == 0) {
                printf("Cliente con la misma cedula ya existe.\n");
                return; // Si ya existe un cliente con la misma cedula, termina la funcion
            }
        }
        
        // Almacena la cedula, nombre y apellido del cliente
        strcpy(cedulas[*numClientes], cedula);
        printf("Ingrese el nombre del cliente: ");
        scanf("%s", nombres[*numClientes]);
        printf("Ingrese el apellido del cliente: ");
        scanf("%s", apellidos[*numClientes]);

        // Abre el archivo "Clientes.txt" en modo de añadir y escribir
        FILE *archivo = fopen("Clientes.txt", "a+");
        
        // Escribe los detalles del nuevo cliente en el archivo
        fprintf(archivo, "Cedula:%s\nNombre:%s\nApellido:%s\n\n", cedulas[*numClientes], nombres[*numClientes], apellidos[*numClientes]);
        fclose(archivo); // Cierra el archivo despues de escribir

        printf("Cliente registrado exitosamente\n"); // Informa al usuario que el cliente fue registrado
        (*numClientes)++; // Incrementa el contador de clientes
    } else {
        printf("No se pueden agregar mas clientes. Se ha alcanzado el limite.\n");
    }
}


void imprimirClientes(char nombres[][MAX_NOMBRE], char apellidos[][MAX_NOMBRE], char cedulas[][11], int numClientes) {
    printf("\nClientes registrados:\n");
    
    // Recorre todos los clientes registrados y muestra sus detalles
    for (int i = 0; i < numClientes; i++) {
        printf("Cedula: %s\n", cedulas[i]);
        printf("Nombre: %s\n", nombres[i]);
        printf("Apellido: %s\n", apellidos[i]);
        printf("\n");
    }
}


void buscarCliente(char nombres[][MAX_NOMBRE], char apellidos[][MAX_NOMBRE], char cedulas[][11], int numClientes) {
    printf("\nIngrese la cedula del cliente a buscar: ");
    char cedulaBuscar[11];
    scanf("%s", cedulaBuscar);

    int encontrado = 0; // Variable para indicar si se encontro al cliente

    // Recorre todos los clientes registrados
    for (int i = 0; i < numClientes; i++) {
        // Compara la cédula del cliente actual con la cedula ingresada por el usuario
        if (strcmp(cedulas[i], cedulaBuscar) == 0) {
            printf("Cliente encontrado:\n");
            printf("Cedula: %s\n", cedulas[i]);
            printf("Nombre: %s\n", nombres[i]);
            printf("Apellido: %s\n", apellidos[i]);
            encontrado = 1; // Marca que se encontro al cliente
            break; // Sale del ciclo porque se encontro al cliente buscado
        }
    }
    // Si no se encontro al cliente, muestra un mensaje indicandolo
    if (!encontrado) {
        printf("Cliente no encontrado.\n");
    }
}


void modificarCliente(char nombres[][MAX_NOMBRE], char apellidos[][MAX_NOMBRE], char cedulas[][11], int numClientes) {
    printf("\nIngrese la cedula del cliente a modificar: ");
    char cedulaModificar[11];
    scanf("%s", cedulaModificar);

    int encontrado = 0; // Variable para indicar si se encontro al cliente

    // Recorre todos los clientes registrados
    for (int i = 0; i < numClientes; i++) {
        // Compara la cedula del cliente actual con la cedula ingresada por el usuario
        if (strcmp(cedulas[i], cedulaModificar) == 0) {
            printf("Cliente encontrado. Ingrese el nuevo nombre: ");
            scanf("%s", nombres[i]); // Solicita y guarda el nuevo nombre del cliente
            printf("Ingrese el nuevo apellido: ");
            scanf("%s", apellidos[i]); // Solicita y guarda el nuevo apellido del cliente

            // Abre el archivo "Clientes.txt" en modo de escribir (sobrescribe el contenido)
            FILE *archivo = fopen("Clientes.txt", "w");
            // Recorre todos los clientes y escribe sus detalles actualizados en el archivo
            for (int j = 0; j < numClientes; j++) {
                fprintf(archivo, "Cedula:%s\nNombre:%s\nApellido:%s\n\n", cedulas[j], nombres[j], apellidos[j]);
            }
            fclose(archivo); // Cierra el archivo despues de escribir

            printf("Cliente modificado exitosamente\n"); // Informa al usuario que el cliente fue modificado
            encontrado = 1; // Marca que se encontro al cliente
            break; // Sale del ciclo porque se encontro al cliente buscado
        }
    }

    // Si no se encontro al cliente, muestra un mensaje indicandolo
    if (!encontrado) {
        printf("Cliente no encontrado.\n");
    }
}


void facturar(char productosNombres[][MAX_NOMBRE], int productosCantidades[], float productosPrecios[], int numProductos,
              char clientesNombres[][MAX_NOMBRE], char clientesApellidos[][MAX_NOMBRE], char clientesCedulas[][11], int numClientes,
              char facturasNombres[][MAX_NOMBRE], char facturasApellidos[][MAX_NOMBRE], char facturasCedulas[][11], float facturasValores[], int facturasCantidades[], int *numFacturas) {
    if (*numFacturas < MAX_FACTURAS) { // Verifica que no se haya alcanzado el limite de facturas
        printf("Ingrese la cedula del cliente: ");
        char cedulaCliente[11];
        scanf("%s", cedulaCliente);
        
        int clienteEncontrado = 0; // Variable para indicar si se encontro al cliente
        int clienteIndice = -1; // indice del cliente encontrado
        
        // Busca al cliente por su cedula entre los clientes registrados
        for (int i = 0; i < numClientes; i++) {
            if (strcmp(clientesCedulas[i], cedulaCliente) == 0) {
                clienteEncontrado = 1; // Marca que se encontro al cliente
                clienteIndice = i; // Guarda el indice del cliente encontrado
                break; // Sale del ciclo porque se encontró al cliente buscado
            }
        }
        
        // Si no se encontro al cliente, muestra un mensaje y termina la funcion
        if (!clienteEncontrado) {
            printf("Cliente no encontrado.\n");
            return;
        }

        // Si se encontro al cliente, procede a facturar el producto
        printf("Ingrese el nombre del producto: ");
        char nombreProducto[MAX_NOMBRE];
        scanf("%s", nombreProducto);

        int productoEncontrado = 0; // Variable para indicar si se encontro el producto
        int productoIndice = -1; // indice del producto encontrado
        
        // Busca el producto por su nombre entre los productos registrados
        for (int i = 0; i < numProductos; i++) {
            if (strcmp(productosNombres[i], nombreProducto) == 0) {
                productoEncontrado = 1; // Marca que se encontro el producto
                productoIndice = i; // Guarda el indice del producto encontrado
                break; // Sale del ciclo porque se encontro el producto buscado
            }
        }
        
        // Si no se encontro el producto, muestra un mensaje y termina la funcion
        if (!productoEncontrado) {
            printf("Producto no encontrado.\n");
            return;
        }

        // Solicita la cantidad a facturar del producto
        printf("Ingrese la cantidad a facturar: ");
        int cantidadFacturar;
        scanf("%d", &cantidadFacturar);

        // Verifica si hay suficiente cantidad en stock para facturar
        if (productosCantidades[productoIndice] < cantidadFacturar) {
            printf("Cantidad insuficiente en stock.\n");
            return;
        }

        // Actualiza la cantidad en stock del producto
        productosCantidades[productoIndice] -= cantidadFacturar;

        // Calcula el valor total de la factura
        float valorFactura = cantidadFacturar * productosPrecios[productoIndice];

        // Guarda los detalles de la factura en los arreglos correspondientes
        strcpy(facturasNombres[*numFacturas], clientesNombres[clienteIndice]);
        strcpy(facturasApellidos[*numFacturas], clientesApellidos[clienteIndice]);
        strcpy(facturasCedulas[*numFacturas], clientesCedulas[clienteIndice]);
        facturasValores[*numFacturas] = valorFactura;
        facturasCantidades[*numFacturas] = cantidadFacturar;

        // Obtener la fecha actual
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char fecha[11];
        snprintf(fecha, 11, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

        // Abre el archivo "Facturas.txt" en modo de agregar contenido ("a+")
        FILE *archivo = fopen("Facturas.txt", "a+");
        
        // Escribe los detalles de la factura en el archivo
        fprintf(archivo, "Fecha: %s\nCedula:%s\nNombre:%s\nApellido:%s\nValor:%.2f\nCantidad:%d\n\n",
                fecha, facturasCedulas[*numFacturas], facturasNombres[*numFacturas], facturasApellidos[*numFacturas],
                facturasValores[*numFacturas], facturasCantidades[*numFacturas]);
        fclose(archivo); // Cierra el archivo despues de escribir

        // Informa al usuario que la factura se genero exitosamente
        printf("Factura generada exitosamente. Valor total: %.2f\n", valorFactura);

        (*numFacturas)++; // Incrementa el contador de facturas
    } else {
        printf("No se pueden generar mas facturas. Se ha alcanzado el limite.\n");
    }
}


void buscarFactura(char facturasNombres[][MAX_NOMBRE], char facturasApellidos[][MAX_NOMBRE], char facturasCedulas[][11], float facturasValores[], int facturasCantidades[], int numFacturas) {
    // Solicita al usuario ingresar la cedula de la factura a buscar
    printf("\nIngrese la cedula de la factura a buscar: ");
    char cedulaBuscar[11];
    scanf("%s", cedulaBuscar);
    
    int encontrado = 0; // Variable para verificar si se encontro la factura

    // Recorre todas las facturas registradas
    for (int i = 0; i < numFacturas; i++) {
        // Compara la cedula ingresada con la cedula de cada factura
        if (strcmp(facturasCedulas[i], cedulaBuscar) == 0) {
            // Si la cedula coincide, imprime los detalles de la factura
            printf("Factura encontrada:\n");
            printf("Cedula: %s\n", facturasCedulas[i]);
            printf("Nombre: %s\n", facturasNombres[i]);
            printf("Apellido: %s\n", facturasApellidos[i]);
            printf("Valor: %.2f\n", facturasValores[i]);
            printf("Cantidad: %d\n", facturasCantidades[i]);
            encontrado = 1; // Marca que se encontro la factura
            break; // Sale del bucle porque ya se encontro la factura
        }
    }

    // Si no se encontro ninguna factura con la cedula ingresada, imprime un mensaje
    if (!encontrado) {
        printf("Factura no encontrada.\n");
    }
}


void imprimirFacturas(char facturasNombres[][MAX_NOMBRE], char facturasApellidos[][MAX_NOMBRE], char facturasCedulas[][11], float facturasValores[], int facturasCantidades[], int numFacturas) {
    // Imprime el encabezado para las facturas registradas
    printf("\nFacturas registradas:\n");

    // Recorre todas las facturas registradas
    for (int i = 0; i < numFacturas; i++) {
        // Imprime los detalles de cada factura
        printf("Cedula: %s\n", facturasCedulas[i]);
        printf("Nombre: %s\n", facturasNombres[i]);
        printf("Apellido: %s\n", facturasApellidos[i]);
        printf("Valor: %.2f\n", facturasValores[i]);
        printf("Cantidad: %d\n", facturasCantidades[i]);
        printf("\n");
    }
}