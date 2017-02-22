#include <utility>
#include <iostream>
#include <unordered_map>
#include <algorithm>


struct node
{
    int key;
    int value;
    node* next;
    node*prev;
    node(int _key, int _value, node* _next, node* _prev):
    key(_key), value(_value), next(_next), prev(_prev)
    {}
};

class LRUCache{
private:

    std::unordered_map<int, node*> m_map;
    int m_size;
    int m_len;
    node* m_head;
    node* m_tail;

    void invalidateLRUItem()
    {
        // Remove last element in the list
        if (!m_tail)
            return;
        if (m_tail->prev)
        {
            m_tail->prev->next = NULL; 
        }
        else
        {
            m_head = NULL;	
        }
        node* temp = m_tail;
        m_tail = m_tail->prev;
        
        // Remove from map
        m_map.erase(temp->key);
        
        delete temp;
        m_len--;
    }

public:
    LRUCache(int capacity)
    : m_size(capacity)	{
    }
    
    int get(int key)
    {
        std::unordered_map<int, node*>::const_iterator it = m_map.find(key);
        if (it == m_map.end())
        {
            return -1;
        }
        node* pNode = it->second;
        if (pNode == m_head)
        {
            return pNode->value;
        }
        if (pNode->prev)
        {
            pNode->prev->next = pNode->next;
        }
        if (pNode->next)
        {
            pNode->next->prev = pNode->prev;
        }
        else
        {
            m_tail = pNode->prev;
        }
        
        pNode->next = m_head;
        if (m_head)
        {
            m_head->prev = pNode;
        }
        m_head = pNode;
        return pNode->value;
    }
    
    void set(int key, int value)
    {
        // Entry exists
        std::unordered_map<int, node*>::const_iterator it = m_map.find(key);
        if (it != m_map.end())
        {
            it->second->value = value;
            get(key);
            return;			
        }
        // New entry
        if (m_len == m_size)
        {
            invalidateLRUItem();
        }
        node = new node(key, value, nullptr, nullptr);
        if (m_head)
        {
            m_head->prev = node;
        }
        m_head = node;
        if (!m_tail)
        {
            m_tail = node;
        }
        m_map[key] = value;
        m_len++;
    }
    
    void printContents() {
        for(std::map<int, Cache>::const_iterator it = m_map.begin(); it != m_map.end(); ++it) {
            std::cout << "Map key: "<< it->first << " Map value: " << it->second.value << " Map value_count: "<< it->second.count << std::endl;
        }
    }
};


int main() {
    std::cout << "Initializing cache" << std::endl; 
    LRUCache cache(5);
    cache.set(1, 10);
    cache.set(2, 20);
    cache.set(3, 30);
    cache.set(4, 40);
    cache.set(5, 50);

    std::cout << "accessing cache to get key:5, value: "<<cache.get(5)<< std::endl;
    std::cout << "accessing cache to get key:5, value: "<<cache.get(5)<< std::endl;
    std::cout << "accessing cache to get key:5, value: "<<cache.get(5)<< std::endl;
    std::cout << "accessing cache to get key:5, value: "<<cache.get(5)<< std::endl;
    std::cout << "accessing cache to get key:5, value: "<<cache.get(5)<< std::endl;
    
    std::cout << "accessing cache to get key:4, value: "<<cache.get(4)<< std::endl;
    std::cout << "accessing cache to get key:4, value: "<<cache.get(4)<< std::endl;
    std::cout << "accessing cache to get key:4, value: "<<cache.get(4)<< std::endl;
    std::cout << "accessing cache to get key:4, value: "<<cache.get(4)<< std::endl;
    
    std::cout << "accessing cache to get key:3, value: "<<cache.get(3)<< std::endl;
    std::cout << "accessing cache to get key:3, value: "<<cache.get(3)<< std::endl;
    std::cout << "accessing cache to get key:3, value: "<<cache.get(3)<< std::endl;
    
    std::cout << "accessing cache to get key:2, value: "<<cache.get(2)<< std::endl;
    std::cout << "accessing cache to get key:2, value: "<<cache.get(2)<< std::endl;
    
    cache.set(8, 80);    
    
    cache.printContents();
    
    return 0;
}
