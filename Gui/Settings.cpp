#include "settings.h"
#include <boost/filesystem.hpp>
#include <iostream>
using namespace std;

namespace bf = boost::filesystem;				// 简单别名

CEditConfig* CEditConfig::m_instance = new CEditConfig();			// TODO: 注册到CGarbo 类中

string CEditConfig::currentPath()
{
	bf::path oCurPath = bf::current_path();		// 取得当前目录, 一般是cpp文件夹，若把exe拿出来运行，就是exe所在的文件夹
	std::string sCurPath = oCurPath.string();
	return sCurPath;
}

string CEditConfig::resourcePath()
{
	string path = currentPath();
	path.append("\\resource");
	return path;
}

string CEditConfig::iconPath()
{
	string path = currentPath();
	path.append("\\resource\\icon");
	return path;
}
