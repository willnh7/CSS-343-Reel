#include <vector>
#include <cstdint> 

class BitWriter {
    // Need to store the byes that will be read out
    // vector
    std::vector<uint8_t> bytes;
    int currBitCount = 0;
    uint8_t currByte = 0;
    size_t  totalBitsWritten = 0;

    // then we need to track the current byte being written and then keep track of the bits
    // after that 

    // adds a bit to the BitWriters internal state.
    void write(bool bitValue) {
        // add a one
        if(bitValue) {
            currByte |= 1 << (7 - currBitCount);
        }

        currBitCount++;
        totalBitsWritten++;

        // only pushes back completed bytes, left over are not push back
        // incompleted push backs would cause issues, so only 100%
        // completed bytes are pushed
        if(currBitCount == 8) {
            // push_back()? 
            bytes.push_back(currByte);
            currByte = 0;
            currBitCount = 0;
        }
    }

    // returns the number of bits written
    // all of the bits that have been written are returned in out

    size_t getData(std::vector<uint8_t>& out) {
        out = bytes;
        // if there are incompleted bytes, we push the byte to the out, vector.
        // done as a "flush" essentially. NOTE: I had to google what a flush was in c++
        // since it's a concept I had no clue about
        if(currBitCount > 0) {
            out.push_back(currByte);
        }
        return totalBitsWritten;
    }
  
};