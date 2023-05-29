#include "parser.hpp"
#include "prepro/prepro.hpp"
#include "binop/binop.hpp"
#include "intval/intval.hpp"
#include "strval/strval.hpp"
#include "noop/noop.hpp"
#include "unop/unop.hpp"
#include "block/block.hpp"
#include "print/print.hpp"
#include "assignment/assignment.hpp"
#include "identifier/identifier.hpp"
#include "if/if.hpp"
#include "while/while.hpp"
#include "readline/readline.hpp"
#include "vardec/vardec.hpp"
#include "funcdec/funcdec.hpp"
#include "return/return.hpp"
#include "funccall/funccall.hpp"

#include <memory>
#include <vector>
#include <iostream>
#include "utils.hpp"

Tokenizer Parser::tokenizer = Tokenizer();

Node *Parser::parseFactor()
{
    std::vector<Node *> children(1, nullptr);
    Node *node = nullptr;

    tokenizer.selectNext();
    if (tokenizer.next.type == "NUMBER")
    {
        node = new IntVal(children, tokenizer.next.value);
        tokenizer.selectNext();
        return node;
    }
    else if (tokenizer.next.type == "STRING")
    {
        node = new StrVal(children, tokenizer.next.value);
        tokenizer.selectNext();
        return node;
    }
    else if (tokenizer.next.type == "IDENTIFIER")
    {
        node = new Identifier(tokenizer.next.value);
        std::string func_name = std::get<std::string>(tokenizer.next.value);
        tokenizer.selectNext();
        std::vector<Node *> params;
        if (tokenizer.next.type == "LPAREN")
        {
            tokenizer.selectNext();
            while (tokenizer.next.type != "RPAREN")
            {
                tokenizer.selectNext();
                params.push_back(parseRelExpr());
                if (tokenizer.next.type == "COMMA" && tokenizer.next.type != "RPAREN")
                    tokenizer.selectNext();
            }
            tokenizer.selectNext();
            return new FuncCall(func_name, params);
        }
        return node;
    }
    else if (tokenizer.next.type == "MINUS")
    {
        children[0] = parseFactor();
        return new UnOp(children, "-");
    }
    else if (tokenizer.next.type == "PLUS")
    {
        children[0] = parseFactor();
        return new UnOp(children, "+");
    }
    else if (tokenizer.next.type == "NOT")
    {
        children[0] = parseFactor();
        return new UnOp(children, "!");
    }
    else if (tokenizer.next.type == "readline")
    {
        tokenizer.selectNext();
        if (tokenizer.next.type != "LPAREN")
            throw "Expected LPAREN";
        tokenizer.selectNext();
        if (tokenizer.next.type != "RPAREN")
            throw "Expected RPAREN";
        tokenizer.selectNext();
        return new ReadLine();
    }
    else if (tokenizer.next.type == "LPAREN")
    {
        node = parseRelExpr();
        if (tokenizer.next.type == "RPAREN")
        {
            tokenizer.selectNext();
            return node;
        }
        else
        {
            delete node;
            for (auto child : children)
                delete child;

            throw "Expected RPAREN";
        }
    }
    else if (tokenizer.next.type == "RPAREN")
    {
        return new NoOp();
    }
    else
    {
        for (auto child : children)
            delete child;
        throw "Expected NUMBER";
    }

    for (auto child : children)
        delete child;
}

Node *Parser::parseTerm()
{
    Node *node = Parser::parseFactor();
    std::vector<Node *> children(2, nullptr);

    while (tokenizer.next.type == "MULT" || tokenizer.next.type == "DIV" || tokenizer.next.type == "AND")
    {
        if (tokenizer.next.type == "MULT")
        {
            children[0] = node;
            children[1] = Parser::parseFactor();
            node = new BinOp(children, "*");
        }
        else if (tokenizer.next.type == "DIV")
        {
            children[0] = node;
            children[1] = Parser::parseFactor();
            node = new BinOp(children, "/");
        }
        else if (tokenizer.next.type == "AND")
        {
            children[0] = node;
            children[1] = Parser::parseFactor();
            node = new BinOp(children, "&&");
        }
    }
    if (tokenizer.next.type == "NUMBER")
        throw "Expected EOF";

    return node;
}

