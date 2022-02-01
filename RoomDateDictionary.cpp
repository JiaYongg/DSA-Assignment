#include "Dictionary.h"
#include <string>
// constructor
Dictionary::Dictionary() {
	for (int i = 0; i < MAX_SIZE;i++)
	{
		items[i] = NULL;
	}
	size = 0;
};

// destructor is to remove dynamic memory
// static memory is destroyed when program ends. But not dynamic memory
// auto called by program, programmer does not call this destructor
Dictionary::~Dictionary(){
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			Node* temp = items[i];
			while (temp != NULL)
			{
				items[i] = temp->next;
				temp->next = NULL;
				delete temp;
				temp = items[i];
			}
		}
	}
};

int charvalue(char c)
{
	if (isalpha(c))
	{
		if (isupper(c))
			return (int)c - (int)'A';
		else
			return (int)c - (int)'a' + 26;
	}
	else
		return -1;
}


int Dictionary::hash(KeyType key){
	int total = charvalue(key[0]);
	for (int i = 1;i < key.length();i++) {
		total = total * 52 + charvalue(key[i]);
		total %= MAX_SIZE;
	}
	return total;
};

// add a new item with the specified key to the Dictionary
// pre : none
// post: new item is added to the Dictionary
//       size of Dictionary is increased by 1
bool Dictionary::add(KeyType newKey, ItemType newItem){
	int index = hash(newKey);
	Node* newNode = new Node;
	newNode->item = newItem;
	newNode->key = newKey;
	newNode->next = NULL;
	if (items[index]==NULL) {
		items[index] = newNode;
	}
	else {
		Node* currentNode = items[index];
		if (currentNode->key == newKey) {
			return false;
		}
		while (currentNode->next!=NULL)
		{
			currentNode = currentNode->next;
			if (currentNode->key == newKey) {
				return false;
			}
		}
		currentNode->next = newNode;
	}
	size += 1;
	return true;
};

// remove an item with the specified key in the Dictionary
// pre : key must exist in the Dictionary
// post: item is removed from the Dictionary
//       size of Dictionary is decreased by 1
void Dictionary::remove(KeyType key){
	int index = hash(key);
	if (items[index] != NULL) {
		Node* currentNode = items[index];
		//more than one
		if(currentNode->next!=NULL) {
			//first Node
			if (currentNode->key == key) {
				items[index] = currentNode->next;
				delete currentNode;
			}
			//rest
			else {
				while (currentNode->next != NULL)
				{
					Node* nextNode = currentNode->next;
					if (nextNode->key == key) {
						currentNode->next = nextNode->next;
						//nextNode->item = nullptr;
						delete nextNode;
					}
				}
			}
		}
		//for one only
		else {
			if (currentNode->key == key) {
				items[index] = NULL;
				delete currentNode;
			}
		}
		size -= 1;
	}
};


// get an item with the specified key in the Dictionary (retrieve)
// pre : key must exist in the dictionary
// post: none
// return the item with the specified key from the Dictionary
ItemType Dictionary::get(KeyType key){
	int index = hash(key);
	if (items[index] != NULL) {
		Node* currentNode = items[index];
		if (currentNode->key == key) {
			return currentNode->item;
		}
		while (currentNode->next != NULL)
		{
			currentNode = currentNode->next;
			if (currentNode->key == key) {
				return currentNode->item;
			}
		}
	}
};

// check if the Dictionary is empty
// pre : none
// post: none
// return true if the Dictionary is empty{}; otherwise returns false
bool Dictionary::isEmpty(){
	return size == 0;
};

// check the size of the Dictionary
// pre : none
// post: none
// return the number of items in the Dictionary
int Dictionary::getLength(){
	return size;
};

//------------------- Other useful functions -----------------

// display the items in the Dictionary
void Dictionary::print(){
	string s;
	for (int i = 0;i < MAX_SIZE;i++) {
		if (items[i] != NULL) {
			Node* currentNode = items[i];
			s += currentNode->key + ":" + currentNode->item + ",";
			while (currentNode->next != NULL) {
				currentNode = currentNode->next;
				s += currentNode->key + ":" + currentNode->item + ",";
			}
		}
	}
	std::cout << s<<endl;
};