#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <functional>
#include <string>


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
        std::function<const char*(T)> toString;

        Heap<T>(std::function<bool(T, T)> comapre, std::function<const char*(T)> toString){
            this->comapre = comapre;
            this->toString = toString;
        }

        void reHeapify(int idx){
            int parent;
            T d = data[idx];
            while(idx != 0){
                parent = getParent(idx);
                // If it's the right place, insert and exit
                if(!comapre(d, data[parent])){
                    break;
                }
                // Otherwise copy value down and go up
                data[idx] = data[parent];
                idx = parent;
            }
            // Place wherever counter wound up
            data[idx] = d;
            printTree(0);
            printf("\n");
        }

        void push(T d){
            printf("Pushing %s\n", toString(d));
            int idx = data.size();
            data.push_back(d);
            reHeapify(idx);
        }

        bool pop(T *out, int idx){
            printf("Popping %d\n", idx);
            if(data.size() == 0){
                printTree(0);
                printf("\n");
                return false;
            }
            int lastIdx = data.size()-1;
            T toAdd = data[lastIdx];
            *out = data[idx];
            int parent = getParent(idx);
            // If it's smaller than parent, bubble up
            if(idx != 0 && comapre(toAdd, data[parent])){
                while(idx != 0){
                    parent = getParent(idx);
                    // If it's the right place, insert and exit
                    if(!comapre(toAdd, data[parent])){
                        break;
                    }
                    // Otherwise copy value down and go up
                    data[idx] = data[parent];
                    idx = parent;
                }
            } else { // Otherwise bubble down
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
            }
            data.pop_back();

            data[idx] = toAdd;
            reHeapify(idx);

            printTree(0);
            printf("\n");
            return true;
        }

        T *peek(int i){
            if(i >= data.size()) return NULL;
            return &data[i];
        }

        int indexOf(std::function<bool(T)> isEqual){
            for(int i=0; i<data.size(); i++){
                if(isEqual(data[i])){
                    return i;
                }
            }
            return -1;
        }

        void printTree (int idx)
        // Print whole tree. We cannot make it look pretty graphically, so we add some
        // characters to make it a little easier to understand.  We also don't really
        // know what the value field is - it is declared to be a void pointer - so we
        // treat it as though it points to an integer.
        {
            // start of this tree
            printf("{");
            // values in the root node (assuming value is pointing to an integer)
            printf("(%s@%d),", toString(data[idx]), idx);
            
            // Now show left subtree or {} if there is no left subtree
            if (getLeft(idx) < data.size())	printTree(getLeft(idx));
            else							printf("{}");
            // Marker between left and right subtrees		
            printf(",");
            // Now show right subtree or {} if there is no right subtree
            if (getRight(idx) < data.size())	printTree(getRight(idx));
            else							printf("{}");
            // Close display of this tree with closing curly bracket	
            printf("}");
        }//printTree()
};


#endif // !HEAP_H
