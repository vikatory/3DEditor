#pragma once
#include <string>

class CEditConfig							// ����
{
public:
	static CEditConfig* getInstance() {return m_instance; }
	std::string currentPath();
	std::string resourcePath();
	std::string iconPath();

private:
	static CEditConfig* m_instance;
	CEditConfig() {}
	CEditConfig(const CEditConfig&) {};		//�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
	CEditConfig& operator=(const CEditConfig&) {};

};


// TODO: ע�ᵽCGarbo ����

