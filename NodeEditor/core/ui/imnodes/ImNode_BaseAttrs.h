#pragma once

#include "ImNode_Base.h"
#include <any>
#include <vector>

namespace NodeEditor {
enum AttrType { INPUT_ATTR,
	OUTPUT_ATTR };
enum VarType { NE_INT,
	NE_FLOAT,
	NE_STRING,
	NE_DOUBLE,
	NE_VECTOR_INT };

class Attr {
public:
	Attr(AttrType attrType, VarType varType, std::any value);
	~Attr();

	int get_id();

	static Attr *getById(int id) ;

	virtual void render() = 0;
	virtual std::any& get() { return value;};
	virtual bool set(std::any *v, VarType varType, bool force = false) = 0;
	virtual void init() = 0; //重置value
	const VarType &getType() { return varType; }

	static bool Link(int id0, int id1);

	static std::vector<Attr *> attrList;
protected:
	//一个数据可以被多个attr共用
	int id;
	AttrType attrType;
	VarType varType;
	std::any value;
};
// std::vector<Attr *> Attr::attrList;


class InAttr : public Attr {
public:
	InAttr(std::any value, const char *text, VarType varType = NE_FLOAT) :
			Attr(INPUT_ATTR, varType, value) {
		this->name = text;
	};
	~InAttr(){};
	void render() {
		ImNodes::BeginInputAttribute(id);
		ImGui::Text(name);
		ImGui::PushItemWidth(60.0f);
		ImNodes::EndInputAttribute();
	};
	bool set(std::any *v, VarType varType, bool force = false) {
		if (varType != this->varType) {
			if (force) {
				std::cout << "错误" << std::endl;
			}
			return false;
		}
		this->value = *(std::any *)v;
		return true;
	};
	void init() {
		value = NULL;
	}

private:
	const char *name;
};

template <class valueType = float>
class OutAttr : public Attr {
public:
	OutAttr(valueType value, const char *text, VarType varType = NE_FLOAT) :
			Attr(OUTPUT_ATTR, varType) {
		this->text = text;
		this->value = value;
	};
	~OutAttr(){};
	void render() {
		ImNodes::BeginOutputAttribute(id);
		ImGui::PushItemWidth(60.0f);
		ImGui::Indent(60.f - ImGui::CalcTextSize(text).x);
		if (varType == NE_FLOAT || varType == NE_DOUBLE) {
			ImGui::DragFloat(text, (float *) &this->value, 0.f);
		} else if (varType == NE_INT) {
			ImGui::DragInt(text, (int *) &this->value, 0);
		}
		ImNodes::EndOutputAttribute();
	};
	bool set(std::any *v, VarType varType, bool force = false) {
		if (varType != this->varType) {
			if (force) {
				std::cout << "错误" << std::endl;
			}
			return false;
		}
		this->value = *(valueType *)v;
		return true;
	};
	void init() {
		value = NULL;
	}

private:
	const char *text;
	std::vector<InAttr *> next;
};
} //namespace NodeEditor