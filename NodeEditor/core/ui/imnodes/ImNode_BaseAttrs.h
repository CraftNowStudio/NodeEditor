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

class Attr 
{
public:
	Attr(AttrType attrType, VarType varType, std::any & value);
	~Attr();

	int get_id();

	static Attr *getById(int id);

	virtual void render() = 0;
	std::any * get();						//获取value
	bool set(const std::any &v, VarType varType);	//与link不同，set只传值
	void init(); 							//重置value为init_value
	const VarType &getType();

	// static bool Link(int id0, int id1);

	// static std::vector<Attr *> inAttrList;
	// static std::vector<Attr *> outAttrList;
	static std::unordered_map<int, Attr *> inAttrMap;
	static std::unordered_map<int, Attr *> outAttrMap;
protected:
	int id;
	AttrType attrType;
	VarType varType;
	std::any * value;		//一个value可以被多个attr共用
	std::any * init_value;	//默认value
};
// std::vector<Attr *> Attr::attrList;


class InAttr : public Attr 
{
public:
	InAttr(std::any & value, const char *name, VarType varType);
	~InAttr();
	void render();
	bool link(Attr * oa, bool force = false);//输入节点只能被连接，此处为接受link动作

private:
	const char *name;
};


class OutAttr : public Attr 
{
public:
	OutAttr(std::any & value, const char *name, VarType varType);
	~OutAttr();
	void render();
	void link(bool force = false);				//输出节点可以主动连接,此处为执行link动作
	void pushNext(InAttr * ia);							//

private:
	const char *name;
	std::vector<InAttr *> next;
};
} //namespace NodeEditor