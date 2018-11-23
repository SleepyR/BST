#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <class T>
class Node
{
  public:
  T data;
  Node<T>* right;
  Node<T>* left; 
};
template <class T>
class BinarySearchTree
{
  public:
    Node<T>* root;

  BinarySearchTree()
  {
    root=NULL;
  }
  ~BinarySearchTree()
  {
    root=NULL;
  }
  bool insert(T data)
  {
    Node<T>* newN=new Node<T>();
    newN->data=data;
    newN->left=NULL;
    newN->left=NULL;
    if(root==NULL)
    {
      root=newN;
      return true;
    }
    else
        {return insertHelper(root,newN);}
  }
  void remove(T data)
  {
    if(find(data)!=NULL){
      root=removeHelper(root,data);
    }
    else{
      cout<<"There's no "<<data<<"in the tree";
    } 
  }

  void printPre()
  {
    preHelper(root);
  } 
  void printPost()
  {
    postHelper(root);
  }
  void printIn()
  {
    inHelper(root);
  }

  Node<T>* find(T data)
  { 
    Node<T>* cur=new Node<T>();
    cur=root;
    while(cur!=NULL)
    {
      if(cur->data==data)
      { return cur;}
      else if(cur->data>data)
      {
        cur=cur->left;
      }
      else if(cur->data<data)
      {
        cur=cur->right;
      }
    }
    return NULL;
  }

  int height()
  {
    return heightHelper(root);
  }

  T findLCA(T d1, T d2)
  {
    Node<T>* n1=find(d1);
    Node<T>* n2=find(d2);
    T ret=findLCAHelper(root, n1, n2)->data;
    cout<<"LCA of "<<d1<<" and "<<d2<< " is "<<ret<<endl<<endl;
    return ret;
  }

  void LOT()
  {
    cout<<"Level Order Print of the tree"<<endl;
    queue<T>* q=new queue<T>();
    Node<T>* cur=new Node<T>();
    cur=root;
    while(cur!=NULL)
    {
      cout<<cur->data<<" ";
      if(cur->left!=NULL)
        q->push(cur->left->data);
      if(cur->right!=NULL)
        q->push(cur->right->data);
      cur=find(q->front());
      q->pop();
    }
  }
  
  Node<T>* recPre(T a[])
  { int ind=0;
    cout<<"The tree has recovered from the preorder traversal"<<endl;
    return recPreHelper(a,&ind,0,sizeof(a)-1,sizeof(a));
  }

 Node<T>* recPreHelper(T a[],int* index,int beg,int end,int s)
  {
    int i;
    if(*index>s)
      return NULL;
    if(beg>end)
      return NULL;
    Node<T>* root=new Node<T>();
    root->data=a[*index];
    *index=*index+1;
    if(beg==end)
      return root;
    for(i=beg;i<=end;i++)
      if(a[i]>root->data)
        break;         
    root->left=recPreHelper(a,index,beg,i-1,s);
    root->right=recPreHelper(a,index,i,end,s);
  }


  private:
  //Node<T>* root;
  bool insertHelper(Node<T>* fakeroot,Node<T>* node)
  {
    if(node->data>fakeroot->data)
    {
      if(fakeroot->right==NULL)
       {
        fakeroot->right=node;
        return true;
       }
      else
        insertHelper(fakeroot->right,node);
    }
    else if(node->data<fakeroot->data)
    {
      if(fakeroot->left==NULL)
      {  
        fakeroot->left=node;
        return true;
      }
      else
        insertHelper(fakeroot->left,node);
    }
    else if(node->data==fakeroot->data)
      return false;
  }

  int heightHelper(Node<T>* fakeroot)
  {
    if(fakeroot==NULL)
      return 0;
    return 1+max(heightHelper(fakeroot->left),heightHelper(fakeroot->right));
  }

  void preHelper(Node<T>* fakeroot)
  {

    if(fakeroot==NULL)
      return;
    else 
    {
      cout<<fakeroot->data<<"  ";
      preHelper(fakeroot->left);
      preHelper(fakeroot->right);
    }
  }

  void inHelper(Node<T>* fakeroot)
  {
    if(fakeroot!=NULL)
    {
      inHelper(fakeroot->left);
      cout<<fakeroot->data<<"  ";
      inHelper(fakeroot->right);
    }
  }
  
  void postHelper(Node<T>* fakeroot)
  {
    if(fakeroot!=NULL)
    {
      postHelper(fakeroot->left);
      postHelper(fakeroot->right);
      cout<<fakeroot->data<<"  ";
    }
  }

  Node<T>* findMin(Node<T>* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

  Node<T>* removeHelper(Node<T>* helper,T value)
  {
   if(helper ==NULL) return helper;
   if(value < helper->data)
   {
      helper->left=removeHelper(helper->left, value);
    }
  else if(value > helper->data)
  {
      helper->right=removeHelper(helper->right, value);
    }
    else if(helper->left && helper->right)
    {

        Node<T>* temp = findMin(helper->right);
        helper->data = temp->data;
        helper->right = removeHelper(helper->right, helper->data);
      }
    else
    {
        if(helper->left == NULL)
            helper = helper->right;
        else if(helper->right == NULL)
            helper = helper->left;        
    }     
    return helper;
  } 

  Node<T>* findLCAHelper(Node<T>* parent,Node<T>* n1, Node<T>* n2)
  {
    if(parent==NULL)
    {
      return NULL;
    }
    else if( (n1->data < parent->data) && (n2->data < parent->data) )
    {
      cout<<"nodes are in left"<<endl;
      return findLCAHelper(parent->left, n1, n2);
    }
    else if( (n1->data > parent->data) && (n2->data > parent->data) )
    {
      cout<<"nodes are in right"<<endl;
      return findLCAHelper(parent->right, n1,n2);
    }
   return parent;
  }

};


int main() {
  BinarySearchTree<int>* tree=new BinarySearchTree<int>();
  cout<<tree->insert(15)<<endl;
  cout<<tree->insert(15)<<endl;
  cout<<tree->insert(13)<<endl;
  cout<<tree->insert(18)<<endl;
  cout<<tree->insert(4)<<endl;
  cout<<tree->insert(2)<<endl;
  cout<<tree->insert(3)<<endl;
  cout<<tree->insert(12)<<endl;
  cout<<tree->insert(11)<<endl;
  cout<<tree->insert(20)<<endl;
  cout<<tree->insert(40)<<endl;


  
  tree->remove(15);
  cout<<tree->height()<<endl;
  tree->printPre();
  cout<<endl;
  tree->printIn();
  cout<<endl;
  tree->printPost();
  cout<<endl<<endl;  
  tree->findLCA(12,3);
  tree->findLCA(20,40);
  tree->findLCA(13,40);
  tree->LOT();
  cout<<endl<<endl;
  BinarySearchTree<int>* tree2=new BinarySearchTree<int>();
  int arr[]= {11, 5, 1, 7 ,8, 40 ,52 ,70, 63};
  tree2->root=tree2->recPre(arr);
  cout<<endl;
  tree2->printIn();
}
