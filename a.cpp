#include <iostream>
#include <chrono>

class ExampleClass {
public:
    void performSessionOperations()
    {
        stack.stack_login();
        system("pause");
        // Perform some actions within the session

        stack.stack_logout();
    }
};

int main()
{
    ExampleClass example;
    example.performSessionOperations();

    return 0;
}
