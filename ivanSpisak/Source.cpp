
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x = 0, ListNode* next = nullptr) : val(x), next(next){}
};

ListNode* reverseIterative(ListNode* head)
{
	ListNode* curr = head, * prev = nullptr, * next;
	while (curr)
	{
		next = curr->next;//: Запазваме връзката към следващия елемент в оригиналния списък, за да не я изгубим при обръщането на указателите.
		curr->next = prev;// Обръщаме указателя на curr, като го насочваме към prev, т.е., текущия curr става последен в новия обрънат списък.
		prev = curr;//Преместваме prev напред с един елемент, така че да сочи към текущия curr.
		curr = next;//Преместваме curr напред към следващия елемент в оригиналния списък, който сме запазили в next.
	}
	return prev;
}
ListNode* detectCycleConstMemory(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head;
    // find the node that two pointers meet
    while (fast != nullptr)
    {
        slow = slow->next;
        if (fast->next == nullptr)
        {
            return nullptr;
        }
        fast = fast->next->next;
        if (slow == fast)
        {
            break;
        }
    }
    if (fast == nullptr)
    {
        return nullptr;
    }
    slow = head;
    // find the node where the cycle begins
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return fast;
}
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode* dummyHead = new ListNode();//: Създаваме фиктивен (dummy) елемент, който служи за начало на новия списък.

    ListNode* curr = dummyHead;//Преместваме curr напред към следващия елемент в новия списък (curr = curr->next).

    while (l1 || l2)
    {
        // Ако l1 е изчерпан, добавяме остатъка от l2 в новия списък
        if (!l1)
        {
            curr->next = l2;
            l2 = l2->next;
        }
        // Ако l2 е изчерпан, добавяме остатъка от l1 в новия списък
        else if (!l2)
        {
            curr->next = l1;
            l1 = l1->next;
        }
        // Ако имаме и в двата списъка оставащи елементи, сравняваме стойностите им
        else
        {
            if (l1->val > l2->val)
            {
                curr->next = l2;
                l2 = l2->next;
            }
            else
            {
                // Иначе добавяме текущия елемент от l1
                curr->next = l1;
                l1 = l1->next;
            }
        }
        //Преместваме curr напред към следващия елемент в новия списък (curr = curr->next).
        curr = curr->next;
    }
    //Накрая връщаме началото на новия списък, което е dummyHead->next, т.е., първият истински елемент след dummyHead
    return dummyHead->next;
}
ListNode* sortList(ListNode* head)
{
    if (!head || !head->next)
    {
        return head;
    }
    //инициализация на указатели за делене на списъка на две части
    ListNode* fast = head, * slow = head, * temp = head;
    while (fast && fast->next)
    {
        fast = fast->next->next;//две позиции напред
        temp = slow;//temp задържа позицията на slow преди да го сортира
        slow = slow->next;//движи се с една позиция напред
    }
    temp->next = nullptr; //разделяме списъка на две части
    ListNode* left = sortList(head); // Рекурсивно сортиране на левата част
    ListNode* right = sortList(slow); // Рекурсивно сортиране на дясната част

    return mergeTwoLists(left, right);
}
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    // Създаваме фиктивен (dummy) елемент dummyHead, който служи за начало на резултатния списък. curr е указател, който показва текущия елемент в резултатния списък.
    ListNode* dummyHead = new ListNode(), * curr = dummyHead;
    //Променлива за съхраняване на преноса при събиране на цифри.
    bool carry = false;
    while (l1 || l2)
    {
        //Вътре в цикъла създаваме нов елемент в резултатния списък (curr->next = new ListNode();) и преместваме curr към този нов елемент (curr = curr->next).
        curr->next = new ListNode();
        curr = curr->next;
        int x = l1 ? l1->val : 0;
        int y = l2 ? l2->val : 0;
        curr->val = (x + y + carry) % 10;
        carry = (x + y + carry) / 10;
        if (l1)
        {
            l1 = l1->next;
        }
        if (l2)
        {
            l2 = l2->next;
        }
    }
    if (carry)
    {
        curr->next = new ListNode(1);
    }
    //Добавяне на остатъчния пренос:

  //  Ако след последната итерация има остатъчен пренос(carry), добавяме нов елемент със стойност 1 (curr->next = new ListNode(1);).
     //   Връщане на резултатния списък :

   // Връщаме началото на резултатния списък, което е dummyHead->next, за да пропуснем фиктивния елемент(dummyHead).
    return dummyHead->next;
}
void deleteNode(ListNode* node)
{
    //Копиране на стойността на следващия възел:
    node->val = node->next->val;
    //4->1->1->9
    //Тук съхраняваме указателя към следващия възел в tmp, за да можем след това да го изтрием.
    ListNode* tmp = node->next;
    node->next = node->next->next;
    //4->1->9
    //изтриваме възела
    delete tmp;
}
ListNode* removeNthFromEnd(ListNode* head, int n)
{
    ListNode* dummyHead = new ListNode(), * slow = dummyHead, * fast = dummyHead;
    dummyHead->next = head;
    for (int i = 0; i < n + 1; i++)
    {
        fast = fast->next;
    }
    while (fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    //delete the node
    slow->next = slow->next->next;
    return dummyHead->next;
}