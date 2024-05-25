#include <iostream>


using namespace std;


class Stack {

    private:
        static const int STACK_MAX_SIZE = 5; // Tamanho máximo da pilha
        int top; // variável que controla qual o topo atual da pilha
        int items[STACK_MAX_SIZE]; // Pilha a ser inseridos dados

    public:

        /*
         * Inicializa as variáveis
         */
        Stack ()
        {
            top = -1;
        }

        /*
         * Empilha um item na Pilha
         */
        void Push (int item)
        {
            if(top >= STACK_MAX_SIZE - 1) {
                cout << "Stack overflow" << endl;
            } else {
                items[++top] = item;
            }
        }

        /*
         * Desempilha o último item da lista
         */
        int Pop ()
        {
            if(top <= -1) {
                cout << "Stack underflow" << endl;
                return -1;
            } else {
                return items[top--];
            }
        }

        /*
         * Retorna o atual tamanho da Pilha
         */
        int Size ()
        {
            return top + 1;
        }

        /*
         * Retorna true caso a pilha esteja vazia. false, caso contrário
         */
        bool isEmpty ()
        {
            return (top == -1) ? true : false;
        }

        /*
         * Retorna true caso a pilha esteja cheia. false, caso contrário
         */
        bool isFull ()
        {
            return (top == STACK_MAX_SIZE - 1) ? true : false;
        }

        /*
         * Pega o item do topo da Pilha mas não o desempilha
         */
        int Peek ()
        {
            return (top == -1) ? -1 : items[top];
        }

        /*
         * Imprime a pilha
         */
        void toString ()
        {
            for(int i=top; i > -1; i--) {
                cout << "[" << items[i] << "]" << endl;
            }
        }
};


int main (int argc, char* argv[])
{
    Stack stack;
    int item;

    item = 42; cout << "Stack Push: " << item << endl; stack.Push(item);
    item = 10; cout << "Stack Push: " << item << endl; stack.Push(item);
    item = 23; cout << "Stack Push: " << item << endl; stack.Push(item);
    item = 76; cout << "Stack Push: " << item << endl; stack.Push(item);
    item = 44; cout << "Stack Push: " << item << endl; stack.Push(item);
    item = 87; cout << "Stack Push: " << item << endl; stack.Push(item);

    stack.toString();

    if(!stack.isEmpty()) {
        cout << "Stack not empty!" << endl;
        cout << "Stack size: " << stack.Size() << endl;
    }

    cout << "Stack Pop: " << stack.Pop() << endl;
    cout << "Stack Pop: " << stack.Pop() << endl;

    stack.toString();

    if(!stack.isFull()) {
        cout << "Stack not full!" << endl;
        item = 50; cout << "Stack Push: " << item << endl; stack.Push(item);
    }

    stack.toString();

    cout << "Stack Peek: " << stack.Peek() << endl;
    stack.toString();

    cout << "Stack Pop: " << stack.Pop() << endl;
    cout << "Stack Pop: " << stack.Pop() << endl;
    cout << "Stack Pop: " << stack.Pop() << endl;
    cout << "Stack Pop: " << stack.Pop() << endl;
    cout << "Stack Pop: " << stack.Pop() << endl;

    return EXIT_SUCCESS;
}