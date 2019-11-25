#include <iostream>
#include <algorithm>

using namespace std;

class BST {
    struct node {
        int data, bFactor, count;
        node *left;
        node *right;
    };
    node *root;
    bool h;

    void makeEmpty(node *t) {
        if (t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    node *insert(int x, node *t) {
        if (t == NULL) // If the tree is empty
        {
            t = new node;
            h = true;
            t->count = 1;
            t->data = x;
            t->bFactor = 0;
            t->left = t->right = NULL;
        } else if (x < t->data) // Insertion in left
        {
            t->left = insert(x, t->left);
            if (h) {
                switch (t->bFactor) {
                    case 1:
                        t->bFactor = 0;
                        h = false;
                        break;
                    case 0:
                        t->bFactor--;
                        break;
                    case -1:
                        // Balancing
                        if (t->left->bFactor == -1)
                            t = singleRightRotate(t);
                        else
                            t = doubleLeftRotate(t);
                        t->bFactor = 0;
                        h = false;
                        break;
                }
            }
        } else if (x > t->data) {
            t->right = insert(x, t->right);
            if (h) {
                switch (t->bFactor) {
                    case -1:
                        t->bFactor = 0;
                        h = false;
                        break;
                    case 0:
                        t->bFactor++;
                        break;
                    case 1:
                        // Balancing
                        if (t->right->bFactor == 1)
                            t = singleLeftRotate(t);
                        else
                            t = doubleRightRotate(t);
                        t->bFactor = 0;
                        h = false;
                        break;
                }
            }
        } else {
            t->count++;
            h = false;
        }
        return t;
    }


    node *singleRightRotate(node *&t) {
        node *u = t->left;
        t->left = u->right;
        u->right = t;
        t->bFactor = 0;
        t = u;
        return t;
    }

    node *singleLeftRotate(node *&t) {
        node *u = t->right;
        t->right = u->left;
        u->left = t;
        t->bFactor = 0;
        t = u;
        return t;
    }

    node *doubleLeftRotate(node *&t) {
        node *u = t->left;
        node *v = u->right;
        u->right = v->left;
        v->left = u;
        t->left = v->right;
        v->right = t;
        if (v->bFactor == -1) {
            t->bFactor = 1;
        } else
            t->bFactor = 0;
        if (v->bFactor == 1) {
            u->bFactor = -1;
        } else
            u->bFactor = 0;
        t = v;
        return t;
    }

    node *doubleRightRotate(node *&t) {
        node *u = t->right;
        node *v = u->left;
        u->left = v->right;
        v->right = u;
        t->right = v->left;
        v->left = t;
        if (v->bFactor == 1) {
            t->bFactor = -1;
        } else
            t->bFactor = 0;
        if (v->bFactor == -1) {
            u->bFactor = 1;
        } else
            u->bFactor = 0;
        t = v;
        return t;
    }

    node *balance1(node *&t) {
        switch (t->bFactor) {
            case -1:
                t->bFactor = 0;
                break;
            case 0:
                t->bFactor = 1;
                break;
            case 1:
                node *t1 = t->right;
                node *t2 = t1->left;
                int b1 = t1->bFactor;
                if (b1 >= 0) {
                    t = singleLeftRotate(t);
                    if (b1 == 0) {
                        t->bFactor = 1;
                        t1->bFactor = -1;
                        h = false;
                    } else {
                        t->bFactor = 0;
                        t1->bFactor = 0;
                    }
                } else {
                    t = doubleRightRotate(t);
                    t2->bFactor = 0;
                }
                break;
        }
        return t;
    }

    node *balance2(node *&t) {
        switch (t->bFactor) {
            case 1:
                t->bFactor = 0;
                break;
            case 0:
                t->bFactor = -1;
                break;
            case -1:
                node *t1 = t->left;
                node *t2 = t1->right;
                int b1 = t1->bFactor;
                if (b1 <= 0) {
                    t = singleRightRotate(t);
                    if (b1 == 0) {
                        t->bFactor = -1;
                        t1->bFactor = 1;
                        h = false;
                    } else {
                        t->bFactor = 0;
                        t1->bFactor = 0;
                    }
                } else {
                    t = doubleLeftRotate(t);
                    t2->bFactor = 0;
                }
                break;
        }
        return t;
    }

    node *findMin(node *t) {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }


    node *del(node *&p, node *&q) {
        if (p->right != NULL) {
            del(p->right, q);
            if (h)
                balance2(p);
        } else {
            q->data = p->data;
            q->count = p->count;
            p = p->left;
            h = true;
        }
        return q;
    }

    node *remove(int x, node *&t) {
        node *q;
        // Element not found
        if (t == NULL) {
            cout << "Element not found";
            h = false;
            return NULL;
        }
            // Searching element
        else if (x < t->data) {
            remove(x, t->left);
            if (h) {
                balance1(t);
            }
        } else if (x > t->data) {
            remove(x, t->right);
            if (h) {
                balance2(t);
            }
        } else {
            q = t;
            if ((q->left == NULL) && (q->right == NULL)) {
                t = NULL;
                h = true;
            } else if (q->right == NULL) {
                t = q->left;
                h = true;
            } else if (q->left == NULL) {
                t = q->right;
                h = true;
            } else {
                del(q->left, q);
                if (h)
                    balance1(t);
            }
        }
        return t;
    }

    node *find(int d, node *r) {
        if (r == NULL) {
            return NULL;  // not found
        }
        if (r->data == d) {
            return r; // found
        }

        if (d <= r->data) {
            // left
            if (r->left != NULL)
                return find(d, r->left); // recursive search by left
            else {
                return NULL; // not found
            }
        } else {
            //right
            if (r->right)
                return find(d, r->right);// recursive search by right
            else {
                return NULL; // not found
            }
        }
    }

    node *PrintTree(node *w, int l) // function for output the tree with r-level
    {
        int i;

        if (w != NULL) {
            PrintTree((w->right), l + 1);
            for (i = 1; i <= l; i++) cout << "   ";
            cout << (*w).data << endl;
            PrintTree((w->left), l + 1);
        }
        return w;
    }

public:
    BST() {
        root = NULL;
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display(int x) {
        root = PrintTree(root, x);
    }

    node *find(int x) {
        return find(x, root);
    }
};

int main() {
    BST t;
    int i, p;
    while (true) {
        cout
                << "Choose:\n1: Insert element\n2: Delete element\n3: Search element\n4: Output the Tree\n5: Exit\n";
        cin >> i;
        switch (i) {
            case 1:
                cout << "Value for insertion: ";
                cin >> p;
                t.insert(p);
                break;
            case 2:
                cout << "Value for deletion: ";
                cin >> p;
                t.remove(p);
                break;
            case 3:
                cout << "Value for search: ";
                cin >> p;
                if (t.find(p) == NULL)
                    cout << "Value not found\n";
                else
                    cout << "Value was found\n";
                break;
            case 4:
                t.display(0);
                break;
            case 5:
                return 0;
        }
    }
}
