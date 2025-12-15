%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);
extern FILE *yyin;
extern int yylineno;

typedef struct Expr Expr;
typedef struct Stmt Stmt;

typedef enum { VT_UNDEF, VT_INT, VT_FLOAT, VT_STRING } VarType;
typedef enum { EX_NUM, EX_VAR, EX_STR, EX_BINOP, EX_CMPOP } ExprKind;
typedef enum { ST_PRINT, ST_ASSIGN, ST_SCAN, ST_IF, ST_FOR, ST_RETURN } StmtKind;
typedef enum { VAL_INT, VAL_FLOAT, VAL_STRING } ValueKind;

typedef struct Var {
    VarType type;
    double num;
    char *str;
} Var;

typedef struct Value {
    ValueKind kind;
    double num;
    char *str;
} Value;

struct Expr {
    ExprKind kind;
    int op;
    double num;
    char *var;
    char *sval;
    Expr *left;
    Expr *right;
};

struct Stmt {
    StmtKind kind;
    Stmt *next;
    union {
        struct { char *text; char *var; } print;
        struct { char *var; Expr *value; int is_string_assign; char *sval; int declared_type; } assign;
        struct { char *var; } scan;
        struct { Expr *cond; Stmt *then_branch; Stmt *else_branch; } if_stmt;
        struct { char *var; Expr *limit; Stmt *body; } for_stmt;
        struct { Expr *value; } ret;
    } u;
};

Var vars[256];
Stmt *root = NULL;
int type_error_count = 0;

Expr *make_num(double n);
Expr *make_var(char *name);
Expr *make_strlit(char *s);
Expr *make_bin(int op, Expr *l, Expr *r, int is_cmp);
Stmt *make_print_text(char *s);
Stmt *make_print_var(char *name);
Stmt *make_assign_expr(char *name, Expr *e);
Stmt *make_assign_string(char *name, char *s);
Stmt *make_scan(char *name);
Stmt *make_if(Expr *cond, Stmt *then_b, Stmt *else_b);
Stmt *make_for(char *var, Expr *limit, Stmt *body);
Stmt *make_return(Expr *e);
Stmt *append_stmt(Stmt *list, Stmt *s);

Value eval_value(Expr *e);
void exec_stmt_list(Stmt *s);
void exec_stmt(Stmt *s);

static Var *get_var_slot(const char *name);
static void set_num(const char *name, double v, VarType t);
static void set_str(const char *name, const char *s);
static const char *expr_get_str(Expr *e);
static Value make_int_value(int x);
static Value make_float_value(double x);
static Value make_string_value(const char *s);
%}

%code requires {
    struct Expr;
    struct Stmt;
}

%union {
    double num;
    char *str;
    struct Expr *expr;
    struct Stmt *stmt;
}

%token PRINT IF THEN ELSE END FOR RETURN SCAN LET CHOLO
%token INT_T FLOAT_T STRING_T
%token <num> NUMBER
%token <str> ID
%token <str> STRING
%token ASSIGN GT LT EQ INC DEC

%left GT LT EQ
%left '+' '-'
%left '*' '/'

%type <stmt> program stmt_list statement opt_else
%type <expr> expr

%%
program
    : stmt_list                 { root = $1; }
    ;

stmt_list
    :                           { $$ = NULL; }
    | stmt_list statement       { $$ = append_stmt($1, $2); }
    ;

