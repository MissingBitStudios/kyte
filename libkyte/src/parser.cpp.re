// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "parser.cpp.re" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

// //                    "%code requires" blocks.
#line 10 "parser.yy" // lalr1.cc:408

#include <map>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

#define ENUM_IDENTIFIERS(o) \
        o(undefined)                              /* undefined */ \
        o(function)                               /* a pointer to given function */ \
        o(parameter)                              /* one of the function params */ \
        o(variable)                               /* a local variable */
#define o(n) n,
enum class id_type {  ENUM_IDENTIFIERS(o) };
#undef o

struct identifier
{
    id_type type  = id_type::undefined;
    std::size_t     index = 0; // function#, parameter# within surrounding function, variable#
    std::string     name;
};

#define ENUM_EXPRESSIONS(o) \
        o(nop) o(string) o(number) o(ident)       /* atoms */ \
        o(add) o(neg) o(eq)                       /* transformation */ \
        o(cor) o(cand) o(loop)                    /* logic. Loop is: while(param0) { param1..n } */ \
        o(addrof) o(deref)                        /* pointer handling */ \
        o(fcall)                                  /* function param0 call with param1..n */ \
        o(copy)                                   /* assign: param1 <<- param0 */ \
        o(comma)                                  /* a sequence of expressions */ \
        o(ret)                                    /* return(param0) */

#define o(n) n,
enum class ex_type {  ENUM_EXPRESSIONS(o) };
#undef o

typedef std::list<struct expression> expr_vec;
struct expression
{
    ex_type type;
    identifier      ident{};    // For ident
    std::string     strvalue{}; // For string
    long            numvalue=0; // For number
    expr_vec        params;
    // For while() and if(), the first item is the condition and the rest are the contingent code
    // For fcall, the first parameter is the variable to use as function

    template<typename... T>
    expression(ex_type t, T&&... args) : type(t), params{ std::forward<T>(args)... } {}

    expression()                    : type(ex_type::nop) {}
    expression(const identifier& i) : type(ex_type::ident),  ident(i)            { }
    expression(identifier&& i)      : type(ex_type::ident),  ident(std::move(i)) { }
    expression(std::string&& s)     : type(ex_type::string), strvalue(std::move(s)) { }
    expression(long v)              : type(ex_type::number), numvalue(v) {}

    bool is_pure() const;
    bool is_compiletime_expr() const;

    expression operator%=(expression&& b) && { return expression(ex_type::copy, std::move(b), std::move(*this)); }
};

#define o(n) \
inline bool is_##n(const identifier& i) { return i.type == id_type::n; }
ENUM_IDENTIFIERS(o)
#undef o

#define o(n) \
inline bool is_##n(const expression& e) { return e.type == ex_type::n; } \
template<typename... T> \
inline expression e_##n(T&&... args) { return expression(ex_type::n, std::forward<T>(args)...); }
ENUM_EXPRESSIONS(o)
#undef o

struct function
{
    std::string name;
    expression  code;
    unsigned num_vars = 0,     num_params = 0;
    bool     pure     = false, pure_known = false;

    expression maketemp() { expression r(identifier{id_type::variable, num_vars, "$C" + std::to_string(num_vars)}); ++num_vars; return r; }
};

struct lexcontext;


#line 139 "parser.cpp.re" // lalr1.cc:408

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif


namespace yy {
#line 214 "parser.cpp.re" // lalr1.cc:408

  template <class T, class S = std::vector<T> >
  class stack
  {
  public:
    // Hide our reversed order.
    typedef typename S::reverse_iterator iterator;
    typedef typename S::const_reverse_iterator const_iterator;

    stack ()
      : seq_ ()
    {
      seq_.reserve (200);
    }

    stack (unsigned int n)
      : seq_ (n)
    {}

    inline
    T&
    operator[] (unsigned int i)
    {
      return seq_[seq_.size () - 1 - i];
    }

    inline
    const T&
    operator[] (unsigned int i) const
    {
      return seq_[seq_.size () - 1 - i];
    }

    /// Steal the contents of \a t.
    ///
    /// Close to move-semantics.
    inline
    void
    push (T& t)
    {
      seq_.push_back (T());
      operator[](0).move (t);
    }

    inline
    void
    pop (unsigned int n = 1)
    {
      for (; n; --n)
        seq_.pop_back ();
    }

    void
    clear ()
    {
      seq_.clear ();
    }

    inline
    typename S::size_type
    size () const
    {
      return seq_.size ();
    }

    inline
    const_iterator
    begin () const
    {
      return seq_.rbegin ();
    }

    inline
    const_iterator
    end () const
    {
      return seq_.rend ();
    }

  private:
    stack (const stack&);
    stack& operator= (const stack&);
    /// The wrapped container.
    S seq_;
  };

  /// Present a slice of the top of a stack.
  template <class T, class S = stack<T> >
  class slice
  {
  public:
    slice (const S& stack, unsigned int range)
      : stack_ (stack)
      , range_ (range)
    {}

    inline
    const T&
    operator [] (unsigned int i) const
    {
      return stack_[range_ - i];
    }

  private:
    const S& stack_;
    unsigned int range_;
  };

  /// Abstract a position.
  class position
  {
  public:
    /// Construct a position.
    explicit position (std::string* f = YY_NULLPTR,
                       unsigned int l = 1u,
                       unsigned int c = 1u)
      : filename (f)
      , line (l)
      , column (c)
    {
    }


    /// Initialization.
    void initialize (std::string* fn = YY_NULLPTR,
                     unsigned int l = 1u,
                     unsigned int c = 1u)
    {
      filename = fn;
      line = l;
      column = c;
    }

    /** \name Line and Column related manipulators
     ** \{ */
    /// (line related) Advance to the COUNT next lines.
    void lines (int count = 1)
    {
      if (count)
        {
          column = 1u;
          line = add_ (line, count, 1);
        }
    }

    /// (column related) Advance to the COUNT next columns.
    void columns (int count = 1)
    {
      column = add_ (column, count, 1);
    }
    /** \} */

    /// File name to which this position refers.
    std::string* filename;
    /// Current line number.
    unsigned int line;
    /// Current column number.
    unsigned int column;

  private:
    /// Compute max(min, lhs+rhs) (provided min <= lhs).
    static unsigned int add_ (unsigned int lhs, int rhs, unsigned int min)
    {
      return (0 < rhs || -static_cast<unsigned int>(rhs) < lhs
              ? rhs + lhs
              : min);
    }
  };

  /// Add \a width columns, in place.
  inline position&
  operator+= (position& res, int width)
  {
    res.columns (width);
    return res;
  }

  /// Add \a width columns.
  inline position
  operator+ (position res, int width)
  {
    return res += width;
  }

  /// Subtract \a width columns, in place.
  inline position&
  operator-= (position& res, int width)
  {
    return res += -width;
  }

  /// Subtract \a width columns.
  inline position
  operator- (position res, int width)
  {
    return res -= width;
  }

  /// Compare two position objects.
  inline bool
  operator== (const position& pos1, const position& pos2)
  {
    return (pos1.line == pos2.line
            && pos1.column == pos2.column
            && (pos1.filename == pos2.filename
                || (pos1.filename && pos2.filename
                    && *pos1.filename == *pos2.filename)));
  }

  /// Compare two position objects.
  inline bool
  operator!= (const position& pos1, const position& pos2)
  {
    return !(pos1 == pos2);
  }

  /** \brief Intercept output stream redirection.
   ** \param ostr the destination output stream
   ** \param pos a reference to the position to redirect
   */
  template <typename YYChar>
  inline std::basic_ostream<YYChar>&
  operator<< (std::basic_ostream<YYChar>& ostr, const position& pos)
  {
    if (pos.filename)
      ostr << *pos.filename << ':';
    return ostr << pos.line << '.' << pos.column;
  }

  /// Abstract a location.
  class location
  {
  public:

    /// Construct a location from \a b to \a e.
    location (const position& b, const position& e)
      : begin (b)
      , end (e)
    {
    }

    /// Construct a 0-width location in \a p.
    explicit location (const position& p = position ())
      : begin (p)
      , end (p)
    {
    }

    /// Construct a 0-width location in \a f, \a l, \a c.
    explicit location (std::string* f,
                       unsigned int l = 1u,
                       unsigned int c = 1u)
      : begin (f, l, c)
      , end (f, l, c)
    {
    }


    /// Initialization.
    void initialize (std::string* f = YY_NULLPTR,
                     unsigned int l = 1u,
                     unsigned int c = 1u)
    {
      begin.initialize (f, l, c);
      end = begin;
    }

    /** \name Line and Column related manipulators
     ** \{ */
  public:
    /// Reset initial location to final location.
    void step ()
    {
      begin = end;
    }

    /// Extend the current location to the COUNT next columns.
    void columns (int count = 1)
    {
      end += count;
    }

    /// Extend the current location to the COUNT next lines.
    void lines (int count = 1)
    {
      end.lines (count);
    }
    /** \} */


