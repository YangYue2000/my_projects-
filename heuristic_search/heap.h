#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class MinHeap {
private:
  struct Node{
    Node(const T& v, const int p, const int n);
    T val;
    int priority;
    int nth;
  };
  int add_times = 0;
  int d;
  vector<int> map;//stores the locations of corresponding items;
  vector<Node*> a;//stores the items
public:
  MinHeap (int D);

 ~MinHeap ();
 
 void swap(Node* x, Node* y);

 int add (T item, int priority);
  
 int bubbleUp(int pos);

 const T & peek () const;

 void remove ();

 void trickleDown(int pos);

 void update (int nth, int priority);

 bool isEmpty ();
};


template <typename T> 
MinHeap<T>::Node::Node(const T& v, const int p, const int n)
: val(v), priority(p), nth(n)
{
}

template <typename T>
MinHeap<T>::MinHeap(int D)
: d(D)
{

}

template<typename T>
MinHeap<T>::~MinHeap()
{
  for(unsigned i=0; i<a.size(); i++){
    delete a[i];
  }
}

template<typename T>
void MinHeap<T>::swap(Node* x, Node*y)
{
  int buffer = map[x->nth];
  map[x->nth] = map[y->nth];
  map[y->nth] = buffer;
  T temp_val = x->val;
  int temp_n = x->nth;
  int temp_p = x->priority;
  x->val = y->val;
  x->nth = y->nth;
  x->priority = y->priority;
  y->val = temp_val;
  y->nth = temp_n;
  y->priority = temp_p;
}

template<typename T>
const T& MinHeap<T>::peek() const
{
  return a[0]->val;
}

template<typename T>
int MinHeap<T>::add(T item, int priority)
{
  Node* new_node = new Node(item, priority, add_times);
  a.push_back(new_node);
  map.push_back((signed)a.size()-1);
  //before bubble up sorts the correct order of the new node,
  //the new node is at the end of the minheap
  int final_position = bubbleUp((signed)a.size()-1);
  map[map.size()-1] = final_position;
  //map[add_times] should be able to access the final position
  add_times++;
  //update add_times;
  return add_times-1;
  //return the number of add calls prior to this one, so minus one.
}

template<typename T>
int MinHeap<T>::bubbleUp(int pos)
{
  if(pos > 0){
    Node* children = a[pos];
    Node* parent = a[(pos-1)/d];
    if(children->priority < parent->priority){
      swap(children,parent);
      return bubbleUp((pos-1)/d);
    }
    else if(children->priority == parent->priority){
      if(children->val < parent->val){
        swap(children, parent);
        return bubbleUp((pos-1)/d);
      }
      else{
        return pos;
      }
    }
    else{
      return pos;
    }
  }
  else if(pos == 0){
    return pos;
  }
  return 666;
  //this is the case when pos is negative, which will not happen
}

template<typename T>
void MinHeap<T>::remove()
{
  if(!isEmpty()){
    Node* first = a[0];
    Node* last = a[a.size()-1];
    swap(first,last);
    for(unsigned i=0; i<map.size(); i++){
      if((unsigned)map[i] == map.size()-1){
        map[i] = -100;
      ///make the last element, which will be deleted, negative
      //so that the update function will know which nth node 
      //does not exist(been deleted) since all the other existing 
      //nodes have non-negative position index.
      }
    }
    a.pop_back();
    delete last;
    trickleDown(0);
  }
}

template<typename T>
void MinHeap<T>::trickleDown(int pos)
{
  unsigned child = d*pos+1;
  if(child < a.size()){
    int min_priority = a[child]->priority;
    int target = child;
    while(child+1 <= (unsigned)(d*pos+d)){
      if(child == a.size()-1){
        break;
        //no need to keep comparing the next child when 
        //the current child is already the last node
      }
      if(a[child+1]->priority < min_priority){
        min_priority = a[child+1]->priority;
        target = child+1;
      }
      child++;
    }
    if(a[pos]->priority > min_priority){
      swap(a[pos], a[target]);
    }
  }
}

template<typename T>
void MinHeap<T>::update(int nth, int priority)
{
  if(map[nth] >= 0){
    //if the nth node has been removed, then map[nth] has 
    //been set to negative
    int location = map[nth];
    if(a[location]->priority > priority){
      a[location]->priority = priority;
      bubbleUp(location);
    }
    else{
      a[location]->priority = priority;
      trickleDown(location);
    }
  }
}

template<typename T>
bool MinHeap<T>::isEmpty()
{
  return a.empty();
}