statement
    : PRINT STRING              { $$ = make_print_text($2); }
    | PRINT ID                  { $$ = make_print_var($2); }

    | LET ID                    { $$ = make_assign_expr($2, make_num(0.0)); }

    | LET ID ASSIGN STRING      { $$ = make_assign_string($2, $4); }
    | LET ID ASSIGN expr        { $$ = make_assign_expr($2, $4); }

    | LET INT_T ID                  { $$ = make_assign_expr($3, make_num(0.0)); ((Stmt*)$$)->u.assign.declared_type = VT_INT; }
    | LET FLOAT_T ID                { $$ = make_assign_expr($3, make_num(0.0)); ((Stmt*)$$)->u.assign.declared_type = VT_FLOAT; }
    | LET STRING_T ID               { $$ = make_assign_string($3, strdup("")); ((Stmt*)$$)->u.assign.declared_type = VT_STRING; }

    | LET INT_T ID ASSIGN expr      { $$ = make_assign_expr($3, $5); ((Stmt*)$$)->u.assign.declared_type = VT_INT; }
    | LET FLOAT_T ID ASSIGN expr    { $$ = make_assign_expr($3, $5); ((Stmt*)$$)->u.assign.declared_type = VT_FLOAT; }
    | LET STRING_T ID ASSIGN expr   { $$ = make_assign_expr($3, $5); ((Stmt*)$$)->u.assign.declared_type = VT_STRING; }

    | ID ASSIGN expr            { $$ = make_assign_expr($1, $3); }
    | ID ASSIGN STRING          { $$ = make_assign_string($1, $3); }

    | SCAN ID                   { $$ = make_scan($2); }

    | IF expr THEN stmt_list opt_else END
                                { $$ = make_if($2, $4, $5); }

    | CHOLO ID FOR expr stmt_list END
                                { $$ = make_for($2, $4, $5); }

    | RETURN expr               { $$ = make_return($2); }
    ;

opt_else
    :                           { $$ = NULL; }
    | ELSE stmt_list            { $$ = $2; }
    ;

expr
    : expr GT expr              { $$ = make_bin(GT,  $1, $3, 1); }
    | expr LT expr              { $$ = make_bin(LT,  $1, $3, 1); }
    | expr EQ expr              { $$ = make_bin(EQ,  $1, $3, 1); }

    | expr '+' expr             { $$ = make_bin('+', $1, $3, 0); }
    | expr '-' expr             { $$ = make_bin('-', $1, $3, 0); }
    | expr '*' expr             { $$ = make_bin('*', $1, $3, 0); }
    | expr '/' expr             { $$ = make_bin('/', $1, $3, 0); }

    | NUMBER                    { $$ = make_num($1); }
    | ID                        { $$ = make_var($1); }
    | STRING                    { $$ = make_strlit($1); }
    ;
%%

Expr *make_num(double n){
    Expr *e = malloc(sizeof(Expr));
    memset(e,0,sizeof(*e));
    e->kind = EX_NUM;
    e->num = n;
    return e;
}

Expr *make_var(char *name){
    Expr *e = malloc(sizeof(Expr));
    memset(e,0,sizeof(*e));
    e->kind = EX_VAR;
    e->var = name;
    return e;
}

Expr *make_strlit(char *s){
    Expr *e = malloc(sizeof(Expr));
    memset(e,0,sizeof(*e));
    e->kind = EX_STR;
    e->sval = s;
    return e;
}

Expr *make_bin(int op, Expr *l, Expr *r, int is_cmp){
    Expr *e = malloc(sizeof(Expr));
    memset(e,0,sizeof(*e));
    e->kind = is_cmp ? EX_CMPOP : EX_BINOP;
    e->op = op;
    e->left = l;
    e->right = r;
    return e;
}

Stmt *make_print_text(char *s){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_PRINT;
    st->next = NULL;
    st->u.print.text = s;
    st->u.print.var = NULL;
    return st;
}

Stmt *make_print_var(char *name){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_PRINT;
    st->next = NULL;
    st->u.print.text = NULL;
    st->u.print.var = name;
    return st;
}

Stmt *make_assign_expr(char *name, Expr *e){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_ASSIGN;
    st->next = NULL;
    st->u.assign.var = name;
    st->u.assign.value = e;
    st->u.assign.is_string_assign = 0;
    st->u.assign.sval = NULL;
    st->u.assign.declared_type = VT_UNDEF;
    return st;
}

