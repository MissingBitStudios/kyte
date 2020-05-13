// A Bison parser, made by GNU Bison 3.4.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





// //                    "%code requires" blocks.
#line 16 "parser.yy"

#include <iostream>
#include <fstream>
#include <algorithm>

struct lexcontext;

#line 50 "parser.cpp.re"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

namespace yy {
#line 165 "parser.cpp.re"


  /// A point in a source file.
  class position
  {
  public:
    /// Construct a position.
    explicit position (std::string* f = YY_NULLPTR,
                       unsigned l = 1u,
                       unsigned c = 1u)
      : filename (f)
      , line (l)
      , column (c)
    {}


    /// Initialization.
    void initialize (std::string* fn = YY_NULLPTR,
                     unsigned l = 1u,
                     unsigned c = 1u)
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
    unsigned line;
    /// Current column number.
    unsigned column;

  private:
    /// Compute max (min, lhs+rhs).
    static unsigned add_ (unsigned lhs, int rhs, int min)
    {
      return static_cast<unsigned> (std::max (min,
                                              static_cast<int> (lhs) + rhs));
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
  std::basic_ostream<YYChar>&
  operator<< (std::basic_ostream<YYChar>& ostr, const position& pos)
  {
    if (pos.filename)
      ostr << *pos.filename << ':';
    return ostr << pos.line << '.' << pos.column;
  }

  /// Two points in a source file.
  class location
  {
  public:

    /// Construct a location from \a b to \a e.
    location (const position& b, const position& e)
      : begin (b)
      , end (e)
    {}

    /// Construct a 0-width location in \a p.
    explicit location (const position& p = position ())
      : begin (p)
      , end (p)
    {}

    /// Construct a 0-width location in \a f, \a l, \a c.
    explicit location (std::string* f,
                       unsigned l = 1u,
                       unsigned c = 1u)
      : begin (f, l, c)
      , end (f, l, c)
    {}


    /// Initialization.
    void initialize (std::string* f = YY_NULLPTR,
                     unsigned l = 1u,
                     unsigned c = 1u)
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
  std::basic_ostream<YYChar>&
  operator<< (std::basic_ostream<YYChar>& ostr, const location& loc)
  {
    unsigned end_col = 0 < loc.end.column ? loc.end.column - 1 : 0;
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


  /// A Bison parser.
  class  parser 
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YYASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
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
    self_type& operator= (const self_type&);
    semantic_type (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // IDENTIFIER
      // TYPE_NAME
      // FUNCTION_NAME
      // VARIABLE_NAME
      char dummy1[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        BLOCK_COMMENT_ERROR = 258,
        IDENTIFIER = 259,
        CONSTANT = 260,
        TYPE_NAME = 261,
        FUNCTION_NAME = 262,
        VARIABLE_NAME = 263,
        ATTRIBUTE = 264,
        UNIFORM = 265,
        SAMPLER = 266,
        IMPORT = 267,
        INC_OP = 268,
        DEC_OP = 269,
        AND_OP = 270,
        OR_OP = 271,
        EQ_OP = 272,
        NE_OP = 273,
        LE_OP = 274,
        GE_OP = 275,
        MUL_ASSIGN = 276,
        DIV_ASSIGN = 277,
        MOD_ASSIGN = 278,
        ADD_ASSIGN = 279,
        SUB_ASSIGN = 280,
        LEFT_OP = 281,
        RIGHT_OP = 282,
        LEFT_ASSIGN = 283,
        RIGHT_ASSIGN = 284,
        AND_ASSIGN = 285,
        XOR_ASSIGN = 286,
        OR_ASSIGN = 287,
        NOT_ASSIGN = 288,
        TYPEDEF = 289,
        EXTERN = 290,
        OPERATOR = 291,
        CONST = 292,
        INT = 293,
        UINT = 294,
        FLOAT = 295,
        DOUBLE = 296,
        BOOL = 297,
        VOID = 298,
        STRUCT = 299,
        ENUM = 300,
        ELLIPSIS = 301,
        ARROW = 302,
        CASE = 303,
        DEFAULT = 304,
        IF = 305,
        ELSE = 306,
        SWITCH = 307,
        WHILE = 308,
        DO = 309,
        FOR = 310,
        CONTINUE = 311,
        BREAK = 312,
        RETURN = 313,
        DISCARD = 314
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
    /// via type_get ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
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
      case 4: // IDENTIFIER
      case 6: // TYPE_NAME
      case 7: // FUNCTION_NAME
      case 8: // VARIABLE_NAME
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

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
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The token.
      token_type token () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {
      /// Superclass.
      typedef basic_symbol<by_type> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YYASSERT (tok == token::END || tok == token::BLOCK_COMMENT_ERROR || tok == token::CONSTANT || tok == token::ATTRIBUTE || tok == token::UNIFORM || tok == token::SAMPLER || tok == token::IMPORT || tok == token::INC_OP || tok == token::DEC_OP || tok == token::AND_OP || tok == token::OR_OP || tok == token::EQ_OP || tok == token::NE_OP || tok == token::LE_OP || tok == token::GE_OP || tok == token::MUL_ASSIGN || tok == token::DIV_ASSIGN || tok == token::MOD_ASSIGN || tok == token::ADD_ASSIGN || tok == token::SUB_ASSIGN || tok == token::LEFT_OP || tok == token::RIGHT_OP || tok == token::LEFT_ASSIGN || tok == token::RIGHT_ASSIGN || tok == token::AND_ASSIGN || tok == token::XOR_ASSIGN || tok == token::OR_ASSIGN || tok == token::NOT_ASSIGN || tok == token::TYPEDEF || tok == token::EXTERN || tok == token::OPERATOR || tok == token::CONST || tok == token::INT || tok == token::UINT || tok == token::FLOAT || tok == token::DOUBLE || tok == token::BOOL || tok == token::VOID || tok == token::STRUCT || tok == token::ENUM || tok == token::ELLIPSIS || tok == token::ARROW || tok == token::CASE || tok == token::DEFAULT || tok == token::IF || tok == token::ELSE || tok == token::SWITCH || tok == token::WHILE || tok == token::DO || tok == token::FOR || tok == token::CONTINUE || tok == token::BREAK || tok == token::RETURN || tok == token::DISCARD || tok == 40 || tok == 41 || tok == 91 || tok == 93 || tok == 46 || tok == 44 || tok == 43 || tok == 45 || tok == 126 || tok == 33 || tok == 42 || tok == 47 || tok == 37 || tok == 60 || tok == 62 || tok == 38 || tok == 94 || tok == 124 || tok == 63 || tok == 58 || tok == 61 || tok == 59 || tok == 123 || tok == 125);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YYASSERT (tok == token::END || tok == token::BLOCK_COMMENT_ERROR || tok == token::CONSTANT || tok == token::ATTRIBUTE || tok == token::UNIFORM || tok == token::SAMPLER || tok == token::IMPORT || tok == token::INC_OP || tok == token::DEC_OP || tok == token::AND_OP || tok == token::OR_OP || tok == token::EQ_OP || tok == token::NE_OP || tok == token::LE_OP || tok == token::GE_OP || tok == token::MUL_ASSIGN || tok == token::DIV_ASSIGN || tok == token::MOD_ASSIGN || tok == token::ADD_ASSIGN || tok == token::SUB_ASSIGN || tok == token::LEFT_OP || tok == token::RIGHT_OP || tok == token::LEFT_ASSIGN || tok == token::RIGHT_ASSIGN || tok == token::AND_ASSIGN || tok == token::XOR_ASSIGN || tok == token::OR_ASSIGN || tok == token::NOT_ASSIGN || tok == token::TYPEDEF || tok == token::EXTERN || tok == token::OPERATOR || tok == token::CONST || tok == token::INT || tok == token::UINT || tok == token::FLOAT || tok == token::DOUBLE || tok == token::BOOL || tok == token::VOID || tok == token::STRUCT || tok == token::ENUM || tok == token::ELLIPSIS || tok == token::ARROW || tok == token::CASE || tok == token::DEFAULT || tok == token::IF || tok == token::ELSE || tok == token::SWITCH || tok == token::WHILE || tok == token::DO || tok == token::FOR || tok == token::CONTINUE || tok == token::BREAK || tok == token::RETURN || tok == token::DISCARD || tok == 40 || tok == 41 || tok == 91 || tok == 93 || tok == 46 || tok == 44 || tok == 43 || tok == 45 || tok == 126 || tok == 33 || tok == 42 || tok == 47 || tok == 37 || tok == 60 || tok == 62 || tok == 38 || tok == 94 || tok == 124 || tok == 63 || tok == 58 || tok == 61 || tok == 59 || tok == 123 || tok == 125);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YYASSERT (tok == token::IDENTIFIER || tok == token::TYPE_NAME || tok == token::FUNCTION_NAME || tok == token::VARIABLE_NAME);
      }
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YYASSERT (tok == token::IDENTIFIER || tok == token::TYPE_NAME || tok == token::FUNCTION_NAME || tok == token::VARIABLE_NAME);
      }
#endif
    };

    /// Build a parser object.
     parser  (lexcontext& ctx_yyarg);
    virtual ~ parser  ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

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

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BLOCK_COMMENT_ERROR (location_type l)
      {
        return symbol_type (token::BLOCK_COMMENT_ERROR, std::move (l));
      }
#else
      static
      symbol_type
      make_BLOCK_COMMENT_ERROR (const location_type& l)
      {
        return symbol_type (token::BLOCK_COMMENT_ERROR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONSTANT (location_type l)
      {
        return symbol_type (token::CONSTANT, std::move (l));
      }
#else
      static
      symbol_type
      make_CONSTANT (const location_type& l)
      {
        return symbol_type (token::CONSTANT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPE_NAME (std::string v, location_type l)
      {
        return symbol_type (token::TYPE_NAME, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TYPE_NAME (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TYPE_NAME, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FUNCTION_NAME (std::string v, location_type l)
      {
        return symbol_type (token::FUNCTION_NAME, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FUNCTION_NAME (const std::string& v, const location_type& l)
      {
        return symbol_type (token::FUNCTION_NAME, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VARIABLE_NAME (std::string v, location_type l)
      {
        return symbol_type (token::VARIABLE_NAME, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_VARIABLE_NAME (const std::string& v, const location_type& l)
      {
        return symbol_type (token::VARIABLE_NAME, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ATTRIBUTE (location_type l)
      {
        return symbol_type (token::ATTRIBUTE, std::move (l));
      }
#else
      static
      symbol_type
      make_ATTRIBUTE (const location_type& l)
      {
        return symbol_type (token::ATTRIBUTE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNIFORM (location_type l)
      {
        return symbol_type (token::UNIFORM, std::move (l));
      }
#else
      static
      symbol_type
      make_UNIFORM (const location_type& l)
      {
        return symbol_type (token::UNIFORM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SAMPLER (location_type l)
      {
        return symbol_type (token::SAMPLER, std::move (l));
      }
#else
      static
      symbol_type
      make_SAMPLER (const location_type& l)
      {
        return symbol_type (token::SAMPLER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IMPORT (location_type l)
      {
        return symbol_type (token::IMPORT, std::move (l));
      }
#else
      static
      symbol_type
      make_IMPORT (const location_type& l)
      {
        return symbol_type (token::IMPORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INC_OP (location_type l)
      {
        return symbol_type (token::INC_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_INC_OP (const location_type& l)
      {
        return symbol_type (token::INC_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEC_OP (location_type l)
      {
        return symbol_type (token::DEC_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_DEC_OP (const location_type& l)
      {
        return symbol_type (token::DEC_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND_OP (location_type l)
      {
        return symbol_type (token::AND_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_AND_OP (const location_type& l)
      {
        return symbol_type (token::AND_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR_OP (location_type l)
      {
        return symbol_type (token::OR_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_OR_OP (const location_type& l)
      {
        return symbol_type (token::OR_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQ_OP (location_type l)
      {
        return symbol_type (token::EQ_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_EQ_OP (const location_type& l)
      {
        return symbol_type (token::EQ_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NE_OP (location_type l)
      {
        return symbol_type (token::NE_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_NE_OP (const location_type& l)
      {
        return symbol_type (token::NE_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LE_OP (location_type l)
      {
        return symbol_type (token::LE_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_LE_OP (const location_type& l)
      {
        return symbol_type (token::LE_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GE_OP (location_type l)
      {
        return symbol_type (token::GE_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_GE_OP (const location_type& l)
      {
        return symbol_type (token::GE_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MUL_ASSIGN (location_type l)
      {
        return symbol_type (token::MUL_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_MUL_ASSIGN (const location_type& l)
      {
        return symbol_type (token::MUL_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV_ASSIGN (location_type l)
      {
        return symbol_type (token::DIV_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_DIV_ASSIGN (const location_type& l)
      {
        return symbol_type (token::DIV_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD_ASSIGN (location_type l)
      {
        return symbol_type (token::MOD_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_MOD_ASSIGN (const location_type& l)
      {
        return symbol_type (token::MOD_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ADD_ASSIGN (location_type l)
      {
        return symbol_type (token::ADD_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_ADD_ASSIGN (const location_type& l)
      {
        return symbol_type (token::ADD_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_ASSIGN (location_type l)
      {
        return symbol_type (token::SUB_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_ASSIGN (const location_type& l)
      {
        return symbol_type (token::SUB_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEFT_OP (location_type l)
      {
        return symbol_type (token::LEFT_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_LEFT_OP (const location_type& l)
      {
        return symbol_type (token::LEFT_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RIGHT_OP (location_type l)
      {
        return symbol_type (token::RIGHT_OP, std::move (l));
      }
#else
      static
      symbol_type
      make_RIGHT_OP (const location_type& l)
      {
        return symbol_type (token::RIGHT_OP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEFT_ASSIGN (location_type l)
      {
        return symbol_type (token::LEFT_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_LEFT_ASSIGN (const location_type& l)
      {
        return symbol_type (token::LEFT_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RIGHT_ASSIGN (location_type l)
      {
        return symbol_type (token::RIGHT_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_RIGHT_ASSIGN (const location_type& l)
      {
        return symbol_type (token::RIGHT_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND_ASSIGN (location_type l)
      {
        return symbol_type (token::AND_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_AND_ASSIGN (const location_type& l)
      {
        return symbol_type (token::AND_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_XOR_ASSIGN (location_type l)
      {
        return symbol_type (token::XOR_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_XOR_ASSIGN (const location_type& l)
      {
        return symbol_type (token::XOR_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR_ASSIGN (location_type l)
      {
        return symbol_type (token::OR_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_OR_ASSIGN (const location_type& l)
      {
        return symbol_type (token::OR_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT_ASSIGN (location_type l)
      {
        return symbol_type (token::NOT_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_NOT_ASSIGN (const location_type& l)
      {
        return symbol_type (token::NOT_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPEDEF (location_type l)
      {
        return symbol_type (token::TYPEDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_TYPEDEF (const location_type& l)
      {
        return symbol_type (token::TYPEDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXTERN (location_type l)
      {
        return symbol_type (token::EXTERN, std::move (l));
      }
#else
      static
      symbol_type
      make_EXTERN (const location_type& l)
      {
        return symbol_type (token::EXTERN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPERATOR (location_type l)
      {
        return symbol_type (token::OPERATOR, std::move (l));
      }
#else
      static
      symbol_type
      make_OPERATOR (const location_type& l)
      {
        return symbol_type (token::OPERATOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONST (location_type l)
      {
        return symbol_type (token::CONST, std::move (l));
      }
#else
      static
      symbol_type
      make_CONST (const location_type& l)
      {
        return symbol_type (token::CONST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT (location_type l)
      {
        return symbol_type (token::INT, std::move (l));
      }
#else
      static
      symbol_type
      make_INT (const location_type& l)
      {
        return symbol_type (token::INT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UINT (location_type l)
      {
        return symbol_type (token::UINT, std::move (l));
      }
#else
      static
      symbol_type
      make_UINT (const location_type& l)
      {
        return symbol_type (token::UINT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (location_type l)
      {
        return symbol_type (token::FLOAT, std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT (const location_type& l)
      {
        return symbol_type (token::FLOAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOUBLE (location_type l)
      {
        return symbol_type (token::DOUBLE, std::move (l));
      }
#else
      static
      symbol_type
      make_DOUBLE (const location_type& l)
      {
        return symbol_type (token::DOUBLE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOL (location_type l)
      {
        return symbol_type (token::BOOL, std::move (l));
      }
#else
      static
      symbol_type
      make_BOOL (const location_type& l)
      {
        return symbol_type (token::BOOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VOID (location_type l)
      {
        return symbol_type (token::VOID, std::move (l));
      }
#else
      static
      symbol_type
      make_VOID (const location_type& l)
      {
        return symbol_type (token::VOID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRUCT (location_type l)
      {
        return symbol_type (token::STRUCT, std::move (l));
      }
#else
      static
      symbol_type
      make_STRUCT (const location_type& l)
      {
        return symbol_type (token::STRUCT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENUM (location_type l)
      {
        return symbol_type (token::ENUM, std::move (l));
      }
#else
      static
      symbol_type
      make_ENUM (const location_type& l)
      {
        return symbol_type (token::ENUM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELLIPSIS (location_type l)
      {
        return symbol_type (token::ELLIPSIS, std::move (l));
      }
#else
      static
      symbol_type
      make_ELLIPSIS (const location_type& l)
      {
        return symbol_type (token::ELLIPSIS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW (location_type l)
      {
        return symbol_type (token::ARROW, std::move (l));
      }
#else
      static
      symbol_type
      make_ARROW (const location_type& l)
      {
        return symbol_type (token::ARROW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE (location_type l)
      {
        return symbol_type (token::CASE, std::move (l));
      }
#else
      static
      symbol_type
      make_CASE (const location_type& l)
      {
        return symbol_type (token::CASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFAULT (location_type l)
      {
        return symbol_type (token::DEFAULT, std::move (l));
      }
#else
      static
      symbol_type
      make_DEFAULT (const location_type& l)
      {
        return symbol_type (token::DEFAULT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (location_type l)
      {
        return symbol_type (token::IF, std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const location_type& l)
      {
        return symbol_type (token::IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (location_type l)
      {
        return symbol_type (token::ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const location_type& l)
      {
        return symbol_type (token::ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SWITCH (location_type l)
      {
        return symbol_type (token::SWITCH, std::move (l));
      }
#else
      static
      symbol_type
      make_SWITCH (const location_type& l)
      {
        return symbol_type (token::SWITCH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (location_type l)
      {
        return symbol_type (token::WHILE, std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const location_type& l)
      {
        return symbol_type (token::WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DO (location_type l)
      {
        return symbol_type (token::DO, std::move (l));
      }
#else
      static
      symbol_type
      make_DO (const location_type& l)
      {
        return symbol_type (token::DO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR (location_type l)
      {
        return symbol_type (token::FOR, std::move (l));
      }
#else
      static
      symbol_type
      make_FOR (const location_type& l)
      {
        return symbol_type (token::FOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTINUE (location_type l)
      {
        return symbol_type (token::CONTINUE, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTINUE (const location_type& l)
      {
        return symbol_type (token::CONTINUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BREAK (location_type l)
      {
        return symbol_type (token::BREAK, std::move (l));
      }
#else
      static
      symbol_type
      make_BREAK (const location_type& l)
      {
        return symbol_type (token::BREAK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (location_type l)
      {
        return symbol_type (token::RETURN, std::move (l));
      }
#else
      static
      symbol_type
      make_RETURN (const location_type& l)
      {
        return symbol_type (token::RETURN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DISCARD (location_type l)
      {
        return symbol_type (token::DISCARD, std::move (l));
      }
#else
      static
      symbol_type
      make_DISCARD (const location_type& l)
      {
        return symbol_type (token::DISCARD, l);
      }
#endif


  private:
    /// This class is not copyable.
     parser  (const  parser &);
     parser & operator= (const  parser &);

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

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short yytable_[];

  static const short yycheck_[];

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
  static const unsigned short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
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
      by_state () YY_NOEXCEPT;

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

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
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::reverse_iterator iterator;
      typedef typename S::const_reverse_iterator const_iterator;
      typedef typename S::size_type size_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (size_type i)
      {
        return seq_[size () - 1 - i];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (int i)
      {
        return operator[] (size_type (i));
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (size_type i) const
      {
        return seq_[size () - 1 - i];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (int i) const
      {
        return operator[] (size_type (i));
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (int n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      size_type
      size () const YY_NOEXCEPT
      {
        return seq_.size ();
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, int range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (int i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        int range_;
      };

    private:
      stack (const stack&);
      stack& operator= (const stack&);
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 1046,     ///< Last index in yytable_.
      yynnts_ = 62,  ///< Number of nonterminal symbols.
      yyfinal_ = 53, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 84  ///< Number of tokens.
    };


    // User arguments.
    lexcontext& ctx;
  };

   parser ::token_number_type
   parser ::yytranslate_ (token_type t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,     2,     2,     2,    72,    75,     2,
      60,    61,    70,    66,    65,    67,    64,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    79,    81,
      73,    80,    74,    78,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    62,     2,    63,    76,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    82,    77,    83,    68,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
    };
    const unsigned user_token_number_max_ = 314;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
   parser ::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
    switch (this->type_get ())
    {
      case 4: // IDENTIFIER
      case 6: // TYPE_NAME
      case 7: // FUNCTION_NAME
      case 8: // VARIABLE_NAME
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
   parser ::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->type_get ())
    {
      case 4: // IDENTIFIER
      case 6: // TYPE_NAME
      case 7: // FUNCTION_NAME
      case 8: // VARIABLE_NAME
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
   parser ::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
   parser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 4: // IDENTIFIER
      case 6: // TYPE_NAME
      case 7: // FUNCTION_NAME
      case 8: // VARIABLE_NAME
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
   parser ::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
   parser ::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

   parser ::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

   parser ::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
   parser ::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
   parser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
   parser ::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }

   parser ::token_type
   parser ::by_type::token () const YY_NOEXCEPT
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
      40,    41,    91,    93,    46,    44,    43,    45,   126,    33,
      42,    47,    37,    60,    62,    38,    94,   124,    63,    58,
      61,    59,   123,   125
    };
    return token_type (yytoken_number_[type]);
  }

} // yy
#line 2351 "parser.cpp.re"







// Unqualified %code blocks.
#line 27 "parser.yy"

enum class IdentifierFlag
{
	TYPE_NAME,
	VARIABLE_NAME,
	FUNCTION_NAME
};

struct lexcontext
{
	const char* cursor;
	yy::location loc;
	IdentifierFlag identifierFlag;
};

namespace yy { parser::symbol_type yylex(lexcontext& ctx); }

#line 2378 "parser.cpp.re"


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

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
    while (false)
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
      *yycdebug_ << '\n';                       \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 2472 "parser.cpp.re"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              else
                goto append;

            append:
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
   parser :: parser  (lexcontext& ctx_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      ctx (ctx_yyarg)
  {}

   parser ::~ parser  ()
  {}

   parser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
   parser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   parser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   parser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   parser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   parser ::symbol_number_type
   parser ::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

   parser ::stack_symbol_type::stack_symbol_type ()
  {}

   parser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 4: // IDENTIFIER
      case 6: // TYPE_NAME
      case 7: // FUNCTION_NAME
      case 8: // VARIABLE_NAME
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   parser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 4: // IDENTIFIER
      case 6: // TYPE_NAME
      case 7: // FUNCTION_NAME
      case 8: // VARIABLE_NAME
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
   parser ::stack_symbol_type&
   parser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 4: // IDENTIFIER
      case 6: // TYPE_NAME
      case 7: // FUNCTION_NAME
      case 8: // VARIABLE_NAME
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   parser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
   parser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   parser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   parser ::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   parser ::debug_level_type
   parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   parser ::state_type
   parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
   parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   parser ::operator() ()
  {
    return parse ();
  }

  int
   parser ::parse ()
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
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
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
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
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 4: // IDENTIFIER
      case 6: // TYPE_NAME
      case 7: // FUNCTION_NAME
      case 8: // VARIABLE_NAME
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {

#line 2909 "parser.cpp.re"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

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
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
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
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
   parser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const short  parser ::yypact_ninf_ = -170;

  const signed char  parser ::yytable_ninf_ = -122;

  const short
   parser ::yypact_[] =
  {
     626,  -170,  -170,  -170,   856,  -170,  -170,  -170,  -170,  -170,
    -170,    21,    28,   461,   473,  -170,   564,   856,  -170,   485,
    -170,  -170,   552,    61,   683,  -170,  -170,  -170,   856,   -34,
     473,   -29,    32,  -170,   -18,   473,     3,   473,   122,  -170,
    -170,   -20,  -170,   540,  -170,  -170,   255,  -170,   564,  -170,
     552,   789,   737,  -170,  -170,   473,   359,  -170,   612,    32,
     -24,   -57,  -170,  -170,  -170,   473,  -170,  -170,   734,   785,
    -170,   131,   461,  -170,   196,  -170,   552,   988,  -170,   940,
     940,   952,   -21,    45,    55,    71,   483,    77,    89,   109,
     613,  -170,   692,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
     132,   966,   952,  -170,   141,     7,   194,    52,   205,    67,
      12,   147,   180,   -12,  -170,  -170,    -1,  -170,  -170,  -170,
     312,   369,  -170,  -170,  -170,  -170,   119,  -170,  -170,  -170,
    -170,   898,   166,   143,  -170,   -46,  -170,  -170,  -170,  -170,
     170,   371,  -170,  -170,   952,    10,  -170,   150,   -44,   952,
      32,  -170,  -170,  -170,   177,   178,  -170,   179,   831,   901,
    -170,   196,  -170,  -170,  -170,   952,  -170,  -170,   161,   483,
     952,   952,   952,   190,   635,  -170,  -170,  -170,    14,    69,
     185,  -170,  -170,   913,   952,   243,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,   952,  -170,
     952,   952,   952,   952,   952,   952,   952,   952,   952,   952,
     952,   952,   952,   952,   952,   952,   952,   952,   952,   952,
    -170,  -170,   426,  -170,  -170,   776,  -170,  -170,  -170,   843,
    -170,   244,  -170,  -170,  -170,   612,  -170,   952,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,   188,  -170,   198,  -170,   -41,
     483,  -170,    75,    82,   107,   210,   635,  -170,  -170,   952,
    -170,   108,  -170,   154,  -170,  -170,  -170,  -170,  -170,   141,
     141,     7,     7,   194,   194,   194,   194,    52,    52,   205,
      67,    12,   147,   180,   -10,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,   184,  -170,  -170,   483,   483,   483,
     952,   917,  -170,  -170,   952,  -170,   952,  -170,  -170,   221,
    -170,  -170,   115,   483,   118,  -170,  -170,   483,   192,  -170,
     483,  -170,  -170,  -170
  };

  const unsigned char
   parser ::yydefact_[] =
  {
       0,    97,    83,    84,    77,    89,    90,    91,    92,    93,
      88,     0,     0,     0,     0,   187,     0,    73,    96,    75,
      94,    95,     0,   120,     0,   184,   186,    78,    75,   100,
       0,   115,     0,   121,     0,   107,     0,   105,   137,    86,
      71,     0,    79,    81,    74,    76,     0,   166,     0,   191,
       0,     0,     0,     1,   185,     0,     0,   101,     0,     0,
     118,     0,   116,   122,   106,     0,    85,   104,     0,     0,
     138,   139,     0,    72,     0,   189,     0,     2,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   183,     0,    18,    19,    20,    21,   170,   162,     5,
      14,    22,     0,    24,    28,    31,    34,    39,    42,    44,
      46,    48,    50,    52,    54,    68,     0,   168,   154,   155,
       0,     0,   156,   157,   158,   159,    81,   167,   190,    97,
     127,   134,     0,   128,   130,     0,     2,   124,    22,    70,
       0,     0,    99,   102,     0,     0,   108,   110,     0,     0,
       0,   113,    87,   145,     0,     0,   141,     0,     0,     0,
      80,     0,   149,    82,   188,     0,    15,    16,     0,     0,
       0,     0,     0,     0,     0,   179,   180,   181,     0,     0,
       0,    10,    11,     0,     0,     0,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    56,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     171,   164,     0,   163,   169,     0,   132,   133,   125,     0,
     126,     0,   123,    98,   111,     0,   103,     0,   114,   119,
     117,   146,   140,   142,   147,     0,   143,     0,   152,     0,
       0,   161,     0,     0,     0,     0,     0,   182,     4,     0,
       7,     0,    12,     0,     9,    55,    25,    26,    27,    29,
      30,    32,    33,    37,    38,    35,    36,    40,    41,    43,
      45,    47,    49,    51,     0,    69,   165,   129,   131,   136,
     109,   112,   148,   144,     0,   150,   160,     0,     0,     0,
       0,     0,    23,     8,     0,     6,     0,   151,   153,   172,
     174,   175,     0,     0,     0,    13,    53,     0,     0,   177,
       0,   173,   176,   178
  };

  const short
   parser ::yypgoto_[] =
  {
    -170,  -170,  -170,  -170,   -52,  -170,   -88,    22,    26,    -4,
      24,    62,    60,    64,    66,    59,  -170,   -51,   -17,  -170,
     -43,   -59,    13,    16,  -170,   208,  -170,  -170,  -170,    46,
    -170,   228,   -45,    17,  -170,    49,  -170,   226,   136,    -7,
    -170,   -39,  -170,    72,  -170,   -58,   -15,  -170,  -159,  -170,
     -83,  -170,    56,    74,   168,  -169,  -170,  -170,  -170,  -170,
     267,  -170
  };

  const short
   parser ::yydefgoto_[] =
  {
      -1,    99,   100,   261,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   198,
     116,   140,    47,    48,    41,    42,    17,    18,    36,    28,
      20,    56,    57,    58,   145,   146,    21,    61,    62,    22,
      23,   154,   133,   134,   135,    39,   155,    71,   163,   249,
     117,   118,   119,    50,   121,   122,   123,   124,   125,    24,
      25,    26
  };

  const short
   parser ::yytable_[] =
  {
     138,   139,   248,   173,   217,   256,    34,   152,   150,    43,
     157,   143,   132,    15,   199,   230,    16,   138,   139,   231,
      27,   150,   168,    70,   294,    29,   151,   166,   167,   138,
     139,    38,    31,    44,   180,    45,    60,    15,   224,   238,
      16,   126,   295,    63,    45,    72,    19,   178,    55,   179,
     138,   147,    64,    59,    67,   219,   149,   162,   169,    33,
      37,    73,    33,   127,   219,   126,   218,   131,    65,   306,
      19,   207,   208,   203,   204,   235,    37,    66,    49,   219,
     220,    37,    38,    37,   131,   234,   251,   301,   214,   127,
     239,   236,   138,   139,    33,   257,   143,   138,   139,    75,
     247,    37,    37,    30,    33,   170,   128,   138,   139,    38,
      32,    37,   266,   267,   268,   171,   227,    76,    33,   245,
     120,    51,   179,    52,   226,   209,   210,   252,   253,   254,
     258,   172,   164,   127,   219,   308,   297,   174,    37,   224,
     219,   263,   213,   298,   162,   181,   182,   219,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   262,   296,   299,   303,
     175,   302,   219,   304,   131,   284,   318,    33,   291,   320,
     219,   265,    68,   219,    69,   138,   139,    37,   136,    78,
     176,   158,   183,   159,   184,   216,   185,    79,    80,    74,
     136,    78,   285,   273,   274,   275,   276,   138,   229,    79,
      80,   200,   201,   202,   309,   310,   311,   305,    34,   219,
     205,   206,   211,   212,   215,   269,   270,   228,   147,   237,
     319,   271,   272,   232,   321,   277,   278,   323,   241,   242,
     250,   131,   243,   255,    92,   131,   259,   264,   289,   292,
      93,    94,    95,    96,   138,   316,    92,   312,   314,    77,
      78,   293,    93,    94,    95,    96,   161,   307,    79,    80,
     300,    19,   317,   322,   280,   279,   283,   162,   161,   281,
     160,    33,   282,   141,   290,   148,   240,   315,   222,     2,
       3,    54,     4,     5,     6,     7,     8,     9,    10,    11,
      12,   288,     0,    81,    82,    83,     0,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    77,    78,     0,     0,
       0,    93,    94,    95,    96,    79,    80,     0,    14,     0,
       0,     0,     0,     0,     0,     0,    97,    46,    98,     0,
       0,     0,     0,     0,     0,     0,     2,     3,     0,     4,
       5,     6,     7,     8,     9,    10,    11,    12,     0,     0,
      81,    82,    83,     1,    84,    85,    86,    87,    88,    89,
      90,    91,    92,   136,    78,     1,     0,     0,    93,    94,
      95,    96,    79,    80,     0,    14,     0,     0,     0,     0,
       0,     0,     0,    97,    46,   221,    35,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,     0,    35,     5,
       6,     7,     8,     9,    10,    11,    12,    81,    82,    83,
       0,    84,    85,    86,    87,    88,    89,    90,    91,    92,
     136,    78,    14,     0,     0,    93,    94,    95,    96,    79,
      80,     0,   142,     0,    14,     0,     0,     0,     0,     0,
      97,    46,   223,     0,   233,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     0,    81,    82,    83,     1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,   136,    78,     1,
       0,     0,    93,    94,    95,    96,    79,    80,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    97,    46,   286,
      35,     5,     6,     7,     8,     9,    10,    11,    12,     2,
       3,    13,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    81,    82,    83,    14,    84,    85,    86,    87,    88,
      89,    90,    91,    92,     1,     0,    14,     0,     0,    93,
      94,    95,    96,     0,     0,     0,     1,     0,    14,     0,
       0,     0,     0,     0,    97,    46,     0,  -121,     1,     0,
       0,     0,     0,     0,     2,     3,     0,     4,     5,     6,
       7,     8,     9,    10,    11,    12,     2,     3,     0,     4,
       5,     6,     7,     8,     9,    10,    11,    12,     0,     0,
       0,     0,     5,     6,     7,     8,     9,    10,    11,    12,
       0,     0,     0,    14,     0,     0,     1,   136,    78,     0,
      74,     0,    46,     0,    13,    14,    79,    80,     0,     0,
       1,     0,     0,     0,    46,     0,     0,    14,     0,   136,
      78,     0,     0,     0,     0,    40,     0,     0,    79,    80,
       5,     6,     7,     8,     9,    10,    11,    12,     0,     0,
       2,     3,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    92,     0,     0,     0,     0,     0,    93,
      94,    95,    96,    53,     0,    14,    13,     1,     0,     0,
       0,   144,     0,     0,   177,    92,    77,    78,     0,    14,
       0,    93,    94,    95,    96,    79,    80,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,     2,     3,     0,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    35,
       5,     6,     7,     8,     9,    10,    11,    12,     1,     0,
       0,   136,    78,    13,     0,     0,     0,     0,     0,     0,
      79,    80,    92,     0,     0,     0,    14,     0,    93,    94,
      95,    96,     0,     0,     0,    14,     0,     0,     2,     3,
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       1,     0,     0,     0,     0,     0,     0,     0,     0,   136,
      78,     0,     0,   129,    68,   153,    69,    92,    79,    80,
     137,     0,     0,    93,    94,    95,    96,    14,     0,     0,
       2,     3,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,     0,     2,     3,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     1,   225,   153,    69,     0,
       0,     0,     0,     0,     0,    92,     0,     1,   156,    14,
     130,    93,    94,    95,    96,     0,     0,     0,     0,     0,
       1,     0,    14,     0,     0,     2,     3,     0,     4,     5,
       6,     7,     8,     9,    10,    11,    12,     2,     3,     0,
       4,     5,     6,     7,     8,     9,    10,    11,    12,   287,
       2,     3,   244,     4,     5,     6,     7,     8,     9,    10,
      11,    12,     1,     0,    14,   136,    78,     0,     0,     0,
       0,     0,     0,     0,    79,    80,    14,   136,    78,     0,
       0,   136,    78,     0,     0,     0,    79,    80,     0,    14,
      79,    80,     0,     0,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,   136,    78,     0,     0,     0,     0,
       0,     0,     0,    79,    80,     0,   136,    78,   225,     0,
      69,    92,     0,     0,   246,    79,    80,    93,    94,    95,
      96,    14,     0,    92,   260,     0,     0,    92,   313,    93,
      94,    95,    96,    93,    94,    95,    96,   186,   187,   188,
     189,   190,   -97,     0,   191,   192,   193,   194,   195,   196,
     165,     0,     0,     0,     0,     0,    93,    94,    95,    96,
       0,     0,    92,     0,     0,     0,     0,     0,    93,    94,
      95,    96,   -97,   -97,     0,   -97,   -97,   -97,   -97,   -97,
     -97,   -97,   -97,   -97,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   197
  };

  const short
   parser ::yycheck_[] =
  {
      52,    52,   161,    86,    16,   174,    13,    65,    65,    16,
      69,    56,    51,     0,   102,    61,     0,    69,    69,    65,
       4,    65,    81,    38,    65,     4,    83,    79,    80,    81,
      81,    14,     4,    17,    92,    19,     4,    24,   121,    83,
      24,    48,    83,    61,    28,    65,     0,    90,    82,    92,
     102,    58,    35,    82,    37,    65,    80,    74,    79,    13,
      14,    81,    16,    50,    65,    72,    78,    51,    65,    79,
      24,    19,    20,    66,    67,    65,    30,    74,    22,    65,
      81,    35,    65,    37,    68,   144,   169,   256,    76,    76,
     149,    81,   144,   144,    48,    81,   141,   149,   149,    43,
     159,    55,    56,    82,    58,    60,    50,   159,   159,    92,
      82,    65,   200,   201,   202,    60,   131,    43,    72,   158,
      46,    60,   165,    62,   131,    73,    74,   170,   171,   172,
      61,    60,    76,   120,    65,   294,    61,    60,    92,   222,
      65,   184,    75,    61,   161,    13,    14,    65,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   183,   250,    61,    61,
      81,   259,    65,    65,   158,   218,    61,   131,   237,    61,
      65,   198,    60,    65,    62,   237,   237,   141,     4,     5,
      81,    60,    60,    62,    62,    15,    64,    13,    14,    80,
       4,     5,   219,   207,   208,   209,   210,   259,    65,    13,
      14,    70,    71,    72,   297,   298,   299,    63,   225,    65,
      26,    27,    17,    18,    77,   203,   204,    61,   235,    79,
     313,   205,   206,    63,   317,   211,   212,   320,    61,    61,
      79,   225,    63,    53,    60,   229,    61,     4,     4,    61,
      66,    67,    68,    69,   306,   306,    60,   300,   301,     4,
       5,    63,    66,    67,    68,    69,    82,    83,    13,    14,
      60,   225,    51,    81,   214,   213,   217,   294,    82,   215,
      72,   235,   216,    55,   235,    59,   150,   304,   120,    34,
      35,    24,    37,    38,    39,    40,    41,    42,    43,    44,
      45,   229,    -1,    48,    49,    50,    -1,    52,    53,    54,
      55,    56,    57,    58,    59,    60,     4,     5,    -1,    -1,
      -1,    66,    67,    68,    69,    13,    14,    -1,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      48,    49,    50,     4,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     4,     5,     4,    -1,    -1,    66,    67,
      68,    69,    13,    14,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    48,    49,    50,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
       4,     5,    73,    -1,    -1,    66,    67,    68,    69,    13,
      14,    -1,    83,    -1,    73,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    -1,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     4,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,     4,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     4,     5,     4,
      -1,    -1,    66,    67,    68,    69,    13,    14,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    81,    82,    83,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    34,
      35,    60,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    48,    49,    50,    73,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     4,    -1,    73,    -1,    -1,    66,
      67,    68,    69,    -1,    -1,    -1,     4,    -1,    73,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,    82,     4,    -1,
      -1,    -1,    -1,    -1,    34,    35,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    34,    35,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    73,    -1,    -1,     4,     4,     5,    -1,
      80,    -1,    82,    -1,    60,    73,    13,    14,    -1,    -1,
       4,    -1,    -1,    -1,    82,    -1,    -1,    73,    -1,     4,
       5,    -1,    -1,    -1,    -1,    81,    -1,    -1,    13,    14,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      34,    35,    -1,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    60,    60,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,     0,    -1,    73,    60,     4,    -1,    -1,
      -1,    79,    -1,    -1,    81,    60,     4,     5,    -1,    73,
      -1,    66,    67,    68,    69,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    34,    35,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     4,    -1,
      -1,     4,     5,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      13,    14,    60,    -1,    -1,    -1,    73,    -1,    66,    67,
      68,    69,    -1,    -1,    -1,    73,    -1,    -1,    34,    35,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,    -1,    -1,     4,    60,    61,    62,    60,    13,    14,
      63,    -1,    -1,    66,    67,    68,    69,    73,    -1,    -1,
      34,    35,    -1,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    34,    35,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,     4,    60,    61,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    -1,     4,    63,    73,
      61,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
       4,    -1,    73,    -1,    -1,    34,    35,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    34,    35,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      34,    35,    61,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     4,    -1,    73,     4,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    13,    14,    73,     4,     5,    -1,
      -1,     4,     5,    -1,    -1,    -1,    13,    14,    -1,    73,
      13,    14,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,     4,     5,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    13,    14,    -1,     4,     5,    60,    -1,
      62,    60,    -1,    -1,    63,    13,    14,    66,    67,    68,
      69,    73,    -1,    60,    61,    -1,    -1,    60,    61,    66,
      67,    68,    69,    66,    67,    68,    69,    21,    22,    23,
      24,    25,     4,    -1,    28,    29,    30,    31,    32,    33,
      60,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    34,    35,    -1,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80
  };

  const unsigned char
   parser ::yystos_[] =
  {
       0,     4,    34,    35,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    60,    73,   106,   107,   110,   111,   113,
     114,   120,   123,   124,   143,   144,   145,   107,   113,     4,
      82,     4,    82,   113,   123,    37,   112,   113,   117,   129,
      81,   108,   109,   123,   107,   107,    82,   106,   107,   136,
     137,    60,    62,     0,   144,    82,   115,   116,   117,    82,
       4,   121,   122,    61,   117,    65,    74,   117,    60,    62,
     130,   131,    65,    81,    80,   136,   137,     4,     5,    13,
      14,    48,    49,    50,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    66,    67,    68,    69,    81,    83,    85,
      86,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   104,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   123,   106,   136,     4,
      61,   107,   125,   126,   127,   128,     4,    63,    88,   101,
     105,   115,    83,   116,    79,   118,   119,   123,   121,    80,
      65,    83,   129,    61,   125,   130,    63,   105,    60,    62,
     109,    82,   102,   132,   136,    60,    88,    88,   105,    79,
      60,    60,    60,   134,    60,    81,    81,    81,   104,   104,
     129,    13,    14,    60,    62,    64,    21,    22,    23,    24,
      25,    28,    29,    30,    31,    32,    33,    80,   103,    90,
      70,    71,    72,    66,    67,    26,    27,    19,    20,    73,
      74,    17,    18,    75,    76,    77,    15,    16,    78,    65,
      81,    83,   138,    83,   134,    60,   123,   130,    61,    65,
      61,    65,    63,    83,   105,    65,    81,    79,    83,   105,
     122,    61,    61,    63,    61,   125,    63,   105,   132,   133,
      79,   134,   104,   104,   104,    53,   139,    81,    61,    61,
      61,    87,   102,   104,     4,   102,    90,    90,    90,    91,
      91,    92,    92,    93,    93,    93,    93,    94,    94,    95,
      96,    97,    98,    99,   104,   102,    83,    46,   127,     4,
     119,   105,    61,    63,    65,    83,   134,    61,    61,    61,
      60,   139,    90,    61,    65,    63,    79,    83,   132,   134,
     134,   134,   104,    61,   104,   102,   101,    51,    61,   134,
      61,   134,    81,   134
  };

  const unsigned char
   parser ::yyr1_[] =
  {
       0,    84,    85,    85,    85,    86,    86,    86,    86,    86,
      86,    86,    87,    87,    88,    88,    88,    88,    89,    89,
      89,    89,    90,    90,    91,    91,    91,    91,    92,    92,
      92,    93,    93,    93,    94,    94,    94,    94,    94,    95,
      95,    95,    96,    96,    97,    97,    98,    98,    99,    99,
     100,   100,   101,   101,   102,   102,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   104,   104,
     105,   106,   106,   107,   107,   107,   107,   107,   107,   108,
     108,   109,   109,   110,   110,   111,   112,   112,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   114,   114,
     114,   115,   115,   116,   117,   117,   117,   117,   118,   118,
     119,   119,   119,   120,   120,   120,   121,   121,   122,   122,
     123,   124,   124,   124,   124,   124,   124,   124,   125,   125,
     126,   126,   127,   127,   127,   128,   128,   129,   129,   130,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   132,
     132,   132,   133,   133,   134,   134,   134,   134,   134,   134,
     135,   135,   136,   136,   136,   136,   137,   137,   138,   138,
     139,   139,   140,   140,   140,   141,   141,   141,   141,   142,
     142,   142,   142,   142,   143,   143,   144,   144,   145,   145,
     145,   145
  };

  const unsigned char
   parser ::yyr2_[] =
  {
       0,     2,     1,     1,     3,     1,     4,     3,     4,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     1,     1,
       1,     1,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     2,     3,     1,     2,     1,     2,     1,     2,     1,
       3,     1,     3,     1,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     4,
       2,     1,     2,     3,     2,     1,     2,     1,     1,     3,
       1,     2,     3,     4,     5,     2,     1,     3,     1,     3,
       1,     1,     3,     4,     3,     4,     4,     3,     1,     3,
       1,     3,     2,     2,     1,     1,     3,     1,     2,     1,
       3,     2,     3,     3,     4,     2,     3,     3,     4,     1,
       3,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       4,     3,     2,     3,     3,     4,     1,     2,     1,     2,
       1,     2,     5,     7,     5,     5,     7,     6,     7,     2,
       2,     2,     3,     1,     1,     2,     1,     1,     4,     3,
       3,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  parser ::yytname_[] =
  {
  "END", "error", "$undefined", "BLOCK_COMMENT_ERROR", "IDENTIFIER",
  "CONSTANT", "TYPE_NAME", "FUNCTION_NAME", "VARIABLE_NAME",
  "\"attribute\"", "\"uniform\"", "\"sampler\"", "\"import\"", "\"++\"",
  "\"--\"", "\"&&\"", "\"||\"", "\"==\"", "\"!=\"", "\"<=\"", "\">=\"",
  "\"*=\"", "\"/=\"", "\"%=\"", "\"+=\"", "\"-=\"", "\"<<\"", "\">>\"",
  "\"<<=\"", "\">>=\"", "\"&=\"", "\"^=\"", "\"|=\"", "\"~=\"",
  "\"typedef\"", "\"extern\"", "\"operator\"", "\"const\"", "\"int\"",
  "\"uint\"", "\"float\"", "\"double\"", "\"bool\"", "\"void\"",
  "\"struct\"", "\"enum\"", "\"...\"", "\"->\"", "\"case\"", "\"default\"",
  "\"if\"", "\"else\"", "\"switch\"", "\"while\"", "\"do\"", "\"for\"",
  "\"continue\"", "\"break\"", "\"return\"", "\"discard\"", "'('", "')'",
  "'['", "']'", "'.'", "','", "'+'", "'-'", "'~'", "'!'", "'*'", "'/'",
  "'%'", "'<'", "'>'", "'&'", "'^'", "'|'", "'?'", "':'", "'='", "';'",
  "'{'", "'}'", "$accept", "primary_expression", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_list_specifier", "type_list",
  "type_specifier", "struct_specifier", "struct_declaration_list",
  "struct_declaration", "specifier_qualifier_list",
  "struct_declarator_list", "struct_declarator", "enum_specifier",
  "enumerator_list", "enumerator", "declarator", "direct_declarator",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "statement", "labeled_statement", "compound_statement",
  "declaration_list", "statement_list", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_definition", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short
   parser ::yyrline_[] =
  {
       0,    71,    71,    72,    73,    77,    78,    79,    80,    81,
      82,    83,    87,    88,    92,    93,    94,    95,    99,   100,
     101,   102,   106,   107,   111,   112,   113,   114,   118,   119,
     120,   124,   125,   126,   130,   131,   132,   133,   134,   138,
     139,   140,   144,   145,   149,   150,   154,   155,   159,   160,
     164,   165,   169,   170,   174,   175,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   194,   195,
     199,   203,   204,   208,   209,   210,   211,   212,   213,   217,
     218,   222,   223,   227,   228,   232,   236,   237,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   254,   255,
     256,   260,   261,   265,   269,   270,   271,   272,   276,   277,
     281,   282,   283,   287,   288,   289,   293,   294,   298,   299,
     303,   307,   308,   309,   310,   311,   312,   313,   317,   318,
     322,   323,   327,   328,   329,   333,   334,   338,   339,   343,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   359,
     360,   361,   365,   366,   370,   371,   372,   373,   374,   375,
     379,   380,   384,   385,   386,   387,   391,   392,   396,   397,
     401,   402,   406,   407,   408,   412,   413,   414,   415,   419,
     420,   421,   422,   423,   427,   428,   432,   433,   437,   438,
     439,   440
  };

  // Print the state stack on the debug stream.
  void
   parser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   parser ::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 3692 "parser.cpp.re"

#line 443 "parser.yy"


yy::parser::symbol_type yy::yylex(lexcontext& ctx)
{
	const char* YYMARKER;
	const char* anchor = ctx.cursor;
	unsigned int comment_scope = 0;
#define walk() { ctx.loc.columns(ctx.cursor - anchor); }
#define advance(label) { anchor = ctx.cursor; ctx.loc.step(); goto label; }
#define token(name) { walk(); return parser::make_##name(ctx.loc); }
#define tokenv(name, ...) { walk(); return parser::make_##name(__VA_ARGS__, ctx.loc); }

	auto getIdentifier = [&](std::string& identifier)
	{
  		switch (ctx.identifierFlag)
		{
			case IdentifierFlag::FUNCTION_NAME: tokenv(FUNCTION_NAME, identifier);
			case IdentifierFlag::VARIABLE_NAME: tokenv(VARIABLE_NAME, identifier);
			case IdentifierFlag::TYPE_NAME: tokenv(TYPE_NAME, identifier);
		}
	};

%{ /* Begin re2c lexer */
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE  = "char";
	re2c:define:YYCURSOR = "ctx.cursor";
	
	end = "\x00";
	%}

init:
	%{
	// Keywords
	"typedef"                { token(TYPEDEF); }
	"if"                     { token(IF); }
	"else"                   { token(ELSE); }
	"switch"                 { token(SWITCH); }
	"case"                   { token(CASE); }
	"for"                    { token(FOR); }
	"do"                     { token(DO); }
	"while"                  { token(WHILE); }
	"break"                  { token(BREAK); }
	"continue"               { token(CONTINUE); }
	"struct"                 { token(STRUCT); }
	"import"                 { token(IMPORT); }
	"extern"                 { token(EXTERN); }
	"const"                  { token(CONST); }
	"return"                 { token(RETURN); }
	"enum"                   { token(ENUM); }
	"discard"                { token(DISCARD); }
	"attribute"              { token(ATTRIBUTE); }
	"uniform"                { token(UNIFORM); }
	"sampler"                { token(SAMPLER); }
	"operator"               { token(OPERATOR); }
	"int"                    { token(INT); }
	"uint"                   { token(UINT); }
	"float"                  { token(FLOAT); }
	"double"                 { token(DOUBLE); }
	"bool"                   { token(BOOL); }

	// Whitespace
	"\r\n" | [\r\n]          { ctx.loc.lines();   advance(init); }
	[\t\v\b\f ]              { ctx.loc.columns(); advance(init); }
	end                      { token(END); }

	// Identifiers
	[a-zA-Z_] [a-zA-Z_0-9]*  { return getIdentifier(std::string(anchor, ctx.cursor)); }

	// Literals
	[0-9]+ [f]               { token(CONSTANT); }
	[0-9]+                   { token(CONSTANT); }

	// Comment
	"//" [^\r\n]*            { walk(); advance(init); }
	"/*"                     { comment_scope++; goto block_comment; }

	// Multi-char operators and any other character (either an operator or an invalid symbol)
	"..."                    { token(ELLIPSIS); }
	"->"                     { token(ARROW); }
	"&&"                     { token(AND_OP); }
	"||"                     { token(OR_OP); }
	"++"                     { token(INC_OP); }
	"--"                     { token(DEC_OP); }
	"!="                     { token(NE_OP); }
	"=="                     { token(EQ_OP); }
	"+="                     { token(ADD_ASSIGN); }
	"-="                     { token(SUB_ASSIGN); }
	"*="                     { token(MUL_ASSIGN); }
	"/="                     { token(DIV_ASSIGN); }
	"%="                     { token(MOD_ASSIGN); }
	"|="                     { token(OR_ASSIGN); }
	"&="                     { token(AND_ASSIGN); }
	"^="                     { token(XOR_ASSIGN); }
	"~="                     { token(NOT_ASSIGN); }
	"<<="                    { token(LEFT_ASSIGN); }
	">>="                    { token(RIGHT_ASSIGN); }
	"<<"                     { token(LEFT_OP); }
	">>"                     { token(RIGHT_OP); }
	"<="                     { token(LE_OP); }
	">="                     { token(GE_OP); }
	*                        { walk(); return parser::symbol_type(parser::token_type(ctx.cursor[-1]&0xFF), ctx.loc); }
	%}

block_comment:
	%{
	// Block Comment
	"/*"                     { comment_scope++; goto block_comment; }
	"*/"                     { walk(); comment_scope--; if(!comment_scope) advance(init); goto block_comment; }
	"\r\n" | [\r\n]          { ctx.loc.lines();   advance(block_comment); }
	[\t\v\b\f ]              { ctx.loc.columns(); advance(block_comment); }
	end                        { token(BLOCK_COMMENT_ERROR); }
	*                        { goto block_comment; }
	%} /* End lexer */
}

void yy::parser::error(const location_type& l, const std::string& message)
{
	std::cerr << l.begin.filename->c_str() << ':' << l.begin.line << ':' << l.begin.column << '-' << l.end.column << ": " << message << '\n';

	// find a better way. dont open and skip for every single error
	std::ifstream f(l.begin.filename->c_str());
	std::string s;

	for (int i = 0; i < l.begin.line; i++)
	{
		std::getline(f, s);
	}

	std::cout << s << std::endl;
   f.close();

std::cerr << std::string(l.begin.column - 1, ' ') << '^' << std::string(l.end.column - l.begin.column - 1, '~') << std::endl;
}

namespace kyte
{
	void parse(const std::string& sourceCode, std::string debugName)
	{
		lexcontext ctx;
		ctx.cursor = sourceCode.c_str();
		ctx.loc.begin.filename = &debugName;
		ctx.loc.end.filename   = &debugName;

		yy::parser parser(ctx);
		parser.parse();
	}
}
