#include <iostream>
#include <stack>
using namespace std;

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int v): val(v), next(NULL){}
};

class Solution{
public:
	//0. print list node in order
	void printList(ListNode* pHead){
		ListNode *curr = pHead;
		while(curr){
			cout<<"->"<<curr->val;
			curr = curr->next;
		}
		cout<<endl;
	}
	
	//1. 求单链表中节点的个数：
	int getListLength(ListNode* pHead){
		int length = 0;
		ListNode * curr = pHead;
		while(curr){
			length++;
			curr = curr->next;
		}
		return length;
	}
	
	//2. 将单链表反转
	ListNode* reverseList(ListNode* head){
		if(!head){
			return head;
		}
		ListNode dummy(-1);
		dummy.next = head;
		ListNode *prev = head;
		
		while(prev->next){
			ListNode *curr = prev->next;
			prev->next = curr->next;
			curr->next = dummy.next;
			dummy.next = curr;
		}
		
		return dummy.next;
	}
	
	//3. 查找单链表中倒数第K个节点（K>0）
	ListNode *rGetKthNode(ListNode *head, int k){
		ListNode dummy(-1);
		dummy.next = head;
		ListNode *fast=&dummy, *slow=&dummy;
		int i=0;
		while(fast&&i<k){
			fast = fast->next;
			i++;
		}
		
		if(i<k){
			return NULL;
		}
		while(fast){
			fast = fast->next;
			slow = slow->next;
		}
		
		return slow;
	}
	
	//4. 查找单链表的中间节点
	ListNode* getMiddleNode(ListNode* head){
		if(!head||!(head->next)||!(head->next->next)){
			return head;
		}
		
		ListNode *two = head;
		ListNode *one = head;
		while(two->next &&two->next->next){
			one = one->next;
			two = two->next->next;
		}
		
		return one;
	}
	
	//5. 从尾到头打印单链表 : (先进后出，or， 后进先出， 也就是栈，stack) 可以recursion来模拟
	void reversePrintList(ListNode* head){
		if(!head){
			return;
		}
		
		reversePrintList(head->next);
		cout<<head->val<<"<-";
	}
	
	//5_2, stack实现
	void reversePrintList_stack(ListNode* head){
		stack<ListNode*> stk;
		while(head){
			stk.push(head);
			head = head->next;
		}
		
		while(!stk.empty()){
			cout<<stk.top()->val<<"<-";
			stk.pop();
		}
	}
	
	//6. 已知两个单链表pHead1 和pHead2 各自有序，把它们合并成一个链表依然有序
	ListNode* mergeSortedList(ListNode* head1, ListNode* head2){
		ListNode dummy(-1);
		dummy.next = head1;
		ListNode* prev = &dummy;
		ListNode* curr1 = head1;
		ListNode* curr2 = head2;
		
		while(curr1&&curr2){
			if(curr1->val>curr2->val){ // 
				prev->next = curr2;
				curr2 = curr2->next;
				prev = prev->next;
				prev->next = curr1;
			}else{
				prev = curr1;
				curr1 = curr1->next;
			}
		}
		
		if(curr2){
			prev->next = curr2;
		}
		
		return dummy.next;
	}
	
	//7. 判断一个单链表中是否有环
	bool hasCircle(ListNode* head){
		ListNode* slow = head;
		ListNode* fast = head;
		while(fast&&fast->next){
			if(slow == fast){
				return true;
			}
			
			slow = slow->next;
			fast = fast->next->next;
		}
		
		return false;
	}
	
	//8. 判断两个单链表是否相交
	bool isIntersected(ListNode* head1, ListNode* head2){
		if(!head1||!head2){
			return false;
		}
		
		ListNode* curr1 = head1;
		while(curr1->next){
			curr1 = curr1->next;
		}
		
		ListNode* curr2 = head2;
		while(curr2->next){
			curr2 = curr2->next;
		}
		
		return curr1 == curr2;
	}
	
	//9. 求两个单链表相交的第一个节点
	ListNode* firstIntersection(ListNode* head1, ListNode* head2){
		if(!head1||!head2){
			return NULL;
		}
		ListNode* curr1 = head1;
		ListNode* curr2 = head2;
		int length1 = 1;
		int length2 = 1;
		while(curr1->next){
			curr1= curr1->next;
			length1++;
		}
		while(curr2->next){
			curr2 = curr2->next;
			length2++;
		}
		
		if(curr1!=curr2){
			return NULL;
		}
		
		ListNode* longer = length1>length2? head1:head2;
		ListNode* shorter = length1>length2? head2:head1;
		
		int difference = abs(length1 - length2);
		while(difference>0){
			longer = longer->next;
			difference--;
		}
		
		while(longer!=shorter){
			longer = longer->next;
			shorter = shorter->next;
		}
		
		return longer;
	}
	
	//10. 已知一个单链表中存在环，求进入环中的第一个节点
	ListNode* firstNodeInCircle(ListNode* head){
		//found some point in the cycle (to test whether there is a cycle)
		if(!head){
			return NULL;
		}
		ListNode *slow = head;
		ListNode *fast = head;
		while(fast&&fast->next){
			slow = slow->next;
			fast = fast->next->next;
			if(fast == slow){
				cout<<"Met at "<<fast->val<<endl;
				break;
			}
		}		
		
		if(!fast||!fast->next){
			return NULL;
		}
		
		//break the circle at the intersection point
		int length1 = 0; //from head;
		int length2 = 0; //from fast->next;
		ListNode* curr1 = head;
		ListNode* curr2 = fast->next;
		while(curr1!=fast){
			length1++;
			curr1 = curr1->next;
		}
		
		while(curr2!=fast){
			length2++;
			curr2 = curr2->next;
		}
		
		ListNode* longer = length1>length2? head:fast->next;
		ListNode* shorter = length1>length2? fast->next:head;
		
		int diff = abs(length1 - length2);
		while(diff>0){
			longer = longer->next;
			diff --;
		}
		
		while(longer!=shorter){
			longer = longer->next;
			shorter= shorter->next;
		}
		
		return longer;
	}
	