  public:
    /// Beginning of the located region.
    position begin;
    /// End of the located region.
    position end;
  };

  /// Join two locations, in place.
  inline location& operator+= (location& res, const location& end)
  {
    res.end = end.end;
    return res;
  }

  /// Join two locations.
  inline location operator+ (location res, const location& end)
  {
    return res += end;
  }

  /// Add \a width columns to the end position, in place.
  inline location& operator+= (location& res, int width)
  {
    res.columns (width);
    return res;
  }

  /// Add \a width columns to the end position.
  inline location operator+ (location res, int width)
  {
    return res += width;
  }

  /// Subtract \a width columns to the end position, in place.
  inline location& operator-= (location& res, int width)
  {
    return res += -width;
  }

  /// Subtract \a width columns to the end position.
  inline location operator- (location res, int width)
  {
    return res -= width;
  }

  /// Compare two location objects.
  inline bool
  operator== (const location& loc1, const location& loc2)
  {
    return loc1.begin == loc2.begin && loc1.end == loc2.end;
  }

  /// Compare two location objects.
  inline bool
  operator!= (const location& loc1, const location& loc2)
  {
    return !(loc1 == loc2);
  }

  /** \brief Intercept output stream redirection.
   ** \param ostr the destination output stream
   ** \param loc a reference to the location to redirect
   **
   ** Avoid duplicate information.
   */
  template <typename YYChar>
  inline std::basic_ostream<YYChar>&
  operator<< (std::basic_ostream<YYChar>& ostr, const location& loc)
  {
    unsigned int end_col = 0 < loc.end.column ? loc.end.column - 1 : 0;
    ostr << loc.begin;
    if (loc.end.filename
        && (!loc.begin.filename
            || *loc.begin.filename != *loc.end.filename))
      ostr << '-' << loc.end.filename << ':' << loc.end.line << '.' << end_col;
    else if (loc.begin.line < loc.end.line)
      ostr << '-' << loc.end.line << '.' << end_col;
    else if (loc.begin.column < end_col)
      ostr << '-' << end_col;
    return ostr;
  }


  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class conj_parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // stmt1
      // exprs1
      // expr1
      // p_expr1
      // stmt
      // com_stmt
      // var_defs
      // var_def1
      // exprs
      // c_expr1
      // expr
      char dummy1[sizeof(expression)];

      // NUMCONST
      char dummy2[sizeof(long)];

      // IDENTIFIER
      // STRINGCONST
      // identifier1
      char dummy3[sizeof(std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        RETURN = 258,
        WHILE = 259,
        IF = 260,
        VAR = 261,
        IDENTIFIER = 262,
        NUMCONST = 263,
        STRINGCONST = 264,
        OR = 265,
        AND = 266,
        EQ = 267,
        NE = 268,
        PP = 269,
        MM = 270,
        PL_EQ = 271,
        MI_EQ = 272
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const expression v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const long v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_RETURN (const location_type& l);

    static inline
    symbol_type
    make_WHILE (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_VAR (const location_type& l);

    static inline
    symbol_type
    make_IDENTIFIER (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_NUMCONST (const long& v, const location_type& l);

    static inline
    symbol_type
    make_STRINGCONST (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_OR (const location_type& l);

    static inline
    symbol_type
    make_AND (const location_type& l);

    static inline
    symbol_type
    make_EQ (const location_type& l);

    static inline
    symbol_type
    make_NE (const location_type& l);

    static inline
    symbol_type
    make_PP (const location_type& l);

    static inline
    symbol_type
    make_MM (const location_type& l);

    static inline
    symbol_type
    make_PL_EQ (const location_type& l);

    static inline
    symbol_type
    make_MI_EQ (const location_type& l);


    /// Build a parser object.
    conj_parser (lexcontext& ctx_yyarg);
    virtual ~conj_parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    conj_parser (const conj_parser&);
    conj_parser& operator= (const conj_parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const signed char yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 602,     ///< Last index in yytable_.
      yynnts_ = 24,  ///< Number of nonterminal symbols.
      yyfinal_ = 3, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 34  ///< Number of tokens.
    };


    // User arguments.
    lexcontext& ctx;
  };

  // Symbol number corresponding to token number t.
  inline
  conj_parser::token_number_type
  conj_parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,     2,     2,     2,    25,     2,
      26,    31,    24,    22,    18,    23,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    20,    28,
       2,    21,     2,    19,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    27,     2,    30,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    29,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17
    };
    const unsigned int user_token_number_max_ = 272;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  conj_parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  conj_parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  conj_parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 47: // stmt1
      case 48: // exprs1
      case 49: // expr1
      case 50: // p_expr1
      case 51: // stmt
      case 52: // com_stmt
      case 53: // var_defs
      case 54: // var_def1
      case 55: // exprs
      case 56: // c_expr1
      case 57: // expr
        value.copy< expression > (other.value);
        break;

      case 8: // NUMCONST
        value.copy< long > (other.value);
        break;

      case 7: // IDENTIFIER
      case 9: // STRINGCONST
      case 41: // identifier1
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  conj_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 47: // stmt1
      case 48: // exprs1
      case 49: // expr1
      case 50: // p_expr1
      case 51: // stmt
      case 52: // com_stmt
      case 53: // var_defs
      case 54: // var_def1
      case 55: // exprs
      case 56: // c_expr1
      case 57: // expr
        value.copy< expression > (v);
        break;

      case 8: // NUMCONST
        value.copy< long > (v);
        break;

      case 7: // IDENTIFIER
      case 9: // STRINGCONST
      case 41: // identifier1
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  conj_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  conj_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const expression v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  conj_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const long v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  conj_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  conj_parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  conj_parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 47: // stmt1
      case 48: // exprs1
      case 49: // expr1
      case 50: // p_expr1
      case 51: // stmt
      case 52: // com_stmt
      case 53: // var_defs
      case 54: // var_def1
      case 55: // exprs
      case 56: // c_expr1
      case 57: // expr
        value.template destroy< expression > ();
        break;

      case 8: // NUMCONST
        value.template destroy< long > ();
        break;

      case 7: // IDENTIFIER
      case 9: // STRINGCONST
      case 41: // identifier1
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  conj_parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  conj_parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 47: // stmt1
      case 48: // exprs1
      case 49: // expr1
      case 50: // p_expr1
      case 51: // stmt
      case 52: // com_stmt
      case 53: // var_defs
      case 54: // var_def1
      case 55: // exprs
      case 56: // c_expr1
      case 57: // expr
        value.move< expression > (s.value);
        break;

      case 8: // NUMCONST
        value.move< long > (s.value);
        break;

      case 7: // IDENTIFIER
      case 9: // STRINGCONST
      case 41: // identifier1
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  conj_parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  conj_parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  conj_parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  conj_parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  conj_parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  conj_parser::by_type::type_get () const
  {
    return type;
  }

  inline
  conj_parser::token_type
  conj_parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    44,    63,
      58,    61,    43,    45,    42,    38,    40,    91,    59,   125,
      93,    41,   123,    33
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  conj_parser::symbol_type
  conj_parser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  conj_parser::symbol_type
  conj_parser::make_RETURN (const location_type& l)
  {
    return symbol_type (token::RETURN, l);
  }

  conj_parser::symbol_type
  conj_parser::make_WHILE (const location_type& l)
  {
    return symbol_type (token::WHILE, l);
  }

  conj_parser::symbol_type
  conj_parser::make_IF (const location_type& l)
  {
    return symbol_type (token::IF, l);
  }

  conj_parser::symbol_type
  conj_parser::make_VAR (const location_type& l)
  {
    return symbol_type (token::VAR, l);
  }

  conj_parser::symbol_type
  conj_parser::make_IDENTIFIER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::IDENTIFIER, v, l);
  }

  conj_parser::symbol_type
  conj_parser::make_NUMCONST (const long& v, const location_type& l)
  {
    return symbol_type (token::NUMCONST, v, l);
  }

  conj_parser::symbol_type
  conj_parser::make_STRINGCONST (const std::string& v, const location_type& l)
  {
    return symbol_type (token::STRINGCONST, v, l);
  }

  conj_parser::symbol_type
  conj_parser::make_OR (const location_type& l)
  {
    return symbol_type (token::OR, l);
  }

  conj_parser::symbol_type
  conj_parser::make_AND (const location_type& l)
  {
    return symbol_type (token::AND, l);
  }

  conj_parser::symbol_type
  conj_parser::make_EQ (const location_type& l)
  {
    return symbol_type (token::EQ, l);
  }

  conj_parser::symbol_type
  conj_parser::make_NE (const location_type& l)
  {
    return symbol_type (token::NE, l);
  }

  conj_parser::symbol_type
  conj_parser::make_PP (const location_type& l)
  {
    return symbol_type (token::PP, l);
  }

  conj_parser::symbol_type
  conj_parser::make_MM (const location_type& l)
  {
    return symbol_type (token::MM, l);
  }

  conj_parser::symbol_type
  conj_parser::make_PL_EQ (const location_type& l)
  {
    return symbol_type (token::PL_EQ, l);
  }

  conj_parser::symbol_type
  conj_parser::make_MI_EQ (const location_type& l)
  {
    return symbol_type (token::MI_EQ, l);
  }



} // yy
#line 1632 "parser.cpp.re" // lalr1.cc:408





// User implementation prologue.

#line 1640 "parser.cpp.re" // lalr1.cc:412
// Unqualified %code blocks.
#line 104 "parser.yy" // lalr1.cc:413


struct lexcontext
{
    const char* cursor;
    yy::location loc;
    std::vector<std::map<std::string, identifier>> scopes;
    std::vector<function> func_list;
    unsigned tempcounter = 0;
    function fun;
public:
    const identifier& define(const std::string& name, identifier&& f)
    {
        auto r = scopes.back().emplace(name, std::move(f));
        if(!r.second) throw yy::conj_parser::syntax_error(loc, "Duplicate definition <"+name+">");
        return r.first->second;
    }
    expression def(const std::string& name)     { return define(name, identifier{id_type::variable,  fun.num_vars++,   name}); }
    expression defun(const std::string& name)   { return define(name, identifier{id_type::function,  func_list.size(), name}); }
    expression defparm(const std::string& name) { return define(name, identifier{id_type::parameter, fun.num_params++, name}); }
    expression temp()                           { return def("$I" + std::to_string(tempcounter++)); }
    expression use(const std::string& name)
    {
        for(auto j = scopes.crbegin(); j != scopes.crend(); ++j)
            if(auto i = j->find(name); i != j->end())
                return i->second;
        throw yy::conj_parser::syntax_error(loc, "Undefined identifier <"+name+">");
    }
    void add_function(std::string&& name, expression&& code)
    {
        fun.code = e_comma(std::move(code), e_ret(0l)); // Add implicit "return 0;" at the end
        fun.name = std::move(name);
        func_list.push_back(std::move(fun));
        fun = {};
    }
    void operator ++() { scopes.emplace_back(); } // Enter scope
    void operator --() { scopes.pop_back();     } // Exit scope
};

namespace yy { conj_parser::symbol_type yylex(lexcontext& ctx); }

#define M(x) std::move(x)
#define C(x) expression(x)


#line 1688 "parser.cpp.re" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 1774 "parser.cpp.re" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  conj_parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  conj_parser::conj_parser (lexcontext& ctx_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

  conj_parser::~conj_parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  conj_parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  conj_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  conj_parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  conj_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  conj_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  conj_parser::symbol_number_type
  conj_parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  conj_parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  conj_parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 47: // stmt1
      case 48: // exprs1
      case 49: // expr1
      case 50: // p_expr1
      case 51: // stmt
      case 52: // com_stmt
      case 53: // var_defs
      case 54: // var_def1
      case 55: // exprs
      case 56: // c_expr1
      case 57: // expr
        value.move< expression > (that.value);
        break;

      case 8: // NUMCONST
        value.move< long > (that.value);
        break;

      case 7: // IDENTIFIER
      case 9: // STRINGCONST
      case 41: // identifier1
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  conj_parser::stack_symbol_type&
  conj_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 47: // stmt1
      case 48: // exprs1
      case 49: // expr1
      case 50: // p_expr1
      case 51: // stmt
      case 52: // com_stmt
      case 53: // var_defs
      case 54: // var_def1
      case 55: // exprs
      case 56: // c_expr1
      case 57: // expr
        value.copy< expression > (that.value);
        break;

      case 8: // NUMCONST
        value.copy< long > (that.value);
        break;

      case 7: // IDENTIFIER
      case 9: // STRINGCONST
      case 41: // identifier1
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  conj_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  conj_parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  conj_parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  conj_parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  conj_parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  conj_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  conj_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  conj_parser::debug_level_type
  conj_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  conj_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline conj_parser::state_type
  conj_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  conj_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  conj_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  conj_parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 47: // stmt1
      case 48: // exprs1
      case 49: // expr1
      case 50: // p_expr1
      case 51: // stmt
      case 52: // com_stmt
      case 53: // var_defs
      case 54: // var_def1
      case 55: // exprs
      case 56: // c_expr1
      case 57: // expr
        yylhs.value.build< expression > ();
        break;

      case 8: // NUMCONST
        yylhs.value.build< long > ();
        break;

      case 7: // IDENTIFIER
      case 9: // STRINGCONST
      case 41: // identifier1
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 167 "parser.yy" // lalr1.cc:859
    { ++ctx; }
#line 2221 "parser.cpp.re" // lalr1.cc:859
    break;

  case 3:
#line 167 "parser.yy" // lalr1.cc:859
    { --ctx; }
#line 2227 "parser.cpp.re" // lalr1.cc:859
    break;

  case 4:
#line 168 "parser.yy" // lalr1.cc:859
    { ctx.defun(yystack_[0].value.as< std::string > ()); ++ctx; }
#line 2233 "parser.cpp.re" // lalr1.cc:859
    break;

  case 5:
#line 168 "parser.yy" // lalr1.cc:859
    { ctx.add_function(M(yystack_[4].value.as< std::string > ()), M(yystack_[0].value.as< expression > ())); --ctx; }
#line 2239 "parser.cpp.re" // lalr1.cc:859
    break;

  case 9:
#line 171 "parser.yy" // lalr1.cc:859
    { ctx.defparm(yystack_[0].value.as< std::string > ()); }
#line 2245 "parser.cpp.re" // lalr1.cc:859
    break;

  case 10:
#line 172 "parser.yy" // lalr1.cc:859
    { ctx.defparm(yystack_[0].value.as< std::string > ()); }
#line 2251 "parser.cpp.re" // lalr1.cc:859
    break;

  case 11:
#line 173 "parser.yy" // lalr1.cc:859
    {}
#line 2257 "parser.cpp.re" // lalr1.cc:859
    break;

  case 12:
#line 173 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = M(yystack_[0].value.as< std::string > ()); }
#line 2263 "parser.cpp.re" // lalr1.cc:859
    break;

  case 13:
#line 174 "parser.yy" // lalr1.cc:859
    {}
#line 2269 "parser.cpp.re" // lalr1.cc:859
    break;

  case 15:
#line 175 "parser.yy" // lalr1.cc:859
    {}
#line 2275 "parser.cpp.re" // lalr1.cc:859
    break;

  case 17:
#line 176 "parser.yy" // lalr1.cc:859
    {}
#line 2281 "parser.cpp.re" // lalr1.cc:859
    break;

  case 19:
#line 177 "parser.yy" // lalr1.cc:859
    {}
#line 2287 "parser.cpp.re" // lalr1.cc:859
    break;

  case 21:
#line 178 "parser.yy" // lalr1.cc:859
    {}
#line 2293 "parser.cpp.re" // lalr1.cc:859
    break;

  case 23:
#line 179 "parser.yy" // lalr1.cc:859
    {}
#line 2299 "parser.cpp.re" // lalr1.cc:859
    break;

  case 24:
#line 179 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[0].value.as< expression > ()); }
#line 2305 "parser.cpp.re" // lalr1.cc:859
    break;

  case 25:
#line 180 "parser.yy" // lalr1.cc:859
    {}
#line 2311 "parser.cpp.re" // lalr1.cc:859
    break;

  case 26:
#line 180 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[0].value.as< expression > ()); }
#line 2317 "parser.cpp.re" // lalr1.cc:859
    break;

  case 27:
#line 181 "parser.yy" // lalr1.cc:859
    {}
#line 2323 "parser.cpp.re" // lalr1.cc:859
    break;

  case 28:
#line 181 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[0].value.as< expression > ()); }
#line 2329 "parser.cpp.re" // lalr1.cc:859
    break;

  case 29:
#line 182 "parser.yy" // lalr1.cc:859
    {}
#line 2335 "parser.cpp.re" // lalr1.cc:859
    break;

  case 30:
#line 182 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[1].value.as< expression > ()); }
#line 2341 "parser.cpp.re" // lalr1.cc:859
    break;

  case 31:
#line 183 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[1].value.as< expression > ()); --ctx; }
#line 2347 "parser.cpp.re" // lalr1.cc:859
    break;

  case 32:
#line 184 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_cand(M(yystack_[1].value.as< expression > ()), M(yystack_[0].value.as< expression > ())); }
#line 2353 "parser.cpp.re" // lalr1.cc:859
    break;

  case 33:
#line 185 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_loop(M(yystack_[1].value.as< expression > ()), M(yystack_[0].value.as< expression > ())); }
#line 2359 "parser.cpp.re" // lalr1.cc:859
    break;

  case 34:
#line 186 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_ret(M(yystack_[1].value.as< expression > ()));         }
#line 2365 "parser.cpp.re" // lalr1.cc:859
    break;

  case 35:
#line 187 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[1].value.as< expression > ());        }
#line 2371 "parser.cpp.re" // lalr1.cc:859
    break;

  case 36:
#line 188 "parser.yy" // lalr1.cc:859
    { }
#line 2377 "parser.cpp.re" // lalr1.cc:859
    break;

