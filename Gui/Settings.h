#pragma once
#include <string>

class CEditConfig							// ����
{
public:
	static CEditConfig* getInstance() {return m_instance; }
	std::string resourcePath();
	std::string iconPath();

private:
	static CEditConfig* m_instance;
	CEditConfig() {}
	CEditConfig(const CEditConfig&) {};		//�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
	CEditConfig& operator=(const CEditConfig&) {};
	std::string currentPath();
	std::string m_CurrentPath = currentPath();

};


// TODO: ע�ᵽCGarbo ����

