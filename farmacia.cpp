#include <stdlib.h>
#include "farmacia.h"

Farmacia::Farmacia()
{
    //File Stream de salida, para la escritura de los datos
    datos_estadisticos.open("datos.csv");
    datos_estadisticos<<"operacion, tiempo total\n";
    
    //Punteros
	inicio = NULL;
	aux = NULL;
	nuevo = NULL;
	cout<<"Sistema de Farmacia"<<endl;
	cin.get();
}

void Farmacia::facturacion()
{
    //Tiempo de inicio
    auto tiempo_inicio = chrono::system_clock::now();
    
    //Operacion de facturacion
    float precioVenta=0;
	int codigo;
	do
    {
		cout << "Ingrese el codigo del producto, si desea terminar, ingrese 0: " << endl;
		cin>>codigo;
        aux = inicio;
        anterior = NULL;
        //Buscamos el producto
        while(aux != NULL && aux->codigo != codigo && codigo != 0)
        {
            anterior = aux;
            aux = aux->ptrsig;
        }
        //Si existe el producto
        if(aux == NULL && codigo != 0)
            cout << "Producto no encontrado..." << endl;
        else
        {
            //Si aun hay existencias de ese producto
            if(aux->cantidad>0)
            {
                precioVenta=precioVenta+aux->precio;
                aux->cantidad=aux->cantidad-1;
                //En caso ya no haya mas stock de ese producto
                if(aux->cantidad == 0)
                {
                    if(anterior == NULL)
                        inicio = inicio->ptrsig;
                    else
                        anterior->ptrsig = aux->ptrsig;
                }
            }
            //Si no hay existencias
            else
            {
                cout<<"No hay suficientes productos de este tipo: "<<aux->codigo<<endl;
            }
        }
	} while(codigo!=0);
	cout<<"El precio a pagar es: "<<precioVenta<<endl;
    
    cin.get();
    cin.get();

    //Tiempo final
    auto tiempo_final = chrono::high_resolution_clock::now();
    
    //Escritura del tiempo
    datos_estadisticos<<"facturacion, "<< chrono::duration_cast<chrono::milliseconds>(tiempo_final-tiempo_inicio).count()<<endl;
}
void Farmacia::registrarProducto()
{
    //Tiempo de inicio
    auto tiempo_inicio = chrono::system_clock::now();
    
    //Operacion de registro de producto
	if (inicio == NULL)
	{
		cout << "Este es el primer nodo que vas a crear" << endl;
		nuevo = new (Producto);

		cout << "---Registrando Producto---" << endl;
		cout << "Codigo: " ;
		cin >> nuevo->codigo;
		cout << "Laboratorio: ";
		cin >> nuevo->laboratorio;
		cout << "Cantidad de productos: ";
		cin >> nuevo->cantidad;
		cout << "Precio: ";
		cin >> nuevo->precio;
		inicio = nuevo;
		aux = nuevo;
		nuevo->ptrsig = NULL;
		cin.get();
	}
	else
    {
		nuevo = new(Producto);
		cout << "---Registrando Producto---" << endl;
		cout << "Codigo: " ;
		cin >> nuevo->codigo;
		cout << "Laboratorio: ";
		cin >> nuevo->laboratorio;
		cout << "Cantidad de productos: ";
		cin >> nuevo->cantidad;
		cout << "Precio: ";
		cin >> nuevo->precio;
		if(inicio->codigo > nuevo->codigo)
		{
			nuevo->ptrsig = inicio;
			inicio = nuevo;
		}
		else
		{
			aux = inicio;
			while(aux->ptrsig != NULL && aux->ptrsig->codigo <= nuevo->codigo)
			{
				aux = aux->ptrsig;
			}
			nuevo->ptrsig = aux->ptrsig;
			aux->ptrsig = nuevo;
		}
	}
    //Tiempo final
    auto tiempo_final = chrono::high_resolution_clock::now();
    
    //Escritura del tiempo
    datos_estadisticos<<"registrar, "<< chrono::duration_cast<chrono::milliseconds>(tiempo_final-tiempo_inicio).count()<<endl;
}
void Farmacia::verProductos()
{
    //Tiempo de inicio
    auto tiempo_inicio = chrono::system_clock::now();
    
    //Operacion de vista de productos
	if(inicio == NULL)
	{
		cout << "No hay productos" << endl;
	}
	else
    {
        aux = inicio;
        while (aux != NULL)
        {
            cout<<aux->codigo <<" "<< aux->laboratorio <<" "<< aux->cantidad <<" "<<aux->precio << endl;
            aux = aux->ptrsig;
        }
    }
	cin.get();
	cin.get();
    
    //Tiempo final
    auto tiempo_final = chrono::high_resolution_clock::now();
    
    //Escritura del tiempo
    datos_estadisticos<<"ver, "<< chrono::duration_cast<chrono::milliseconds>(tiempo_final-tiempo_inicio).count()<<endl;

}
void Farmacia::eliminar()
{
    //Tiempo de inicio
    auto tiempo_inicio = chrono::system_clock::now();
    
	int codigo;
	cout << "Ingrese el codigo del producto: ";
	cin >> codigo;
	if(inicio == NULL)
	{
		cout  << "No ha ingresado ningun medicamento." << endl;
	}
	else
	{
		aux = inicio;
		anterior = NULL;
		while(aux != NULL && aux->codigo != codigo)
		{
			anterior = aux;
			aux = aux->ptrsig;
		}
		if(aux == NULL)
		{
			cout << "Producto no encontrado..." << endl;
		}
		else
		{
			if(anterior == NULL)
			{
				inicio = inicio->ptrsig;
			}
			else
			{
				anterior->ptrsig = aux->ptrsig;
			}
			delete(aux);
			cout << "Producto Eliminado!"<< endl;
		}
	}
	cin.get();

    //Tiempo final
    auto tiempo_final = chrono::high_resolution_clock::now();
    
    //Escritura del tiempo
    datos_estadisticos<<"eliminar, "<< chrono::duration_cast<chrono::milliseconds>(tiempo_final-tiempo_inicio).count()<<endl;
}
void Farmacia::inventario()
{
    //Tiempo de inicio
    auto tiempo_inicio = chrono::system_clock::now();
    
    //Operacion de inventario
	system("cls||clear");
	int op;
	do{
        cout << "1.Agregar nuevo producto" << endl;
        cout << "2.Eliminar Producto" << endl;
        cout << "3.Ver todos los productos" << endl;
        cout << "0.Regresar" << endl;
        cin >> op;

        switch(op)
        {
            case 0:
                system("cls||clear");
                break;
                system("cls||clear");
            case 1:
                system("cls||clear");
                registrarProducto();
                system("cls||clear");
                break;
            case 2:
                system("cls||clear");
                eliminar();
                system("cls||clear");
                break;
            case 3:
                system("cls||clear");
                verProductos();
                system("cls||clear");
                break;
        }
	} while(op!=0);
    //Tiempo final
    auto tiempo_final = chrono::high_resolution_clock::now();
    
    //Escritura del tiempo
    datos_estadisticos<<"inventario, "<< chrono::duration_cast<chrono::milliseconds>(tiempo_final-tiempo_inicio).count()<<endl;
}
void Farmacia::guardar()
{
    datos_estadisticos.close();
}
