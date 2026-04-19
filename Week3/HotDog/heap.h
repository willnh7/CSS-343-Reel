#pragma once


/**
 * This is a zero based heap so that all insertion and deletion
 * will occur using the zero based parents and children.
 * T for the data type and Comparator for the functors.
 */
template<typename T, typename Comparator>
class Heap {
    private:
        std::vector<T> data;
        Comparator compare;
        // Taken from the slides 
        // but changed for a min-heap insertion 
        void upHeap(int idx) {
            T value = data[idx];
            while(idx > 0 ){
                int parentIdx = (idx - 1) / 2;
                // value is cheaper(better) than the parent.
                if(compare(value, data[parentIdx])) {
                    data[idx] = data[parentIdx]; 
                    idx = (idx-1)/2;
                } else {
                    // found the right spot for the insertion
                    break;
                }
            }
            data[idx] = value;
        }

        void downHeap(int idx) {

        }

    public:
        /**
         * This is the method that is contains abstraction for 
         * inserting into a heap. Taken from the slides
         */
        void add(const T& item) {
            data.push_back(value); 
            upHeap(data.size()-1);
        }
        /**
         * Taken from the slides, this is for deletion off the heap;
         */
        T remove() {
            T ret = data[0];
            data[0] = data[data.size() - 1];
            data.pop_back();
            downHeap(0);
            return ret;
        }
};