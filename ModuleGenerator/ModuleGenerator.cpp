// ModuleGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <regex>
#include <vector>

using namespace std;


vector<string> get_input(const int _argc, char** _argv)
{
	vector<string> OutParam(_argc, "");

	string parttern("=");
	regex r(parttern);

	for (size_t i = 0; i < _argc; i++)
	{
		string param(*(_argv + i));

		vector<string> v(sregex_token_iterator(param.begin(), param.end(), r, -1), sregex_token_iterator());
		for (auto re : v)
		{
			cout << re << endl;
		}
		//printf("%i get ( %s , %s) \n", i, result[1].str(), result[2].str());

	}

	string param("a=b=c=d");

	vector<string> v(sregex_token_iterator(param.begin(), param.end(), r, -1), sregex_token_iterator());
	for (auto re : v)
	{
		cout << re << endl;
	}

	int* a = new int[]{1, 5, 6, 8, 9};
	int b = *(a+2);
	int c = sizeof(a) / sizeof(int*);
	int d = _msize(a) /sizeof(int);
	vector<int> vv(d);
	for (auto re : vv)
	{
		cout << re << endl;
	}
	return OutParam;
}


int main(int argc, char** argv)
{
	/*for (size_t i = 0; i < argc; i++)
	{
		printf("%i ,arvg == %s, *arvg == %p \n", i, *(argv+i), **argv);
	}*/
	
	auto out_param = get_input(argc, argv);
	
	system("pause");

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