  case 37:
#line 189 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_comma(); ++ctx; }
#line 2383 "parser.cpp.re" // lalr1.cc:859
    break;

  case 38:
#line 190 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[1].value.as< expression > ()); yylhs.value.as< expression > ().params.push_back(M(yystack_[0].value.as< expression > ())); }
#line 2389 "parser.cpp.re" // lalr1.cc:859
    break;

  case 39:
#line 191 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_comma(M(yystack_[0].value.as< expression > ())); }
#line 2395 "parser.cpp.re" // lalr1.cc:859
    break;

  case 40:
#line 192 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[2].value.as< expression > ()); yylhs.value.as< expression > ().params.push_back(M(yystack_[0].value.as< expression > ())); }
#line 2401 "parser.cpp.re" // lalr1.cc:859
    break;

  case 41:
#line 193 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = ctx.def(yystack_[2].value.as< std::string > ()) %= M(yystack_[0].value.as< expression > ()); }
#line 2407 "parser.cpp.re" // lalr1.cc:859
    break;

  case 42:
#line 194 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = ctx.def(yystack_[0].value.as< std::string > ()) %= 0l; }
#line 2413 "parser.cpp.re" // lalr1.cc:859
    break;

  case 43:
#line 195 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[0].value.as< expression > ()); }
#line 2419 "parser.cpp.re" // lalr1.cc:859
    break;

  case 44:
#line 196 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[0].value.as< expression > ()); }
#line 2425 "parser.cpp.re" // lalr1.cc:859
    break;

  case 45:
#line 197 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_comma(M(yystack_[2].value.as< expression > ())); yylhs.value.as< expression > ().params.splice(yylhs.value.as< expression > ().params.end(), M(yystack_[0].value.as< expression > ().params)); }
#line 2431 "parser.cpp.re" // lalr1.cc:859
    break;

  case 46:
#line 198 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_comma(M(yystack_[0].value.as< expression > ())); }
#line 2437 "parser.cpp.re" // lalr1.cc:859
    break;

  case 47:
#line 199 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[2].value.as< expression > ()); yylhs.value.as< expression > ().params.push_back(M(yystack_[0].value.as< expression > ())); }
#line 2443 "parser.cpp.re" // lalr1.cc:859
    break;

  case 48:
#line 200 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = yystack_[0].value.as< long > ();    }
#line 2449 "parser.cpp.re" // lalr1.cc:859
    break;

  case 49:
#line 201 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[0].value.as< std::string > ()); }
#line 2455 "parser.cpp.re" // lalr1.cc:859
    break;

  case 50:
#line 202 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = ctx.use(yystack_[0].value.as< std::string > ());   }
#line 2461 "parser.cpp.re" // lalr1.cc:859
    break;

  case 51:
#line 203 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[1].value.as< expression > ()); }
#line 2467 "parser.cpp.re" // lalr1.cc:859
    break;

  case 52:
#line 204 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_deref(e_add(M(yystack_[3].value.as< expression > ()), M(yystack_[1].value.as< expression > ()))); }
#line 2473 "parser.cpp.re" // lalr1.cc:859
    break;

  case 53:
#line 205 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_fcall(M(yystack_[2].value.as< expression > ())); }
#line 2479 "parser.cpp.re" // lalr1.cc:859
    break;

  case 54:
#line 206 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_fcall(M(yystack_[3].value.as< expression > ())); yylhs.value.as< expression > ().params.splice(yylhs.value.as< expression > ().params.end(), M(yystack_[1].value.as< expression > ().params)); }
#line 2485 "parser.cpp.re" // lalr1.cc:859
    break;

  case 55:
#line 207 "parser.yy" // lalr1.cc:859
    {yylhs.value.as< expression > ()=M(yystack_[2].value.as< expression > ());}
#line 2491 "parser.cpp.re" // lalr1.cc:859
    break;

  case 56:
#line 207 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = M(yystack_[2].value.as< expression > ()) %= M(yystack_[0].value.as< expression > ()); }
#line 2497 "parser.cpp.re" // lalr1.cc:859
    break;

  case 57:
#line 208 "parser.yy" // lalr1.cc:859
    {yylhs.value.as< expression > ()=M(yystack_[2].value.as< expression > ());}
#line 2503 "parser.cpp.re" // lalr1.cc:859
    break;

  case 58:
#line 208 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_add( M(yystack_[2].value.as< expression > ()), M(yystack_[0].value.as< expression > ())); }
#line 2509 "parser.cpp.re" // lalr1.cc:859
    break;

  case 59:
#line 209 "parser.yy" // lalr1.cc:859
    {yylhs.value.as< expression > ()=M(yystack_[2].value.as< expression > ());}
#line 2515 "parser.cpp.re" // lalr1.cc:859
    break;

  case 60:
#line 209 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_add( M(yystack_[2].value.as< expression > ()), e_neg(M(yystack_[0].value.as< expression > ()))); }
#line 2521 "parser.cpp.re" // lalr1.cc:859
    break;

  case 61:
#line 210 "parser.yy" // lalr1.cc:859
    {yylhs.value.as< expression > ()=M(yystack_[2].value.as< expression > ());}
#line 2527 "parser.cpp.re" // lalr1.cc:859
    break;

  case 62:
#line 210 "parser.yy" // lalr1.cc:859
    { if(!yystack_[0].value.as< expression > ().is_pure()) { yylhs.value.as< expression > () = ctx.temp() %= e_addrof(M(yystack_[2].value.as< expression > ())); yystack_[2].value.as< expression > () = e_deref(yylhs.value.as< expression > ().params.back()); }
                                                              yylhs.value.as< expression > () = e_comma(M(yylhs.value.as< expression > ()), M(yystack_[2].value.as< expression > ()) %= e_add(C(yystack_[2].value.as< expression > ()), M(yystack_[0].value.as< expression > ()))); }
#line 2534 "parser.cpp.re" // lalr1.cc:859
    break;

  case 63:
#line 213 "parser.yy" // lalr1.cc:859
    {yylhs.value.as< expression > ()=M(yystack_[2].value.as< expression > ());}
#line 2540 "parser.cpp.re" // lalr1.cc:859
    break;

  case 64:
#line 213 "parser.yy" // lalr1.cc:859
    { if(!yystack_[0].value.as< expression > ().is_pure()) { yylhs.value.as< expression > () = ctx.temp() %= e_addrof(M(yystack_[2].value.as< expression > ())); yystack_[2].value.as< expression > () = e_deref(yylhs.value.as< expression > ().params.back()); }
                                                              yylhs.value.as< expression > () = e_comma(M(yylhs.value.as< expression > ()), M(yystack_[2].value.as< expression > ()) %= e_add(C(yystack_[2].value.as< expression > ()), e_neg(M(yystack_[0].value.as< expression > ())))); }
#line 2547 "parser.cpp.re" // lalr1.cc:859
    break;

  case 65:
#line 216 "parser.yy" // lalr1.cc:859
    {}
#line 2553 "parser.cpp.re" // lalr1.cc:859
    break;

  case 66:
#line 216 "parser.yy" // lalr1.cc:859
    { if(!yystack_[0].value.as< expression > ().is_pure()) { yylhs.value.as< expression > () = ctx.temp() %= e_addrof(M(yystack_[0].value.as< expression > ())); yystack_[0].value.as< expression > () = e_deref(yylhs.value.as< expression > ().params.back()); }
                                                              yylhs.value.as< expression > () = e_comma(M(yylhs.value.as< expression > ()), M(yystack_[0].value.as< expression > ()) %= e_add(C(yystack_[0].value.as< expression > ()),  1l)); }
#line 2560 "parser.cpp.re" // lalr1.cc:859
    break;

  case 67:
#line 219 "parser.yy" // lalr1.cc:859
    {}
#line 2566 "parser.cpp.re" // lalr1.cc:859
    break;

  case 68:
#line 219 "parser.yy" // lalr1.cc:859
    { if(!yystack_[0].value.as< expression > ().is_pure()) { yylhs.value.as< expression > () = ctx.temp() %= e_addrof(M(yystack_[0].value.as< expression > ())); yystack_[0].value.as< expression > () = e_deref(yylhs.value.as< expression > ().params.back()); }
                                                              yylhs.value.as< expression > () = e_comma(M(yylhs.value.as< expression > ()), M(yystack_[0].value.as< expression > ()) %= e_add(C(yystack_[0].value.as< expression > ()), -1l)); }
#line 2573 "parser.cpp.re" // lalr1.cc:859
    break;

  case 69:
#line 222 "parser.yy" // lalr1.cc:859
    { if(!yystack_[1].value.as< expression > ().is_pure()) { yylhs.value.as< expression > () = ctx.temp() %= e_addrof(M(yystack_[1].value.as< expression > ())); yystack_[1].value.as< expression > () = e_deref(yylhs.value.as< expression > ().params.back()); }
                                                              auto i = ctx.temp(); yylhs.value.as< expression > () = e_comma(M(yylhs.value.as< expression > ()), C(i) %= C(yystack_[1].value.as< expression > ()), C(yystack_[1].value.as< expression > ()) %= e_add(C(yystack_[1].value.as< expression > ()),  1l), C(i)); }
#line 2580 "parser.cpp.re" // lalr1.cc:859
    break;

