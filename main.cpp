#include <iostream>
#include <string>
#include <random>
using namespace std;
template <class T> class Deck { 
private: 
    template <class TT> class Carta { 
    public: 
        Carta<int> *prox; 
        int def, atk, vel;
        Carta(int def, int atk, int vel){
            this->def = def;
            this->atk = atk;
            this->vel = vel;
        };
        }; 
    int tamanho; 
    Carta<int> *topo;    
public: 
        Deck() { 
            topo = nullptr; 
            tamanho = 0; 
        } 
        ~Deck() { 
            Carta<int> *aux; 
            while(topo!=nullptr) { 
            aux=topo; 
            topo = topo->prox; 
            delete aux; 
            } 
        } 
        int getTamanho() { 
            return tamanho; 
        } 
        bool inserir(int def, int atk, int vel) { 
            if(this->topo == nullptr) { 
                this->topo = new Carta<int>(def, atk, vel); 
            } else { 
                Carta<int> *aux = new Carta<int>(def, atk, vel); 
                aux->prox = this->topo; 
                this->topo = aux; 
            } 
            ++tamanho; 
            return true; 
        } 
        bool excluir(void) { 
            if(this->topo==nullptr) { 
                return false; 
            } else { 
                Carta<int> *aux; 
                aux = topo; 
                this->topo = this->topo->prox; 
                delete aux; 
                --tamanho; 
                return true;
            } 
        } 
        void mostrar() { 
            if(this->topo== nullptr) { 
                cout << "<<nada>>"; 
            } else { 
                cout<<"       +---------+"<<endl;
                cout <<"         Atk: "<< this->topo->atk<<endl; 
                cout <<"         Def: "<< this->topo->def<<endl;
                cout <<"         Vel: "<< this->topo->vel<<endl;
                cout<<"       +---------+"<<endl;
            } 
        } 
        int getTopoAtk(){
            if(this->topo== nullptr) { 
                return 1000; 
            } else { 
                return this->topo->atk; 
            } 
        }
        int getTopoDef(){
            if(this->topo== nullptr) { 
                return 1000; 
            } else { 
                return this->topo->def; 
            } 
        }
        int getTopoVel(){
            if(this->topo== nullptr) { 
                return 1000; 
            } else { 
                return this->topo->vel; 
            } 
        }
        void encheDeck(){
            random_device device;
            mt19937 generator(device());
            uniform_int_distribution<int> distribution(1, 10);  
            for(int i = 0; i < 13; i++){
                int newAtk = distribution(generator), newDef = distribution(generator), newVel = distribution(generator);
                this->inserir(newAtk, newDef, newVel);
            }
        }
        
}; 


