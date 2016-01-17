#pragma once
#include <string>

class CEditConfig							// 单例
{
public:
	static CEditConfig* getInstance() {return m_instance; }
	std::string resourcePath();
	std::string iconPath();

private:
	static CEditConfig* m_instance;
	CEditConfig() {}
	CEditConfig(const CEditConfig&) {};		//把复制构造函数和=操作符也设为私有,防止被复制
	CEditConfig& operator=(const CEditConfig&) {};
	std::string currentPath();
	std::string m_CurrentPath = currentPath();

};


// TODO: 注册到CGarbo 类中

