
class QueryResult {
friend class TextQuery;
};

class TextQuery {
public:
    TextQuery() {}
    TextQuery(ifstream& in) {
        string line, word;
        int lineno = 0;
        cout << "okay let's get the data\n";
        while (getline(in, line)) {
            file.push_back(line);
            istringstream words(line);
            while (words >> word) {
                map_strs[word].insert(lineno);
            }
            ++lineno;
        }
        
    }

    ostream& print(ostream& out, const set<int> &qs) {
        for (set<int>::iterator si = qs.begin(); 
                si != qs.end(); ++si) {
                cout << *si << ", ";
        }
        return out;
    }

    set<int>& query(string s) {
        auto& qs = map_strs[s];
        return qs;
    }

    void show() {
       for (auto& x : map_strs) {
            cout << x.first << " : ";
            for (set<int>::iterator vi = x.second.begin(); 
                        vi != x.second.end(); ++vi) {
                cout << *vi << ", ";
            }
            cout << endl;
        }
    }

private:
    vector<string> file;
    map<string, set<int>> map_strs;
};



class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual std::string rep() const = 0;
};

class WordQuery : public Query_base {
    friend class Query;
    WordQuery(const std::string &s): query_word(s){}
    QueryResult eval(const TextQuery &t) const
                { return t.query(query_word); }
    std::string rep() const { return query_word; }
    std::string query_word;
};

class NotQuery : public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) {}
    std::string rep() const { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery&) const;
    Query query;
};

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query&l, const Query &r, std::string s) :
        lhs(l), rhs(r), opSym(s) {}
    std::string rep() const { return "(" + lhs.rep() + " "
        + opSym + " " + rhs.rep() + ")"; }
    Query lhs, rhs;
    std::string opSym;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right) :
        BinaryQuery(left, right, "&") {}
    QueryResult eval(const TextQuery&) const;
};
inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right) :
        BinaryQuery(left, right, "|") {}
    QueryResult eval(const TextQuery&) const;
};
inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));

class Query {
    friend Query operator~(const Query &);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&);
    QueryResult eval(const TextQuery &t) const
                            { return q->eval(t); }
    std::string rep() const { return q->rep(); }
private:
    Query(std::shared_ptr<Query_base> query): q(query) {}
    std::shared_ptr<Query_base> q;
};

inline
Query::Query(const std::string &s) : q(new WordQuery(s)) {}

std::ostream& 
operator<<(std::ostream &os, const Query &query)
{
    return os << query.rep();
}
