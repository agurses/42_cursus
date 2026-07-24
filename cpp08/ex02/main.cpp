#include "MutantStack.hpp"
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>

static void check(bool condition, const char *name, int &failures)
{
    if (condition)
        std::cout << "PASS: " << name << std::endl;
    else
    {
        std::cout << "FAIL: " << name << std::endl;
        ++failures;
    }
}

template <typename ExpectedContainer>
static bool sameSequence(MutantStack<int> &stack,
                         const ExpectedContainer &expected)
{
    MutantStack<int>::iterator stackIt = stack.begin();
    typename ExpectedContainer::const_iterator expectedIt = expected.begin();

    while (stackIt != stack.end() && expectedIt != expected.end())
    {
        if (*stackIt != *expectedIt)
            return false;
        ++stackIt;
        ++expectedIt;
    }
    return stackIt == stack.end() && expectedIt == expected.end();
}

int main(void)
{
    int failures = 0;

    MutantStack<int> stack;
    check(stack.empty(), "new stack is empty", failures);
    check(stack.size() == 0, "new stack has size zero", failures);

    stack.push(5);
    stack.push(17);
    check(stack.top() == 17, "top returns the last pushed value", failures);
    check(stack.size() == 2, "size counts pushed values", failures);

    stack.pop();
    check(stack.top() == 5, "pop removes the top value", failures);
    check(stack.size() == 1, "size decreases after pop", failures);

    stack.push(3);
    stack.push(5);
    stack.push(737);
    stack.push(0);

    std::vector<int> expected;
    expected.push_back(5);
    expected.push_back(3);
    expected.push_back(5);
    expected.push_back(737);
    expected.push_back(0);

    check(stack.top() == 0, "top returns the current top", failures);
    check(!stack.empty(), "stack is not empty after push", failures);
    check(sameSequence(stack, expected), "iterator traverses all values", failures);

    MutantStack<int>::iterator begin = stack.begin();
    MutantStack<int>::iterator current = begin;
    ++current;
    --current;
    check(current == begin, "iterator moves forward and backward", failures);

    std::list<int> expectedList;
    expectedList.push_back(5);
    expectedList.push_back(3);
    expectedList.push_back(5);
    expectedList.push_back(737);
    expectedList.push_back(0);
    check(sameSequence(stack, expectedList),
          "iterator output matches std::list", failures);

    MutantStack<int> empty;
    check(empty.begin() == empty.end(),
          "begin equals end for an empty stack", failures);

    MutantStack<int> copied(stack);
    check(sameSequence(copied, expected),
          "copy constructor copies the stack", failures);

    MutantStack<int> assigned;
    assigned.push(-1);
    assigned = stack;
    check(sameSequence(assigned, expected),
          "assignment operator copies the stack", failures);

    MutantStack<int> &same = assigned;
    assigned = same;
    check(sameSequence(assigned, expected),
          "self-assignment keeps the stack valid", failures);

    std::stack<int> normalStack(stack);
    check(normalStack.size() == stack.size()
          && normalStack.top() == stack.top(),
          "MutantStack copies to std::stack", failures);

    MutantStack<std::string> words;
    words.push("first");
    words.push("second");
    check(words.top() == "second", "template works with std::string", failures);
    check(*words.begin() == "first", "string iterator works", failures);

    if (failures == 0)
        std::cout << "All tests passed" << std::endl;
    else
        std::cout << failures << " test(s) failed" << std::endl;

    return failures;
}
