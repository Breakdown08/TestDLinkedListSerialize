#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "dlinkedlist.h"

using namespace DLinkedList;

const char* BINARY_FILE = "dump.bin";

void PrintList(const ListRand& list)
{
    ListNode* currentNode = list.Head;
    while (currentNode)
    {
        std::cout << "Data: " << currentNode->Data << std::endl;
        if (currentNode->Prev)
        {
            std::cout << "  Prev: " << currentNode->Prev->Data << std::endl;
        }
        if (currentNode->Next)
        {
            std::cout << "  Next: " << currentNode->Next->Data << std::endl;
        }
        if (currentNode->Rand)
        {
            std::cout << "  Rand: " << currentNode->Rand->Data << std::endl;
        }
        currentNode = currentNode->Next;
    }
}

void FillRandomList(ListRand& list, int listSize)
{
    ListNode* prevNode = nullptr;
    srand(time(nullptr));
    double randProb = 0.5;
    for (int i = 1; i <= listSize; ++i)
    {
        std::string nodeName = "Data " + std::to_string(i);
        list.Count++;
        ListNode* newNode = new ListNode(nodeName);
        newNode->Prev = prevNode;
        if (prevNode)
        {
            prevNode->Next = newNode;
        }
        else
        {
            list.Head = newNode;
        }

        if (randProb > static_cast<double>(rand()) / RAND_MAX)
        {
            int randomIndex = rand() % i;
            ListNode* randomNode = list.Head;
            for (int j = 0; j < randomIndex; ++j)
            {
                randomNode = randomNode->Next;
            }
            newNode->Rand = randomNode;
        }

        prevNode = newNode;
    }
    list.Tail = prevNode;
}

void WriteList(ListRand& list)
{
    std::cout << "Original List:" << std::endl;
    PrintList(list);
    std::ofstream outFile(BINARY_FILE, std::ios::binary);
    if (outFile)
    {
        list.Serialize(outFile);
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << BINARY_FILE << std::endl;
    }
}

void ReadList(ListRand& list)
{
    std::ifstream inFile(BINARY_FILE, std::ios::binary);
    if (inFile)
    {
        list.Deserialize(inFile);
        inFile.close();
    }

    else
    {
        std::cerr << "Unable to open file for reading: " << BINARY_FILE << std::endl;
    }
    std::cout << std::endl << "Deserialized  List:" << std::endl;
    PrintList(list);
}

int main()
{
    ListRand list; FillRandomList(list, 10); WriteList(list);
    ListRand list2; ReadList(list2);
    return 0;
}
