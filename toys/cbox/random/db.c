#include <stdio.h>
#include <stdlib.h>


// https://www.codingunit.com/c-tutorial-binary-file-io
// TODO:
//  create an index file off account number and offset
//  on opening database, have option to rescan to update index file
// Flow:
//    when accessing an account:
//        1. scan index file for existence
//        2. if exists, update and rewrite
//        3. if not exists,
//            a. create new account
//            b. allocate new index and file offset
//            c. write new account record to file


struct rec
{
    int w,x,y,z;
};

void hexdump(const unsigned char *buffer, unsigned int length)
{
    char OffsetBuf[10];
    unsigned int LastStart = 0, i, k, j;
    fflush(dbfile);
    dump(dbfile);

    fclose(dbfile);
    return 0;
}

#if 0
class account
{
public:
    account(int n = 0, double bal = 0.0): acctNo(n), balance(bal) {}
    void update(char type, double amt) {
        if (type == 'D') {
            balance += amt;
        } else {
            balance -= amt;
        }
    }
    friend ostream& operator<< (ostream& ostr, const account& acct) {
        ostr << acct.acctNo << ": " << acct.balance << ": " << acct.file_offset;
        return ostr;
    }
    int getAcctNo() {
    return acctNo;
    }

//private:
    int acctNo;
    double balance;
    long file_offset;
};

#if 0
void access()
{
    fstream f;
    f.open("data.bin", ios::in | ios::binary);
    f.seekg(0, ios::beg);
    f.seekg(sizeof(int), ios::cur);
    f.seekg(0, ios::end);
    cout << f.tellg() << '\n';
    cout << f.tellg()/sizeof(int) << '\n';
}
#endif




int main()
{
    fstream acctFile;
    account acct;

    int i, n;
    char type;
    double amt;

    acctFile.open("accounts.dat", ios::in | ios::out | ios::trunc | ios::binary);

    if (!acctFile) {
        cerr << "cannot create 'accounts.dat'\n";
        exit(1);
    }

    acctFile.seekg(0, ios::beg);

    // write 5 bogus records
    for (i = 0; i < 5; i++) {
        acct = account(i);
        acct.file_offset = acctFile.tellg();
        acctFile.write((char *) &acct, sizeof(account));
    }

    // ui
    while (true) {
        cout << "Enter acct#, type (D or W), and amount: ";
        cin >> n;
        if (n == -1) {
            break;
        }
        cin >> type >> amt;

        //acct = account();

        // seek to record n
        int seekloc = n * sizeof(account);
        cout << "seek: " << seekloc << '\n';

        acctFile.seekg(n*sizeof(account), ios::beg);
        // read record and update balance
        acctFile.read((char *) &acct, sizeof(account));

    if (acct.getAcctNo() == n) {
        cout << "account already exists.\n";
        acct.update(type, amt);
    } else {
        cout << "account does not exists, creating new one.\n";
        acct = account(n);
        acct.update(type, amt);
    }

        // seek back to previous record
        acctFile.seekg(-int(sizeof(account)), ios::cur);
        acctFile.write((char *) &acct, sizeof(account));
    }

    // output final state
    cout << '\n' << "Final state of accounts\n";
    outputAccounts(acctFile);

    acctFile.close();

    return 0;

}

void outputAccounts(fstream &f)
{
    account acct;

    // go to end of file
    f.seekg(0, ios::end);
    
    // calc number of records
    int n = f.tellg()/sizeof(account), i;
    cout << "there are: " << n << "records\n";

    f.seekg(0, ios::beg);

    for (i = 0; i < n; ++i) {
        f.read((char *) &acct, sizeof(account));
        cout << acct << '\n';
    }
}
#endif

