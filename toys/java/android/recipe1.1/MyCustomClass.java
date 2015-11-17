package com.example.cindygregory.helllo;

import java.io.Serializable;

public class MyCustomClass implements Serializable {
    private static final long serialVersionUID = 1L;
    String _name;
    String _email;

    public void setName(String name) {
        _name = name;
    }
    public String Name() {
        return _name;
    }
    public void setEmail(String email) {
        _email = email;
    }
    public String Email() {
        return _email;
    }
}
