#include <utility>
#include <iostream>
#include <map>
#include <algorithm>

class LRUCache{
private:
    typedef struct {
        int value;
        int count;
    } Cache;

    std::map<int, Cache> m_map;
    int m_capacity;

    std::pair<bool, int> getValue(int key) {
        std::map<int, Cache>::iterator it = m_map.find(key);
        if (it ==  m_map.end()) {
            return std::pair<bool, int>(false, -1);
        }        
        return std::pair<bool, int>(true, m_map[key].value);
    }
    
    struct Compare {
        template <typename T>
        bool operator() (const T& lhs, const T& rhs) {
            return lhs.second.value < rhs.second.value;
        }
    };

    void invalidateLRUItem() {
        std::map<int, Cache>::iterator it = std::min_element(m_map.begin(), m_map.end(), Compare());
        m_map.erase(it);
    }

public:
    LRUCache(int capacity)
    : m_capacity(capacity)	{
    }
    
    int get(int key) {
        std::pair<bool, int> p = getValue(key);
        if (p.first == true) {
            m_map[key].count++;
            return p.second;
        }
    }
    
    void set(int key, int value) {
        std::pair<bool, int> p = getValue(key);
        if (p.first == false) {
            if (m_map.size() >= m_capacity) {
                invalidateLRUItem();   
            }
            Cache c;
            c.value = value;
            c.count = 1;
            m_map[key] = c;
        }
        else {
            std::cerr<< "Not set as element already exists"<<std::endl;
        }
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
