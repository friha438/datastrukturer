/*File to test exercise 3 of lab 3*/

/*  Moa Gutenwik, moagu002
	Frida Hartman, friha438 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <fstream>
#include <string>
#include <cassert>  //assert

#include "BinarySearchTree.h"
#include "frequencytable.h"

using namespace std;

bool issymbol(char c)
{
	if (c != '.' && c != '!' && c != ',' && c != '?' && c != ':' && c != '/' && c != '(' && c != ')' && c != ';' && c != '"') return true;
	return false;
}

void lowerCase(std::string& t)
{
	//Args: (startpunkt, slutpunkt, resultat, funktion)
	std::transform(t.begin(), t.end(), t.begin(), ::tolower);
}
void eraseSymbol(std::string& str, std::string& temp) 
{
	copy_if(str.begin(), str.end(), back_inserter(temp), issymbol);
}

int main()
{
	BinarySearchTree<TableFreq> t;
	BinarySearchTree<TableFreq>::Iterator it;
	//ifstream file("text.txt");
	ifstream file("text_long.txt");

	if (!file)
	{
		cout << "couldn't open file" << endl;
		return 1;
	}

	vector<string> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
	file.close();


	for (auto j : V1)
	{
		string temp = "";
		lowerCase(j);
		eraseSymbol(j, temp);
		TableFreq* rad = new TableFreq(temp, 1);

		it = t.contains(*rad);

		if (it != t.end()) {		
			it->increaseCounter();
		}
		else {
			t.insert(*rad);
		}
	}

	for (auto i : t) {
		std::cout << left <<setw(12) << i.getKey() << setw(12) << i.getCounter() << std::endl;
	}

	return 0;
}