  case 70:
#line 225 "parser.yy" // lalr1.cc:859
    { if(!yystack_[1].value.as< expression > ().is_pure()) { yylhs.value.as< expression > () = ctx.temp() %= e_addrof(M(yystack_[1].value.as< expression > ())); yystack_[1].value.as< expression > () = e_deref(yylhs.value.as< expression > ().params.back()); }
                                                              auto i = ctx.temp(); yylhs.value.as< expression > () = e_comma(M(yylhs.value.as< expression > ()), C(i) %= C(yystack_[1].value.as< expression > ()), C(yystack_[1].value.as< expression > ()) %= e_add(C(yystack_[1].value.as< expression > ()), -1l), C(i)); }
#line 2587 "parser.cpp.re" // lalr1.cc:859
    break;

  case 71:
#line 228 "parser.yy" // lalr1.cc:859
    {yylhs.value.as< expression > ()=M(yystack_[2].value.as< expression > ());}
#line 2593 "parser.cpp.re" // lalr1.cc:859
    break;

  case 72:
#line 228 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_cor( M(yystack_[2].value.as< expression > ()), M(yystack_[0].value.as< expression > ())); }
#line 2599 "parser.cpp.re" // lalr1.cc:859
    break;

  case 73:
#line 229 "parser.yy" // lalr1.cc:859
    {yylhs.value.as< expression > ()=M(yystack_[2].value.as< expression > ());}
#line 2605 "parser.cpp.re" // lalr1.cc:859
    break;

  case 74:
#line 229 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_cand(M(yystack_[2].value.as< expression > ()), M(yystack_[0].value.as< expression > ())); }
#line 2611 "parser.cpp.re" // lalr1.cc:859
    break;

  case 75:
#line 230 "parser.yy" // lalr1.cc:859
    {yylhs.value.as< expression > ()=M(yystack_[2].value.as< expression > ());}
#line 2617 "parser.cpp.re" // lalr1.cc:859
    break;

  case 76:
#line 230 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_eq(  M(yystack_[2].value.as< expression > ()), M(yystack_[0].value.as< expression > ())); }
#line 2623 "parser.cpp.re" // lalr1.cc:859
    break;

  case 77:
#line 231 "parser.yy" // lalr1.cc:859
    {yylhs.value.as< expression > ()=M(yystack_[2].value.as< expression > ());}
#line 2629 "parser.cpp.re" // lalr1.cc:859
    break;

  case 78:
#line 231 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_eq(e_eq(M(yystack_[2].value.as< expression > ()), M(yystack_[0].value.as< expression > ())), 0l); }
#line 2635 "parser.cpp.re" // lalr1.cc:859
    break;

  case 79:
#line 232 "parser.yy" // lalr1.cc:859
    {}
#line 2641 "parser.cpp.re" // lalr1.cc:859
    break;

  case 80:
#line 232 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_addrof(M(yystack_[0].value.as< expression > ())); }
#line 2647 "parser.cpp.re" // lalr1.cc:859
    break;

  case 81:
#line 233 "parser.yy" // lalr1.cc:859
    {}
#line 2653 "parser.cpp.re" // lalr1.cc:859
    break;

  case 82:
#line 233 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_deref(M(yystack_[0].value.as< expression > ()));  }
#line 2659 "parser.cpp.re" // lalr1.cc:859
    break;

  case 83:
#line 234 "parser.yy" // lalr1.cc:859
    {}
#line 2665 "parser.cpp.re" // lalr1.cc:859
    break;

  case 84:
#line 234 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_neg(M(yystack_[0].value.as< expression > ()));    }
#line 2671 "parser.cpp.re" // lalr1.cc:859
    break;

  case 85:
#line 235 "parser.yy" // lalr1.cc:859
    {}
#line 2677 "parser.cpp.re" // lalr1.cc:859
    break;

  case 86:
#line 235 "parser.yy" // lalr1.cc:859
    { yylhs.value.as< expression > () = e_eq(M(yystack_[0].value.as< expression > ()), 0l); }
#line 2683 "parser.cpp.re" // lalr1.cc:859
    break;

  case 87:
#line 236 "parser.yy" // lalr1.cc:859
    {yylhs.value.as< expression > ()=M(yystack_[2].value.as< expression > ());}
#line 2689 "parser.cpp.re" // lalr1.cc:859
    break;

  case 88:
#line 236 "parser.yy" // lalr1.cc:859
    { auto i = ctx.temp();
                                                              yylhs.value.as< expression > () = e_comma(e_cor(e_cand(M(yystack_[4].value.as< expression > ()), e_comma(C(i) %= M(yystack_[2].value.as< expression > ()), 1l)), C(i) %= M(yystack_[0].value.as< expression > ())), C(i)); }
#line 2696 "parser.cpp.re" // lalr1.cc:859
    break;


#line 2700 "parser.cpp.re" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  conj_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  conj_parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char conj_parser::yypact_ninf_ = -83;

  const signed char conj_parser::yytable_ninf_ = -4;

  const short int
  conj_parser::yypact_[] =
  {
     -83,    51,   -83,   -83,    23,   -83,   -83,   -83,     8,   -83,
      30,    46,   -83,   -83,   111,    59,   -83,   139,    13,    13,
      59,   -83,   -83,   -83,    11,   179,   199,   219,   239,   139,
     -83,   -83,   259,   -83,   -83,    78,    49,    10,   516,   -83,
     -83,    10,   -83,   -83,   139,   111,   111,    47,   -83,   -83,
      62,   -83,    62,   -83,    62,   -83,    62,   -83,    62,    12,
     -83,    62,   -83,   -83,   -83,   -83,    59,   -83,   -83,   -83,
     279,   299,   319,   339,   -83,   -83,   359,   379,   399,   419,
     439,   459,   479,   159,   139,   -83,    12,   -83,   -83,   399,
     -83,   -83,   -83,   -83,   -83,   569,   -83,   575,   -83,    48,
     -83,    48,   -83,   552,   -83,   552,   -83,   -83,    55,   552,
     -83,   534,   -83,   552,   -83,    62,   -83,    62,   -83,     9,
      15,   -83,   -83,   399,   492,   -83,   -83,   -83,   -83,   -83,
     552
  };

  const unsigned char
  conj_parser::yydefact_[] =
  {
       2,     0,     6,     1,     0,    11,    12,     4,     8,    10,
       0,     7,    13,    14,     0,     0,    23,     0,     0,     0,
       0,    50,    48,    49,     0,     0,     0,     0,     0,     0,
      36,    37,     0,     5,    24,     0,    43,     0,    44,     9,
      25,     0,    26,    29,     0,     0,     0,    42,    39,    65,
      66,    67,    68,    83,    84,    81,    82,    79,    80,     0,
      85,    86,    17,    18,    31,    38,     0,    15,    16,    35,
       0,     0,     0,     0,    69,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,    33,    32,     0,
      21,    22,    51,    40,    71,    72,    73,    74,    75,    76,
      77,    78,    61,    62,    63,    64,    27,    46,    45,    28,
      87,     0,    55,    56,    57,    58,    59,    60,    53,     0,
       0,    30,    41,     0,     0,    54,    19,    20,    52,    47,
      88
  };

  const signed char
  conj_parser::yypgoto_[] =
  {
     -83,   -83,   -83,   -83,   -83,   -83,   -83,    18,   -83,    28,
     -83,   -83,   -77,   -17,   -23,   -82,    61,    43,   -83,   -83,
      24,   -12,    14,   -24
  };

  const short int
  conj_parser::yydefgoto_[] =
  {
      -1,     1,     2,     4,     8,    10,    11,    47,    14,    69,
      64,   128,    92,    33,    41,   107,    45,    34,    35,    36,
      48,    37,   108,    38
  };

