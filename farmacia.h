#include <fstream>
#include <chrono>
#include "producto.h"

using namespace std;

class Farmacia
{
    ofstream datos_estadisticos;
    Producto *nuevo, *aux, *inicio, *anterior;
public:
    Farmacia();
    void facturacion();
    void registrarProducto();
    void verProductos();
    void eliminar();
    void inventario();
    void guardar();
};