//
//  table.h
//  W19 - Lab04
//
#ifndef table_h
#define table_h
#include <iostream>
#include "entry.h"
#include <vector>

using namespace std;

class Table {
public:
	Table();
	Table(int size);
	Table(unsigned int entries, std::istream& input);
	void put(unsigned int key, std::string data);
	void put(Entry e);
	std::string get(unsigned int key) const;
	bool remove(unsigned int key);
	friend std::ostream& operator<< (std::ostream& out,const Table& t);
	int returnsize() const;
	Entry returnentry(int key) const;

private:
	int numentries;
	vector<Entry> list;

};

#endif /* table_h */
