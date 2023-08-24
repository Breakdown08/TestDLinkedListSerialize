#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

namespace DLinkedList
{
    class ListNode
    {
    public:
        ListNode* Prev;
        ListNode* Next;
        ListNode* Rand;
        std::string Data;

        ListNode(std::string& data);
    };

    class ListRand
    {
    public:
        ListNode* Head;
        ListNode* Tail;
        int Count;

        ListRand();
        ~ListRand() // Free Memory
        {
            ListNode* current = Head;
            while (current)
            {
                ListNode* next = current->Next;
                delete current;
                current = next;
            }
        }

        void Serialize(std::ofstream& s);
        void Deserialize(std::ifstream& s);
    };
}
