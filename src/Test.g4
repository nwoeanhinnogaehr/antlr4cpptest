grammar Test;

// Expression
expr : expr op=(MUL|DIV) expr # op
     | expr op=(ADD|SUB) expr # op
     | INT # int
     | '(' expr ')' # parens
     ;

// Tokens
INT: [0-9]+ ;
MUL: '*' ;
DIV: '/' ;
ADD: '+' ;
SUB: '-' ;

// Skip whitespace
WS : [ \t\r\n]+ -> skip;
