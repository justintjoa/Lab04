#include <iostream>
#include <cstring>
#include <sstream>
#include "table.h"

using namespace std;

Table::Table() {
	numentries = 100;
	p1 = new bucket[100];
}

Table::Table(unsigned int size) {
	numentries = size;
	p1 = new bucket[size];
}           

Table::Table(unsigned int entries, std::istream& input) {
	numentries = entries;
	p1 = new bucket[numentries];
	for (int i = 0; i < entries; i++) {   
		Entry e;
  		input >> e;
		int a;
		a = (e.get_key())%numentries;
		((p1[a]).arr).push_back(e);
		((p1[a]).size)++;
	}
}

bool Table::remove(unsigned int key) {
        int a;
        a = key%numentries;
        bucket* p2; 
        p2 = &(p1[key]);
        for (int i = 0; i < ((p2)->size); i++) {
                if ((p2->arr).at(i) != key) {
                        continue;
                }   
                else {
                        (p2->arr).erase((p2->arr).begin() + i); 
                        ((p2)->size)--;
			return true;
                }
        }
        return false;
}


void Table::put(unsigned int key, std::string data) {
	remove(key);	
	Entry e;
	e.set_key(key);
	e.set_data(data);
	int a;
	a = key%numentries;
	((p1[a]).arr).push_back(e);
        ((p1[a]).size)++;
}

void Table::put(Entry e) {
	remove(e.get_key());
	int a;
	a = (e.get_key())%numentries;
	((p1[a]).arr).push_back(e);
        ((p1[a]).size)++;
}

std::string Table::get(unsigned int key) const {
	std::ostringstream oss;
	int a;
	a = key%numentries;
	bucket* p2;
	p2 = &(p1[a]);
  	for (int i = 0; i < ((p2)->size); i++) {
		if (((p2->arr).at(i)).get_key() != key) {
			continue;
		}
		else {
	
			oss <<  (((p2)->arr).at(i)).get_data(); 
  		}
	}
	return oss.str();
}

int Table::returnsize() const {
	return numentries;
}
Entry Table::returnentry(int key) const {
	int a;
	a = key%numentries;
	bucket* p2;
	p2 = &(p1[a]);
	  for (int i = 0; i < ((p2)->size); i++) {
                if (((p2->arr).at(i)).get_key() != key) {
                        continue;
                }
                else {
                	return ((p2)->arr).at(i);
		}
        }
}

bucket* Table::returnbuck(int index) const {
	return &(p1[index]);
}

std::ostream& operator<< (std::ostream& out, const Table& t) {
	for (int i = 0; i < t.returnsize(); i++) {
		bucket* p2;
		p2 = t.returnbuck(i);
		for (int j = 0; j < p2->size; j++) {
			out << ((p2->arr).at(j)).get_key() << ":" << ((p2->arr).at(j)).get_data() << "\n";
		}
	}
	return out;
}