  const short int
  conj_parser::yytable_[] =
  {
      50,    52,    54,    56,    58,    42,    59,   122,    61,   121,
      90,    67,    49,    90,    43,     9,   126,    42,    21,    22,
      23,    86,     7,    -3,     5,    24,    25,   123,    87,    88,
       6,    12,    42,    39,    26,    27,    28,    29,    68,    44,
      91,   129,   125,    91,    32,   127,    95,    97,    99,   101,
      13,     3,   103,   105,   109,   111,   113,   115,   117,   109,
       5,   120,    74,    75,    15,   109,     6,    66,    89,    85,
      81,    82,    42,   123,    83,    84,    74,    75,    65,    62,
      46,    17,    18,    19,    20,    21,    22,    23,    83,    84,
      93,     0,    24,    25,     0,     0,     0,   119,     0,   109,
     130,    26,    27,    28,    29,     0,    30,    63,     0,     0,
      31,    32,    16,     0,    17,    18,    19,    20,    21,    22,
      23,     0,     0,     0,     0,    24,    25,     0,     0,     0,
       0,     0,     0,     0,    26,    27,    28,    29,     0,    30,
      40,     0,     0,    31,    32,    20,    21,    22,    23,     0,
       0,     0,     0,    24,    25,     0,     0,     0,     0,     0,
     106,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
      51,     0,    26,    27,    28,    29,    21,    22,    23,     0,
     118,     0,    32,    24,    25,     0,     0,     0,     0,     0,
      53,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
      55,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
      57,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
      60,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
      94,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
      96,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
      98,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
     100,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
     102,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
     104,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
     106,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
     110,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
     112,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
     114,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,     0,
     116,     0,    26,    27,    28,    29,    21,    22,    23,     0,
       0,     0,    32,    24,    25,     0,     0,     0,     0,    21,
      22,    23,    26,    27,    28,    29,    24,    25,     0,     0,
       0,     0,    32,     0,     0,    26,    27,    28,    29,     0,
       0,     0,     0,     0,     0,    32,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,     0,    80,    81,    82,
       0,     0,    83,    84,    70,    71,    72,    73,    74,    75,
      76,    77,     0,    79,   124,    80,    81,    82,     0,     0,
      83,    84,    70,    71,    72,    73,    74,    75,    76,    77,
       0,    79,     0,    80,    81,    82,     0,     0,    83,    84,
      71,    72,    73,    74,    75,     0,     0,    72,    73,    74,
      75,    81,    82,     0,     0,    83,    84,    81,    82,     0,
       0,    83,    84
  };

  const signed char
  conj_parser::yycheck_[] =
  {
      24,    25,    26,    27,    28,    17,    29,    89,    32,    86,
       1,     1,     1,     1,     1,     7,     1,    29,     7,     8,
       9,    44,     4,     0,     1,    14,    15,    18,    45,    46,
       7,     1,    44,    15,    23,    24,    25,    26,    28,    26,
      31,   123,   119,    31,    33,    30,    70,    71,    72,    73,
      20,     0,    76,    77,    78,    79,    80,    81,    82,    83,
       1,    84,    14,    15,    18,    89,     7,    18,    21,    41,
      22,    23,    84,    18,    26,    27,    14,    15,    35,     1,
      19,     3,     4,     5,     6,     7,     8,     9,    26,    27,
      66,    -1,    14,    15,    -1,    -1,    -1,    83,    -1,   123,
     124,    23,    24,    25,    26,    -1,    28,    29,    -1,    -1,
      32,    33,     1,    -1,     3,     4,     5,     6,     7,     8,
       9,    -1,    -1,    -1,    -1,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    24,    25,    26,    -1,    28,
       1,    -1,    -1,    32,    33,     6,     7,     8,     9,    -1,
      -1,    -1,    -1,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      31,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    23,    24,    25,    26,     7,     8,     9,    -1,
      -1,    -1,    33,    14,    15,    -1,    -1,    -1,    -1,     7,
       8,     9,    23,    24,    25,    26,    14,    15,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    23,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    21,    22,    23,
      -1,    -1,    26,    27,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    19,    20,    21,    22,    23,    -1,    -1,
      26,    27,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    19,    -1,    21,    22,    23,    -1,    -1,    26,    27,
      11,    12,    13,    14,    15,    -1,    -1,    12,    13,    14,
      15,    22,    23,    -1,    -1,    26,    27,    22,    23,    -1,
      -1,    26,    27
  };

  const unsigned char
  conj_parser::yystos_[] =
  {
       0,    35,    36,     0,    37,     1,     7,    41,    38,     7,
      39,    40,     1,    20,    42,    18,     1,     3,     4,     5,
       6,     7,     8,     9,    14,    15,    23,    24,    25,    26,
      28,    32,    33,    47,    51,    52,    53,    55,    57,    41,
       1,    48,    55,     1,    26,    50,    50,    41,    54,     1,
      57,     1,    57,     1,    57,     1,    57,     1,    57,    48,
       1,    57,     1,    29,    44,    51,    18,     1,    28,    43,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      21,    22,    23,    26,    27,    43,    48,    47,    47,    21,
       1,    31,    46,    54,     1,    57,     1,    57,     1,    57,
       1,    57,     1,    57,     1,    57,     1,    49,    56,    57,
       1,    57,     1,    57,     1,    57,     1,    57,    31,    56,
      48,    46,    49,    18,    20,    46,     1,    30,    45,    49,
      57
  };

  const unsigned char
  conj_parser::yyr1_[] =
  {
       0,    34,    36,    35,    38,    37,    37,    39,    39,    40,
      40,    41,    41,    42,    42,    43,    43,    44,    44,    45,
      45,    46,    46,    47,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      53,    54,    54,    55,    55,    55,    56,    56,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57
  };

