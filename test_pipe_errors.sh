#!/bin/bash

echo "Testing pipe error handling..."
echo "================================"

# Test 1: Command not found in first command of pipeline
echo "Test 1: nonexistent_command | echo hello"
echo "Expected: Only 'command not found' error, no 'hello' output"
./minikabuk/minishell << EOF
nonexistent_command | echo hello
EOF

echo ""
echo "================================"

# Test 2: Command not found in middle of pipeline
echo "Test 2: echo hello | nonexistent_command | echo world"
echo "Expected: Only 'command not found' error, no output"
./minikabuk/minishell << EOF
echo hello | nonexistent_command | echo world
EOF

echo ""
echo "================================"

# Test 3: Permission denied in first command
echo "Test 3: /etc/shadow | echo hello"
echo "Expected: Only 'permission denied' error, no 'hello' output"
./minikabuk/minishell << EOF
/etc/shadow | echo hello
EOF

echo ""
echo "================================"

# Test 4: Directory as command in first position
echo "Test 4: /etc | echo hello"
echo "Expected: Only 'is a directory' error, no 'hello' output"
./minikabuk/minishell << EOF
/etc | echo hello
EOF

echo ""
echo "================================"

# Test 5: Successful pipeline (control test)
echo "Test 5: echo hello | echo world"
echo "Expected: 'hello world' output"
./minikabuk/minishell << EOF
echo hello | echo world
EOF

echo ""
echo "================================"

# Test 6: Redirect error in first command
echo "Test 6: echo hello > /root/test | echo world"
echo "Expected: Only 'permission denied' error, no 'world' output"
./minikabuk/minishell << EOF
echo hello > /root/test | echo world
EOF

echo ""
echo "================================"

echo "Testing completed!"