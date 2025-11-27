#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
class NodoValor {
public:
	string valor;
	NodoValor* siguiente;
	NodoValor() : valor(""), siguiente(nullptr) {}
	NodoValor(const string& v) : valor(v), siguiente(nullptr) {}
};
class ListaValores {
private:
	NodoValor* cabeza;
public:
	ListaValores() : cabeza(nullptr) {}
	~ListaValores() {
		while (cabeza != nullptr) {
			NodoValor* temp = cabeza;
			cabeza = cabeza->siguiente;
			delete temp;
		}
	}
	void agregarFinal(const string& v) {
		NodoValor* nuevo = new NodoValor(v);
		if (!cabeza) cabeza = nuevo;
		else {
			NodoValor* aux = cabeza; while (aux->siguiente) aux = aux->siguiente; aux->siguiente
				= nuevo;
		}
	}
	int contar() {
		int c = 0; NodoValor* aux = cabeza; while (aux) { c++; aux = aux->siguiente; } return
			c;
	}
	string obtener(int pos) {
		NodoValor* aux = cabeza; for (int i = 0; i < pos && aux; i++) aux =
			aux->siguiente; return aux ? aux->valor : "";
	}
	void modificar(int pos, const string& nuevo) {
		NodoValor* aux = cabeza; for (int i = 0; i < pos &&
			aux; i++) aux = aux->siguiente; if (aux) aux->valor = nuevo;
	}
	friend ostream& operator<<(ostream& out, ListaValores& lv) {
		NodoValor* aux = lv.cabeza; out << "[";
		while (aux) {
			out << "\"" << aux->valor << "\""; if (aux->siguiente) out << ", "; aux =
				aux->siguiente;
		}
		out << "]"; return out;
	}
};
class Campo {
public:
	string nombreCampo;
	string tipoDato;
	int tamano;
	Campo() : nombreCampo(""), tipoDato(""), tamano(0) {}
	void ingresarCampo();
	void mostrarCampo();
};
void Campo::ingresarCampo() {
	cout << "Nombre del campo: ";
	getline(cin, nombreCampo);
	cout << "Tipo de dato (int/float/char/string): "; cin >> tipoDato;
	if (tipoDato == "char" || tipoDato == "string") {
		cout << "Tamano (max. caracteres): ";
		while (!(cin >> tamano)) {
			cout << "Entrada invalida. Por favor, ingrese un NUMERO ENTERO: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	else {
		tamano = 0;
	}
	cin.ignore();
}
void Campo::mostrarCampo() {
	cout << "Nombre: " << nombreCampo
		<< " | Tipo: " << tipoDato
		<< " | Tamano: " << tamano << endl;
}
class NodoCampo {
public:
	Campo campo;
	NodoCampo* siguiente;
	NodoCampo() : siguiente(nullptr) {}
};
class ListaCampos {
private:
	NodoCampo* cabeza;
public:
	ListaCampos() : cabeza(nullptr) {}
	~ListaCampos() {
		while (cabeza != nullptr) {
			NodoCampo* temp = cabeza;
			cabeza = cabeza->siguiente;
			delete temp;
		}
	}
	void agregarCampo() {
		NodoCampo* nuevo = new NodoCampo();
		nuevo->campo.ingresarCampo();
		if (!cabeza) cabeza = nuevo;
		else {
			NodoCampo* aux = cabeza; while (aux->siguiente) aux = aux->siguiente;
			aux->siguiente = nuevo;
		}
	}
	void mostrarCampos() {
		NodoCampo* aux = cabeza; int i = 1;
		while (aux) {
			cout << "Campo " << i++ << ": "; aux->campo.mostrarCampo(); aux =
				aux->siguiente;
		}
	}
	int contarCampos() {
		int c = 0; NodoCampo* aux = cabeza; while (aux) {
			c++; aux =
				aux->siguiente;
		} return c;
	}
	bool modificarCampo(const string& nombre) {
		NodoCampo* aux = cabeza;
		while (aux) {
			if (aux->campo.nombreCampo == nombre) {
				cout << "Modificando campo '" << nombre << "'...\n";
				aux->campo.ingresarCampo();
				return true;
			}
			aux = aux->siguiente;
		}
		return false;
	}
	bool existeCampo(const string& nombre) {
		NodoCampo* aux = cabeza;
		while (aux) {
			if (aux->campo.nombreCampo == nombre) return true;
			aux = aux->siguiente;
		}
		return false;
	}
	Campo obtenerCampo(int pos) {
		NodoCampo* aux = cabeza; for (int i = 0; i < pos && aux; i++)
			aux = aux->siguiente; return aux ? aux->campo : Campo();
	}
};
class Dato {
private:
	ListaValores valores;
public:
	void ingresarDato(ListaCampos& campos);
	void mostrarDato(ListaCampos& campos);
	void modificarDato(ListaCampos& campos);
	ListaValores& getValores() { return valores; }
};
void Dato::ingresarDato(ListaCampos& campos) {
	int n = campos.contarCampos();
	for (int i = 0; i < n; i++) {
		Campo c = campos.obtenerCampo(i);
		cout << "Valor para [" << c.nombreCampo << "] (" << c.tipoDato << "): ";
		string val;
		getline(cin, val);
		valores.agregarFinal(val);
	}
}
void Dato::mostrarDato(ListaCampos& campos) {
	int n = campos.contarCampos();
	cout << "{ ";
	for (int i = 0; i < n; i++) {
		Campo c = campos.obtenerCampo(i);
		cout << c.nombreCampo << "=" << valores.obtener(i);
		if (i < n - 1) cout << ", ";
	}
	cout << " }" << endl;
}
void Dato::modificarDato(ListaCampos& campos) {
	int n = campos.contarCampos();
	cout << "Que campo desea modificar? (1-" << n << "): ";
	int pos;
	cin >> pos;
	if (pos < 1 || pos > n) {
		cout << "Posicion invalida.\n";
		return;
	}
	Campo c = campos.obtenerCampo(pos - 1);
	cout << "Nuevo valor para [" << c.nombreCampo << "]: ";
	string nuevo;
	cin.ignore();
	getline(cin, nuevo);
	valores.modificar(pos - 1, nuevo);
}
class NodoDato {
public:
	Dato dato;
	NodoDato* siguiente;
	NodoDato() : siguiente(nullptr) {}
};
class ListaDatos {
private:
	NodoDato* cabeza;
public:
	ListaDatos() : cabeza(nullptr) {}
	~ListaDatos() {
		while (cabeza != nullptr) {
			NodoDato* temp = cabeza; cabeza =
				cabeza->siguiente; delete temp;
		}
	}
	void agregarDato(ListaCampos& campos) {
		NodoDato* nuevo = new NodoDato();
		nuevo->dato.ingresarDato(campos);
		if (!cabeza) cabeza = nuevo;
		else {
			NodoDato* aux = cabeza; while (aux->siguiente) aux = aux->siguiente; aux->siguiente
				= nuevo;
		}
	}
	void mostrarDatos(ListaCampos& campos) {
		NodoDato* aux = cabeza; int i = 1;
		while (aux) {
			cout << "Registro " << i++ << ": "; aux->dato.mostrarDato(campos); aux =
				aux->siguiente;
		}
		if (i == 1) cout << "(No hay registros)\n";
	}
	int contarDatos() {
		int c = 0; NodoDato* aux = cabeza; while (aux) { c++; aux = aux->siguiente; }
		return c;
	}
	bool modificarDato(ListaCampos& campos) {
		if (!cabeza) { cout << "No hay registros para modificar.\n"; return false; }
		cout << "\n--- REGISTROS EXISTENTES ---\n";
		mostrarDatos(campos);
		cout << "----------------------------\n";
		cout << "Que registro desea modificar? (1-" << contarDatos() << "): ";
		int reg;
		cin >> reg;
		if (reg < 1) return false;
		NodoDato* aux = cabeza;
		for (int i = 1; i < reg && aux; i++) aux = aux->siguiente;
		if (!aux) { cout << "Registro no encontrado.\n"; return false; }
		aux->dato.modificarDato(campos);
		return true;
	}
};
class Cabecera {
public:
	string nombreArchivo;
	string descripcion;
	string fechaCreacion;
	int numCampos;
	int numRegistros;
	Cabecera() : nombreArchivo(""), descripcion(""), fechaCreacion(""), numCampos(0),
		numRegistros(0) {
	}
	void ingresarCabecera();
	void mostrarCabecera();
	void actualizarCampos(int n) { numCampos = n; }
	void actualizarRegistros(int n) { numRegistros = n; }
};
void Cabecera::ingresarCabecera() {
	cout << "Nombre del archivo: "; cin >> nombreArchivo;
	cin.ignore();
	cout << "Descripcion breve: "; getline(cin, descripcion);
}
void Cabecera::mostrarCabecera() {
	cout << "\n=== CABECERA ===\n";
	cout << "Nombre: " << nombreArchivo << endl;
	cout << "Descripcion: " << descripcion << endl;
	time_t now = time(0);
	fechaCreacion = ctime(&now);
	cout << "Fecha creacion: " << fechaCreacion << endl;
	cout << "N° Campos: " << numCampos << endl;
	cout << "N° Registros: " << numRegistros << endl;
	cout << "================\n";
}
class ArchivoRAM {
public:
	Cabecera cabecera;
	ListaCampos listaCampos;
	ListaDatos listaDatos;
	void crearArchivo();
	void mostrarCabecera() { cabecera.mostrarCabecera(); }
	void mostrarCampos() { listaCampos.mostrarCampos(); }
	void mostrarDatos() { listaDatos.mostrarDatos(listaCampos); }
	bool modificarCampo() {
		cout << "\n----------CAMPOS EXISTENTES----------\n";
		listaCampos.mostrarCampos();
		cout << "---------------------------------------\n";
		string nom;
		cout << "Nombre del campo a modificar: ";
		cin.ignore();
		getline(cin, nom);
		if (!listaCampos.existeCampo(nom)) {
			cout << "Campo no encontrado.\n";
			return false;
		}
		return listaCampos.modificarCampo(nom);
	}
	bool modificarDato() { return listaDatos.modificarDato(listaCampos); }
};
void ArchivoRAM::crearArchivo() {
	cabecera.ingresarCabecera();
	cout << "\n--- Ingresar CAMPOS ---\n";
	char resp;
	do {
		listaCampos.agregarCampo();
		do {
			cout << "Agregar otro campo? (s/n): ";
			cin >> resp;
			if (resp != 's' && resp != 'S' && resp != 'n' && resp != 'N') {
				cout << "Opcion invalida. Por favor ingrese 's' o 'n'.\n";
			}
		} while (resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
		cin.ignore();
	} while (resp == 's' || resp == 'S');
	cabecera.actualizarCampos(listaCampos.contarCampos());
	cout << "\n--- Ingresar REGISTROS (datos) ---\n";
	do {
		listaDatos.agregarDato(listaCampos);
		do {
			cout << "Agregar otro registro? (s/n): ";
			cin >> resp;
			if (resp != 's' && resp != 'S' && resp != 'n' && resp != 'N') {
				cout << "Opcion invalida. Por favor ingrese 's' o 'n'.\n";
			}
		} while (resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
		cin.ignore();
	} while (resp == 's' || resp == 'S');
	cabecera.actualizarRegistros(listaDatos.contarDatos());
}
class NodoArchivo {
public:
	ArchivoRAM archivo;
	NodoArchivo* siguiente;
	NodoArchivo() : siguiente(nullptr) {}
};
class ListaArchivos {
private:
	NodoArchivo* cabeza;
public:
	ListaArchivos() : cabeza(nullptr) {}
	~ListaArchivos() {
		while (cabeza != nullptr) {
			NodoArchivo* temp = cabeza; cabeza =
				cabeza->siguiente; delete temp;
		}
	}
	void crearNuevoArchivo() {
		NodoArchivo* nuevo = new NodoArchivo();
		nuevo->archivo.crearArchivo();
		if (!cabeza) cabeza = nuevo;
		else {
			NodoArchivo* aux = cabeza; while (aux->siguiente) aux = aux->siguiente;
			aux->siguiente = nuevo;
		}
		cout << "\n Archivo creado exitosamente.\n";
	}
	ArchivoRAM* buscarArchivo(const string& nombre) {
		NodoArchivo* aux = cabeza;
		while (aux) {
			if (aux->archivo.cabecera.nombreArchivo == nombre) return &(aux->archivo);
			aux = aux->siguiente;
		}
		return nullptr;
	}
	void mostrarArchivos() {
		if (!cabeza) { cout << "\n(No hay archivos creados)\n"; return; }
		NodoArchivo* aux = cabeza;
		cout << "\n=== ARCHIVOS EN MEMORIA ===\n";
		while (aux) {
			cout << "• " << aux->archivo.cabecera.nombreArchivo
				<< " (" << aux->archivo.cabecera.fechaCreacion << ")\n";
			aux = aux->siguiente;
		}
		cout << "============================\n";
	}
};
class SubMenuArchivo {
public:
	void mostrarSubMenu(ArchivoRAM* archivo);
};
void SubMenuArchivo::mostrarSubMenu(ArchivoRAM* archivo) {
	if (!archivo) return;
	int sub;
	string nombre = archivo->cabecera.nombreArchivo;
	do {
		cout << "\n--- SUBMENU (" << nombre << ") ---\n";
		cout << "1. Mostrar cabecera\n";
		cout << "2. Mostrar lista de campos\n";
		cout << "3. Mostrar datos\n";
		cout << "4. Modificar campo\n";
		cout << "5. Modificar dato\n";
		cout << "6. Volver al menu principal\n";
		cout << "Opcion: ";
		cin >> sub;
		switch (sub) {
		case 1: archivo->mostrarCabecera(); system("pause"); break;
		case 2: archivo->mostrarCampos(); system("pause"); break;
		case 3: archivo->mostrarDatos(); system("pause"); break;
		case 4: archivo->modificarCampo(); system("pause"); break;
		case 5: archivo->modificarDato(); system("pause"); break;
		case 6: break;
		default: cout << "Opcion invalida.\n";
		}
	} while (sub != 6);
}
class MenuPrincipal {
private:
	ListaArchivos listaArchivos;
	SubMenuArchivo subMenu;
	void opcionCrearArchivo() {
		listaArchivos.crearNuevoArchivo();
	}
	void opcionSeleccionarArchivo() {
		string nombre;
		cout << "Nombre del archivo a usar: ";
		cin.ignore();
		getline(cin, nombre);
		ArchivoRAM* archivo = listaArchivos.buscarArchivo(nombre);
		if (!archivo) {
			cout << "\n Archivo no encontrado.\n";
			return;
		}
		subMenu.mostrarSubMenu(archivo);
	}
	void opcionListarArchivos() {
		listaArchivos.mostrarArchivos();
		system("pause");
	}
public:
	void ejecutar();
};
void MenuPrincipal::ejecutar() {
	int opcion;
	do {
		cout << "\n=== MENU PRINCIPAL ===\n";
		cout << "1. Crear nuevo archivo\n";
		cout << "2. Seleccionar archivo existente\n";
		cout << "3. Listar archivos\n";
		cout << "4. Salir\n";
		cout << "Opcion: ";
		cin >> opcion;
		switch (opcion) {
		case 1:
			opcionCrearArchivo();
			break;
		case 2:
			opcionSeleccionarArchivo();
			break;
		case 3:
			opcionListarArchivos();
			break;
		case 4:
			cout << "\nSaliendo y liberando la memoria.\n";
			break;
		default:
			cout << "\nOpcion invalida.\n";
		}
	} while (opcion != 4);
}
int main() {
	MenuPrincipal menu;
	menu.ejecutar();
	return 0;
}

