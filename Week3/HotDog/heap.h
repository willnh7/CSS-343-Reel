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
        /**
         * This downheaps the heap to allow for the smallest to remain in the first element.
         * Follows the min-heap data structure
         */
        void downHeap(int idx) {
            T value = data[idx];
            int size = data.size();

            while((idx * 2) + 1 < size) {
                // the parents first child
                int idxChild = (idx * 2) + 1;
                // Finds the min index
                if(idxChild + 1 < size && compare(data[idxChild + 1], data[idxChild])) {
                    idxChild++;
                }
                // The curr value is already the min so you stop
                if(compare(value, data[idxChild])) {
                    break;
                }
                data[idx] = data[idxChild];
                idx = idxChild;
            }
            data[idx] = value;
        }

    public:
        /**
         * This is the method that is contains abstraction for 
         * inserting into a heap. Taken from the slides
         */
        void add(const T& value) {
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
        /**
         * Size for the heap.
         */
        size_t size() {
            return data.size();
        }
};