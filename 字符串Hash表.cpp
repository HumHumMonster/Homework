#include <string.h>
#include<iostream>
#include<string>

using namespace std;

unsigned int HashCode(string s);

template <typename KeyType, typename ValueType>
struct HashMap {
	struct Pair {
		KeyType key;
		ValueType value;
		Pair* next = NULL;
		Pair() { next = NULL; }
		Pair(KeyType k, ValueType v) {
			key = k; value = v; next = NULL;
		}
	};
	int capacity;
	Pair* headers;
	HashMap(int c = 10) {
		capacity = c;
		headers = new Pair[c];
		memset(headers, NULL, sizeof(Pair) * c);

	}
	~HashMap() {
		delete[] headers;
	}
	Pair* find(KeyType key) {
		unsigned int m = HashCode(key);
		int i = m % capacity;
		Pair* p = &headers[i];
		while (p->next != NULL) {
			if (p->key == key)
				return p;
			p = p->next;
		}
		return p;

	}
	void put(KeyType key, ValueType value){
		Pair* p = find(key);
		if (p->key == key)
			p->value = value;
		else
			p->next = new Pair(key, value);
	}
	void remove(KeyType key) {
		int hashcode = HashCode(key);
		Pair* p = &headers[hashcode];
		while (p) {
			if (p->next.key == key) {
				p->next = p->next->next;
				delete p->next;
				return;
			}
			p = p->next;
		}

	}
	void output() {
		for (int i = 0; i < capacity; i++) {
			Pair* p = headers[i].next;
			cout << "hash code" << i << ":";
			while (p) {
				cout << "{" << p->key << ":" << p->value << "}";
				p = p->next;
			}
			cout << endl;
		}
	}
};
unsigned int HashCode(string s) {
	unsigned int h = 0;
	for (int i = 0; i < s.length(); i++)
		h = h * 131 + s[i];
	return h;
}
int main() {
	HashMap<string, string> map(5);
	map.put("秦王", "李世民");
	map.put("唐太宗", "李世民");
	map.put("隋炀帝", "杨广");
	map.put("宋太祖", "赵匡胤");
	map.put("清太祖", "努尔哈赤");
	map.put("宋高宗", "赵构");
	map.put("秦王", "赢政");
	map.output();
	return 0;

}


