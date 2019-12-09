#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Node {
	Node* next;
	Node* prev;
	int value;
	int key;
	Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
	Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
	map<int, Node*> mp; //map the key to the node in the linked list
	int cp;  //capacity
	Node* tail; // double linked list tail pointer
	Node* head; // double linked list head pointer
	virtual void set(int, int) = 0; //set function
	virtual int get(int) = 0; //get function

};

//--- zoncpp edited ----------------------------------------------------------------------------
class LRUCache : Cache 
{
public:
	LRUCache(int ic) { cp = ic; tail = head = NULL; };
	virtual ~LRUCache() { for (auto var : mp)  if(var.second != NULL) delete var.second; }
	void set(int key, int val) 
	{
		Node* todeleted = NULL;
		int curSize = mp.size();
		auto f = mp.find(key);
		if (f != mp.end())
			todeleted = f->second;
		else if (curSize >= cp)
			todeleted = head;
		if (todeleted != NULL)
		{
			if (todeleted->next != NULL)
				todeleted->next->prev = todeleted->prev;
			else
				tail = todeleted->prev;
			if (todeleted->prev != NULL)
				todeleted->prev->next = todeleted->next;
			else
				head = todeleted->next;
			
			mp.erase(todeleted->key);
			delete todeleted;
		}

		Node* t = new Node(tail, NULL, key, val);
		if(tail != NULL) tail->next = t;
		if (curSize == 0)
			head = t;
		else if (curSize == 1)
			head->next = t;
		t->prev = tail;
		mp.insert(std::pair<int, Node*>(key, t));
		tail = t;
	}
	int get(int key) 
	{ 
		if (mp.find(key) == mp.end()) return -1;
		return mp[key]->value; 
	}
};
//----------------------------------------------------------------------------------------------------

int main() 
{
  int n, capacity, i;
	cin >> n >> capacity;
	LRUCache l(capacity);
	for (i = 0; i < n; i++) {
		string command;
		cin >> command;
		if (command == "get") {
			int key;
			cin >> key;
			cout << l.get(key) << endl;
		}
		else if (command == "set") {
			int key, value;
			cin >> key >> value;
			l.set(key, value);
		}
	}
	return 0;
}
