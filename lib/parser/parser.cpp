#include "parser.hpp"
#include "prepro/prepro.hpp"
#include "binop/binop.hpp"
#include "intval/intval.hpp"
#include "noop/noop.hpp"
#include "unop/unop.hpp"
#include <memory>
#include <vector>
#include <iostream>

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
    else if (tokenizer.next.type == "MINUS")
    {
        children[0] = parseFactor();
        node = new UnOp(children, "-");
        return node;
    }
    else if (tokenizer.next.type == "PLUS")
    {
        children[0] = parseFactor();
        node = new UnOp(children, "+");
        return node;
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
    // if NUMBER throw "Expected EOF"
    if (tokenizer.next.type == "NUMBER")
        throw "Expected EOF";
    return node;
}

int Parser::run(std::string code)
{
    Prepro::filter(code);
    tokenizer.source = code;
    tokenizer.position = 0;
    tokenizer.fetchTokens();

    Node *tree = parseExpression();
    if (tokenizer.next.type != "EOF")
        throw "Expected EOF";


    int result = tree->Evaluate();
    delete tree;
    return result;
}