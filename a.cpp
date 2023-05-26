// Function to merge two sorted linked lists
Member_st* SortedMerge(Member_st* a, Member_st* b)
{
    Member_st* result = NULL;
 
    // Base cases
    if (a == NULL)
        return(b);
    else if (b == NULL)
        return(a);
 
    // Pick either a or b, and recur
    if (a->mem_name <= b->mem_name)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return(result);
}
 
// Function to do Front Back Split
void FrontBackSplit(Member_st* source,
                    Member_st** frontRef, Member_st** backRef)
{
    Member_st* fast;
    Member_st* slow;
    slow = source;
    fast = source->next;
 
    // Advance 'fast' two nodes, and advance 'slow' one node
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    // 'slow' is before the midpoint in the list, so split it in two
    // at that point.
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}
 
// Function to sort the linked list using Merge Sort
void MergeSort(Member_st** headRef)
{
    Member_st* head = *headRef;
    Member_st* a;
    Member_st* b;
 
    // Base case -- length 0 or 1
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }
 
    // Split head into 'a' and 'b' sublists
    FrontBackSplit(head, &a, &b); 
 
    // Recursively sort the sublists
    MergeSort(&a);
    MergeSort(&b);
 
    // answer = merge the two sorted lists together
    *headRef = SortedMerge(a, b);
}

void view_member()
{
    int i = 1;
    const int nameWidth = 20;
    ifstream cusfile("members.txt");
    if (cusfile.fail()) {
        cout << "File opening failed.\n";
    } else {
        LinkedQueue memberQueue; // Create a LinkedQueue object to store member information
        string line;
        while (getline(cusfile, line)) {
            if (line.empty()) {
                continue;
            }
            Member_st* newMember = new Member_st;
            newMember->mem_name = line;

            getline(cusfile, line);
            newMember->mem_phone = line;

            getline(cusfile, line);
            newMember->mem_email = line;

            getline(cusfile, line);
            newMember->mem_password = line;

            memberQueue.enqueue(newMember); // Enqueue member
        }

        cusfile.close();

        // Sort the members by name
        MergeSort(&(memberQueue.front));

        // Display the member information from the queue
        if (memberQueue.isEmpty()) {
            cout << "No member information available." << endl;
        } else {
            cout << "-----------------------------------------------------------------------------------Member Information-----------------------------------------------------------------------------------" << endl;
            while (!memberQueue.isEmpty()) {
                Member_st* member = memberQueue.getFront();
                cout << i << ". Member Name : " << left << setw(name