Stmt *make_assign_string(char *name, char *s){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_ASSIGN;
    st->next = NULL;
    st->u.assign.var = name;
    st->u.assign.value = NULL;
    st->u.assign.is_string_assign = 1;
    st->u.assign.sval = s;
    st->u.assign.declared_type = VT_UNDEF;
    return st;
}

Stmt *make_scan(char *name){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_SCAN;
    st->next = NULL;
    st->u.scan.var = name;
    return st;
}

Stmt *make_if(Expr *cond, Stmt *t, Stmt *e){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_IF;
    st->next = NULL;
    st->u.if_stmt.cond = cond;
    st->u.if_stmt.then_branch = t;
    st->u.if_stmt.else_branch = e;
    return st;
}

Stmt *make_for(char *var, Expr *limit, Stmt *body){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_FOR;
    st->next = NULL;
    st->u.for_stmt.var = var;
    st->u.for_stmt.limit = limit;
    st->u.for_stmt.body = body;
    return st;
}

Stmt *make_return(Expr *e){
    Stmt *st = malloc(sizeof(Stmt));
    st->kind = ST_RETURN;
    st->next = NULL;
    st->u.ret.value = e;
    return st;
}

Stmt *append_stmt(Stmt *list, Stmt *s){
    if(!list) return s;
    Stmt *p = list;
    while(p->next) p = p->next;
    p->next = s;
    return list;
}

static Var *get_var_slot(const char *name){
    unsigned char idx = (unsigned char)name[0];
    return &vars[idx];
}

static void set_num(const char *name, double v, VarType t){
    Var *slot = get_var_slot(name);
    slot->type = t;
    slot->num = v;
    if(slot->str){
        free(slot->str);
        slot->str = NULL;
    }
}

static void set_str(const char *name, const char *s){
    Var *slot = get_var_slot(name);
    slot->type = VT_STRING;
    slot->num = 0.0;
    if(slot->str) free(slot->str);
    slot->str = s ? strdup(s) : strdup("");
}

static const char *expr_get_str(Expr *e){
    if(!e) return NULL;
    if(e->kind == EX_STR) return e->sval;
    if(e->kind == EX_VAR){
        Var *slot = get_var_slot(e->var);
        if(slot->type == VT_STRING) return slot->str;
        return NULL;
    }
    return NULL;
}

static Value make_int_value(int x){
    Value v; v.kind = VAL_INT; v.num = x; v.str = NULL; return v;
}

static Value make_float_value(double x){
    Value v; v.kind = VAL_FLOAT; v.num = x; v.str = NULL; return v;
}

static Value make_string_value(const char *s){
    Value v; v.kind = VAL_STRING; v.num = 0.0; v.str = (char*)s; return v;
}

Value eval_value(Expr *e){
    if(!e) return make_int_value(0);
    switch(e->kind){
    case EX_NUM:
        if(e->num == (int)e->num) return make_int_value((int)e->num);
        return make_float_value(e->num);

    case EX_VAR: {
        Var *slot = get_var_slot(e->var);
        if(slot->type == VT_STRING) return make_string_value(slot->str);
        if(slot->type == VT_FLOAT)  return make_float_value(slot->num);
        return make_int_value((int)slot->num);
    }

    case EX_STR:
        return make_string_value(e->sval);

    case EX_BINOP: {
        Value a = eval_value(e->left);
        Value b = eval_value(e->right);
        if(a.kind == VAL_STRING || b.kind == VAL_STRING){
            fprintf(stderr, "Type error (line %d): string used in arithmetic\n", yylineno);
            type_error_count++;
            return make_int_value(0);
        }
        double na = a.num, nb = b.num, r = 0.0;
        switch(e->op){
            case '+': r = na + nb; break;
            case '-': r = na - nb; break;
            case '*': r = na * nb; break;
            case '/': r = (nb != 0.0) ? na / nb : 0.0; break;
        }
        if(a.kind == VAL_FLOAT || b.kind == VAL_FLOAT || r != (int)r)
            return make_float_value(r);
        return make_int_value((int)r);
    }

    case EX_CMPOP: {
        Value a = eval_value(e->left);
        Value b = eval_value(e->right);

        if(a.kind == VAL_STRING || b.kind == VAL_STRING){
            if(a.kind != VAL_STRING || b.kind != VAL_STRING){
                fprintf(stderr, "Type error (line %d): cannot compare string with number\n", yylineno);
                type_error_count++;
                return make_int_value(0);
            }
            if(e->op != EQ){
                fprintf(stderr, "Type error (line %d): only == allowed for strings\n", yylineno);
                type_error_count++;
                return make_int_value(0);
            }
            const char *sa = a.str ? a.str : "";
            const char *sb = b.str ? b.str : "";
            return make_int_value(strcmp(sa, sb) == 0);
        }

        double na = a.num, nb = b.num;
        int res = 0;
        switch(e->op){
            case GT: res = na > nb; break;
            case LT: res = na < nb; break;
            case EQ: res = na == nb; break;
        }
        return make_int_value(res);
    }
    }
    return make_int_value(0);
}

