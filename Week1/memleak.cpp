
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


////////////////////////////////////////////////////
// leak1

void leak1() {
    int* pData = new int;
    cout << "Integer address: " << pData << "\n";
    delete pData;
    pData = nullptr;
}

//////////////////////////////////////////
// leak2

class Reader {
public:
    unsigned char* pBuffer;
    unsigned cbBuffer;
    Reader(unsigned bufferSize) {
        this->cbBuffer = bufferSize;
        this->pBuffer = new unsigned char[bufferSize];
    }
    unsigned readFromNetwork() {
        return 255; // pretend we read 255 bytes from network into our buffer
    }
    ~Reader() {
        delete[] pBuffer;
        pBuffer = nullptr;
        cbBuffer = 0;
    }
};
    
unsigned leak2(){
    Reader reader(1024);
    unsigned bytesRead = reader.readFromNetwork();
    return bytesRead;
}
    
//////////////////////////////////////////
// leak3

void leak3() {
    try {
        int* data = new int;
        delete data;
        throw std::runtime_error("oops");
    } catch (const std::exception& e){
        cout << e.what() << endl;
    }
}

//////////////////////////////////////////
// leak4

void leak4() {
    vector<char*> buffers;
    buffers.push_back((char*) new char[255]);
    buffers.push_back((char*) new char[255]);
    buffers.push_back((char*) new char[255]);
    buffers.push_back((char*) new char[255]);
    for(char* pointer : buffers) {
        delete[] pointer;
    }
}

//////////////////////////////////////////
// leak5
// NOTE:  there are two bugs in the BufferManager

typedef unsigned char byte;

class BufferManager {
private:
    const int numBuffers;
    const int bufferSize;
    int idxNext;
    byte** buffers;
public:    
    BufferManager(int numBuffers, int bufferSize):
        numBuffers(numBuffers), bufferSize(bufferSize), idxNext(numBuffers-1) {
        this->buffers = new byte* [this->numBuffers];
        for(int i = 0; i < this->numBuffers; i++) {
            this->buffers[i] = new byte[this->bufferSize];
        }
    }
    ~BufferManager() {
        delete [] buffers;
    }

    byte* getBuffer(){
        byte* ret = nullptr;
        if(idxNext >= 0) {
            ret = this->buffers[idxNext];
            this->buffers[idxNext] = nullptr;
            idxNext--;
        }
        return ret;        
    }

    void releaseBuffer(byte* buffer) {
        this->buffers[idxNext] = buffer;
        idxNext++;
    }
};

void leak5() {
    int numBuffers = 10;
    int bufSize = 100;
    BufferManager bm(numBuffers, bufSize);

    vector<byte*> acquired;
    for(int i = 0; i < 5; i++) {
        acquired.push_back(bm.getBuffer());
    }

    for(byte* buffer : acquired) {
        bm.releaseBuffer(buffer);
    }
}

//////////////////////////////////////////
// leak6

class Node {
public:
    int val;
    Node* pNext;
    Node(int val, Node* pNext):
        val(val), pNext(pNext) {}    
};

void leak6() {
    Node* pNode = new Node(1,nullptr);
    pNode = new Node(2, pNode);
    delete pNode;
}
    
//////////////////////////////////////////
// leak7

Node* addNode(int value, Node* pNode){
    Node* pNewNode = new Node(value, pNode);
    return pNewNode;
}

void leak7(void){
    Node* pHead = nullptr;
    for(int i = 0; i < 5; i++) {
        pHead = addNode(i, pHead);
    }
    while(pHead != nullptr) {
        cout << pHead->val << " ";
        pHead = pHead->pNext;
    }
    cout << "\n";
    delete pHead;
}
    

int main() {

    leak1();
    leak2();
    leak3();
    leak4();
    leak5();
    leak6();
    leak7();
    return 0;
}

