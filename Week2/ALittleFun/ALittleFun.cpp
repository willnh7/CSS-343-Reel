#include <vector>
#include <cstdint>
#include <iostream> 
// lint issue solved by including
#include <cstddef>
#include <string>

class BitWriter {
    private:
        // Nibble filter
        const uint8_t  NIBBLE_FILTER = 0x0F;
        //most significant bit
        const int MSB_INDEX = 7;
        const int MAX_BITS_PER_BYTE = 8;
        // Need to store the byes that will be read out
        // vector
        // then we need to track the current byte being written and then keep track of the bits
        // after that 
        std::vector<uint8_t> bytes;
        int currBitCount = 0;
        uint8_t currByte = 0;
        size_t totalBitsWritten = 0;

    public:
        // adds a bit to the BitWriters internal state.
        void write(bool bitValue) {
            // add a one
            if(bitValue) {
                currByte |= 1 << (MSB_INDEX - currBitCount);
            }
            currBitCount++;
            totalBitsWritten++;

            // only pushes back completed bytes, left over are not push back
            // incompleted push backs would cause issues, so only 100%
            // completed bytes are pushed
            if(currBitCount == MAX_BITS_PER_BYTE) {
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
        // Converts our binary to hexidecimal and then adding that to a string that will be returned
        std::string toHexString(std::vector<uint8_t> bytes, const std::string& delim = "") {
            std::string result;
            // This will hold our hexidecimal values once we break the byte into nibbles
            const char HEX_CHARS[]= "0123456789ABCDEF";
            for(size_t i = 0; i < bytes.size(); i++) {
                const uint8_t currByte = bytes[i];
                // first nibble, right shift so the first half of the byte 
                // can be evaluated
                // 1010 1010 (currByte >> 4)
                // 0000 1010
                // 0000 1111 (currByte & 0x0F)
                //-----------
                // 0000 1010
                result += HEX_CHARS[(currByte >> 4) & NIBBLE_FILTER];
                // second nibble, so if the whole byte is 10101010
                // it'll compare the entire byte with the bitwise and 
                // and evaluate the char index so that it can be add to the string
                // as 
                // 1010 1010
                // 0000 1111
                //-----------
                // 0000 1010
                result += HEX_CHARS[currByte & NIBBLE_FILTER];
                // only add delim to those that aren't last
                if(i < bytes.size() - 1 ) {
                    result += delim;
                }
            } 
            return result;
        }

};

int totalPassed = 0;
int totalTests = 0;

void hexEqual(const std::string& testName, const std::string& expected, const std::string& actual) {
    if(expected == actual) {
        std::cout << "[PASSED] " << testName << "\n" 
                         << "Expected: " << expected
                         <<"\nActual: " << actual << "\n"; 
        totalPassed++;
        
    } else {
        std::cout << "[FAILED] " << testName << "\n" 
                         << "Expected: " << expected
                         <<"\nActual: " << actual << "\n";
    }
    totalTests++;
}
void dataEqual(const std::string& testName, int expected, int actual) {
    if(expected == actual) {
        std::cout << "[PASSED] " << testName << "\n" 
                         << "Expected: " << expected
                         <<"\nActual: " << actual << "\n"; 
        totalPassed++;
        
    } else {
        std::cout << "[FAILED] " << testName << "\n" 
                         << "Expected: " << expected
                         <<"\nActual: " << actual << "\n";
    }
    totalTests++;
}

int main() {
    BitWriter myBits;
    // 10101010 10100000
    myBits.write(true);
    myBits.write(false);
    myBits.write(true);
    myBits.write(false);
    myBits.write(true);
    myBits.write(false);
    myBits.write(true);
    myBits.write(false);
    myBits.write(true);
    myBits.write(false);
    myBits.write(true);
    myBits.write(false);
    
    std::vector<uint8_t> myBytes;
    dataEqual("First bits: 12 written", 12, myBits.getData(myBytes));
    hexEqual("A little fun test", "AA-A0", myBits.toHexString(myBytes,"-"));

    BitWriter mySecondBit;
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(false);
    mySecondBit.write(true);
    mySecondBit.getData(myBytes);
    dataEqual("Testing one true: 16 written", 16, mySecondBit.getData(myBytes));
    hexEqual("One bit only", "00-01", mySecondBit.toHexString(myBytes,"-"));


    std::cout << "\nTotal Tests Passed: " << totalPassed << "/" << totalTests << "\n";
}