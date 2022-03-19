#include <iostream>

using namespace std;

class Foo {
  public:
    static void *operator new(size_t);
    static void operator delete(void *, size_t);

  private:
    int doop;
    //long scoop;
};

static void *Foo::operator new(size_t size) {
     cout << "Foo new\n";
     void *p = malloc(size);
     //[[maybe_unused]]long doop = 12345432;
     //[[maybe_unused]] long scoop = 12345;
     return p;
}

static void Foo::operator delete(void* p, size_t size) {
    cout << "Foo delete(" << size << ")\n";
    free(p);
}

class Bar : public Foo {
  public:
    static void *operator new(size_t);
    static void operator delete(void *, size_t);
    int datum;
};

union Node {			// Not a class, not a struct: a union!
    Node *next;
    char pad[sizeof(Bar)];
};
static Node *freelist;

static void *Bar::operator new(size_t) {
    if (freelist == nullptr) {				// Out of free nodes?
	constexpr int NODES_PER_PAGE = 8192/sizeof(Node);  // A bunch of them
	Node *n = new Node[NODES_PER_PAGE];		// Allocate many
	// Link all the new free nodes into the freelist
	freelist = n;
	for (int i=0; i<NODES_PER_PAGE-1; i++, n++)
	    n->next = n+1;
	n->next = nullptr;
    }
    void *result = freelist;	// Get the first node
    freelist = freelist->next;	// Remove it from the free list
    return result;
}

static void Bar::operator delete(void *p, size_t) {
    if (!p) return;				// Pesky null pointer!
    // Return this node to the list of free nodes.
    Node *n = reinterpret_cast<Node *>(p);
    n->next = freelist;
    freelist = n;
}

int main() {
    cout << "sizeof(int) = " << sizeof(int) << '\n'
	 << "sizeof(Bar) = " << sizeof(Bar) << '\n'
	 << "sizeof(Foo) = " << sizeof(Foo) << '\n';
//    for(int i = 0; i < 10000000; i++) {
    Bar *r = new Bar;
    Bar *s = new Bar;
    Foo *q = new Foo;
    cout << "r=" << r << '\n'
	 << "s=" << s << '\n'
	 << "q=" << q << '\n';
    delete r;
    delete s;
    delete q;
//    }
    return 0;
}
