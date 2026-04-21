#include <bits/stdc++.h>
using namespace std;

namespace LIST {

struct NODE {
    int val;
    NODE* next;
};

static NODE* head = nullptr;
static int len = 0;

void init() { head = nullptr; len = 0; }

static NODE* move_to(int i) {
    NODE* cur = head;
    while (i--) cur = cur->next;
    return cur;
}

void insert(int i, int x) {
    NODE* node = new NODE{ x, nullptr };
    if (len == 0) {
        node->next = node; head = node; len = 1; return;
    }
    if (i == 0) {
        NODE* tail = move_to(len - 1);
        node->next = head; tail->next = node; head = node; ++len; return;
    }
    if (i == len) {
        NODE* tail = move_to(len - 1);
        tail->next = node; node->next = head; ++len; return;
    }
    NODE* prev = move_to(i - 1);
    node->next = prev->next; prev->next = node; ++len;
}

void remove(int i) {
    if (len == 0) return;
    if (len == 1) { delete head; head = nullptr; len = 0; return; }
    if (i == 0) {
        NODE* tail = move_to(len - 1);
        NODE* old = head; head = head->next; tail->next = head; delete old; --len; return;
    }
    NODE* prev = move_to(i - 1);
    NODE* cur = prev->next; prev->next = cur->next; delete cur; --len;
}

void remove_insert(int i) {
    if (len <= 1) return;
    if (i == len - 1) return;
    if (i == 0) { head = head->next; return; }
    // Compute tail before modifying links to avoid breaking traversal
    NODE* tail = move_to(len - 1);
    NODE* prev = move_to(i - 1);
    NODE* cur = prev->next; prev->next = cur->next;
    tail->next = cur; cur->next = head;
}

void get_length() { cout << len << '\n'; }

void query(int i) {
    if (i < 0 || i >= len) { cout << -1 << '\n'; return; }
    NODE* cur = move_to(i); cout << cur->val << '\n';
}

void get_max() {
    if (len == 0) { cout << -1 << '\n'; return; }
    int mx = INT_MIN; NODE* cur = head;
    for (int k = 0; k < len; ++k) { mx = max(mx, cur->val); cur = cur->next; }
    cout << mx << '\n';
}

void clear() {
    if (!head) { len = 0; return; }
    NODE* tail = move_to(len - 1); tail->next = nullptr;
    NODE* cur = head; while (cur) { NODE* nxt = cur->next; delete cur; cur = nxt; }
    head = nullptr; len = 0;
}

} // namespace LIST

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if (!(cin >> n)) return 0;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
            case 0: LIST::get_length(); break;
            case 1: cin >> p >> x; LIST::insert(p, x); break;
            case 2: cin >> p; LIST::query(p); break;
            case 3: cin >> p; LIST::remove(p); break;
            case 4: cin >> p; LIST::remove_insert(p); break;
            case 5: LIST::get_max(); break;
        }
    }
    LIST::clear();
    return 0;
}
