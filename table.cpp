#include <iostream>
#include <cstring>
#include <sstream>
#include "table.h"

using namespace std;


Table::Table(unsigned int max_entries) {
	numentries = max_entries;
	p1 = new bucket[max_entries];
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

 void merge(vector<Entry> b, vector<Entry>::iterator a, int leftsize, int rightsize) {
	vector<Entry>* temp;
	int copied = 0;
	int leftcopy = 0;
	int rightcopy = 0;
	temp = new vector<Entry>(leftsize + rightsize);
	while ((leftcopy < leftsize) && (rightcopy < rightsize)) {
		if ((a + leftcopy)->get_key() < ((a + leftcopy + rightcopy))->get_key()) {
			int alpha;
			string beta;
			alpha = ((a + leftcopy))->get_key();
			beta = ((a + leftcopy))->get_data();
			(temp->at(copied)).set_key(alpha);
			(temp->at(copied)).set_data(beta);
			copied++;
			leftcopy++;
		}
		else {

			int alpha;
			string beta;
			alpha = ((a + rightcopy + leftsize))->get_key();
			beta = ((a + rightcopy + leftsize))->get_data();
			(temp->at(copied)).set_key(alpha);
                        (temp->at(copied)).set_data(beta);
			copied++;	
			rightcopy++;
		}
	}
	while (leftcopy < leftsize) {
 
		int alpha;
                 string beta;
                 alpha = ((a + leftcopy))->get_key();
                 beta = ((a + leftcopy))->get_data();
                (temp->at(copied)).set_key(alpha);
		(temp->at(copied)).set_data(beta);
		copied++;
		leftcopy++;
	}
	 while (rightcopy < rightsize) {
 
		int alpha;
                 string beta;
                 alpha = ((a + rightcopy + leftsize))->get_key();
                 beta = ((a + rightcopy + leftsize))->get_data();
                (temp->at(copied)).set_key(alpha);
                (temp->at(copied)).set_data(beta);
                copied++;
                rightcopy++;
        }
	for (int j = 0; j < leftsize + rightsize; j++) {
		int alpha;
                 string beta;
                 alpha = (temp->at(j)).get_key();
                 beta = (temp->at(j)).get_data();
                (a + j)->set_key(alpha);
                (a + j)->set_data(beta);
		
	}
	temp->clear();
}
	


 void mergesort(vector<Entry> b, vector<Entry>::iterator a, int size) {
	int leftsize;
	int rightsize;
	if (size > 1) {
		leftsize = size/2;
		rightsize = size - leftsize;
		mergesort(b, a, leftsize);
		mergesort(b, a + leftsize,rightsize);
		merge(b, a, leftsize, rightsize);
	}
}



std::ostream& operator<< (std::ostream& out, const Table& t) {
	bucket p2;
	p2.arr = vector<Entry>((t.returnbuck(0))->arr.size());
	for (int i = 0; i < (t.returnbuck(0))->arr.size(); i++) {
		unsigned int alpha;
		string beta;
		alpha = ((t.returnbuck(0))->arr.at(i)).get_key();
		beta = ((t.returnbuck(0))->arr.at(i)).get_data();
		((p2.arr).at(i)).set_key(alpha);
		((p2.arr).at(i)).set_data(beta);
		(p2.size)++;
	}
	for (int i = 1; i < t.returnsize(); i++) {
		(p2.arr).insert((p2.arr).end(), (t.returnbuck(i))->arr.begin(), (t.returnbuck(i))->arr.end());
		(p2.size) = (p2.size) + (t.returnbuck(i))->arr.size();
	}
	mergesort((p2.arr), (p2.arr).begin(), (p2.arr).size());
	for (int i = 0; i < (p2.arr).size(); i++) {
		out << ((p2.arr).at(i)).get_key() << ":" << ((p2.arr).at(i)).get_data() << "\n";
	}
	return out;
}