  const unsigned char
  conj_parser::yyr2_[] =
  {
       0,     2,     0,     2,     0,     6,     0,     1,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     3,     3,     3,     2,     1,     1,     2,     2,
       3,     3,     1,     1,     1,     3,     1,     3,     1,     1,
       1,     3,     4,     3,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     5
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const conj_parser::yytname_[] =
  {
  "END", "error", "$undefined", "\"return\"", "\"while\"", "\"if\"",
  "\"var\"", "IDENTIFIER", "NUMCONST", "STRINGCONST", "\"||\"", "\"&&\"",
  "\"==\"", "\"!=\"", "\"++\"", "\"--\"", "\"+=\"", "\"-=\"", "','", "'?'",
  "':'", "'='", "'+'", "'-'", "'*'", "'&'", "'('", "'['", "';'", "'}'",
  "']'", "')'", "'{'", "'!'", "$accept", "library", "$@1", "functions",
  "$@2", "paramdecls", "paramdecl", "identifier1", "colon1", "semicolon1",
  "cl_brace1", "cl_bracket1", "cl_parens1", "stmt1", "exprs1", "expr1",
  "p_expr1", "stmt", "com_stmt", "var_defs", "var_def1", "exprs",
  "c_expr1", "expr", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  conj_parser::yyrline_[] =
  {
       0,   167,   167,   167,   168,   168,   169,   170,   170,   171,
     172,   173,   173,   174,   174,   175,   175,   176,   176,   177,
     177,   178,   178,   179,   179,   180,   180,   181,   181,   182,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   207,   208,   208,   209,
     209,   210,   210,   213,   213,   216,   216,   219,   219,   222,
     225,   228,   228,   229,   229,   230,   230,   231,   231,   232,
     232,   233,   233,   234,   234,   235,   235,   236,   236
  };

  // Print the state stack on the debug stream.
  void
  conj_parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  conj_parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 3257 "parser.cpp.re" // lalr1.cc:1167
#line 239 "parser.yy" // lalr1.cc:1168


yy::conj_parser::symbol_type yy::yylex(lexcontext& ctx)
{
    const char* anchor = ctx.cursor;
    ctx.loc.step();
    auto s = [&](auto func, auto&&... params) { ctx.loc.columns(ctx.cursor - anchor); return func(params..., ctx.loc); };
%{ /* Begin re2c lexer */
re2c:yyfill:enable   = 0;
re2c:define:YYCTYPE  = "char";
re2c:define:YYCURSOR = "ctx.cursor";

// Keywords:
"return"                { return s(conj_parser::make_RETURN); }
"while" | "for"         { return s(conj_parser::make_WHILE); }
"var"                   { return s(conj_parser::make_VAR); }
"if"                    { return s(conj_parser::make_IF); }

// Identifiers:
[a-zA-Z_] [a-zA-Z_0-9]* { return s(conj_parser::make_IDENTIFIER, std::string(anchor,ctx.cursor)); }

// String and integer literals:
"\"" [^"]* "\""         { return s(conj_parser::make_STRINGCONST, std::string(anchor+1, ctx.cursor-1)); }
[0-9]+                  { return s(conj_parser::make_NUMCONST, std::stol(std::string(anchor,ctx.cursor))); }

// Whitespace and comments:
"\000"                  { return s(conj_parser::make_END); }
"\r\n" | [\r\n]         { ctx.loc.lines();   return yylex(ctx); }
"//" [^\r\n]*           {                    return yylex(ctx); }
[\t\v\b\f ]             { ctx.loc.columns(); return yylex(ctx); }

// Multi-char operators and any other character (either an operator or an invalid symbol):
"&&"                    { return s(conj_parser::make_AND); }
"||"                    { return s(conj_parser::make_OR); }
"++"                    { return s(conj_parser::make_PP); }
"--"                    { return s(conj_parser::make_MM); }
"!="                    { return s(conj_parser::make_NE); }
"=="                    { return s(conj_parser::make_EQ); }
"+="                    { return s(conj_parser::make_PL_EQ); }
"-="                    { return s(conj_parser::make_MI_EQ); }
.                       { return s([](auto...s){return conj_parser::symbol_type(s...);}, conj_parser::token_type(ctx.cursor[-1]&0xFF)); } // Return that character
%} /* End lexer */
}

void yy::conj_parser::error(const location_type& l, const std::string& m)
{
    std::cerr << (l.begin.filename ? l.begin.filename->c_str() : "(undefined)");
    std::cerr << ':' << l.begin.line << ':' << l.begin.column << '-' << l.end.column << ": " << m << '\n';
}

#include <fstream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <numeric>
#include <set>

/* GLOBAL DATA */
std::vector<function> func_list;

// pure_fcall tells whether the given fcall expression refers
//            to a function that is known to have no side effects,
//            i.e. its only outcome is the return value.
static bool pure_fcall(const expression& exp)
{
    // Identify the called function. Note that that the function
    // may be any arbitrary expression, not only a function identifier.
    if(const auto& p = exp.params.front(); is_ident(p) && is_function(p.ident))
        if(auto called_function = p.ident.index; called_function < func_list.size())
            if(const auto& f = func_list[called_function]; f.pure_known && f.pure)
                return true;
    return false;
}

// is_pure tells whether the expression is safe to duplicate,
// or even delete if the return value is not used,
// without changing the program semantics.
bool expression::is_pure() const
{
    // if any parameter is not pure, the expression is not pure
    for(const auto& e: params) if(!e.is_pure()) return false;
    switch(type)
    {
        // Function calls are judged using a lookup.
        case ex_type::fcall: return pure_fcall(*this);
        // Assigns are not pure.
        case ex_type::copy:  return false;
        // Returns and not pure either, because they do not evaluate into a value.
        case ex_type::ret:   return false;
        // Loops are not pure, because they may be infinite,
        // in which case deleting the loop would alter the program behavior.
        case ex_type::loop:  return false;
        // Anything else is pure
        default:             return true;
    }
}

bool expression::is_compiletime_expr() const
{
    for(const auto& e: params) if(!e.is_compiletime_expr()) return false;
    switch(type)
    {
        case ex_type::number: case ex_type::string:
        case ex_type::add:    case ex_type::neg:    case ex_type::cand:  case ex_type::cor:
        case ex_type::comma:  case ex_type::nop:
            return true;
        case ex_type::ident:
            return is_function(ident);
        default:
            return false;
    }
}

// callv: Invokes the functor with args.
// Returns its return value, except, if func returns void, callv() returns def instead.
template<typename F, typename B, typename... A>
static decltype(auto) callv(F&& func, B&& def, A&&... args)
{
    if constexpr(std::is_invocable_r_v<B,F,A...>) { return std::forward<F>(func)(std::forward<A>(args)...); }
    else                                          { static_assert(std::is_void_v<std::invoke_result_t<F,A...>>);
                                                    std::forward<F>(func)(std::forward<A>(args)...); return std::forward<B>(def); }
}

// for_all_expr() executes the given callbacks on all sub-expressions of the given expression
// (but not on itself). The first param can be: function&, expression&, const expression&.
// The provided callbacks will be executed sequentially. Recursion is depth-first.
// If a callback returns false, the rest of following callbacks will not be executed for that expression.
// If all callbacks return true, testing ends immediately and for_all_expr returns true.
// If a callback returns void, it is treated as if it returned false.
template<typename E, typename... F>
static bool for_all_expr(E& p, bool inclusive, F&&... funcs)
{
    static_assert(std::conjunction_v<std::is_invocable<F,expression&>...>);
    return std::any_of(p.params.begin(), p.params.end(), [&](E& e) { return for_all_expr(e, true, funcs...); })
         || (inclusive && ... && callv(funcs,false,p));
}

static void FindPureFunctions()
{
    // Reset the information
    for(auto& f: func_list) f.pure_known = f.pure = false;
    // Loop until the algorithm can't find new functions to identify as pure/impure
    do {} while(std::count_if(func_list.begin(), func_list.end(), [&](function& f)
    {
        if(f.pure_known) return false;
        std::cerr << "Identifying " << f.name << '\n';

        // The function has side-effects, if there is _any_ pointer dereference
        // in the LHS side of an assign operator, or if the function calls
        // some other function that is known to have side-effects.
        bool unknown_functions = false;
        bool side_effects      = for_all_expr(f.code, true, [&](const expression& exp)
        {
            if(is_copy(exp)) { return for_all_expr(exp.params.back(), true, is_deref); }
            if(is_fcall(exp))
            {
                const auto& e = exp.params.front();
                // Indirect function calls are always considered impure
                if(!e.is_compiletime_expr()) return true;
                // Identify the function that was called
                const auto& u = func_list[e.ident.index];
                if(u.pure_known && !u.pure) return true; // An impure function called
                if(!u.pure_known && e.ident.index != (&f - &func_list[0])) // Recursion is ignored
                {
                    std::cerr << "Function " << f.name << " calls unknown function " << u.name << '\n';
                    unknown_functions = true; // An unknown function called
                }
            }
            return false;
        });
        // If found side-effects, mark impure. If nothing of that sort was found
        // and all called functions were known pure, mark this function also pure.
        if(side_effects || !unknown_functions)
        {
            f.pure_known = true;
            f.pure       = !side_effects;
            std::cerr << "Function " << f.name << (f.pure ? " is pure\n" : " may have side-effects\n");
            return true; // improvements found; restart the do-while loop
        }
        return false;
    }));
    for(auto& f: func_list)
        if(!f.pure_known)
            std::cerr << "Could not figure out whether " << f.name << " is a pure function\n";
}

bool expression_equal(const expression& a, const expression& b)
{
	return (a.type == b.type)
		&& (!is_ident(a) || (a.ident.type == b.ident.type && a.ident.index == b.ident.index))
		&& (!is_string(a) || a.strvalue == b.strvalue)
		&& (!is_number(a) || a.numvalue == b.numvalue)
		&& std::equal(a.params.begin(), a.params.end(), b.params.begin(), b.params.end(), expression_equal);
}

bool function_equal(const function& a, const function& b)
{
	return (a.name == b.name)
		&& (expression_equal(a.code, b.code))
		&& (a.num_vars == b.num_vars)
		&& (a.num_params == b.num_params)
		&& (a.pure == b.pure)
		&& (a.pure_known == b.pure_known);
}

static void ConstantFolding(expression& e, function& f)
{
    if(is_add(e) || is_comma(e) || is_cor(e) || is_cand(e))
    {
        // Adopt all params of that same type
        for(auto j = e.params.end(); j != e.params.begin(); )
            if((--j)->type == e.type)
            {
                // Adopt all params of the parameter. Delete *j.
                auto tmp(M(j->params));
                e.params.splice(j = e.params.erase(j), std::move(tmp));
            }
        // No need to do this recursively, it has already been done recursively
    }

    // If an assign operator (copy) is used as a parameter
    // to any other kind of expression than a comma or an addrof,
    // create a comma sequence, such that e.g. x + 3 + (y=4) is replaced with x + 3 + (y=4, 4).
    // If the RHS of the assign has side-effects, use a temporary:
    // x + (y = f()) becomes x + (temp=f(), y = temp, temp)
    // This helps bring out the RHS into the outer levels of optimizations,
    // because the expression will be converted into (y=4, x+3+4) etc.
    // For while-loops, only the first operand will be inspected; the rest is treated as comma.
    if(!is_comma(e) && !is_addrof(e) && !e.params.empty())
        for(auto i = e.params.begin(), j = (is_loop(e) ? std::next(i) : e.params.end()); i != j; ++i)
            if(is_copy(*i))
            {
                auto assign = M(*i); *i = e_comma();
                if(assign.params.front().is_pure())
                {
                    i->params.push_back(C(assign.params.front()));
                    i->params.push_front(M(assign));
                }
                else
                {
                    expression temp = f.maketemp();
                    i->params.push_back(C(temp)                 %= M(assign.params.front()));
                    i->params.push_back(M(assign.params.back()) %= C(temp));
                    i->params.push_back(M(temp));
                }
            }

    // If expr has multiple params, such as in a function calls,
    // and any of those parameters are comma expressions,
    // keep only the last value in each comma expression.
    //
    // Convert e.g.      func((a,b,c), (d,e,f), (g,h,i))
    //               --> (a,b, temp=c, d,e, temp2=f, g,h, func(temp,temp2,i))
    //
    // This way, expr itself becomes a comma expression,
    // providing the same optimization opportunity to the parent expression.
    //
    // Take care to preserve execution order.
    // For "loop", nothing is hoisted because everything must be re-executed every loop iteration.
    if(std::find_if(e.params.begin(), e.params.end(), is_comma) != e.params.end())
    {
        // For conditional execution, only the first parameter is operated on, because
        // the rest of them are only executed depending on the value of the first.
        auto end = (is_cand(e) || is_cor(e) || is_loop(e)) ? std::next(e.params.begin()) : e.params.end();
        // Move the "end" backwards until we hit a comma parameter.
        for(; end != e.params.begin(); --end)
        {
            auto prev = std::prev(end);
            if(is_comma(*prev) && prev->params.size() > 1) break;
        }
        expr_vec comma_params;
        for(expr_vec::iterator i = e.params.begin(); i != end; ++i)
        {
            if(std::next(i) == end) // last?
            {
                if(is_comma(*i) && i->params.size() > 1)
                    comma_params.splice(comma_params.end(), i->params, i->params.begin(), std::prev(i->params.end()));
            }
            else if(!i->is_compiletime_expr())
            {
                expression temp = f.maketemp();
                if(is_comma(*i) && i->params.size() > 1)
                    comma_params.splice(comma_params.end(), i->params, i->params.begin(), std::prev(i->params.end()));
                comma_params.insert(comma_params.end(), C(temp) %= M(*i));
                *i = M(temp);
            }
        }
        if(!comma_params.empty())
        {
            // If the condition to a "loop" statement is a comma expression, replicate
            // the expression to make it better optimizable:
            //           while(a,b,c) { code }
            // --> a; b; while(c)     { code; a; b; }
            if(is_loop(e)) { for(auto& f: comma_params) e.params.push_back(C(f)); }
            comma_params.push_back(M(e));
            e = e_comma(M(comma_params));
        }
    }

    switch(e.type)
    {
        case ex_type::add:
        {
            // Count the sum of literals
            long tmp = std::accumulate(e.params.begin(), e.params.end(), 0l,
                                       [](long n,auto&p){ return is_number(p) ? n + p.numvalue : n; });
            // And remove them
            e.params.remove_if(is_number);
            // Adopt all negated adds: x + -(y + z) --> x + -(y) + -(z)
            for(auto j = e.params.begin(); j != e.params.end(); ++j)
                if(is_neg(*j) && is_add(j->params.front()))
                {
                    auto tmp(std::move(j->params.front().params));
                    for(auto& p: tmp) p = e_neg(M(p));
                    e.params.splice(j = e.params.erase(j), std::move(tmp));
                }
            // Readd the literal parameter if nonzero.
            if(tmp != 0) e.params.push_back(tmp);
            // Count inverted parameters. If the number is greater
            // than the number of non-inverted parameters, flip the inversion
            // and invert the sum. E.g. -(a) + -(b) + -(c) + d --> -(a + b + c + -(d))
            if(std::count_if(e.params.begin(), e.params.end(), is_neg) > long(e.params.size()/2))
            {
                for(auto& p: e.params) p = e_neg(M(p));
                e = e_neg(M(e));
            }
            break;
        }
        case ex_type::neg:
            // If the parameter is a literal, replace with negated literal
            if(is_number(e.params.front()))   e = -e.params.front().numvalue;
            else if(is_neg(e.params.front())) e = C(M(e.params.front().params.front()));
            break;
        case ex_type::eq:
            if(is_number(e.params.front()) && is_number(e.params.back()))
                e = long(e.params.front().numvalue == e.params.back().numvalue);
            else if(expression_equal(e.params.front(), e.params.back()) && e.params.front().is_pure())
                e = 1l;
            break;
        case ex_type::deref:
            // Convert deref(addrof(x)) into x
            if(is_addrof(e.params.front())) e = C(M(e.params.front().params.front()));
            break;
        case ex_type::addrof:
            // Convert addrof(deref(x)) into x ; this is meaningful when x is a pointer
            if(is_deref(e.params.front())) e = C(M(e.params.front().params.front()));
            break;
        case ex_type::cand:
        case ex_type::cor:
        {
            std::function<bool(long)> value_kind;
			if (is_cand(e))
			{
				value_kind = [](long v) { return v != 0; };
			}
			else
			{
				value_kind = [](long v) { return v == 0; };
			}
            // With &&, delete nonzero literals. With ||, delete zero literals.
            e.params.erase(std::remove_if(e.params.begin(), e.params.end(),
                                          [&](expression& p) { return is_number(p) && value_kind(p.numvalue); }),
                           e.params.end());
            // Found zero (&&) or nonzero (||) --> delete all remaining params and all *preceding* pure params
            if(auto i = std::find_if(e.params.begin(), e.params.end(), [&](const expression& p)
                                     { return is_number(p) && !value_kind(p.numvalue); });
               i != e.params.end())
            {
                // Find the last non-pure param before that constant
                while(i != e.params.begin() && std::prev(i)->is_pure()) { --i; }
                // Delete everything that follows that
                e.params.erase(i, e.params.end());
                // Replace with a comma stmt that produces 0 (&&) or 1 (||)
                e = e_comma(M(e), is_cand(e) ? 0l : 1l);
            }
            break;
        }
        case ex_type::copy:
        {
            auto& tgt = e.params.back(), &src = e.params.front();
            // If an assign-statement assigns into itself, and the expression has no side effects,
            // replace with the lhs.
            if(expression_equal(tgt, src) && tgt.is_pure())
                e = C(M(tgt));
            // If the target expression of the assign-statement is also used in the source expression,
            // replace the target-param reference with a temporary variable. A new temporary is created
            // for every repeated reference in case the expression is question is impure.
            else
            {
                expr_vec comma_params;
                for_all_expr(src, true, [&](auto& e)
                                        { if(expression_equal(e, tgt)) comma_params.push_back(C(e = f.maketemp()) %= C(tgt)); });
                if(!comma_params.empty())
                {
                    comma_params.push_back(M(e));
                    e = e_comma(M(comma_params));
                }
            }
            break;
        }
        case ex_type::loop:
            // If the loop condition is a literal zero, delete the code that is never executed.
            if(is_number(e.params.front()) && !e.params.front().numvalue) { e = e_nop(); break; }
            // Process the contingent code like a comma statement
            [[fallthrough]];
        case ex_type::comma:
            for(auto i = e.params.begin(); i != e.params.end(); )
            {
                // For while(), leave the condition expression untouched
                // For comma,   leave the *final* expression untouched
                if(is_loop(e))
                    { if(i == e.params.begin()) { ++i; continue; } }
                else
                    { if(std::next(i) == e.params.end()) break; }

                // Delete all pure params except the last
                if(i->is_pure())
                    { i = e.params.erase(i); }
                else switch(i->type)
                {
                    // Adopt members from any sub-expression where the result is not needed
                    default:
                        ++i;
                        break;
                    case ex_type::fcall:
                        // Even if the function call is not pure, it might be
                        // because of the parameters, not the function itself.
                        // Check if only need to keep the parameters.
                        if(!pure_fcall(e)) { ++i; break; }
                        [[fallthrough]];

                    case ex_type::add:
                    case ex_type::neg:
                    case ex_type::eq:
                    case ex_type::addrof:
                    case ex_type::deref:
                    case ex_type::comma:
                        // Adopt all params of the parameter. Delete *i.
                        auto tmp(std::move(i->params));
                        e.params.splice(i = e.params.erase(i), std::move(tmp));
                }
            }
            // Delete all params following a "return" statement or following an infinite loop
            if(auto r = std::find_if(e.params.begin(), e.params.end(),
                                  [](const expression& e) { return is_ret(e)
                                                                || (is_loop(e)
                                                                    && is_number(e.params.front())
                                                                    && e.params.front().numvalue != 0); });
               r != e.params.end() && ++r != e.params.end())
            {
                std::cerr << std::distance(r, e.params.end()) << " dead expressions deleted\n";
                e.params.erase(r, e.params.end());
            }

            // If the last element in the list is the same as the preceding assign-target,
            // delete the last element. e.g. x = (a=3, a)  -->  x = (a=3)
            if(e.params.size() >= 2)
            {
                auto& last = e.params.back(), &prev = *std::next(e.params.rbegin());
                if(is_copy(prev) && expression_equal(prev.params.back(), last))
                    e.params.pop_back();
            }
            if(e.params.size() == 1 && !is_loop(e))
            {
                // Replace with param
                e = C(M(e.params.front()));
            }
            break;

        default:
            break;
    }

    // If the type is add, cand or cor, and there remains only one operand, replace with the operand
    switch(e.params.size())
    {
        case 1: if(is_add(e))                    e = C(M(e.params.front()));
                else if(is_cor(e) || is_cand(e)) e = e_eq(e_eq(M(e.params.front()), 0l), 0l); // bool-cast
                break;
        case 0: if(is_add(e) || is_cor(e))       e = 0l;
                else if(is_cand(e))              e = 1l;
    }
}

static void DoConstantFolding()
{
    do {} while(std::any_of(func_list.begin(), func_list.end(), [&](function& f)
    {
        // Recalculate function purity; the status may have changed
        // as unreachable statements have been deleted etc.
        FindPureFunctions();

        function function_before = f;

        for_all_expr(f.code, true, [&](expression& e){ ConstantFolding(e,f); });

        return !function_equal(f, function_before);
    }));
}

namespace kyte
{
	void parse(std::string filename)
	{
		std::ifstream f(filename);
		std::string buffer(std::istreambuf_iterator<char>(f), {});

		lexcontext ctx;
		ctx.cursor = buffer.c_str();
		ctx.loc.begin.filename = &filename;
		ctx.loc.end.filename   = &filename;

		yy::conj_parser parser(ctx);
		parser.parse();
		func_list = std::move(ctx.func_list);

		DoConstantFolding();
	}
}
