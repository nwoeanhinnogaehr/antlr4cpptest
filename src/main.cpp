#include <iostream>
#include <string>

#include "TestBaseVisitor.h"
#include "TestLexer.h"
#include "TestParser.h"
#include "antlr4-runtime.h"

using namespace antlrcpptest;
using namespace antlr4;

class Interpreter : public TestBaseVisitor {
  public:
    virtual antlrcpp::Any visitOp(TestParser::OpContext *ctx) override {
        int lhs = (int)visit(&*ctx->expr(0));
        int rhs = (int)visit(&*ctx->expr(1));
        switch (ctx->op->getType()) {
        case TestLexer::SUB:
            return antlrcpp::Any(lhs - rhs);
        case TestLexer::ADD:
            return antlrcpp::Any(lhs + rhs);
        case TestLexer::MUL:
            return antlrcpp::Any(lhs * rhs);
        case TestLexer::DIV:
            return antlrcpp::Any(lhs / rhs);
        }
        return antlrcpp::Any(-1);
    }

    virtual antlrcpp::Any visitParens(TestParser::ParensContext *ctx) override {
        return visit(&*ctx->expr());
    }

    virtual antlrcpp::Any visitInt(TestParser::IntContext *ctx) override {
        int value = stoi(ctx->getText());
        return antlrcpp::Any(value);
    }
};

int main(int, const char **) {
    std::string input_string, tmp;
    while (std::getline(std::cin, tmp)) {
        input_string += tmp;
    }
    ANTLRInputStream input(input_string);
    TestLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    TestParser parser(&tokens);
    Ref<tree::ParseTree> tree = parser.expr();
    std::cout << tree->toStringTree(&parser) << std::endl;

    Interpreter ipt;
    std::cout << (int)ipt.visit(&*tree) << std::endl;

    return 0;
}
