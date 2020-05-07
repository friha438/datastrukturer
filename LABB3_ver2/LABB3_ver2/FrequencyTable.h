/*  Moa Gutenwik, moagu002
	Frida Hartman, friha438 */

#pragma once

#define TABLEROW_H

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <string>
#include <algorithm>


//Class with objects for each row in the table
class TableFreq
{
private:
	std::string key;
	int counter;

public:
	TableFreq() :
		key(NULL), counter(0) { };

	TableFreq(std::string s, int c) :
		key{ s }, counter(c) { };

	std::string& getKey() {
		return key;
	}

	int& getCounter() {
		return counter;
	}

	bool operator<(const TableFreq& t) const {
		if (key < t.key)
		{
			return true;
		}
		return false;
	}

	bool operator>(const TableFreq& t) const {
		return (!operator<(t));
	}

	void increaseCounter() {
		counter++;
	}

};

