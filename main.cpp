#include <iostream>

using namespace std;

template<typename T>
class list_Iterator;

template<typename T>
class node{
private:
    T data;
    node<T> *next;
public:
    node(){
        data=0;
        next=NULL;
    }
    node(const node<T> &n){
        data=n.data;
        next=n.next;
    }
    T getData(){
        return data;
    }
    void setData(T d){
        data=d;
    }
    node* get_next(){
        return next;
    }
    void set_next(node<T> *n){
        next=n;
    }

};

template<typename T>
class linked_list{
private:
    node<T> *head,*tail;
    int c;
public:
    linked_list(){
        cout<<"Construido"<<endl;
        head=NULL;
        tail=NULL;
        c=0;
    }
    ~linked_list(){
        while(head!=NULL){
            //cout<<head->getData()<<":borrado "<<endl;
            delete head;
            head=head->get_next();
        }
        cout<<"Destruido"<<endl;
    }
    node<T>* crear_nodo(T new_data){
        node<T> *new_node=new node<T>;
        new_node->setData(new_data);
        return new_node;
    }
    void primer_nodo(T new_data){
        c++;
        node<T> *new_node=crear_nodo(new_data);
        head=new_node;
        tail=new_node;
        cout<<"primer_nodo"<<endl;
    }
    void insertar_tail(T new_data){
        c++;
        node<T> *new_node=crear_nodo(new_data);
        tail->set_next(new_node);
        tail=tail->get_next();
        cout<<"insertar_tail"<<endl;
    }
    void insertar_head(T new_data){
        c++;
        node<T> *new_node=crear_nodo(new_data);
        new_node->set_next(head);
        head=new_node;
        cout<<"insertar_head"<<endl;
    }
    void eliminar_nodo(int pos){
        int i=1;
        node<T>* aux=head;
        node<T>* prev;
        while(i!=pos){
            prev=aux;
            aux=aux->get_next();
            i++;
        }
        prev->set_next(aux->get_next() );
        delete aux;
        c--;
        cout<<"nodo " <<pos<<" eliminado"<<endl;

    }
    node<T>* getNodo(int n){
        int i=0;
        node<T>* aux=head;
        while(i!=n){
            aux=aux->get_next();
            i++;
        }
        return aux;
    }
    int getC(){
        return c;
    }
    list_Iterator<T>* crearIterator(){
        return new list_Iterator<T>(this);
    }
    /*void mostrar(){
        cout<<"Mostrando:"<<endl;
        node<T>* aux=head;
        while(aux->get_next()!=NULL){
            cout<<aux->getData()<<" -> ";
            aux=aux->get_next();
        }
        cout<<aux->getData()<<endl;
    }*/
    void mostrar(){
        cout<<"Mostrando:"<<endl;
        list_Iterator<T>* lista=crearIterator();
        for(lista->first();lista->isDone();lista->next()){
            cout<<lista->currentNodo()<<"->";
        }
    }
};

template<typename T>
class list_Iterator{
private:
    int index;
    linked_list<T>* linkedList;
public:
    list_Iterator(linked_list<T>* lista){
        index=0;
        linkedList=lista;
    }
    void first(){
        index=0;
    }
    void next(){
        index++;
    }
    bool isDone(){
        return(index==(linkedList->getC()-1));
    }
    void last(){
        index=(linkedList->getC()-1);
    }
    node<T>* currentNodo(){
        return linkedList->getNodo(index);
    }
};

int main()
{
    linked_list<int> lista;
    lista.primer_nodo(3);
    lista.insertar_head(4);
    lista.insertar_tail(5);
    lista.insertar_tail(6);
    lista.insertar_tail(7);
    lista.mostrar();
    cout<<lista.getC()<<endl;
    lista.eliminar_nodo(2);
    lista.mostrar();
    cout<<lista.getC()<<endl;

    return 0;
}
