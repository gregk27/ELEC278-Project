#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <functional>


template <class T>
class Heap{
    private:
        int getLeft(int idx){
            return 2*idx+1;
        }

        int getRight(int idx){
            return 2*idx+2;
        }

        int getParent(int idx){
            return (idx-1)/2;
        }

    public:
        std::vector<T> data;
        std::function<bool(T, T)> comapre;

        Heap(int size, std::function<bool(T, T)> comapre){
            this->comapre = comapre;
        }

        void push(T d){
            int idx = data.size();
            data.resize(idx+1);
            int parent;
            while(idx != 0){
                parent = getParent(idx);
                // If it's the right place, insert and exit
                if(!comapre(d, data[parent])){
                    data[idx] = d;
                    return;
                }
                // Otherwise copy value down and go up
                data[idx] = data[parent];
                idx = parent;
            }
            // If we get this far, then only place left is root of heap
            data[idx] = d;
        }

        bool pop(T *out){
            if(data.size() == 0){
                return false;
            }
            int lastIdx = data.size()-1;
            int toAdd = data[lastIdx];
            *out = data[0];
            int idx = 0;
            while(idx < lastIdx){
                int right = getRight(idx);
                int left = getLeft(idx);
                // If the right is in bounds, the left will also be
                if(right < lastIdx){
                    // Take the oposite of compare
                    if(!comapre(data[left],data[right])){
                        data[idx] = data[right];
                        idx = right;
                    } else {
                        data[idx] = data[left];
                        idx = left;
                    }
                } else if(right == lastIdx) { // If there is only left child
                    if(comapre(data[left],toAdd)){
                        data[idx] = data[left];
                        idx = left;
                    } else {
                        break;
                    }
                } else if(left >= lastIdx){ // If there are no children, break
                    break;
                }
            }

            data[idx] = toAdd;
            data.pop_back();
            return true;
        }
};


#endif // !HEAP_H
