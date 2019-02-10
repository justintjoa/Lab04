#include <iostream>
#include <cstring>
#include <sstream>
#include "table.h"

using namespace std;

Table::Table() {
	numentries = 100;
	int a;
	a = 0;
	list.resize(100);
	for (vector<Entry>::iterator i = list.begin(); i < list.end(); i++) {
		(*i).set_key(a);
		(*i).set_data("");
		a++;
	}
}

Table::Table(int size) {
	numentries = size;
	int a;
	a = 0;
	list.resize(size);
        for (vector<Entry>::iterator i = list.begin(); i < list.end(); i++) {
                (*i).set_key(a);
                (*i).set_data("");
                a++;
        }
}           

Table::Table(unsigned int entries, std::istream& input) {
	numentries = entries;
        int a;
        a = 0;
	list.resize(entries);
        for (vector<Entry>::iterator i = list.begin(); i < list.end(); i++) {
                (*i).set_key(a);
                (*i).set_data("");
                a++;
        }
	for (int i = 0; i < a; i++) {   
		Entry e;
  		input >> e;
		int a;
		a = (e.get_key())%numentries;
		while ((list.at(a)).access_count() != 0) {
			a = 1 + a%(numentries - 2);
		}
		(list.at(a)).set_data(e.get_data());
	}
}

void Table::put(unsigned int key, std::string data) {
	int a;
	a = key%numentries;
	(list.at(a)).set_data(data);
}

void Table::put(Entry e) {
	int a;
	a = (e.get_key())%numentries;
	(list.at(a)).set_data(e.get_data());
}

std::string Table::get(unsigned int key) const {
	std::ostringstream oss;
  	oss << (list.at(key)).get_data(); 
  	return oss.str();
}

bool Table::remove(unsigned int key) {
	if ((list.at(key)).access_count() == 0) {
		return false;
	}
	else {
		Entry e;
		e.set_key(key);
		e.set_data("");
		this->put(e);
		return true;
	}
}

int Table::returnsize() const {
	return numentries;
}
Entry Table::returnentry(int key) const {
        return list.at(key);
}

std::ostream& operator<< (std::ostream& out, const Table& t) {
	for (int i = 0; i < t.returnsize(); i++) {
		out << (t.returnentry(i)).get_key() << ":" <<
		(t.returnentry(i)).get_data() << "\n";
	}
	return out;
}
