#!/bin/bash

echo "Testing additional pipe error scenarios..."
echo "=========================================="

# Test 1: Multiple errors in pipeline
echo "Test 1: nonexistent1 | nonexistent2 | echo hello"
echo "Expected: Only first error message"
./minikabuk/minishell << EOF
nonexistent1 | nonexistent2 | echo hello
EOF

echo ""
echo "================================"

# Test 2: Error in last command
echo "Test 2: echo hello | nonexistent"
echo "Expected: Only error message, no 'hello' output"
./minikabuk/minishell << EOF
echo hello | nonexistent
EOF

echo ""
echo "================================"

# Test 3: Successful pipeline with multiple commands
echo "Test 3: echo hello | echo world | echo test"
echo "Expected: 'test' output"
./minikabuk/minishell << EOF
echo hello | echo world | echo test
EOF

echo ""
echo "================================"

# Test 4: Error in middle with redirect
echo "Test 4: echo hello | /etc | echo world"
echo "Expected: Only 'is a directory' error"
./minikabuk/minishell << EOF
echo hello | /etc | echo world
EOF

echo ""
echo "================================"

# Test 5: Redirect error in middle
echo "Test 5: echo hello | echo world > /root/test | echo test"
echo "Expected: Only permission denied error"
./minikabuk/minishell << EOF
echo hello | echo world > /root/test | echo test
EOF

echo ""
echo "================================"

echo "Additional testing completed!"