void exec_stmt_list(Stmt *s){
    while(s){
        exec_stmt(s);
        s = s->next;
    }
}

void exec_stmt(Stmt *s){
    if(!s) return;
    switch(s->kind){

    case ST_PRINT: {
        if(s->u.print.text){
            printf("%s\n", s->u.print.text);
        } else {
            Var *slot = get_var_slot(s->u.print.var);
            if(slot->type == VT_STRING)
                printf("%s\n", slot->str ? slot->str : "");
            else if(slot->type == VT_FLOAT)
                printf("%g\n", slot->num);
            else
                printf("%d\n", (int)slot->num);
        }
        break;
    }

    case ST_ASSIGN: {
        Value v;
        if(s->u.assign.is_string_assign)
            v = make_string_value(s->u.assign.sval);
        else
            v = eval_value(s->u.assign.value);

        Var *slot = get_var_slot(s->u.assign.var);
        VarType t = slot->type;
        VarType declared = (VarType)s->u.assign.declared_type;
        if(declared != VT_UNDEF)
            t = declared;

        if(t == VT_UNDEF){
            if(v.kind == VAL_STRING) t = VT_STRING;
            else if(v.kind == VAL_FLOAT) t = VT_FLOAT;
            else t = VT_INT;
        }

        if(t == VT_STRING){
            if(v.kind != VAL_STRING){
                fprintf(stderr,
                        "Type error (line %d): cannot assign numeric value to string variable '%s'\n",
                        yylineno, s->u.assign.var);
                type_error_count++;
                break;
            }
            set_str(s->u.assign.var, v.str);
        } else if(t == VT_INT){
            if(v.kind == VAL_STRING){
                fprintf(stderr,
                        "Type error (line %d): cannot assign string value to numeric variable '%s'\n",
                        yylineno, s->u.assign.var);
                type_error_count++;
                break;
            }
            if(v.num != (int)v.num){
                fprintf(stderr,
                        "Type error (line %d): cannot assign non-integer value %f to int variable '%s'\n",
                        yylineno, v.num, s->u.assign.var);
                type_error_count++;
                break;
            }
            set_num(s->u.assign.var, (int)v.num, VT_INT);
        } else if(t == VT_FLOAT){
            if(v.kind == VAL_STRING){
                fprintf(stderr,
                        "Type error (line %d): cannot assign string value to numeric variable '%s'\n",
                        yylineno, s->u.assign.var);
                type_error_count++;
                break;
            }
            set_num(s->u.assign.var, v.num, VT_FLOAT);
        }
        break;
    }

    case ST_SCAN: {
        char buf[1024];
        printf("Enter value for %s: ", s->u.scan.var);
        if(!fgets(buf, sizeof(buf), stdin)){
            fprintf(stderr, "Input error\n");
            type_error_count++;
            break;
        }
        size_t L = strlen(buf);
        if(L && buf[L-1] == '\n') buf[L-1] = '\0';

        Var *slot = get_var_slot(s->u.scan.var);
        VarType t = slot->type;

        int has_digit = 0, has_dot = 0;
        char *p = buf;
        if(*p == '+' || *p == '-') p++;
        while(*p){
            if(*p >= '0' && *p <= '9') has_digit = 1;
            else if(*p == '.'){
                if(has_dot){ has_dot = 2; break; }
                has_dot = 1;
            } else { has_digit = 0; break; }
            p++;
        }
        int is_num = has_digit && has_dot != 2;

        if(t == VT_STRING){
            set_str(s->u.scan.var, buf);
        } else if(is_num){
            double val = atof(buf);
            if(t == VT_UNDEF){
                if(has_dot) t = VT_FLOAT;
                else t = VT_INT;
            }
            if(t == VT_INT){
                if(val != (int)val){
                    fprintf(stderr,
                            "Type error (line %d): cannot assign non-integer input to int variable '%s'\n",
                            yylineno, s->u.scan.var);
                    type_error_count++;
                    break;
                }
                set_num(s->u.scan.var, (int)val, VT_INT);
            } else {
                set_num(s->u.scan.var, val, VT_FLOAT);
            }
        } else {
            if(t != VT_UNDEF && t != VT_STRING){
                fprintf(stderr,
                        "Type error (line %d): non-numeric input for numeric variable '%s'\n",
                        yylineno, s->u.scan.var);
                type_error_count++;
                break;
            }
            set_str(s->u.scan.var, buf);
        }
        break;
    }

    case ST_IF: {
        Value v = eval_value(s->u.if_stmt.cond);
        if(v.kind == VAL_STRING){
            fprintf(stderr,
                    "Type error (line %d): string used as condition\n",
                    yylineno);
            type_error_count++;
            break;
        }
        if((int)v.num)
            exec_stmt_list(s->u.if_stmt.then_branch);
        else if(s->u.if_stmt.else_branch)
            exec_stmt_list(s->u.if_stmt.else_branch);
        break;
    }

    case ST_FOR: {
        Var *slot = get_var_slot(s->u.for_stmt.var);
        if(slot->type == VT_UNDEF)
            set_num(s->u.for_stmt.var, 0.0, VT_INT);
        Value lim = eval_value(s->u.for_stmt.limit);
        if(lim.kind == VAL_STRING){
            fprintf(stderr,
                    "Type error (line %d): string used as loop limit\n",
                    yylineno);
            type_error_count++;
            break;
        }
        int limit = (int)lim.num;
        while((int)get_var_slot(s->u.for_stmt.var)->num < limit){
            exec_stmt_list(s->u.for_stmt.body);
            double now = get_var_slot(s->u.for_stmt.var)->num;
            set_num(s->u.for_stmt.var, now + 1.0, VT_INT);
        }
        break;
    }

    case ST_RETURN: {
        Value v = eval_value(s->u.ret.value);
        if(v.kind == VAL_STRING)
            printf("Return: %s\n", v.str ? v.str : "");
        else
            printf("Return: %g\n", v.num);
        exit(0);
    }
    }
}

void yyerror(const char *s){
    fprintf(stderr, "Parse error (line %d): %s\n", yylineno, s);
}

int main(int argc,char **argv){
    int i;
    for(i = 0; i < 256; i++){
        vars[i].type = VT_UNDEF;
        vars[i].num = 0.0;
        vars[i].str = NULL;
    }
    FILE *src = NULL;
    if(argc > 1){
        src = fopen(argv[1], "r");
        if(!src){
            perror("Cannot open source file");
            return 1;
        }
        yyin = src;
    } else {
        yyin = stdin;
    }
    if(yyparse() == 0)
        exec_stmt_list(root);

    if(type_error_count > 0){
        fprintf(stderr, "\nProgram finished with %d type error(s).\n", type_error_count);
    }

    if(src) fclose(src);
    return 0;
}
