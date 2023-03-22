#include "parser.hpp"
#include "prepro/prepro.hpp"
#include "binop/binop.hpp"
#include "intval/intval.hpp"
#include "noop/noop.hpp"
#include "unop/unop.hpp"
#include "block/block.hpp"
#include "print/print.hpp"
#include "assignment/assignment.hpp"
#include "identifier/identifier.hpp"

#include <memory>
#include <vector>

Tokenizer Parser::tokenizer = Tokenizer();

Node *Parser::parseFactor()
{
    std::vector<Node *> children(1);
    children.reserve(1);
    Node *node = nullptr;

    tokenizer.selectNext();
    if (tokenizer.next.type == "NUMBER")
    {
        node = new IntVal(children, tokenizer.next.value);
        tokenizer.selectNext();
        return node;
    }
    else if (tokenizer.next.type == "IDENTIFIER")
    {
        node = new Identifier(tokenizer.next.value);
        tokenizer.selectNext();
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
    else if (tokenizer.next.type == "LPAREN")
    {
        node = parseExpression();
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
    std::vector<Node *> children(2);
    children.reserve(2);

    while (tokenizer.next.type == "MULT" || tokenizer.next.type == "DIV")
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
    }
    if (tokenizer.next.type == "NUMBER")
        throw "Expected EOF";

    return node;
}

Node *Parser::parseExpression()
{
    Node *node = Parser::parseTerm();
    std::vector<Node *> children(2);
    children.reserve(2);

    while (tokenizer.next.type == "PLUS" || tokenizer.next.type == "MINUS")
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
    }
    if (tokenizer.next.type == "NUMBER" || tokenizer.next.type == "UNKNOWN")
        throw "Expected EOF";
    return node;
}

Node *Parser::parseStatement()
{
    std::vector<Node *> children(2);
    children.reserve(2);
    Node *node = nullptr;
    if (tokenizer.next.type == "RESERVED")
    {
        tokenizer.selectNext();
        if (tokenizer.next.type == "LPAREN")
        {
            children[0] = parseExpression();
            if (tokenizer.next.type == "RPAREN")
            {
                tokenizer.selectNext();
                return new Print(children);
            }
            else
                throw "Expected RPAREN";
        }
        else
            throw "Expected LPAREN";
    }
    else if (tokenizer.next.type == "IDENTIFIER")
    {
        node = new Identifier(tokenizer.next.value);
        std::string identifier = std::get<std::string>(tokenizer.next.value);
        tokenizer.selectNext();
        if (tokenizer.next.type == "ASSIGN")
        {
            children[0] = node;
            children[1] = parseExpression();
            return new Assignment(children, identifier);
        }
        else
            throw "Expected ASSIGN";
    }
    else
        throw "Expected RESERVED or IDENTIFIER";
    return new NoOp();
}

Node *Parser::parseBlock()
{
    std::vector<Node *> children;
    tokenizer.selectNext();
    while (1)
    {
        if (tokenizer.next.type != "NEWLINE" && tokenizer.next.type != "EOF")
            children.push_back(parseStatement());
        if (tokenizer.next.type == "EOF")
            break;
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