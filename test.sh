clang++ test.cpp vref.cpp -std=c++11 || (echo "Compilation failed!")
echo "Running tests..."
($(./a.out 0 >/dev/null 2>&1) && echo "Test 0 succeeded") || (echo "Test 0 failed!" && exit 1)
$(./a.out 1 >/dev/null 2>&1) && echo "Test 1 failed!" && exit 1 || echo "Test 1 succeeded"
$(./a.out 2 >/dev/null 2>&1) && echo "Test 2 failed!" && exit 1 || echo "Test 2 succeeded"
($(./a.out 3 >/dev/null 2>&1) && echo "Test 3 succeeded") || (echo "Test 3 failed!" && exit 1)
$(./a.out 4 >/dev/null 2>&1) && echo "Test 4 failed!" && exit 1 || echo "Test 4 succeeded"
echo "Tests pass!"
