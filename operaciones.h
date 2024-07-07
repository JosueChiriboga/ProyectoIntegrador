#define MAX_PRODUCTOS 100 // Número máximo de productos
#define MAX_NOMBRE 50 // Longitud máxima del nombre del producto
#define MAX_CLIENTES 100 // Número máximo de clientes
#define MAX_FACTURAS 100 // Número máximo de facturas

//PROTOTIPOS
void agregarProducto(char[][MAX_NOMBRE], int[], float[], int*);
void imprimirProductos(char[][MAX_NOMBRE], int[], float[], int);
void buscarProducto(char[][MAX_NOMBRE], int[], float[], int);
void modificarProducto(char[][MAX_NOMBRE], int[], float[], int);
void eliminarProducto(char[][MAX_NOMBRE], int[], float[], int*);
void adicionarStock(char[][MAX_NOMBRE], int[], float[], int);
void mostrarMenu();

bool verificarCedula(int[]);
void ingresarCedula(char*);
int validarCedula(char*);

void agregarCliente(char[][MAX_NOMBRE], char[][MAX_NOMBRE], char[][11], int*);
void imprimirClientes(char[][MAX_NOMBRE], char[][MAX_NOMBRE], char[][11], int);
void buscarCliente(char[][MAX_NOMBRE], char[][MAX_NOMBRE], char[][11], int);
void modificarCliente(char[][MAX_NOMBRE], char[][MAX_NOMBRE], char[][11], int);

void facturar(char[][MAX_NOMBRE], int[], float[], int, char[][MAX_NOMBRE], char[][MAX_NOMBRE], char[][11], int, char[][MAX_NOMBRE], char[][MAX_NOMBRE], char[][11], float[], int[], int*);
void buscarFactura(char[][MAX_NOMBRE], char[][MAX_NOMBRE], char[][11], float[], int[], int);
void imprimirFacturas(char[][MAX_NOMBRE], char[][MAX_NOMBRE], char[][11], float[], int[], int);