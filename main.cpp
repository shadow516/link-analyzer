#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string processLink(const string& link, const string& archiveNumber) {
    const string prefix1 = "https://web.archive.org/web/" + archiveNumber + "/http://jump.5ch.net/?";
    const string prefix2 = "https://web.archive.org/web/" + archiveNumber + "/";

    size_t pos = link.find(prefix1);
    if (pos != string::npos) {
        return link.substr(pos + prefix1.length());
    }

    pos = link.find(prefix2);
    if (pos != string::npos) {
        return link.substr(pos + prefix2.length());
    }

    // Si no encuentra ninguno de los prefijos, devuelve el enlace original
    return link;
}

void checkeoIndividual(const string& archiveNumber) {
    string link;

    while (true) {
        cout << "Introduce el enlace (o '0' para salir): ";
        getline(cin, link);

        if (link == "0") {
            cout << "Saliendo del checkeo individual..." << endl;
            break;
        }

        string result = processLink(link, archiveNumber);
        cout << "Enlace procesado: " << result << endl;
    }
}

void checkeoMultiple(const string& archiveNumber) {
    string fileName;
    cout << "Introduce el nombre del fichero a abrir: ";
    getline(cin, fileName);

    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Error al abrir el fichero " << fileName << endl;
        return;
    }

    ofstream outputFile("Link.txt");
    if (!outputFile) {
        cerr << "Error al crear el fichero Link.txt" << endl;
        return;
    }

    string link;
    while (getline(inputFile, link)) {
        string result = processLink(link, archiveNumber);
        outputFile << result << endl;
    }

    cout << "Enlaces procesados y guardados en Link.txt" << endl;
}

int main() {
    string archiveNumber;
    while (true) {
        cout << "Menu:\n";
        cout << "1- Checkeo Individual\n";
        cout << "2- Checkeo Multiple\n";
        cout << "0- Salir\n";
        cout << "Introduce una opción: ";

        int option;
        cin >> option;
        cin.ignore(); // Para ignorar el salto de línea después de la entrada del número

        switch (option) {
            case 1:
                cout << "Introduce el número del archivo de archivo web (ej. 20220302063212): ";
                getline(cin, archiveNumber);
                checkeoIndividual(archiveNumber);
                break;
            case 2:
                cout << "Introduce el número del archivo de archivo web (ej. 20220302063212): ";
                getline(cin, archiveNumber);
                checkeoMultiple(archiveNumber);
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                return 0;
            default:
                cout << "Opción no válida. Por favor, introduce una opción válida.\n";
        }
    }
}
