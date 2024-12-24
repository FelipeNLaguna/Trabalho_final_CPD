#ifndef TRIEST_HPP
#define TRIEST_HPP

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory>
#include "Jogador.hpp"

template <typename Value>
class TrieST
{
private:
    static const int R = 256; // radix
    struct Node
    {
        std::shared_ptr<Value> val;
        std::vector<std::shared_ptr<Node>> next = std::vector<std::shared_ptr<Node>>(R);
    };
    std::shared_ptr<Node> root;

    std::shared_ptr<Node> get(std::shared_ptr<Node> x, const std::string &key, int d)
    {
        if (x == nullptr)
            return nullptr;
        if (d == key.length())
            return x;
        char c = key[d];
        return get(x->next[c], key, d + 1);
    }

    std::shared_ptr<Node> put(std::shared_ptr<Node> x, const std::string &key, std::shared_ptr<Jogador> val, int d)
    {
        if (x == nullptr)
            x = std::make_shared<Node>();
        if (d == key.length())
        {
            x->val = val;
            return x;
        }
        char c = key[d];
        x->next[c] = put(x->next[c], key, val, d + 1);
        return x;
    }

    void collect(std::shared_ptr<Node> x, std::string &pre, std::vector<std::string> &q)
    {
        if (x == nullptr)
            return;
        if (x->val != nullptr)
            q.push_back(pre);

        for (char c = 0; c < R; c++)
        {
            if (x->next[c] != nullptr)
            {
                pre.push_back(c);            // Adiciona o caractere ao prefixo
                collect(x->next[c], pre, q); // Recurso para o próximo nó
                pre.pop_back();              // Remove o caractere após a recursão
            }
        }
    }

    void collect(std::shared_ptr<Node> x, const std::string &pre, const std::string &pat, std::vector<std::string> &q)
    {
        int d = pre.length();
        if (x == nullptr)
            return;
        if (d == pat.length() && x->val != nullptr)
            q.push_back(pre);
        if (d == pat.length())
            return;
        char next = pat[d];
        for (char c = 0; c < R; c++)
            if (next == '.' || next == c)
                collect(x->next[c], pre + c, pat, q);
    }

public:
    TrieST() : root(nullptr) {}
    ~TrieST() { root = nullptr; } // Gerenciamento automático por shared_ptr

    std::shared_ptr<Value> get(const std::string &key)
    {
        auto x = get(root, key, 0);
        if (x == nullptr)
            return nullptr;
        return x->val;
    }

    void put(const std::string &key, Jogador val)
    {
        root = put(root, key, std::make_shared<Jogador>(val), 0);
    }

    std::vector<std::string> keys()
    {
        std::vector<std::string> q;
        std::string pre = "";
        collect(root, pre, q);
        return q;
    }

    std::vector<std::string> keysWithPrefix(const std::string &pre)
    {
        std::vector<std::string> q;
        collect(get(root, pre, 0), pre, q);
        return q;
    }

    std::vector<std::string> keysThatMatch(const std::string &pat)
    {
        std::vector<std::string> q;
        collect(root, "", pat, q);
        return q;
    }
};

#endif
