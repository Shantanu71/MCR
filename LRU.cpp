#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

class LRUCache {
    public: 
        class node {
            public:
                int key;
                int val;
                node *next;
                node *prev;

                node(int _key, int _val){
                    key = _key;
                    val = _val;
                }
        };

        node *head = new node(-1,-1);
        node *tail = new node(-1,-1);
        int cap;
        unordered_map<int, node*> m;

        LRUCache(int capacity){
            cap = capacity;
            head->next = tail;
            tail->prev = head;
        }

        void addNode(node *newNode){
            node *temp = head->next;
            newNode->next = temp;
            newNode->prev = head;
            head->next = newNode;
            temp->prev = newNode;
        }

        void deleteNode(node *delNode){
            node *delNext = delNode->next;
            node *delPrev = delNode->prev;
            delNext->prev = delPrev;
            delPrev->next = delNext;
            delete(delNode);
        }

        int getKeyValue(int key){
            if(m.find(key) != m.end()){
                node *resNode = m[key];
                int res = resNode->val;
                deleteNode(resNode);
                addNode(resNode);
                m[key] = head->next;
                return res;
            }
            return -1;
        }

        void setKeyValue(int key, int val){
            if(m.find(key) != m.end()){
                node *existingNode = m[key];
                m.erase(key);
                deleteNode(existingNode);
            }
            if(m.size() == cap){
                m.erase(tail->prev->key);
                deleteNode(tail->prev);
            }
            addNode(new node(key, val));
            m[key] = head->next;
        }

        void getAll(){
            for(auto it: m) cout<<it.first<<" "<<it.second->val<<endl;
        }
};

int main(){
    LRUCache *cache = new LRUCache(3);
    cout<<cache->getKeyValue(1)<<endl;
    cache->setKeyValue(1,5);
    cache->setKeyValue(2,6);
    cache->setKeyValue(3,7);
    cache->setKeyValue(1,4);
    cache->setKeyValue(8,8);
    cache->setKeyValue(12,-6);
    cout<<cache->getKeyValue(12)<<endl;
    cache->getAll();
}