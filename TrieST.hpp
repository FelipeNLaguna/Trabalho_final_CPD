#ifndef TRIEST_HPP
#define TRIEST_HPP

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory>
#include "Jogador.hpp"

template <typename Value>
class TrieST {
private:
    static const int R = 256; // radix
    struct Node {
        std::shared_ptr<Value> val;
        std::vector<std::shared_ptr<Node>> next = std::vector<std::shared_ptr<Node>>(R);
    };
    std::shared_ptr<Node> root;

    std::shared_ptr<Node> get(std::shared_ptr<Node> x, const std::string& key, int d) const {
        if (x == nullptr)
            return nullptr;
        if (d == key.length())
            return x;
        char c = key[d];
        return get(x->next[c], key, d + 1);
    }

    std::shared_ptr<Node> put(std::shared_ptr<Node> x, const std::string& key, std::shared_ptr<Value> val, int d) {
        if (x == nullptr)
            x = std::make_shared<Node>();
        if (d == key.length()) {
            x->val = val;
            return x;
        }
        char c = key[d];
        x->next[c] = put(x->next[c], key, val, d + 1);
        return x;
    }

    void collect(std::shared_ptr<Node> x, const std::string& pre, std::vector<std::string>& q) const {
        if (x == nullptr) return;
        if (x->val != nullptr) q.push_back(pre);
        for (int c = 0; c < R; c++) {
            if (x->next[c]) {
                collect(x->next[c], pre + static_cast<char>(c), q);
            }
        }
    }

public:
    TrieST() : root(nullptr) {}
    ~TrieST() { root = nullptr; } // Gerenciamento automático por shared_ptr

    std::shared_ptr<Value> get(const std::string& key) const {
        auto x = get(root, key, 0);
        if (x == nullptr)
            return nullptr;
        return x->val;
    }

    void put(const std::string& key, Value val) {
        root = put(root, key, std::make_shared<Value>(val), 0);
    }

    std::vector<std::string> keys() const {
        std::vector<std::string> q;
        collect(root, "", q);
        return q;
    }

    std::vector<std::string> keysWithPrefix(const std::string& pre) const {
        std::vector<std::string> q;
        collect(get(root, pre, 0), pre, q);
        return q;
    }
};

// Nova classe TrieSTInt onde o valor é um vetor de inteiros
class TrieST_tags {
private:
    static const int R = 256; // Tamanho do alfabeto (ASCII)
    struct Node {
        std::vector<int> val; // Vetor de inteiros associados à chave completa
        std::vector<std::shared_ptr<Node>> next = std::vector<std::shared_ptr<Node>>(R);
    };
    std::shared_ptr<Node> root = nullptr; // Raiz da trie

    std::shared_ptr<Node> put(std::shared_ptr<Node> x, const std::string& key, int val, int d) {
        if (x == nullptr) x = std::make_shared<Node>();
        if (d == key.length()) {
            x->val.push_back(val); // Adiciona o valor ao vetor
            return x;
        }
        char c = key[d];
        x->next[c] = put(x->next[c], key, val, d + 1);
        return x;
    }

    std::shared_ptr<Node> get(std::shared_ptr<Node> x, const std::string& key, int d) const {
        if (x == nullptr) return nullptr;
        if (d == key.length()) return x;
        char c = key[d];
        return get(x->next[c], key, d + 1);
    }

public:
    void put(const std::string& key, int val) {
        root = put(root, key, val, 0);
    }

    std::vector<int> get(const std::string& key) const {
        auto x = get(root, key, 0);
        if (x == nullptr) return std::vector<int>(); // Retorna vetor vazio se não encontrado
        return x->val;
    }

    std::vector<std::string> keys() const {
        std::vector<std::string> results;
        collect(root, "", results);
        return results;
    }

    std::vector<std::string> keysWithPrefix(const std::string& prefix) const {
        std::vector<std::string> results;
        auto x = get(root, prefix, 0);
        collect(x, prefix, results);
        return results;
    }

private:
    void collect(std::shared_ptr<Node> x, const std::string& prefix, std::vector<std::string>& results) const {
        if (x == nullptr) return;
        if (!x->val.empty()) results.push_back(prefix);
        for (char c = 0; c < R; c++) {
            collect(x->next[c], prefix + c, results);
        }
    }
};

#endif // TRIEST_HPP