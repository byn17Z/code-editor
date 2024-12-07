#ifndef _debugger_h
#define _debugger_h

#include <vector>
#include <string>
#include <unordered_map>
#include <array>

class VT{
	public:
	std::vector<std::array<std::string,4>> table;
	
    VT(){}
	void add(std::array<std::string,4>& v); //����һ�б�����Ϣ 
	void add(std::array<std::string, 2>& v); //�޸�һ�б�����Ϣ
	void del(const std::string& scope); // ɾ��ĳ���������ڵı��� 
	std::array<std::string, 4> get(const std::string& variable) const;
	VT& operator=(const VT& other); // ���ظ�ֵ�����
};

class VTs{
	public:
	std::unordered_map<int,VT> map;
	int sz = 0;
	
	VTs();
	void setstep(int line,VT vt); //����line����״̬����Ϊvt 
	VT getstep(int line); //��ȡ��line����VT 
	int size(); //��ȡVTs�Ĵ�С
};

#endif
