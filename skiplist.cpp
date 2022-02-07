#include "skiplist.hpp"
  
skiplist::skiplist(int maxLevel, float fractation)
{
    std::srand(time(NULL));


    this->maxLevel = maxLevel;
    this->fractation = fractation;
    curLevel = 0;
   
  
    header = new node(std::numeric_limits<int>::min(), maxLevel);
};

skiplist::~skiplist(){
    node* delNode;
    for (int i = this->curLevel; i >=0 ; i--)
    {
        while (header->Forward(i) != nullptr )
        {   delNode=header;
            header=header->Forward(i);
            delete delNode;

        }
      
    }  
  
};
  
int skiplist::randLevel()
{  
    int ranLev=static_cast<int>(std::log( (float)std::rand()/RAND_MAX)/std::log(1.0-fractation));
    return ranLev<maxLevel ? ranLev : maxLevel;
};


 
node::node(int data, int curLevel)
{
    this->data = data;  
    towar = new node*[curLevel+1];
    std::fill_n(towar,curLevel+1,nullptr);
    
};


node::~node(){

    delete[] towar;

}


bool skiplist::Insert(int Insdata)
{
    node *curHeader = header;  
    node *newOne[maxLevel+1];
    std::fill_n(newOne,maxLevel+1,nullptr);
    for (int i = this->curLevel; i >=0 ; i--)
    {
        while (curHeader->Forward(i) != nullptr && curHeader->Forward(i)->data <Insdata)
        {

            curHeader=curHeader->Forward(i);
        }

        newOne[i]=curHeader;
    }
    curHeader = curHeader->Forward(0);
    if (curHeader == nullptr || curHeader->data != Insdata)
    {
        int newLevel = randLevel();  
        if(newLevel > curLevel)
        {
            for(int i=curLevel+1;i<newLevel+1;i++){
                newOne[i] = header;  
            }
            curLevel = newLevel;
        }
  
        node* n = new node(Insdata, newLevel);
  
        for(int i=0;i<=newLevel;i++)
        {
            n->Assign(i,newOne[i]->Forward(i)); 
            newOne[i]->Assign(i,n);
            
        }
        size+=1;
        int newMaxLevel=static_cast<int>(std::log(size)/std::log(1.0/fractation));
        if(newMaxLevel>maxLevel){
            
            node* newHeader = new node(std::numeric_limits<int>::min(), newMaxLevel);
            for (int i = 0; i < maxLevel; i++)
            {
                newHeader->Assign(i,header->Forward(i));
            }
            delete header;
            header=newHeader;
            maxLevel= newMaxLevel;
        }
        return true;
    }
    return false;
    
};
  
bool skiplist::Delete(int Deldata)
{
    node *curHeader = header;
    node *newOne[maxLevel+1];
    std::fill_n(newOne,maxLevel+1,nullptr);
    
    for (int i = this->curLevel; i >=0 ; i--)
    {
        while (curHeader->Forward(i) != nullptr && curHeader->Forward(i)->data <Deldata)
        {
            curHeader=curHeader->Forward(i);
        }
        newOne[i]=curHeader;
    }
 
    curHeader = curHeader->Forward(0);  
    if(curHeader != nullptr and curHeader->data == Deldata)
    {       
        for(int i=0;i<=curLevel;i++)
        {
            if(newOne[i]->Forward(i) != curHeader)
                break;
  
            newOne[i]->Assign(i,curHeader->Forward(i));
        }
        while(curLevel > 0 && header->Forward(curLevel)==0){
            curLevel--;

        }
        return true;
    }
    return false;
};
  
bool skiplist::Search(int Searchdata)
{
    node *curHeader = header;
      for (int i = this->curLevel; i >=0 ; i--)
    {
        while (curHeader->Forward(i) != nullptr && curHeader->Forward(i)->data <Searchdata)
        {
            curHeader=curHeader->Forward(i);
        }
    }
    curHeader = curHeader->Forward(0);  

    if(curHeader and curHeader->data == Searchdata){
        return true;
    } 
     return false;   
};
  
void skiplist::Print()
{
       
    std::cout<< "\n"<<"--------------------------------------------------------------------------------"<<"\n";
    for(int i=curLevel;0<=i;i--)
    {
        node *node = header->Forward(i);
        std::cout<<"Level "<<i<<": ";
        while(node != nullptr)
        {
            std::cout<<node->data<<"->";
            node = node->Forward(i);
        }
        std::cout<<"nullptr\n";
    }
    std::cout<<"--------------------------------------------------------------------------------"<<"\n";

};


