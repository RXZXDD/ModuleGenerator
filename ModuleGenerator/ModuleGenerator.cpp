// ModuleGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <regex>
#include <vector>
#include <iosfwd>
#include <direct.h>
#include <io.h>
#include <Windows.h>

using namespace std;

#define BUILD_CS_FILENAME(ModuleName) ModuleName + ".Build.cs"

#define HEADER_FILENAME(ModuleName) ModuleName + ".h"

#define CPP_FILENAME(ModuleName) ModuleName + ".cpp"

#define BUILD_CS_TEMPLATE "/TemplateFile/Build_cs_template.txt"

#define HEADER_TEMPLATE "/TemplateFile/Header_template.txt"

#define CPP_TEMPLATE "/TemplateFile/Cpp_template.txt"

//new module name
static string module_name;

//new module path
static string path;

//read template file path, default to exe path
static string run_path;


bool get_input(const int _argc, char** _argv)
{
	string parttern("=");
	regex r(parttern);

	for (size_t i = 1; i < _argc; i++)
	{
		string param(*(_argv + i));

		vector<string> v(sregex_token_iterator(param.begin(), param.end(), r, -1), sregex_token_iterator());
		if (!v.empty())
		{
			if (v[0]._Equal("ModuleName"))
			{
				//cout <<"module" << v[1].c_str() << endl;
				module_name = v[1];
			}
			else if (v[0]._Equal("Path"))
			{
				path = v[1] + "\\" + module_name;
				//cout <<"path" << v[1].c_str() << endl;
			}
			else
			{
				printf("unknown key %s", v[0].c_str());
			}
		}

	}


	return !module_name.empty() && !path.empty();
}

//replace [ModuleName] in template file
string ReplaceChunk(const char* in_buffer)
{
	string line(in_buffer);
	string parttern("[ModuleName]");
	size_t idx = line.find(parttern);

	while (idx < line.length())
	{
		line.replace(idx, parttern.length(), module_name);
		idx = line.find(parttern);
	}

	return line;
}

bool create_build_cs()
{
	ifstream in(run_path + BUILD_CS_TEMPLATE);
	if (in.fail())
	{
		std::cout << "build cs read failed" << endl;
		return false;
	}

	string full_path = regex_replace(path, regex("\\\\"), "/") + "/";
	if (_access(full_path.c_str(), 0) == -1)
	{
		if (-1 == _mkdir(full_path.c_str()))
		{
			std::cout << "path create failed" << endl;

			return false;
		}
	}
	
	string full_file_name = full_path + "/" + BUILD_CS_FILENAME(module_name);

	ofstream out(full_file_name);

	if (!out.is_open())
	{
		std::cout << "create failed" << endl;
		return false;
	}

	char buff[1024] = { 0 };
	while (in.getline(buff, sizeof(buff)))
	{
		//cout << buff << endl;
		out << ReplaceChunk(buff).c_str() << endl;
	}
	out.close();

	std::cout << BUILD_CS_FILENAME(module_name) << " created at " << full_file_name << endl;

	return true;
}

bool create_header()
{
	ifstream in(run_path + HEADER_TEMPLATE);
	if (in.fail())
	{
		std::cout << "header tmplate read failed" << endl;
		return false;
	}

	string full_path = path + "\\Public\\";

	full_path = regex_replace(full_path, regex("\\\\"), "/");

	if (_access(full_path.c_str(), 0) == -1)
	{
		if (-1 == _mkdir(full_path.c_str()))
		{
			std::cout << "path create failed" << endl;

			return false;
		}
	}

	string full_file_name = full_path + HEADER_FILENAME(module_name);


	ofstream out(full_file_name);

	if (!out.is_open())
	{
		std::cout << "create new file failed" << endl;
		return false;
	}

	char buff[1024] = { 0 };
	while (in.getline(buff, sizeof(buff)))
	{
		//cout << buff << endl;
		out << ReplaceChunk(buff).c_str() << endl;
	}
	out.close();

	std::cout << HEADER_FILENAME(module_name) << " created at " << full_file_name  << endl;

	return true;
}

bool create_cpp()
{
	ifstream in(run_path + CPP_TEMPLATE);
	if (in.fail())
	{
		std::cout << "header tmplate read failed" << endl;
		return false;
	}
	string full_path = path + "\\Private\\";

	full_path = regex_replace(full_path, regex("\\\\"), "/");

	string full_file_name = full_path + CPP_FILENAME(module_name);

	if (_access(full_path.c_str(), 0) == -1)
	{
		if (-1 == _mkdir(full_path.c_str()))
		{
			std::cout << "path create failed" << endl;

			return false;
		}
	}

	ofstream out(full_file_name);

	if (!out.is_open())
	{
		std::cout << "create new file failed" << endl;
		return false;
	}

	char buff[1024] = { 0 };
	while (in.getline(buff, sizeof(buff)))
	{
		//cout << buff << endl;
		out << ReplaceChunk(buff).c_str() << endl;
	}
	out.close();

	std::cout << CPP_FILENAME(module_name) << " created at " << full_file_name  << endl;

	return true;
}

int main(int argc, char** argv)
{
	
	if (!get_input(argc, argv))
	{
		cout << "no input arg... 请输入参数 ModuleName=[新模块名] Path=[新模块产出路径]";
		system("pause");
		return 0;
	}

	char _runPath[MAX_PATH];
	GetModuleFileName(NULL, (LPSTR)_runPath, MAX_PATH);

	string RunPath(_runPath);

	size_t pos = RunPath.find("\\ModuleGenerator.exe");
	RunPath.replace(pos, strlen("\\ModuleGenerator.exe"), "");

	//cout << "--" << RunPath << endl;

	run_path = regex_replace(RunPath, regex("\\\\"), "/");

	create_build_cs();
	create_header();
	create_cpp();

	//string tmp;
	//while (in >> tmp)
	//{
	//	cout << tmp << endl;
	//}
	
	
	//system("pause");

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
