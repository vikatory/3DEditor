#include "settings.h"
#include <boost/filesystem.hpp>
#include <iostream>
using namespace std;

namespace bf = boost::filesystem;				// �򵥱���

CEditConfig* CEditConfig::m_instance = new CEditConfig();			// TODO: ע�ᵽCGarbo ����

string CEditConfig::currentPath()
{
	bf::path oCurPath = bf::current_path();		// ȡ�õ�ǰĿ¼, һ����cpp�ļ��У�����exe�ó������У�����exe���ڵ��ļ���
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
