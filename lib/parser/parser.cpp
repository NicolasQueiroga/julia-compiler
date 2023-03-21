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
#include "utils.hpp"

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
    //std::cout << "parseFactor: Next: " << tokenizer.next.type << " " << tokenizer.next.value << '\n';
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
    if (tokenizer.next.type == "NUMBER")
        throw "Expected EOF";
    return node;
}

Node *Parser::parseStatement()
{
    std::vector<Node *> children(2);
    children.reserve(2);
    if (tokenizer.next.type == "RESERVED")
    {
        tokenizer.selectNext();
        if (tokenizer.next.type == "LPAREN")
        {
            children[0] = parseExpression();
            if (tokenizer.next.type == "RPAREN")
            {
                Node *node = new Print(children);
                return node;
            }
            else
                throw "Expected RPAREN";
        }
        else
            throw "Expected LPAREN";
    }
    else if (tokenizer.next.type == "IDENTIFIER")
    {
        Node *identifier = new Identifier(tokenizer.next.value);
        tokenizer.selectNext();
        if (tokenizer.next.type == "ASSIGN")
        {
            children[0] = identifier;
            children[1] = parseExpression();
            //std::cout << "parseStatement: Next: " << tokenizer.next.type << " " << tokenizer.next.value << '\n';
            Node *node = new Assignment(children, tokenizer.next.value);
            return node;
        }
        else
            throw "Expected ASSIGN";
    }
    else
        throw "Expected PRINT or IDENTIFIER";
}

Node *Parser::parseBlock()
{
    std::vector<Node *> children;
    tokenizer.selectNext();
    while (tokenizer.next.type != "EOF")
    {
        children.push_back(parseStatement());
        tokenizer.selectNext();
        // //std::cout << "parseBlock: Next: " << tokenizer.next.type << " " << tokenizer.next.value << '\n';
    }

    Node *node = new Block(children);
    return node;
}

Node *Parser::run(std::string code)
{
    Prepro::filter(code);
    tokenizer.source = code;
    tokenizer.position = 0;
    tokenizer.fetchTokens();
    return parseBlock();
}