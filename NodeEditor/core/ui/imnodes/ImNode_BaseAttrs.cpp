#include "core/nepch.h"
#include "ImNode_BaseAttrs.h"

namespace NodeEditor {
    
std::unordered_map<int, Attr *> Attr::inAttrMap;
std::unordered_map<int, Attr *> Attr::outAttrMap;

Attr::Attr(AttrType attrType, VarType varType, std::any & value, Node * node) :
        attrType(attrType), varType(varType), fartherNode(node)
{
    this->value = new std::any(value);
    this->init_value = new std::any(value);
    if (attrType == INPUT_ATTR) {
        id = nodeManager.get_NextInputAttrId();
        // inAttrList.push_back(this);
        inAttrMap.insert(std::make_pair(id, this));
    } else {
        id = nodeManager.get_NextOutputAttrId();
        outAttrMap.insert(std::make_pair(id, this));
    }
    this->changeFlag = true;
};

bool Attr::is_change(){
    bool f=changeFlag;
    changeFlag = false;
    return f;
}

Node * Attr::get_fartherNode(){
    return fartherNode;
}

Attr::~Attr() 
{
    if (attrType == INPUT_ATTR) {
        inAttrMap.erase(id);
    } else {
        outAttrMap.erase(id);
    }
    delete value;
};


std::any * Attr::get()
{
    return value;
}


bool Attr::set(const std::any &v, VarType varType)
{
    if(varType!=this->varType){
        return false;
    }else{
        changeFlag = true;
        *(this->value) = v;
        return true;
    }
}


void Attr::init()
{
    *value = *init_value;
}

const VarType & Attr::getType() 
{ 
    return varType; 
}

int Attr::get_id() 
{ 
    return id; 
}

Attr * Attr::getById(int id) 
{
    if(inAttrMap.find(id)!=inAttrMap.end()){
        return inAttrMap.find(id)->second;
    }
    if(outAttrMap.find(id)!=outAttrMap.end()){
        return outAttrMap.find(id)->second;
    }
    return nullptr;
};

// bool Attr::Link(int id0, int id1) 
// {
//     // 将id0赋值到id1
//     Attr *a = getById(id0);
//     Attr *b = getById(id1);
//     if (a == nullptr || b == nullptr) {
//         return false;
//     } else {
//         if (a->set(b->get(), b->varType))
//             return true;
//         return false;
//     }
// }


InAttr::InAttr(std::any & value, const char *name, VarType varType, Node * node) :
			Attr(INPUT_ATTR, varType, value, node), name(name)
{
}
InAttr::~InAttr(){}

void InAttr::render()
{
    ImNodes::BeginInputAttribute(id);
    ImGui::Text(name);
    ImGui::PushItemWidth(60.0f);
    ImNodes::EndInputAttribute();
}

bool InAttr::link(Attr * oa, bool force)
{
    std::any * v = oa->get();
    VarType varType = oa->getType();
    if(varType!=this->varType){
        if(force){
            this->varType = varType;
            this->value = v;
            return true;
        }else{
            return false;
        }
    }else{
        this->value = v;
        return true;
    }
}



OutAttr::OutAttr(std::any & value, const char *name, VarType varType, Node * node) :
			Attr(OUTPUT_ATTR, varType, value, node), name(name) 
{
}
OutAttr::~OutAttr(){}
void OutAttr::render() 
{
    ImNodes::BeginOutputAttribute(id);
    ImGui::PushItemWidth(60.0f);
    ImGui::Indent(60.f - ImGui::CalcTextSize(name).x);
    if (varType == NE_FLOAT || varType == NE_DOUBLE) {
        ImGui::DragFloat(name, (float *) this->value, 0.01f);
    } else if (varType == NE_INT) {
		ImGui::DragInt(name, (int *) this->value, 1);
    }
    ImNodes::EndOutputAttribute();
};


void OutAttr::link(bool force)
{
    for(auto it=next.begin(); it<next.end(); it++)
    {
        (*it)->link(this, force);
    }
}

void OutAttr::pushNext(InAttr * ia)
{
    next.push_back(ia);
}

}  //namespace NodeEditor