template <class G> class Mao{
    private:
        template <class F> class Carta{
            public:
            Carta<int> *prox;
            int def, atk, vel;
            Carta(int def, int atk, int vel){
                this->def= def;
                this->atk = atk;
                this->vel = vel;
                prox = nullptr;
            }
        };
        int tamanho;
        Carta<int> *fim;
        Carta<int> *inicio;
    public: 
        Mao(){
            inicio = fim = nullptr;
            tamanho = 0;
        }
        ~Mao(){
            Carta<int> *aux;
            while(inicio!=nullptr){
                aux = inicio;
                inicio = inicio->prox;
                delete aux;
            }
        }
        bool put(int def, int atk, int vel){
            if(inicio == nullptr){
                inicio = fim = new Carta<int>(def, atk, vel);
                tamanho++;
            }else{
                Carta<int> *aux = new Carta<int>(def, atk, vel);
                aux->prox = inicio;
                tamanho++;
                inicio = aux;
            }
            return true;
        }
        bool putMd(int def, int atk, int vel, const int &posicao){
            Carta<int> *nValor, *aux;
            aux = this->inicio;
            for(int i = 0; i < posicao-1; i++){
                aux = aux->prox;
            }
            nValor =new Carta<int>(def, atk, vel);
            nValor->prox = aux->prox;
            aux->prox = nValor;
            this->tamanho++;
            return true;
        }
        bool pop(){
        if(this->inicio == nullptr) { 
            return false; 
        } else { 
            if(this->inicio->prox == nullptr) {//só tem um elemento! 
                delete this->inicio; 
                this->inicio = this->fim = nullptr; 
            } else { 
                Carta<int> *aux=this->inicio, *aux1; 
                while(aux->prox->prox!= nullptr){  
                    aux=aux->prox; 
                }
                aux1 = aux;
                delete fim;
                this->fim = aux1;
                aux->prox = nullptr;
            } 
            this->tamanho--; 
            return true; 
        }
        }
        bool popBg(){
            if(this->inicio==nullptr){
                return false;
            }else{
                Carta<int> *aux;
                aux = this->inicio;
                this->inicio = this->inicio->prox;
                delete aux;
                tamanho--;
                return true;
            }
            
        }
        bool popMd(int const &pos){
            if(pos<=tamanho){
                Carta<int> *aux = this->inicio, *proc;
                for(int i = 0; i < pos-1; i++){
                    aux = aux->prox;
                }
                proc = aux->prox;
                aux->prox = aux->prox->prox; 
                if(aux->prox == nullptr){
                    this->fim = aux;
                    delete proc;
                    this->tamanho--;  
                }
                return true;
            }else{
                return false;
            }
        }        
        void show(){
            Carta<int> *aux = this->inicio;
            int ct = 0;
            while(aux != nullptr){
                cout<<"       +---------+"<<endl;
                cout<<"          ID: "<<ct<<endl;
                cout <<"         Atk: "<< aux->atk<<endl; 
                cout <<"         Def: "<< aux->def<<endl;
                cout <<"         Vel: "<< aux->vel<<endl;
                cout<<"       +---------+"<<endl;
                aux=aux->prox;
                ct++;
            }
        }
        int showMdAtk(int const &pos){
            if(pos<=tamanho && pos >= 0){
                Carta<int> *aux;
                aux = this->inicio;
                for(int i = 0; i < pos; i++){
                    aux=aux->prox;
                }
                return aux->atk;
            }else{
                cout<<"Erro: a posicao escolhida nao existe na lista!"<<endl;
                return 0;
            }
            
        }
        int showMdDef(int const &pos){
            if(pos<=tamanho && pos >= 0){
                Carta<int> *aux;
                aux = this->inicio;
                for(int i = 0; i < pos; i++){
                    aux=aux->prox;
                }
                return aux->def;
            }else{
                cout<<"Erro: a posicao escolhida nao existe na lista!"<<endl;
                return 0;
            }
            
        }
        int showMdVel(int const &pos){
            if(pos<=tamanho && pos >= 0){
                Carta<int> *aux;
                aux = this->inicio;
                for(int i = 0; i < pos; i++){
                    aux=aux->prox;
                }
                return aux->vel;
            }else{
                cout<<"Erro: a posicao escolhida nao existe na lista!"<<endl;
                return 0;
            }
            
        }
        int lenght(){
            return tamanho;
        }
};

int embate(int cartaHm[], int cartaPc[]){
    if(cartaHm[2] > cartaPc[2]){
        if(cartaHm[0] > cartaPc[1]){
            return 1;
        }else if(cartaHm[1]<cartaPc[0]){
            return 0;
        }else{
            return 2;
        }
    }else if(cartaHm[2]<cartaPc[2]){
        if(cartaPc[0]>cartaHm[1]){
            return 0;
        }else if(cartaPc[1]<cartaHm[0]){
            return 1;
        }else{
            return 2;
        }
    }
    return 3;
}

