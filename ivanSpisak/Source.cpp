
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
		next = curr->next;//: ��������� �������� ��� ��������� ������� � ����������� ������, �� �� �� � ������� ��� ���������� �� �����������.
		curr->next = prev;// �������� ��������� �� curr, ���� �� ��������� ��� prev, �.�., ������� curr ����� �������� � ����� ������� ������.
		prev = curr;//����������� prev ������ � ���� �������, ���� �� �� ���� ��� ������� curr.
		curr = next;//����������� curr ������ ��� ��������� ������� � ����������� ������, ����� ��� �������� � next.
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
    ListNode* dummyHead = new ListNode();//: ��������� �������� (dummy) �������, ����� ����� �� ������ �� ����� ������.

    ListNode* curr = dummyHead;//����������� curr ������ ��� ��������� ������� � ����� ������ (curr = curr->next).

    while (l1 || l2)
    {
        // ��� l1 � ��������, �������� �������� �� l2 � ����� ������
        if (!l1)
        {
            curr->next = l2;
            l2 = l2->next;
        }
        // ��� l2 � ��������, �������� �������� �� l1 � ����� ������
        else if (!l2)
        {
            curr->next = l1;
            l1 = l1->next;
        }
        // ��� ����� � � ����� ������� �������� ��������, ���������� ����������� ��
        else
        {
            if (l1->val > l2->val)
            {
                curr->next = l2;
                l2 = l2->next;
            }
            else
            {
                // ����� �������� ������� ������� �� l1
                curr->next = l1;
                l1 = l1->next;
            }
        }
        //����������� curr ������ ��� ��������� ������� � ����� ������ (curr = curr->next).
        curr = curr->next;
    }
    //������ ������� �������� �� ����� ������, ����� � dummyHead->next, �.�., ������� �������� ������� ���� dummyHead
    return dummyHead->next;
}
ListNode* sortList(ListNode* head)
{
    if (!head || !head->next)
    {
        return head;
    }
    //������������� �� ��������� �� ������ �� ������� �� ��� �����
    ListNode* fast = head, * slow = head, * temp = head;
    while (fast && fast->next)
    {
        fast = fast->next->next;//��� ������� ������
        temp = slow;//temp ������� ��������� �� slow ����� �� �� �������
        slow = slow->next;//����� �� � ���� ������� ������
    }
    temp->next = nullptr; //��������� ������� �� ��� �����
    ListNode* left = sortList(head); // ���������� ��������� �� ������ ����
    ListNode* right = sortList(slow); // ���������� ��������� �� ������� ����

    return mergeTwoLists(left, right);
}
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    // ��������� �������� (dummy) ������� dummyHead, ����� ����� �� ������ �� ����������� ������. curr � ��������, ����� ������� ������� ������� � ����������� ������.
    ListNode* dummyHead = new ListNode(), * curr = dummyHead;
    //���������� �� ����������� �� ������� ��� �������� �� �����.
    bool carry = false;
    while (l1 || l2)
    {
        //����� � ������ ��������� ��� ������� � ����������� ������ (curr->next = new ListNode();) � ����������� curr ��� ���� ��� ������� (curr = curr->next).
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
    //�������� �� ���������� ������:

  //  ��� ���� ���������� �������� ��� ��������� ������(carry), �������� ��� ������� ��� �������� 1 (curr->next = new ListNode(1);).
     //   ������� �� ����������� ������ :

   // ������� �������� �� ����������� ������, ����� � dummyHead->next, �� �� ��������� ��������� �������(dummyHead).
    return dummyHead->next;
}
void deleteNode(ListNode* node)
{
    //�������� �� ���������� �� ��������� �����:
    node->val = node->next->val;
    //4->1->1->9
    //��� ����������� ��������� ��� ��������� ����� � tmp, �� �� ����� ���� ���� �� �� �������.
    ListNode* tmp = node->next;
    node->next = node->next->next;
    //4->1->9
    //��������� ������
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