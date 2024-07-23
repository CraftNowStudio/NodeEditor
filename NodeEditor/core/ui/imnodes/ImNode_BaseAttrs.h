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
	Attr(AttrType attrType, VarType varType);
	~Attr();

	int get_id();

	static Attr *getById(int id) ;

	virtual void render() = 0;
	virtual std::any *get() = 0;
	virtual bool set(std::any *v, VarType varType, bool force = false) = 0;
	virtual void init() = 0; //重置value

	static bool Link(int id0, int id1);

	VarType varType;
	static std::vector<Attr *> attrList;

protected:
	//一个数据可以被多个attr共用
	int id;
	AttrType attrType;

private:
};
// std::vector<Attr *> Attr::attrList;

template <class valueType = float>
class InAttr : public Attr {
public:
	InAttr(valueType value, const char *text, VarType varType = NE_FLOAT) :
			Attr(INPUT_ATTR, varType) {
		this->text = text;
		this->value = value;
	};
	~InAttr(){};
	void render() {
		ImNodes::BeginInputAttribute(id);
		ImGui::Text(text);
		ImGui::PushItemWidth(60.0f);
		ImNodes::EndInputAttribute();
	};
	std::any *get() {
		return (std::any *)&value;
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
	valueType value;
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
	std::any *get() {
		return (std::any *)&value;
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
	valueType value;
};
} //namespace NodeEditor