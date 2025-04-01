#include <iostream>

using namespace std;


class Node{
public:
    int val;
    Node * next = NULL;

    Node(int _val){
        val = _val;
    }
};

Node * getPartitionedList2(Node* head, int x){
    Node * smaller = NULL, *larger=NULL;
    Node * largerStart, *smallerStart;

    Node* curr = head;

    while(curr!=NULL){
        if(curr ->val < x){
            if(smaller == NULL){
                smaller = curr;
                smallerStart = smaller;
            } else {
                smaller ->next = curr;
                smaller = smaller->next;
            }
            curr = curr->next;
            smaller->next = NULL;
        } else {
            if(larger == NULL){
                larger = curr;
                largerStart = larger;
            } else {
                larger ->next = curr;
                larger = larger->next;
            }
            curr = curr->next;
            larger->next = NULL;
        }
    }

    smaller->next = largerStart;
    return smallerStart;

}

Node * getPartitionedList(Node* root, int x){
    Node * smaller = NULL, *larger=NULL;
    Node * largerStart, *smallerStart;

    Node* curr = root;

    while(curr!=NULL){
        if(curr ->val < x){
            if(smaller == NULL){
                smaller = new Node(curr->val);
                smallerStart = smaller;
            } else {
                smaller ->next = new Node(curr->val);
                smaller = smaller->next;
            }
        } else {
            if(larger == NULL){
                larger = new Node(curr->val);
                largerStart = larger;
            } else {
                larger ->next = new Node(curr->val);
                larger = larger->next;
            }
        }
        curr = curr->next;
    }

    smaller->next = largerStart;
    return smallerStart;
}


int main() {
    Node *root, *curr;

    curr = new Node(1);
    root = curr;
    curr->next = new Node(4);
    curr = curr->next;
        curr->next = new Node(3);
    curr = curr->next;
        curr->next = new Node(2);
    curr = curr->next;
        curr->next = new Node(5);
    curr = curr->next;
        curr->next = new Node(2);

    
    Node * result = getPartitionedList2(root, 3);
    while(result != NULL){
        cout << result->val << " ";
        result = result->next;
    }

    std::cout << "This is a debug message" << std::endl;

    return 0;
}