Node *Parser::parseExpression()
{
    Node *node = Parser::parseTerm();
    std::vector<Node *> children(2, nullptr);

    while (tokenizer.next.type == "PLUS" || tokenizer.next.type == "MINUS" || tokenizer.next.type == "OR")
    {
        if (tokenizer.next.type == "PLUS")
        {
            children[0] = node;
            children[1] = Parser::parseTerm();
            node = new BinOp(children, "+");
        }
        else if (tokenizer.next.type == "MINUS")
        {
            children[0] = node;
            children[1] = Parser::parseTerm();
            node = new BinOp(children, "-");
        }
        else if (tokenizer.next.type == "OR")
        {
            children[0] = node;
            children[1] = Parser::parseTerm();
            node = new BinOp(children, "||");
        }
    }
    if (tokenizer.next.type == "NUMBER" || tokenizer.next.type == "UNKNOWN")
        throw "Expected EOF";
    return node;
}

Node *Parser::parseRelExpr()
{
    Node *node = Parser::parseExpression();
    std::vector<Node *> children(2, nullptr);

    if (tokenizer.next.type == "EQUALS")
    {
        children[0] = node;
        children[1] = Parser::parseExpression();
        node = new BinOp(children, "==");
    }
    else if (tokenizer.next.type == "NOTEQUALS")
    {
        children[0] = node;
        children[1] = Parser::parseExpression();
        node = new BinOp(children, "!=");
    }
    else if (tokenizer.next.type == "LESSTHAN")
    {
        children[0] = node;
        children[1] = Parser::parseExpression();
        node = new BinOp(children, "<");
    }
    else if (tokenizer.next.type == "GREATERTHAN")
    {
        children[0] = node;
        children[1] = Parser::parseExpression();
        node = new BinOp(children, ">");
    }
    else if (tokenizer.next.type == "LESSTHANEQUALS")
    {
        children[0] = node;
        children[1] = Parser::parseExpression();
        node = new BinOp(children, "<=");
    }
    else if (tokenizer.next.type == "GREATERTHANEQUALS")
    {
        children[0] = node;
        children[1] = Parser::parseExpression();
        node = new BinOp(children, ">=");
    }
    else if (tokenizer.next.type == "CONCAT")
    {
        children[0] = node;
        children[1] = Parser::parseExpression();
        node = new BinOp(children, ".");
    }
    if (tokenizer.next.type == "NUMBER" || tokenizer.next.type == "UNKNOWN")
        throw "Expected EOF";
    return node;
}

