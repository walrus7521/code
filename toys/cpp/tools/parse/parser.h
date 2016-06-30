// ================================================================
// $Id: simple_file_parser.h,v 1.3 2010/08/02 16:59:30 jdl Exp jdl $
//
// Copyright (C) 2010 Joe Linoff
//
// This source code is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see http://www.gnu.org/licenses/.
//
// ----------------------------------------------------------------
//
// Simple file parser that carries over some of the semantics
// from the LALR(n) parser. Namely it supports C++ style
// single line comments (//), multi-line C style comments
// and it ignores blank lines.
//
// It was developed to allow use to use a single paradigm
// for parsing the sites, tnames and nodes files.
// ================================================================
#ifndef include_simple_file_parser_h
#define include_simple_file_parser_h
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

class simple_file_parser
{
public:
    typedef std::vector<std::string> tokens_t;
    simple_file_parser();
    ~simple_file_parser();
    static bool file_exists(const char* fn);
    static bool file_exists(const std::string& fn);
    bool open(const std::string& fn);
    void close();
    inline unsigned get_line_number() const {return m_lineno;}
    inline const std::string& get_file_name() const {return m_fn;}
    bool eof() const;
    void rewind();
    size_t get_next_line();
    bool get_next_line(size_t num_tokens,
                       const std::string& tok1 = "",
                       const std::string& tok2 = "",
                       const std::string& tok3 = "",
                       const std::string& tok4 = "",
                       const std::string& tok5 = "",
                       const std::string& tok6 = "",
                       const std::string& tok7 = "",
                       const std::string& tok8 = "");
    size_t get_num_tokens() const {return m_tokens.size();}
    const std::string& get_token(size_t i) const {return m_tokens[i];}
    unsigned get_token_uint(size_t i) const {return atoi(m_tokens[i].c_str());}
    bool is_token_uint(size_t i) const;
    unsigned get_token_int(size_t i) const {return atoi(m_tokens[i].c_str());}
    bool is_token_int(size_t i) const;
    void set_single_char_tokens(const char* tokens);
    const char* get_single_char_tokens() const;

private:
    simple_file_parser(const simple_file_parser& obj);
    simple_file_parser& operator=(const simple_file_parser& obj);
    char* skip_to_end_of_comment(char* p);
    char* skip_comments(char* p);
    char* skip_whitespace(char* p);
    char* skip_to_whitespace(char* p);
    char* is_continuation_line(char* line) const;
    void add_token(char* token);

    std::string    m_fn;
    std::ifstream* m_ifs;
    tokens_t       m_tokens;
    unsigned       m_lineno;
    char*          m_buf;
    unsigned       m_bufsz;
    unsigned       m_v;
    bool           m_single_char_tokens[256];
    bool           m_in_comment;
};

#endif

