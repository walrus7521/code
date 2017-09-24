#ifndef _ATOM_H_
#define _ATOM_H_

int         Atom_length(const char *str);
const char *Atom_new(const char *str, int len);
const char *Atom_string(const char *str);
const char *Atom_int(long n);


#endif // _ATOM_H_
