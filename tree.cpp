#include <iostream>
#include <string>
#include <ctime>
using namespace std;

template <typename T>
struct Node {
    T data_;
    Node* lch;
    Node* rch;

    Node(T in=0):data_(in), lch(0), rch(0) {/*cout<<"Node Ctor called"<<endl;*/}
    /*
    private:
    Nodde& operator=(Node& ref)=delete;
    Node(T& sref)=delete;
    */
};

template <typename T>
class Tree : public Node<T> {
    public:
    Tree(T in=0):Node<T>(in)
    {
        count_ = 0 ;
        root_ = 0 ; 
        cout << "Tree Ctor called"<<endl; 
    }


    void del(Node<T>* in)
    {
        if(!in)
        {
            return;
        }
        if(in->lch)
        {
            del(in->lch);
            in->lch = 0;
        }
        if(in->rch)
        {
            del(in->rch);
            in->rch = 0;
        }
        cout<<"Deleting :"<< in->data_<<endl;
        delete in;
    }

    virtual ~Tree()
    {
        cout<<"Destructing Tree"<<endl;
        del(root_);
        root_ = 0;
    }

    void insert(T in)
    {
        if(root_ == 0)
        {
            root_ = new Node<T>(in);
            ++count_;
            return ;
        }

        Node<T>* tmp = root_;
        while(tmp)
        {
            if(in < tmp->data_)
            {
                if(tmp->lch)
                {
                    tmp = tmp->lch;
                }
                else
                {
                    tmp->lch = new Node<T>(in);
                    ++count_;
                    break;
                }
            }
            else
            {
                if(tmp->rch)
                {
                    tmp = tmp->rch;
                }
                else
                {
                    tmp->rch = new Node<T>(in);
                    ++count_;
                    break;
                }
            }
        }

    }
    
    Node<T>* inOrderSucc(Node<T>* in)
    {
        while(in)
        {
            if(in->lch && in->lch->lch) 
            {
                in = in->lch;
            }
            else
                return in;
        }
        return 0;
    }
         

    void remove(T in)
    {
        Node<T>* tmp = root_;
        Node<T>* ptmp = root_;
        while(tmp)
        {
            if (in < tmp->data_) 
            {
                ptmp = tmp;
                tmp = tmp->lch;
            }
            else if (in > tmp->data_) 
            {
                ptmp = tmp;
                tmp = tmp->rch;
            }
            else if( in == tmp->data_) // Search successeded
            {
                if(tmp->rch && tmp->lch) // both childs
                {
                    //minPar is the parent Node of samallest Node
                    Node<T>* minPar = inOrderSucc(tmp->rch);
                    if(minPar)
                    {
                        if(!minPar->lch && !minPar->rch)
                        {
                            tmp->data_ = minPar->data_;
                            delete minPar;
                            tmp->rch = 0;
                            --count_;
                            break;
                        }
                        else if(minPar->lch)
                        {
                            tmp->data_ = minPar->lch->data_;
                            if(minPar->lch->rch)
                            {
                                Node<T>* store = minPar->lch;
                                minPar->lch = minPar->lch->rch ; 
                                cout <<"Deleting Node "<<in<<endl;
                                delete store;
                            }
                            else
                            {
                                cout <<"Deleting Node "<<in<<endl;
                                delete minPar->lch;
                                minPar->lch = 0;
                            }
                            --count_;
                            break;
                        }
                        else if(minPar->rch)
                        {
                            tmp->data_ = minPar->data_;
                            tmp->rch = minPar->rch;
                            cout <<"Deleting Node "<<in<<endl;
                            delete minPar;
                            --count_;
                            break;
                        }
                    }
                }

                if(!tmp->lch && tmp->rch) // one rch
                {
                    if(ptmp->lch == tmp)
                    {
                        ptmp->lch = tmp->rch;
                    }
                    else if(ptmp->rch == tmp)
                    {
                        ptmp->rch = tmp->rch;
                    }
                    delete tmp;
                    --count_;
                    break;
                }

                if(!tmp->rch && tmp->lch) // one lch
                {
                    if(ptmp->lch == tmp)
                    {
                        ptmp->lch = tmp->lch;
                    }
                    else if(ptmp->rch == tmp)
                    {
                        ptmp->rch = tmp->lch;
                    }
                    delete tmp;
                    --count_;
                    break;
                }

                if(!tmp->lch && !tmp->rch) // No child case
                {
                    if(tmp == root_)
                    {
                        delete root_;
                        root_ = 0;
                        --count_;
                        break;
                        
                    }
                    if(ptmp->lch == tmp)
                    {
                        delete ptmp->lch;
                        ptmp->lch = 0;
                    }
                    else if(ptmp->rch == tmp)
                    {
                        delete ptmp->rch;
                        ptmp->rch = 0;
                    }
                    --count_;
                    break;
                }
            }
        }
    }

    void postOrder()
    {
        cout<< "Post Order Traversal \n";
        post(root_);
        cout<<endl; 
    }
    void post(Node<T>* in=0)
    {
        if( in == 0 )
            return;

        post(in->lch);
        post(in->rch);
        cout<<in->data_<<" ";
    }


    void preOrder() 
    { 
        cout<< "Pre Order Traversal \n";
        pre(root_);
        cout<<endl; 
    }
    void pre(Node<T>* in=0)
    {
        if( in == 0 )
            return;

        cout<<in->data_<<" ";
        pre(in->lch);
        pre(in->rch);
    }

    void inOrder()
    { 
        cout<< "In Order Traversal \n";
        inOd(root_);
        cout<<endl; 
    }
    void inOd(Node<T>* in=0)
    {
        if( in == 0 )
            return;

        inOd(in->lch);
        cout<<in->data_<<" ";
        inOd(in->rch);
    }

    unsigned int getCount() { return count_; }

    private:
    Node<T>* root_;
    unsigned int count_;
    
};

int main()
{
    Tree<unsigned > bTree(0);
    srand((unsigned)time(0));
    int x = 0;
    for(unsigned i = 1 ; i <= 1500000 ; ++i)
    {
        x = (rand()%1500000);
        cout<<"Inserting : "<<x<<endl;
        bTree.insert(x);
        cout <<"Current count is: "<<bTree.getCount() <<endl; 
    }
    bTree.inOrder();
    bTree.preOrder();
    bTree.postOrder();

    for(unsigned i = 1 ; i <= 500000 ; ++i)
    {
        x = (rand()%1500000);
        bTree.remove(x);
    }

    bTree.inOrder();
    bTree.preOrder();
    bTree.postOrder();

    return 0;
}
