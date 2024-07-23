#include "core/nepch.h"

#include "ImNode_BaseAttrs.h"
#include "ImNode_Base.h"
#include <any>

namespace NodeEditor {
    
std::vector<Attr *> Attr::attrList;

Attr::Attr(AttrType attrType, VarType varType) :
        attrType(attrType), varType(varType) {
    if (attrType == INPUT_ATTR) {
        id = nodeManager.get_NextInputAttrId();
    } else {
        id = nodeManager.get_NextOutputAttrId();
    }
    attrList.push_back(this);
};

Attr::~Attr() {
    for (auto it = attrList.begin(); it < attrList.end(); it++) {
        if (this == *it) {
            attrList.erase(it);
        }
    }
};

int Attr::get_id() { return id; }

Attr * Attr::getById(int id) {
    for (auto it = attrList.begin(); it < attrList.end(); it++) {
        if (id == (*it)->id) {
            return *it;
        }
    }
    return nullptr;
};

bool Attr::Link(int id0, int id1) {
    // 将id0赋值到id1
    Attr *a = getById(id0);
    Attr *b = getById(id1);
    if (a == nullptr || b == nullptr) {
        return false;
    } else {
        if (a->set(b->get(), b->varType))
            return true;
        return false;
    }
}

}