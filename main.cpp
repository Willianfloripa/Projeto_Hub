#include <iostream> //Bliblioteca padrão
#include <string> //Bliblioteca para uso string
#include <vector> //Bliblioteca para uso do for nas portas
#include <cstdlib> // Bliblioteca para uso limpaTela

using namespace std;

void limpaTela() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux ou MacOS
    #endif
}

// Classe criada para a conexão das portas do HUB
class Porta {
private:
    bool ocupada;
    string equipamento;
public:
    Porta() : ocupada(false), equipamento("") {}
    //Função retorna se a porta está ocupada    
    bool isOcupada() const {
        return ocupada;
    }
    //Função de conexão ao HUB onde ao conectar ele verifica se a porta está ocupada e caso não anexa um equipamento a porta.
    void conectar(const string& equip) {
        if (ocupada) {
            cout << "Porta ja esta ocupada!" << endl;
        } else {
            equipamento = equip;
            ocupada = true;
            cout << "Equipamento '" << equipamento << "' conectado a porta." << endl;
        }
    }
    //Função desconectar verifica se há algo na porta e caso haja desconecta.
    void desconectar() {
        if (!ocupada) {
            cout << "Porta ja esta vazia!" << endl;
        } else {
            cout << "Equipamento '" << equipamento << "' desconectado da porta." << endl;
            ocupada = false;
            equipamento = "";
        }
    }
    //Exibe os equipamentos conectados
    void exibirStatus(int numero) const {
        if (ocupada) {
            cout << "Porta " << numero << ": " << equipamento << " conectado" << endl;
        } else {
            cout << "Porta " << numero << ": Vazia" << endl;
        }
    }
};

class Hub {
private:
    vector<Porta> portas;
    bool ligado;

//Função onde o equipamento inicia desligado e com um vector porta de 5
public:
    Hub() : ligado(false), portas(5) {}  // Inicializa 5 portas

    //Função que liga o equipamento caso não esteja ligado.
    void ligar() {
        if (ligado) {
            cout << "O hub ja esta ligado!" << endl;
        } else {
            ligado = true;
            cout << "Hub ligado!" << endl;
        }
    }
    // Função que identifica que está ligado e desliga
    void desligar() {
        if (!ligado) {
            cout << "O hub ja esta desligado!" << endl;
        } else {
            ligado = false;
            cout << "Hub desligado!" << endl;
        }
    }

    // Função que conecta equipamento a porta selecionando porta, equipamento string
    void conectar(int porta, const string& equipamento) {
        if (!ligado) {
            cout << "O hub esta desligado. Ligue o hub primeiro!" << endl;
            return;
        }
        if (porta < 1 || porta > 5) {
            cout << "Porta invalida!" << endl;
        } else {
            portas[porta - 1].conectar(equipamento);
        }
    }

    //Função que desconecta o equipamento da porta pelo numero da porta
    void desconectar(int porta) {
        if (!ligado) {
            cout << "O hub esta desligado. Ligue o hub primeiro!" << endl;
            return;
        }
        if (porta < 1 || porta > 5) {
            cout << "Porta invalida!" << endl;
        } else {
            portas[porta - 1].desconectar();
        }
    }

    //Função que exibe o status de cada porta
    void exibirStatus() const {
        if (!ligado) {
            cout << "O hub esta desligado!" << endl;
        } else {
            cout << "Status das portas:" << endl;
            for (int i = 0; i < 5; ++i) {
                portas[i].exibirStatus(i + 1);
            }
        }
    }
};

int main() {
    Hub hub;
    int opcao, porta;
    string equipamento;

    do {
        cout << "\nMenu do Hub\n";
        cout << "1. Ligar Hub\n";
        cout << "2. Desligar Hub\n";
        cout << "3. Conectar equipamento\n";
        cout << "4. Desconectar equipamento\n";
        cout << "5. Exibir status das portas\n";
        cout << "6. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        limpaTela(); // Limpa a tela após exibir o menu

        switch (opcao) {
            case 1:
                hub.ligar();
                break;
            case 2:
                hub.desligar();
                break;
            case 3:
                cout << "Escolha uma porta para conectar (1-5): ";
                cin >> porta;
                cout << "Digite o nome do equipamento: ";
                cin >> equipamento;
                hub.conectar(porta, equipamento);
                break;
            case 4:
                cout << "Escolha uma porta para desconectar (1-5): ";
                cin >> porta;
                hub.desconectar(porta);
                break;
            case 5:
                hub.exibirStatus();
                break;
            case 6:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 6);

    return 0;
}
