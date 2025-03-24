#ifndef HUFFMANREAD_H_INCLUDED
#define HUFFMANREAD_H_INCLUDED
#include <iostream>
using namespace std;

//THIS IS THE SORTED LINKED LIST CODE COPIED FROM CSE225 LAB COURSE CODE SEGMENT
template <class ItemType>
class SortedType
{
    struct NodeType
    {
        ItemType info;
        NodeType* next;
    };
public:
    SortedType();
    ~SortedType();
    bool IsFull();
    int LengthIs();
    void MakeEmpty();
    void RetrieveItem(ItemType&, bool&);
    void InsertItem(ItemType);
    void DeleteItem(ItemType);
    void ResetList();
    void GetNextItem(ItemType&);
    ItemType* GetPointerToFirstItem();

private:
    NodeType* listData;
    int length;
    NodeType* currentPos;
};

template <class ItemType>
SortedType<ItemType>::SortedType()
{
    length = 0;
    listData = NULL;
    currentPos = NULL;
}

template <class ItemType>
int SortedType<ItemType>::LengthIs()
{
    return length;
}

template<class ItemType>
bool SortedType<ItemType>::IsFull()
{
    NodeType* location;
    try
    {
        location = new NodeType;
        delete location;
        return false;
    }
    catch(bad_alloc& exception)
    {
        return true;
    }
}

template <class ItemType>
void SortedType<ItemType>::InsertItem(ItemType item)
{
    NodeType* newNode;
    NodeType* predLoc;
    NodeType* location;
    bool moreToSearch;
    location = listData;
    predLoc = NULL;
    moreToSearch = (location != NULL);
    while (moreToSearch)
    {
        if (location->info < item)
        {
            predLoc = location;
            location = location->next;
            moreToSearch = (location != NULL);
        }
        else moreToSearch = false;
    }
    newNode = new NodeType;
    newNode->info = item;
    if (predLoc == NULL)
    {
        newNode->next = listData;
        listData = newNode;
    }
    else
    {
        newNode->next = location;
        predLoc->next = newNode;
    }
    length++;
}

template <class ItemType>
void SortedType<ItemType>::DeleteItem(ItemType item)
{
    NodeType* location = listData;
    NodeType* tempLocation;
    if (item == listData->info)
    {
        tempLocation = location;
        listData = listData->next;
    }
    else
    {
        while (!(item==(location->next)->info))
            location = location->next;
        tempLocation = location->next;
        location->next = (location->next)->next;
    }
    delete tempLocation;
    length--;
}

template <class ItemType>
void SortedType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
    NodeType* location = listData;
    bool moreToSearch = (location != NULL);
    found = false;
    while (moreToSearch && !found)
    {
        if (item == location->info)
            found = true;
        else if (item > location->info)
        {
            location = location->next;
            moreToSearch = (location != NULL);
        }
        else
            moreToSearch = false;
    }
}

template <class ItemType>
void SortedType<ItemType>::MakeEmpty()
{
    NodeType* tempPtr;
    while (listData != NULL)
    {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
    length = 0;
}

template <class ItemType>
SortedType<ItemType>::~SortedType()
{
    MakeEmpty();
}

template <class ItemType>
void SortedType<ItemType>::ResetList()
{
    currentPos = NULL;
}

template <class ItemType>
void SortedType<ItemType>::GetNextItem(ItemType& item)
{
    if (currentPos == NULL)
        currentPos = listData;
    else
        currentPos = currentPos->next;
    item = currentPos->info;
}
template <class ItemType> // This method had to be added to share the address of the root node
ItemType* SortedType<ItemType>::GetPointerToFirstItem() {
    return &(listData->info);
}


// THE ENCODING AND DECODING PART STARTS HERE
struct Node {
    char letter = ' ';
    int num = 0;
    Node* left = nullptr;
    Node* right = nullptr;

   
    bool operator<(const Node& other) {
        return num < other.num;
    }
    bool operator>(const Node& other) {
        return num > other.num;
    }
    bool operator==(const Node& other){
        return num == other.num;
    }
    bool operator!=(const Node& other){
        return num != other.num;
    }
};


struct Final {
    char letter;
    string code;
};

void decoding(Node* root);
void GenerateCodes(Node* root, string code, Final farr[], int& count);
static Node* ROOTNODE = nullptr;

void encoding() {
    
    
    const int SIZE = 10; 
    SortedType<Node> sortedLL; 

    ifstream inputFile("input.txt"); 
    string line;

    if (inputFile.is_open()) {
        getline(inputFile, line); 
        inputFile.close();
    } else {
        cout << "Error opening file!" << endl;
        return;
    }

    
    char letters[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'J', 'R', 'S', 'W'};
    Node items[SIZE];
    int fcount = 0; 

    
    for (int i = 0; i < SIZE; i++) {
        for (char c : line) {
            if (letters[i] == c) {
                fcount++;
            }
        }
        items[i].letter = letters[i];
        items[i].num = fcount;
        fcount = 0;
    }

    
    for (int i = 0; i < SIZE; i++) {
        sortedLL.InsertItem(items[i]);
    }

    Node temp;
    Node* x;
    Node* y;
    Node* nNode;

  
    while (sortedLL.LengthIs() != 1) {
        nNode = new Node; 
        x = new Node;     
        y = new Node;     
        sortedLL.GetNextItem(*x);
        sortedLL.GetNextItem(*y);
        nNode->left = x;
        nNode->right = y; 
        nNode->num = x->num + y->num; 
        sortedLL.ResetList(); 
        sortedLL.DeleteItem(*x);
        sortedLL.DeleteItem(*y);
        sortedLL.InsertItem(*nNode); 
        sortedLL.ResetList();
    }

    sortedLL.GetNextItem(temp); 
    sortedLL.ResetList();
    
    ROOTNODE = sortedLL.GetPointerToFirstItem(); 
   

    int counter = 0; 
    Final farr[SIZE]; 

    GenerateCodes(&temp, "", farr, counter); 
    string compressed;

    
    for (char c : line) {
        for (int j = 0; j < counter; j++) {
            if (c == farr[j].letter) {
                compressed += farr[j].code;
                break;
            }
        }
    }

    
    ofstream file("output.txt");
    if (file.is_open()) {
        file << compressed;
        file.close();
        cout << "String written to file successfully!" << endl;
    } else {
        cout << "Failed to open file for writing." << endl;
    }
    
   decoding(ROOTNODE); 
   
}


//This is the decoding function:
void decoding(Node* root) {
    
    
    ifstream inFile("output.txt");
    string codedString;

    if (inFile.is_open()) {
        getline(inFile, codedString); 
        inFile.close();
    } else {
        cout << "Failed to open file" << endl;
        return;
    }

    string originalText = "";
    Node* current = root;

    
    for (char bit : codedString) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            originalText += current->letter;
            current = root; 
        }
    }


    ofstream outFile("decoded.txt");
    if (outFile.is_open()) {
        outFile << originalText;
        outFile.close();
        cout << "Decoding done!" << endl;
    } else {
        cout << "Failed to open decoded.txt for writing." << endl;
    }
}





//This code here helps generate the code from my root node to the leaf nodes.
void GenerateCodes(Node* root, string code, Final farr[], int& count) {
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr) {
        farr[count].letter = root->letter;
        farr[count].code = code;
        count++;
        return;
    }

    GenerateCodes(root->left, code + "0", farr, count);
    GenerateCodes(root->right, code + "1", farr, count);
}


#endif // HUFFMANREAD_H_INCLUDED