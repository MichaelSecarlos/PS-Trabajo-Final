#include <iostream>

#include "farmacia.h"

using namespace std;

int main()
{
    //Objeto farmacia
    Farmacia farm;

	int op;
	do {
		cout << "Menu Principal" << endl;
		cout << "1.Facturacion" << endl;
		cout << "2.Inventario" << endl;
		cout << "0.Salir" << endl;
		cin >> op;

		switch(op)
		{
            case 0: break;
			case 1:
                system("cls||clear");
                farm.facturacion();
                system("cls||clear");
                break;
			case 2:
                system("cls||clear");
                farm.inventario();
                break;
            default:
                cout<<"Comando invalido"<<endl;
        }
	}while(op!= 0);

}