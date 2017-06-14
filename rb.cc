#include <iostream>
#include <vector>
#include <string>

enum class Color
{
    RED = 0,
    BLACK
};

template <typename T>
struct rbNode
{
    T data_;
    rbNode* lch;
    rbNode* rch;
    rbNode* par;
    Color color;
    rbNode(T in=0):lch(nullptr),rch(nullptr),par(nullptr),color(Color::RED) { }
};

template <typename T>
class rbTree : public rbNode<T>
{
    public:
    rbTree(T in=0): rbNode<T>(in)
    {
        count_ = 0;
        root_ = nullptr;
    }

    void insert(T& in)
    {
        if(root_ == nullptr)
        {
            root_ = new rbNode<T>(in);
            root_->color = Color::BLACK;
        } 
        else
        {
            rbNode<T>* tmp = root_;
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
                        tmp->lch = new rbNode<T>(in);
                        tmp->lch->par = tmp;
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
                        tmp->rch = new rbNode<T>(in);
                        tmp->rch->par = tmp;
                    }
                }
            }
        }
    }

    rbNode<T>* find(T& in)
    {
        rbNode<T>* tmp = root_;
        while(tmp)
        {
            if(in == tmp->data_)
            {
                return tmp;
            }
            else if(in < tmp->data_)
            {
                tmp = tmp->lch;
            }
            else 
            {
                tmp = tmp->rch;
            }
        
        }
        // search not successfull.
        return nullptr;
    }  

    void restorRbProp() 
    {
    }
    private:
    unsigned int count_;
    rbNode<T>* root_;
};

int main()
{
    rbTree<int> x;
    return 0;
}