	//11. 给出一单链表头指针pHead和一节点指针pToBeDeleted，O(1)时间复杂度删除节点pToBeDeleted
	void deleteListNode(ListNode* head, ListNode* deleted){
		if(!head||!deleted){
			return;
		}
		
		if(!head->next&&head==deleted){
			delete head;
			return;
		}
		
		if(deleted->next){
			ListNode *tmp = deleted->next;
			deleted->val = tmp->val;
			deleted->next = tmp->next;
			delete tmp;
		}else{		
			ListNode* curr = head;
			while(curr->next!=deleted){
				curr = curr->next;
			}
			
			curr->next = NULL;
			delete deleted;
		}
	}
};

int main(){
	Solution s;
	ListNode *l1 =new ListNode(1);
	ListNode *l2 =new ListNode(2);
	ListNode *l3 =new ListNode(3);
	ListNode *l4 =new ListNode(4);
	ListNode *l5 =new ListNode(5);
	l1->next = l2;
	l2->next = l3;
	l3->next = l4;
	l4->next = l5;
	
	ListNode *l = NULL;
	cout<<"l1 is: ";
	s.printList(l1);
	cout<<"length: "<<s.getListLength(l1)<<endl;
	cout<<"l is: ";
	s.printList(l);
	cout<<"length is: "<<s.getListLength(l)<<endl;
	//ListNode* rHead = s.reverseList(l1);
	//s.printList(s.reverseList(l1));
	ListNode *r2 = s.rGetKthNode(l, 2);
	if(r2){
		cout<<r2->val<<endl;
	}else{
		cout<<"no such node"<<endl;
	}
	s.printList(l2);
	cout<<s.getMiddleNode(l2)->val<<endl;
	s.reversePrintList(l1);
	cout<<endl;
	s.reversePrintList_stack(l1);
	cout<<endl;
	
	//6. merge two sorted lists: 
	ListNode *sl1 = new ListNode(3);
	ListNode *sl2 = new ListNode(8);
	ListNode *sl3 = new ListNode(15);
	ListNode *sl4 = new ListNode(70);
	sl1->next = sl2;
	sl2->next = sl3;
	sl3->next = sl4;
	ListNode *sll1 = new ListNode(1);
	ListNode *sll2 = new ListNode(2);
	ListNode *sll3 = new ListNode(14);
	sll1->next = sll2;
	sll2->next = sll3;
	s.printList(sl1);
	s.printList(sll1);
	ListNode * sortedList = s.mergeSortedList(sl1, sll1);
	s.printList(sortedList);
	
	//7. 判断一个单链表中是否有环
	cout<<"//7. 判断一个单链表中是否有环"<<endl;
	ListNode* c1 = new ListNode(1);
	ListNode* c2 = new ListNode(2);
	ListNode* c3 = new ListNode(3);
	c1->next = c2;
	c2->next = c1;
	c3->next = c2;
	cout<<"has circle: "<<s.hasCircle(c1)<<endl;
	
	//8. 判断两个单链表是否相交
	cout<<"//8. 判断两个单链表是否相交"<<endl;
	ListNode* hl11 = new ListNode(1);
	ListNode* hl12 = new ListNode(2);
	ListNode* hl13 = new ListNode(3);
	ListNode* hl21 = new ListNode(4);
	hl11->next = hl12;
	hl12->next = hl13;
	hl21->next = hl13;
	
	cout<<"Intersected? "<<s.isIntersected(hl11, hl21)<<endl;
	
	//9. 求两个单链表相交的第一个节点
	cout<<"//9. 求两个单链表相交的第一个节点"<<endl;
	ListNode* firstIntersection = s.firstIntersection(hl11, hl21);
	if(firstIntersection){
		cout<<"The first intersect node: "<<firstIntersection->val<<endl;
	}else{
		cout<<"There is no intersection "<<endl;
	}
	
	//10. 已知一个单链表中存在环，求进入环中的第一个节点
	cout<<"10. 已知一个单链表中存在环，求进入环中的第一个节点"<<endl;
	ListNode* f1 = new ListNode(1);
	ListNode* f2 = new ListNode(2);
	ListNode* f3 = new ListNode(3);
	ListNode* f4 = new ListNode(4);
	ListNode* f5 = new ListNode(5);
	f1->next = f2;
	f2->next = f3;
	f3->next = f4;
	f4->next = f5;
	f5->next = f4;
	
	ListNode *firstInCircle = s.firstNodeInCircle(f1);
	if(firstInCircle){
		cout<<"Found circle: "<<firstInCircle->val<<endl;
	}else{
		cout<<"No circle!"<<endl;
	}
	
	//11. 给出一单链表头指针pHead和一节点指针pToBeDeleted，O(1)时间复杂度删除节点pToBeDeleted
	cout<<"//11. 给出一单链表头指针pHead和一节点指针pToBeDeleted，O(1)时间复杂度删除节点pToBeDeleted"<<endl;
	ListNode *d1 = new ListNode(1);
	ListNode *d2 = new ListNode(2);
	ListNode *d3 = new ListNode(3);
	ListNode *d4 = new ListNode(4);
	d1->next = d2;
	d2->next = d3;
	d3->next = d4;
	
	s.printList(d1);
	s.deleteListNode(d1, d4);
	s.printList(d1);
}
