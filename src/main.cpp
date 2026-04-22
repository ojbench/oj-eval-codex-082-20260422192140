// Problem 082 - Linked Hash Map implementation and CLI
#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* next = nullptr;      // per-key singly-linked list next
    Node* timePre = nullptr;   // global doubly-linked list prev
    Node* timeNext = nullptr;  // global doubly-linked list next
    int key = 0;
    string value;
};

struct Data { int key; string value; };

class LinkedHashMap;
static vector<Data> traverseByTime(const LinkedHashMap& obj);
static vector<Data> traverseByIndex(const LinkedHashMap& obj);

class LinkedHashMap {
public:
    int len;
    Node** array;
    Node* beg;      // dummy head for time list
    Node* current;  // tail pointer (last real node or beg if empty)
    vector<Data> (*forEachMethod)(const LinkedHashMap&);

    LinkedHashMap(int _len_, bool forEachByTime) {
        len = _len_;
        beg = new Node();
        current = beg;
        array = new Node*[len];
        for (int i = 0; i < len; ++i) array[i] = nullptr;
        if (forEachByTime) forEachMethod = traverseByTime; else forEachMethod = traverseByIndex;
    }

    ~LinkedHashMap() {
        // Delete all nodes via time list
        Node* p = beg->timeNext;
        while (p) {
            Node* nxt = p->timeNext;
            delete p;
            p = nxt;
        }
        delete[] array;
        delete beg;
    }

    void insert(int key, const string& value) {
        if (key < 0 || key >= len) return;
        Node* nd = new Node();
        nd->key = key;
        nd->value = value;
        // insert to per-key list head
        nd->next = array[key];
        array[key] = nd;
        // append to global time list tail (after current)
        nd->timePre = current;
        nd->timeNext = nullptr;
        current->timeNext = nd;
        current = nd;
    }

    void remove(int key, const string& value) {
        if (key < 0 || key >= len) return;
        Node* prev = nullptr;
        Node* cur = array[key];
        while (cur) {
            if (cur->value == value) {
                // unlink from per-key list
                if (prev) prev->next = cur->next; else array[key] = cur->next;
                // unlink from time list in O(1); cur->timePre always exists (at least beg)
                cur->timePre->timeNext = cur->timeNext;
                if (cur->timeNext) cur->timeNext->timePre = cur->timePre; else current = cur->timePre;
                delete cur;
                return; // remove only first matched
            }
            prev = cur;
            cur = cur->next;
        }
    }

    vector<string> ask(int key) const {
        vector<string> res;
        if (key < 0 || key >= len) return res;
        Node* p = array[key];
        while (p) { res.push_back(p->value); p = p->next; }
        return res;
    }

    vector<Data> forEach() const { return forEachMethod(*this); }

    friend vector<Data> traverseByTime(const LinkedHashMap& obj);
    friend vector<Data> traverseByIndex(const LinkedHashMap& obj);
};

static vector<Data> traverseByTime(const LinkedHashMap& obj) {
    vector<Data> res;
    Node* p = obj.beg->timeNext;
    while (p) { res.push_back({p->key, p->value}); p = p->timeNext; }
    return res;
}

static vector<Data> traverseByIndex(const LinkedHashMap& obj) {
    vector<Data> res;
    for (int i = 0; i < obj.len; ++i) {
        Node* p = obj.array[i];
        while (p) { res.push_back({p->key, p->value}); p = p->next; }
    }
    return res;
}

// CLI protocol (deduced):
// We implement a generic runner:
// First line: n m order
//   n = array length, m = number of operations, order = 0 (by index) or 1 (by time)
// Next m lines: commands:
//   insert k v
//   remove k v
//   ask k    -> prints values (head to tail) separated by space on one line; empty line if none
//   foreach  -> prints pairs "k:value" separated by space on one line
// If input is empty, do nothing.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, order;
    if (!(cin >> n >> m >> order)) return 0;
    LinkedHashMap mp(n, order != 0);
    string cmd;
    for (int i = 0; i < m; ++i) {
        if (!(cin >> cmd)) break;
        if (cmd == "insert") {
            int k; string v; cin >> k >> v; mp.insert(k, v);
        } else if (cmd == "remove") {
            int k; string v; cin >> k >> v; mp.remove(k, v);
        } else if (cmd == "ask") {
            int k; cin >> k; vector<string> vec = mp.ask(k);
            for (size_t j = 0; j < vec.size(); ++j) { if (j) cout << ' '; cout << vec[j]; }
            cout << "\n";
        } else if (cmd == "foreach") {
            vector<Data> all = mp.forEach();
            for (size_t j = 0; j < all.size(); ++j) { if (j) cout << ' '; cout << all[j].key << ':' << all[j].value; }
            cout << "\n";
        } else {
            // unknown, skip line
            string line; getline(cin, line);
        }
    }
    return 0;
}
