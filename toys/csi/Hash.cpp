#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

struct ContactList {
    // Equal function for hash.
    bool operator==(const ContactList & that) const {
        return unordered_set <string >( names.begin (), names.end ()) ==
        unordered_set <string >( that.names.begin (), that.names.end ());
    }
    vector <string > names;
};

// Hash function for ContactList .
struct HashContactList {
    size_t operator()(const ContactList & contacts) const {
        size_t hash_code = 0;
        for (const string& name : unordered_set <string >( contacts .names.begin (),
            contacts.names.end ())) {
                hash_code ^= hash <string >()(name);
        }
        return hash_code ;
    }
};

vector <ContactList > MergeContactLists (const vector <ContactList >& contacts) {
    unordered_set <ContactList , HashContactList > unique_contacts (
    contacts.begin (), contacts.end ());
    return { unique_contacts .begin (), unique_contacts .end ()};
}

void list(ContactList& cl)
{
    for (std::vector<string>::iterator si = cl.names.begin();
            si != cl.names.end(); ++si) {
        cout << *si << endl;
    }
}

void test()
{
    vector<string> names = {"cindy", "gretchen", "bart"};
    ContactList cl;// = new ContactList();
    cl.names = names;

    vector<string> names2 = {"bob", "jack", "george"};
    ContactList cl2; // = new ContactList();
    cl2.names = names2;

    vector<ContactList> vcl; // = new vector<ContactList>();
    vcl.push_back(cl);
    vcl.push_back(cl2);

    //list(cl);
    //list(cl2);
    //cout << endl;

    vector<ContactList> nvcl = MergeContactLists(vcl);
    for (std::vector<ContactList>::iterator si = nvcl.begin();
             si != nvcl.end(); ++si) {
        list(*si);
    }

}

int main()
{
    test();
    return 0;

}