Node *Parser::parseStatement()
{
    std::vector<Node *> children(3, nullptr);
    Node *node = nullptr;
    if (tokenizer.next.type == "println")
    {
        tokenizer.selectNext();
        if (tokenizer.next.type == "LPAREN")
        {
            children[0] = parseRelExpr();
            if (tokenizer.next.type == "RPAREN")
            {
                tokenizer.selectNext();
                if (tokenizer.next.type != "NEWLINE")
                    throw "Expected NEWLINE";
                return new Print(children);
            }
            else
                throw "Expected RPAREN";
        }
        else
            throw "Expected LPAREN";
    }
    else if (tokenizer.next.type == "function")
    {
        tokenizer.selectNext();
        if (tokenizer.next.type == "IDENTIFIER")
        {
            node = new Identifier(tokenizer.next.value);
            children[0] = node;
            std::string func_identifier = std::get<std::string>(tokenizer.next.value);
            tokenizer.selectNext();
            if (tokenizer.next.type == "LPAREN")
            {
                tokenizer.selectNext();
                std::string param_identifier;
                std::string param_type;
                std::vector<Node *> params;
                std::vector<Node *> param_children(1, nullptr);
                while (tokenizer.next.type != "RPAREN")
                {
                    if (tokenizer.next.type == "IDENTIFIER")
                    {
                        param_children[0] = new Identifier(tokenizer.next.value);
                        param_identifier = std::get<std::string>(tokenizer.next.value);
                        tokenizer.selectNext();
                        if (tokenizer.next.type == "DECLARATION")
                        {
                            tokenizer.selectNext();
                            if (tokenizer.next.type == "TYPE")
                            {
                                param_type = std::get<std::string>(tokenizer.next.value);
                                tokenizer.selectNext();
                                if (tokenizer.next.type == "COMMA")
                                {
                                    tokenizer.selectNext();
                                    if (tokenizer.next.type != "IDENTIFIER")
                                        throw "Expected IDENTIFIER";
                                }
                                else if (tokenizer.next.type != "COMMA" && tokenizer.next.type != "RPAREN")
                                    throw "Expected COMMA or RPAREN";
                            }
                        }
                        params.push_back(new VarDec(param_type, param_identifier, param_children));
                    }
                }

                std::string func_type;
                tokenizer.selectNext();
                if (tokenizer.next.type == "DECLARATION")
                {
                    tokenizer.selectNext();
                    if (tokenizer.next.type == "TYPE")
                    {
                        func_type = std::get<std::string>(tokenizer.next.value);
                        tokenizer.selectNext();
                        if (tokenizer.next.type == "NEWLINE")
                        {
                            tokenizer.selectNext();
                            std::vector<Node *> func_children;
                            while (tokenizer.next.type != "end")
                            {
                                func_children.push_back(parseStatement());
                                tokenizer.selectNext();
                            }
                            children[1] = new Block(func_children);
                            return new FuncDec(func_type, func_identifier, params, children);
                        }
                    }
                }
            }
        }
    }
    else if (tokenizer.next.type == "return")
    {
        children[0] = parseRelExpr();
        if (tokenizer.next.type == "NEWLINE")
        {
            return new Return(children);
        }
    }
    else if (tokenizer.next.type == "if")
    {
        children[0] = parseRelExpr();
        if (tokenizer.next.type == "NEWLINE")
        {
            std::vector<Node *> ifBlocklockChildren;
            tokenizer.selectNext();
            while (tokenizer.next.type != "else" && tokenizer.next.type != "end")
            {
                ifBlocklockChildren.push_back(parseStatement());
                tokenizer.selectNext();
            }
            children[1] = new Block(ifBlocklockChildren);
            if (tokenizer.next.type == "else")
            {
                tokenizer.selectNext();
                if (tokenizer.next.type == "NEWLINE")
                {
                    tokenizer.selectNext();
                    std::vector<Node *> elseBlocklockChildren;
                    while (tokenizer.next.type != "end")
                    {
                        elseBlocklockChildren.push_back(parseStatement());
                        tokenizer.selectNext();
                    }
                    children[2] = new Block(elseBlocklockChildren);
                }
            }
            tokenizer.selectNext();
            return new If(children);
        }
    }
    else if (tokenizer.next.type == "while")
    {
        children[0] = parseRelExpr();
        if (tokenizer.next.type == "NEWLINE")
        {
            std::vector<Node *> whileBlocklockChildren;
            tokenizer.selectNext();
            while (tokenizer.next.type != "end")
            {
                whileBlocklockChildren.push_back(parseStatement());
                tokenizer.selectNext();
            }
            children[1] = new Block(whileBlocklockChildren);
            tokenizer.selectNext();
            return new While(children);
        }
    }
    else if (tokenizer.next.type == "IDENTIFIER")
    {
        node = new Identifier(tokenizer.next.value);
        std::string identifier = std::get<std::string>(tokenizer.next.value);
        tokenizer.selectNext();
        if (tokenizer.next.type == "ASSIGN")
        {
            children[0] = node;
            children[1] = parseRelExpr();
            return new Assignment(children, identifier);
        }
        else if (tokenizer.next.type == "DECLARATION")
        {
            tokenizer.selectNext();
            if (tokenizer.next.type == "TYPE")
            {
                std::string type = std::get<std::string>(tokenizer.next.value);
                tokenizer.selectNext();
                if (tokenizer.next.type == "ASSIGN")
                {
                    children[0] = node;
                    children[1] = parseRelExpr();
                    return new VarDec(type, identifier, children);
                }
                else if (tokenizer.next.type == "NEWLINE")
                {
                    children[1] = nullptr;
                    return new VarDec(type, identifier, children);
                }
                else
                    throw "Expected ASSIGN or NEWLINE";
            }
        }
        else if (tokenizer.next.type == "LPAREN")
        {
            std::vector<Node *> args;
            while (tokenizer.next.type != "RPAREN")
            {
                args.push_back(parseRelExpr());
                tokenizer.selectNext();
                if (tokenizer.next.type != "COMMA" && tokenizer.next.type != "RPAREN")
                    throw "Expected COMMA or RPAREN";
            }
            return new FuncCall(identifier, args);
        }
        else
            throw "Expected ASSIGN";
    }
    else if (tokenizer.next.type == "NEWLINE")
        return new NoOp();
    else
        throw "Expected RESERVED or IDENTIFIER or NEWLINE";
    return new NoOp();
}

Node *Parser::parseBlock()
{
    std::vector<Node *> children;
    tokenizer.selectNext();
    while (tokenizer.next.type != "EOF")
    {
        children.push_back(parseStatement());
        tokenizer.selectNext();
    }

    return new Block(children);
}

Node *Parser::run(std::string code)
{
    Prepro::filter(code);
    tokenizer.source = code;
    tokenizer.position = 0;
    tokenizer.fetchTokens();
    return parseBlock();
}