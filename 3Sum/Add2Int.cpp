//
//  Add2Int.cpp
//  3Sum
//
//  Created by 洪锐 李 on 16/9/6.
//  Copyright © 2016年 洪锐 李. All rights reserved.
//

#include <stdio.h>


struct ListNode {
         int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
     };


class Add2int {
public:
    
    ListNode* addNumbers(ListNode* l1, int l2) {
        ListNode *p = l1;
        if (l2 == 0) {
            l1->val = 0;
        }
        else{
            while (l2) {
                l1->val = l2 % 10;
                l2 = l2 / 10;
                l1->next = new ListNode(0);
                p = l1;
                l1 = l1->next;
            }
            p -> next = NULL;

        }
        return l1;
    }
    
    
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int i = 0;
        ListNode *l3 = new ListNode(0);
        ListNode *l4 = new ListNode(0);
        ListNode *q = new ListNode(0);
        l4 = l3;
        while(l1 && l2){
            if (i == 0) {
                l3 -> val = l1->val + l2->val;
            }
            else{
                l3->val = l1->val + l2->val + i;
                i = 0;
            }
            
            if (l3->val > 9) {
                l3->val -= 10;
                i = 1;
            }
            q = l3;
            l3 -> next = new ListNode(0);
            l3 = l3->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        
        while (l1) {
            if (i == 0) {
                l3->val = l1->val;
            }
            else{
                l3->val = l1->val + i;
                i = 0;
            }
            if (l3->val > 9) {
                l3->val -= 10;
                i = 1;
            }
            l3 -> next = new ListNode(0);
            q = l3;
            l3 = l3->next;
            l1 = l1->next;
        }
        while (l2) {
            if (i == 0) {
                l3->val = l2->val;
            }
            else{
                l3->val = l2->val + i;
                i = 0;
            }
            if (l3->val > 9) {
                l3->val -= 10;
                i = 1;
            }
            l3 -> next = new ListNode(0);
            q = l3;
            l3 = l3->next;
            l2 = l2->next;

        }
        
        if (i == 0) {
             q -> next = NULL;
        }
        else{
            q->next ->val = 1;
        }
       
        
        return l4;
    }
};