#pragma once
using namespace std;

// Класс узла списка с пропуском
template<class Value>
class SkipNode {
public:
    Value value;
    std::vector<SkipNode<Value>*> next;

    SkipNode(int value, int maxLevel) {
        this->value = value;
        next = std::vector<SkipNode<Value>*>(maxLevel + 1, nullptr);
    }
};

// Класс списка с пропуском
template <class Value>
class SkipList {
private:
    int maxLevel;
    SkipNode<Value>* header;
    int size;
    double ver = 1 / 2.0;
public:
    SkipList(int maxLevel) {
        this->maxLevel = maxLevel;
        header = new SkipNode<Value>(-1, maxLevel);
        size = 0;
    }

    ~SkipList() {
        SkipNode<Value>* tmp;
        for (int i = 0; i < size; i++) {
            tmp = header;
            header = header->next[0];

            if (tmp)
                delete tmp;
        }
    }

    // Вставка элемента в список
    void insert(Value value) {
        SkipNode<Value>* newNode = new SkipNode<Value>(value, maxLevel);
        SkipNode<Value>* current = header;

        // Найти правильное положение для вставки
        std::vector<SkipNode<Value>*> update(maxLevel + 1, nullptr);
        for (int i = maxLevel; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->value < value) {
                current = current->next[i];
            }
            update[i] = current;
        }

        // Вставить новый узел
        bool flag = true;
        int i = 0;
        do {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;

            i++;
            int p = rand() % 100;
            if (!(p < (ver * 100)))
                flag = false;  
        } while (flag && i <= maxLevel);
        

        size++;
    }

    // Поиск элемента в списке
    bool search(Value value) {
        SkipNode<Value>* current = header;

        // Найти элемент или его следующее положение
        for (int i = maxLevel; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->value < value) {
                current = current->next[i];
            }
        }

        current = current->next[0];
        return current != nullptr && current->value == value;
    }

    void remove(Value value) {
        if (!search(value))
            return;

        std::vector<SkipNode<Value>*> update(maxLevel + 1, nullptr);
        SkipNode<Value>* current = header;

        for (int i = maxLevel; i >= 0; i--) {
            while (current->next[i] && current->next[i]->value < value) { current = current->next[i]; }
            update[i] = current;
        }

        current = current->next[0];

        if (current && current->value == value) {

            for (int i = 0; i <= maxLevel; i++) {
                if (update[i] && update[i]->next[i] == current) {
                    update[i]->next[i] = current->next[i];
                }
            }
            if (header == current) {
                header = current->next[0];
            }
        }
        size--;

        if (current)
            delete current;
    }

    int getSize() {
        return size;
    }

    friend ostream& operator<<(ostream& os, SkipList<Value>& list) {
        SkipNode<Value>* current = list.header->next[0];
        for (int i = 0; i < list.size; i++) {
            os << current->value << " ";
            current = current->next[0];
        }
        return os;
    }
};