void placar(int numero){
    switch (numero){
    case 1:
        cout<<"        ██╗"<<endl;
        cout<<"       ███║"<<endl;
        cout<<"       ╚██║"<<endl;
        cout<<"        ██║"<<endl;
        cout<<"        ██║"<<endl;
        cout<<"        ╚═╝"<<endl;        
        break;
    case 2:
        cout<<"       ██████╗ "<<endl;
        cout<<"       ╚════██╗"<<endl;
        cout<<"        █████╔╝"<<endl;
        cout<<"       ██╔═══╝ "<<endl;
        cout<<"       ███████╗"<<endl;
        cout<<"       ╚══════╝"<<endl;
        break;
    case 3:
        cout<<"       ██████╗ "<<endl;
        cout<<"       ╚════██╗"<<endl;
        cout<<"        █████╔╝"<<endl;
        cout<<"        ╚═══██╗"<<endl;
        cout<<"       ██████╔╝"<<endl;
        cout<<"       ╚═════╝ "<<endl;
        break;
    case 4:
        cout<<"       ██╗  ██╗"<<endl;
        cout<<"       ██║  ██║"<<endl;
        cout<<"       ███████║"<<endl;
        cout<<"       ╚════██║"<<endl;
        cout<<"            ██║"<<endl;
        cout<<"            ╚═╝"<<endl;
        break;
    case 5:
        cout<<"       ███████╗"<<endl;
        cout<<"       ██╔════╝"<<endl;
        cout<<"       ███████╗"<<endl;
        cout<<"       ╚════██║"<<endl;
        cout<<"       ███████║"<<endl;
        cout<<"       ╚══════╝"<<endl; 
        break;
    case 6:
        cout<<"        ██████╗ "<<endl;
        cout<<"       ██╔════╝ "<<endl;
        cout<<"       ███████╗ "<<endl;
        cout<<"       ██╔═══██╗"<<endl;
        cout<<"       ╚██████╔╝"<<endl;
        cout<<"        ╚═════╝ "<<endl;
        break;
    case 7:
        cout<<"       ███████"<<endl;
        cout<<"       ╚════██"<<endl;
        cout<<"           ██╔"<<endl;
        cout<<"          ██╔╝"<<endl;
        cout<<"          ██║ "<<endl;
        cout<<"          ╚═╝ "<<endl;
        break;
    case 8:
        cout<<"        █████╗ "<<endl;
        cout<<"       ██╔══██╗"<<endl;
        cout<<"       ╚█████╔╝"<<endl;
        cout<<"       ██╔══██╗"<<endl;
        cout<<"       ╚█████╔╝"<<endl;
        cout<<"        ╚════╝ "<<endl; 
        break;
    case 9:
        cout<<"        █████╗ "<<endl;
        cout<<"       ██╔══██╗"<<endl;
        cout<<"       ╚██████║"<<endl;
        cout<<"        ╚═══██║"<<endl;
        cout<<"        █████╔╝"<<endl;
        cout<<"        ╚════╝ "<<endl; 
        break;
    case 10:
        cout<<"        ██╗ ██████╗ "<<endl;
        cout<<"       ███║██╔═████╗"<<endl;
        cout<<"       ╚██║██║██╔██║"<<endl;
        cout<<"        ██║████╔╝██║"<<endl;
        cout<<"        ██║╚██████╔╝"<<endl;
        cout<<"        ╚═╝ ╚═════╝ "<<endl;
    default:
        break;
    }
}
int main(){
    Deck<int> deck1;
    Deck<int> deck2;
    Mao<int> mao1;
    Mao<int> mao2;
    char continuar;
    int menu;
    cout<<"          +============================================+"<<endl;
    cout<<"          |           Projeto final de AEDs            |"<<endl;
    cout<<"          |                  Grupo 2                   |"<<endl;
    cout<<"          |          Augusto dos Anjos Sigolo          |"<<endl;
    cout<<"          |               RA: 2020010886               |"<<endl;
    cout<<"          |             Tulio Benfica Lopes            |"<<endl;
    cout<<"          |               RA: 2020010886               |"<<endl;
    cout<<"          |        Marco Tulio Madeira Ferreira        |"<<endl;
    cout<<"          +============================================+"<<endl;
    system("sleep 3");
    do{
        system("clear || cls");
        cout<<endl<<endl;
        cout<<"        █████╗ ███████╗ ██████╗██╗██╗     ██╗   ██╗ ██████╗  "<<endl;
        cout<<"       ██╔══██╗██╔════╝██╔════╝██║██║     ╚██╗ ██╔╝██╔═══██╗"<<endl;
        cout<<"       ███████║███████╗██║     ██║██║█████╗╚████╔╝ ██║   ██║"<<endl;
        cout<<"       ██╔══██║╚════██║██║     ██║██║╚════╝ ╚██╔╝  ██║   ██║"<<endl;
        cout<<"       ██║  ██║███████║╚██████╗██║██║        ██║   ╚██████╔╝"<<endl;
        cout<<"       ╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝╚═╝        ╚═╝    ╚═════╝ "<<endl<<endl;
        cout<<"       ╔╦╗┌─┐┌┐┌┬ ┬"<<endl;
        cout<<"       ║║║├┤ ││││ │"<<endl;
        cout<<"       ╩ ╩└─┘┘└┘└─┘"<<endl<<endl;
        cout<<"       1. Ler regras"<<endl
            <<"       2. Jogar"<<endl
            <<"       ";
        cin>>menu;
        switch(menu){
            case 1:
            system("clear || cls");
            cout<<"O ASCII-YO é um jogo de cartas em que o jogador e a  maquina recebem 13  cartas  cada  um."<<endl
                <<"Cada carta conta com atributos de ataque, defesa e velocidade. O computador sempre  começa"<<endl
                <<"jogando sua carta mais forte, depois disso o jogador escolhe uma das 3 cartas em sua  mao "<<endl
                <<"para combater a carta jogada pela máquina. Depois de 10 rodadas, quem tiver ganho mais ro-"<<endl
                <<"dadas, ganha o jogo!"<<endl;
            cout<<"Como funciona o combate: "<<endl
                <<"O computador joga uma carta, voce pode escolher qual da sua mao voce quer jogar"<<endl
                <<"a carta com maior velocidade ataca primeiro, ganha o jogador que jogar uma carta com mais ataque do que a defesa do adversário"<<endl;
                system("sleep 30");
                break;
            case 2:
                break;
            default:
                break;

        }                                 
    }while(menu != 2);
    do{
        system("clear || cls");
        int op, vitoriaHm = 0, vitoriaPc = 0, statsHm[3], statsPc[3];
        deck1.encheDeck();
        deck2.encheDeck();
        /* Passando 3 cartas para a mão do jogador */
        for(int j = 0; j<3; j++){
        mao1.put(deck1.getTopoDef(), deck1.getTopoAtk(), deck1.getTopoVel());
        deck1.excluir();
    }
        /* Passando 3 cartas para a mão do computador */
        for(int j = 0; j<3; j++){
        mao2.put(deck2.getTopoDef(), deck2.getTopoAtk(), deck2.getTopoVel());
        deck2.excluir();
    }

        for(int i = 0; i < 10; i++){
            system("clear || cls");
            /* Computador escolhe qual sua melhor carta */
            int melhorAtk = 0, melhorDef=0, melhorVel=0, melhorCarta=0;
            for(int j = 0; j < 3; j++){
                /* Computador achar os tres melhores status da sua mão */
                if(mao2.showMdAtk(j)>melhorAtk){
                melhorAtk = j;
            }
                if(mao2.showMdDef(j)>melhorDef){
                melhorDef = j;
            }
                if(mao2.showMdVel(j)>melhorVel){
                    melhorVel = j;
                }
            }
            /* Computador compara qual carta é a melhor olhando qual delas tem melhores status */
            if(melhorAtk == melhorDef == melhorVel){
                melhorCarta = melhorAtk;
            }else if(melhorAtk == melhorDef){
                melhorCarta = melhorAtk;
            }else if(melhorAtk == melhorVel){
                melhorCarta == melhorAtk;
            }else if(melhorDef == melhorVel){
                melhorCarta == melhorDef;
            }else{
                melhorCarta == melhorDef;
            }
            cout<<
            "       O computador jogou a carta: "<<endl
            <<"       +---------------+"<<endl
            <<"            Atk: "<<mao2.showMdAtk(melhorCarta)<<endl
            <<"            Def: "<<mao2.showMdDef(melhorCarta)<<endl
            <<"            Vel: "<<mao2.showMdVel(melhorCarta)<<endl
            <<"       +---------------+"<<endl;
            statsPc[0] = mao2.showMdAtk(melhorCarta);
            statsPc[1] = mao2.showMdDef(melhorCarta);
            statsPc[2] = mao2.showMdVel(melhorCarta);
            if(melhorCarta == 0){
                mao2.popBg();
                mao2.put(deck2.getTopoDef(), deck2.getTopoAtk(), deck2.getTopoVel());
                deck2.excluir();
            }else{
                mao2.popMd(melhorCarta);
                mao2.putMd(deck2.getTopoDef(), deck2.getTopoAtk(), deck2.getTopoVel(), melhorCarta);
                deck2.excluir();
            }

            cout<<"       Essa é sua mao: "<<endl;
            mao1.show();
            cout<<"       Seu deck ainda tem "<<deck1.getTamanho()<<" cartas"<<endl;
            cout<<"       Qual carta você deseja jogar: ";
            cin>>op;
            statsHm[0] = mao1.showMdAtk(op);
            statsHm[1] = mao1.showMdDef(op);
            statsHm[2] = mao1.showMdVel(op);  
            if(op == 0){
                mao1.popBg();
                mao1.put(deck1.getTopoDef(), deck1.getTopoAtk(), deck1.getTopoVel());
                deck1.excluir();    
            }else{
                mao1.popMd(op);
                mao1.putMd(deck1.getTopoDef(), deck1.getTopoAtk(), deck1.getTopoVel(), op);
                deck1.excluir();
            }
            if(embate(statsHm, statsPc) == 1){
                system("clear || cls");
                cout<<endl<<endl;
                cout<<"       ██╗    ██╗██╗███╗   ██╗"<<endl;
                cout<<"       ██║    ██║██║████╗  ██║"<<endl;
                cout<<"       ██║ █╗ ██║██║██╔██╗ ██║"<<endl;
                cout<<"       ██║███╗██║██║██║╚██╗██║"<<endl;
                cout<<"       ╚███╔███╔╝██║██║ ╚████║"<<endl;
                cout<<"        ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝"<<endl;
                system("sleep 3");
                vitoriaHm++;
            }else if(embate(statsHm, statsPc) == 0){
                system("clear || cls");
                cout<<endl<<endl;
                cout<<"       ██╗      ██████╗ ███████╗███████╗"<<endl;
                cout<<"       ██║     ██╔═══██╗██╔════╝██╔════╝"<<endl;
                cout<<"       ██║     ██║   ██║███████╗█████╗  "<<endl;
                cout<<"       ██║     ██║   ██║╚════██║██╔══╝  "<<endl;
                cout<<"       ███████╗╚██████╔╝███████║███████╗"<<endl;
                cout<<"       ╚══════╝ ╚═════╝ ╚══════╝╚══════╝"<<endl;
                system("sleep 3");
                vitoriaPc++;
            }else{
                system("clear || cls");
                cout<<endl<<endl;
                cout<<"       ██████╗ ██████╗  █████╗ ██╗    ██╗"<<endl;
                cout<<"       ██╔══██╗██╔══██╗██╔══██╗██║    ██║"<<endl;
                cout<<"       ██║  ██║██████╔╝███████║██║ █╗ ██║"<<endl;
                cout<<"       ██║  ██║██╔══██╗██╔══██║██║███╗██║"<<endl;
                cout<<"       ██████╔╝██║  ██║██║  ██║╚███╔███╔╝"<<endl;
                cout<<"       ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚══╝╚══╝ "<<endl;                
                system("sleep 3");
            }
        }
        system("clear || cls");
        if((vitoriaHm-vitoriaPc) > 0){
            cout<<"        ██████╗  █████╗ ███╗   ███╗███████╗    ██╗    ██╗██╗███╗   ██╗███╗   ██╗███████╗██████╗ "<<endl;
            cout<<"       ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██║    ██║██║████╗  ██║████╗  ██║██╔════╝██╔══██╗"<<endl;
            cout<<"       ██║  ███╗███████║██╔████╔██║█████╗      ██║ █╗ ██║██║██╔██╗ ██║██╔██╗ ██║█████╗  ██████╔╝"<<endl;
            cout<<"       ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║███╗██║██║██║╚██╗██║██║╚██╗██║██╔══╝  ██╔══██╗"<<endl;
            cout<<"       ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚███╔███╔╝██║██║ ╚████║██║ ╚████║███████╗██║  ██║"<<endl;
            cout<<"        ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝"<<endl<<endl;
            cout<<"       ██████╗  ██████╗   "<<endl;
            cout<<"       ██╔══██╗██╔════╝██╗"<<endl;
            cout<<"       ██████╔╝██║     ╚═╝"<<endl;
            cout<<"       ██╔═══╝ ██║     ██╗"<<endl;
            cout<<"       ██║     ╚██████╗╚═╝"<<endl;
            cout<<"       ╚═╝      ╚═════╝   "<<endl<<endl;
            placar(vitoriaPc);
            cout<<"██╗   ██╗ ██████╗ ██╗   ██╗   "<<endl;
            cout<<"╚██╗ ██╔╝██╔═══██╗██║   ██║██╗"<<endl;
            cout<<" ╚████╔╝ ██║   ██║██║   ██║╚═╝"<<endl;
            cout<<"  ╚██╔╝  ██║   ██║██║   ██║██╗"<<endl;
            cout<<"   ██║   ╚██████╔╝╚██████╔╝╚═╝"<<endl;
            cout<<"   ╚═╝    ╚═════╝  ╚═════╝    "<<endl<<endl;
            placar(vitoriaHm);
        }else if((vitoriaHm-vitoriaPc) == 0){
            cout<<"        ██████╗  █████╗ ███╗   ███╗███████╗    ██████╗ ██████╗  █████╗ ██╗    ██╗"<<endl;
            cout<<"       ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔══██╗██╔══██╗██╔══██╗██║    ██║"<<endl;
            cout<<"       ██║  ███╗███████║██╔████╔██║█████╗      ██║  ██║██████╔╝███████║██║ █╗ ██║"<<endl;
            cout<<"       ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║  ██║██╔══██╗██╔══██║██║███╗██║"<<endl;
            cout<<"       ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ██████╔╝██║  ██║██║  ██║╚███╔███╔╝"<<endl;
            cout<<"        ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚══╝╚══╝ "<<endl;
            cout<<"       ██████╗  ██████╗   "<<endl;
            cout<<"       ██╔══██╗██╔════╝██╗"<<endl;
            cout<<"       ██████╔╝██║     ╚═╝"<<endl;
            cout<<"       ██╔═══╝ ██║     ██╗"<<endl;
            cout<<"       ██║     ╚██████╗╚═╝"<<endl;
            cout<<"       ╚═╝      ╚═════╝   "<<endl<<endl;
            placar(vitoriaPc);
            cout<<"██╗   ██╗ ██████╗ ██╗   ██╗   "<<endl;
            cout<<"╚██╗ ██╔╝██╔═══██╗██║   ██║██╗"<<endl;
            cout<<" ╚████╔╝ ██║   ██║██║   ██║╚═╝"<<endl;
            cout<<"  ╚██╔╝  ██║   ██║██║   ██║██╗"<<endl;
            cout<<"   ██║   ╚██████╔╝╚██████╔╝╚═╝"<<endl;
            cout<<"   ╚═╝    ╚═════╝  ╚═════╝    "<<endl<<endl;
            placar(vitoriaHm);
        }else{
            cout<<"        ██████╗  █████╗ ███╗   ███╗███████╗    ██╗      ██████╗ ███████╗███████╗██████╗ "<<endl;
            cout<<"       ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██║     ██╔═══██╗██╔════╝██╔════╝██╔══██╗"<<endl;
            cout<<"       ██║  ███╗███████║██╔████╔██║█████╗      ██║     ██║   ██║███████╗█████╗  ██████╔╝"<<endl;
            cout<<"       ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║     ██║   ██║╚════██║██╔══╝  ██╔══██╗"<<endl;
            cout<<"       ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ███████╗╚██████╔╝███████║███████╗██║  ██║"<<endl;
            cout<<"        ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    ╚══════╝ ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝"<<endl;
            cout<<"       ██████╗  ██████╗   "<<endl;
            cout<<"       ██╔══██╗██╔════╝██╗"<<endl;
            cout<<"       ██████╔╝██║     ╚═╝"<<endl;
            cout<<"       ██╔═══╝ ██║     ██╗"<<endl;
            cout<<"       ██║     ╚██████╗╚═╝"<<endl;
            cout<<"       ╚═╝      ╚═════╝   "<<endl<<endl;
            placar(vitoriaPc);
            cout<<"██╗   ██╗ ██████╗ ██╗   ██╗   "<<endl;
            cout<<"╚██╗ ██╔╝██╔═══██╗██║   ██║██╗"<<endl;
            cout<<" ╚████╔╝ ██║   ██║██║   ██║╚═╝"<<endl;
            cout<<"  ╚██╔╝  ██║   ██║██║   ██║██╗"<<endl;
            cout<<"   ██║   ╚██████╔╝╚██████╔╝╚═╝"<<endl;
            cout<<"   ╚═╝    ╚═════╝  ╚═════╝    "<<endl<<endl;
            placar(vitoriaHm);
        }
        cout<<"       Deseja jogar novamente?[Y/n]: ";
        cin>>continuar;
    }while(continuar != 'n');
    return 0;
}