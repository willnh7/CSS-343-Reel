#pragma once


/**
 * This is a zero based heap so that all insertion and deletion
 * will occur using the zero based parents and children.
 */
template<typename T, typename Comparator>
class Heap {
    private:
        std::vector<T> data;
        Comparator compare;
        // Taken from the slides 
        // Straight rip off the slides, 
        // but for insertion it would be best to do this
        void upHeap(int idx) {
            T value = data[idx];
            while(idx > 0 && data[(idx-1)/2] <= value){
                data[idx] = data[(idx-1)/2]; 
                idx = (idx-1)/2; 
            }
            data[idx] = value;
        }

    public:
        void add(const T& item) {
            //TODO:
            data.push_back(value); 
            upHeap(data.size()-1);
        }

    

    
    
};