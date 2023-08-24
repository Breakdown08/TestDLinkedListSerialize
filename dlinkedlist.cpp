#include "dlinkedlist.h"


namespace DLinkedList
{
    ListNode::ListNode(std::string& data): Prev(nullptr), Next(nullptr), Rand(nullptr), Data(data){}
    ListRand::ListRand(): Head(nullptr), Tail(nullptr), Count(0) {}

    void ListRand::Serialize(std::ofstream& s)
    {
        s.write(reinterpret_cast<const char*>(&Count), sizeof(int));
        std::unordered_map<ListNode*, int[4]> nodeLinksMap;
        ListNode* current = Head;
        int index = 0;

        while (current) // First Entry Initializing
        {
            uint32_t dataSize = current->Data.length();
            s.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32_t));
            s.write(current->Data.c_str(), dataSize);

            nodeLinksMap[current][0] = index; // Self Index
            nodeLinksMap[current][1] = -1; // Prev
            nodeLinksMap[current][2] = -1; // Next
            nodeLinksMap[current][3] = -1; // Rand
            current = current->Next;
            index++;
        }

        current = Head;
        index = 0;
        while (current) // Second Entry Initializing
        {
            if (current->Prev)
            {
                nodeLinksMap[current][1] = nodeLinksMap[current->Prev][0];
            }
            if (current->Next)
            {
                nodeLinksMap[current][2] = nodeLinksMap[current->Next][0];
            }
            if (current->Rand)
            {
                nodeLinksMap[current][3] = nodeLinksMap[current->Rand][0];
            }
            s.write(reinterpret_cast<char*>(nodeLinksMap[current]), sizeof(nodeLinksMap[current]));
            current = current->Next;
            index++;
        }
        int zeroIndex = 0;
        s.write(reinterpret_cast<const char*>(&zeroIndex), sizeof(int)); // Head
        s.write(reinterpret_cast<const char*>(&Count - 1), sizeof(int)); // Tail

    }

    void ListRand::Deserialize(std::ifstream& s)
    {
        std::string _data;
        uint32_t  dataSize;
        std::vector<ListNode*> nodeIndexes;
        int linksArray[4];
        int headIndex;
        int tailIndex;
        s.read(reinterpret_cast<char*>(&Count), sizeof(int));

        for (size_t i = 0; i < Count; i++)
        {
            s.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32_t));
            _data.resize(dataSize);
            s.read(&_data[0], dataSize);
            ListNode* newNode = new ListNode(_data);
            nodeIndexes.push_back(newNode);
        }

        for (size_t i = 0; i < Count; i++)
        {
            s.read(reinterpret_cast<char*>(linksArray), sizeof(linksArray));
            if (linksArray[1] != -1) // Prev Link
            {
                nodeIndexes[linksArray[0]]->Prev = nodeIndexes[linksArray[1]];
            }
            if (linksArray[2] != -1) // Next Link
            {
                nodeIndexes[linksArray[0]]->Next = nodeIndexes[linksArray[2]];
            }
            if (linksArray[3] != -1) // Rand Link
            {
                nodeIndexes[linksArray[0]]->Rand = nodeIndexes[linksArray[3]];
            }
        }
        s.read(reinterpret_cast<char*>(&headIndex), sizeof(int));
        s.read(reinterpret_cast<char*>(&tailIndex), sizeof(int));

        Head = nodeIndexes[headIndex];
        Tail = nodeIndexes[tailIndex];
    }
}
