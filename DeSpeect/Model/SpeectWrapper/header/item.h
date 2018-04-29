#ifndef ITEM_H
#define ITEM_H
#include "speect.h"
#include "string"
//this item only iterate over the SItem and allow to get and set data
//have no responsibility of memory
class Item
{
private:
    //SItem of speect
    SItem* item;
    //ID that rappresent the path from the head of relationship to nod
    std::string ID;
public:
    //construct the item
    Item(SItem*,const std::string& id=" ");
    Item(const Item&);
    ~Item();
    //check if pointer is NULL
    bool isNull()const;
    //chech if next is valid
    bool hasNext()const;
    //check if previus is valid
    bool hasPrev()const;
    //check if daughter is valid
    bool hasDaughter()const;
    //check if father is valid
    bool hasFather()const;
    //check if it's of the given relation
    bool checkRelation(const std::string &)const;
    //return the pointer to the item don't do check use hasnext,.. to check before
    Item next()const;
    Item daughter()const;
    Item prev()const;
    Item father()const;

    //return the Id that is the path of item from the head item of the relation
    const std::string &getId()const;
    //return the name of the item
    const std::string getName()const;
    //check if this SItem is equal to the SItem found in the given relation at given Path
    //using Speect equals function
    //return 0 if !equal 1 if equal and same relation 2 if equal and different relations
    int IsEqual(const std::string&, const std::string &) const;


};
#endif // ITEM_H
