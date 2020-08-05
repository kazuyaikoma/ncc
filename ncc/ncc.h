#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  Tokenizer
 */
typedef enum {
  TK_RESERVED,  // reserved Token
  TK_IDENT,     // variables identifier
  TK_NUM,       // Integer
  TK_EOF,       // EOF
} TokenKind;

typedef struct Token Token;

struct Token {
  TokenKind kind;   // Token Type
  Token *next;      // next Token
  int val;          // token's integer value
  char *str;        // token's text
  int len;          // token's length
};

// current focused Token
Token *token;

// input
char *user_input;

void error_at(char *loc, char *fmt, ...);

/**
 *  次のトークンが期待通りの記号の場合:
 *    トークンを１つ読み進めてtrueを返す
 *  そうでない場合:
 *    falseを返す
 */
bool consume(char *op);

bool consume_ident();

/**
 *  次のトークンが期待通りの記号の場合:
 *    トークンを１つ読み進める
 *  そうでない場合:
 *    エラーを起こす
 */
void expect(char op);

/**
 *  次のトークンが数値の場合:
 *    トークンを１つ読み進めてその数値を返す
 *  そうでない場合:
 *    エラーを起こす
 */
int expect_number();

bool at_eof();

/**
 *  新しいトークンを作りcurに繋げる
 */
Token *new_token(TokenKind kind, Token *cur, char *str, int len);

bool startsWith(char *p, char *q);

/**
 * 入力文字列pをtokenizeしてから返す
 */
Token *tokenize(char *p);

/*
 *  Parser
 */
typedef struct Node Node;

Node *code[100];

typedef enum {
  ND_ADD,       // +
  ND_SUB,       // -
  ND_MUL,       // *
  ND_DIV,       // /
  ND_EQ,        // ==
  ND_NE,        // !=
  ND_LT,        // <
  ND_LE,        // <=
  ND_LVAR,      // variable name
  ND_NUM,       // Integer
} NodeKind;

struct Node {
  NodeKind kind;  // Node type
  Node *lhs;      // left-hand side Node
  Node *rhs;      // right-hand side Node
  int val;        // Node's value if kind is ND_NUM
  int offset;     // Node's value if kind is ND_LVAR, offset from base pointer
};

Node *new_node(NodeKind kind);

Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);

Node *new_num(int val);

void program();
Node *stmt();
Node *expr();
Node *assign();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

/*
 *  Generator
 */
void gen(Node *node);
