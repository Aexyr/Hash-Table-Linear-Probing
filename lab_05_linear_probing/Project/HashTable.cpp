#include "HashTable.h"

ostream & operator << (ostream & out, const HashTable & hash)
{
	int temp;
	for (int i = 0; i < 11; ++i) 
	{
		temp = hash.table[i];
		out << "Index " << i << ": ";
		if (temp == -1)
			out << "E ";
		else
			out << hash.table[i];
		out << "\n";
	}

	return out;
}

HashTable::HashTable()
{
	capacity = CAPACITY;
	numOfElements = 0;
	table = new int[capacity];

	for (int i = 0; i < 11; ++i) 
		table[i] = -1;
}

HashTable::HashTable(int cap)
{
	capacity = cap;
	numOfElements = 0;
	table = new int[cap];

	for (int i = 0; i < cap; ++i) 
		table[i] = -1;
}

HashTable::HashTable(const HashTable & otherHash)
{
	capacity = otherHash.capacity;
	numOfElements = otherHash.numOfElements;
	table = new int[capacity];

	for (int i = 0; i < capacity; ++i)
		table[i] = otherHash.table[i];
}

void HashTable::insert(int key)
{
	int index = hashValue(key);
	bool added = false;

	if (numOfElements == capacity)
		cout << "Table is already full!!!" << endl;
	else 
	{
		while (!added) 
		{
			if (table[index] == -1) 
			{
				table[index] = key;
				++numOfElements;
				added = true;
			} 
			else
				index = (index == capacity) ? 0 : index + 1;
		}
	}
}

bool HashTable::search(int key) const
{
	int index = hashValue(key), counter = 0;
	while (counter <= capacity && table[index] != -1) 
	{
		if (table[index] == key)
			return true;

		index = (index == capacity) ? 0 : index + 1;
		++counter;
	}

	return false;
}

int HashTable::getCapacity() const
{
	return capacity;
}

HashTable HashTable::operator=(const HashTable & otherHash)
{
	if (this != &otherHash)
	{
		if (capacity != otherHash.capacity)
		{
			delete[] table;
			capacity = otherHash.capacity;
			table = new int[capacity];
		}
		for (int i = 0; i < otherHash.numOfElements; ++i)
			table[i] = otherHash.table[i];
		numOfElements = otherHash.numOfElements;
	}
	else
		cerr << "Attempted assignment to itself.";

	return *this;
}

int HashTable::operator[](int index) const
{
	return table[index];
}

HashTable::~HashTable()
{
	delete[] table;
	table = NULL;
}

int HashTable::hashValue(int key) const
{
	return key % capacity;
}
