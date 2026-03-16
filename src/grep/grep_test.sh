# Создание тестовой директории и файла
TEST_DIR="grep_test_dir"
TEST_FILE="$TEST_DIR/test.txt"

# Создаем директорию и тестовый файл
mkdir -p $TEST_DIR
cat > $TEST_FILE << EOF
hello world
test line
another line
HELLO WORLD
empty line

line with tabs	here
multiple hello hello
grep test line
EOF

echo "Тесты для s21_grep"

# Простой поиск
grep "hello" $TEST_FILE > base_output.txt
./s21_grep "hello" $TEST_FILE > my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на простой поиск пройден"
else
    echo "Тест на простой поиск НЕ пройден"
fi

# Поиск с игнорированием регистра (-i)
grep -i "hello" $TEST_FILE > base_output.txt
./s21_grep -i "hello" $TEST_FILE > my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -i пройден"
else
    echo "Тест на -i НЕ пройден"
fi

# Инвертированный поиск (-v)
grep -v "hello" $TEST_FILE > base_output.txt
./s21_grep -v "hello" $TEST_FILE > my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -v пройден"
else
    echo "Тест на -v НЕ пройден"
fi

# Подсчет количества совпадений (-c)
grep -c "hello" $TEST_FILE > base_output.txt
./s21_grep -c "hello" $TEST_FILE > my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -c пройден"
else
    echo "Тест на -c НЕ пройден"
fi

# Вывод номера строки (-n)
grep -n "hello" $TEST_FILE > base_output.txt
./s21_grep -n "hello" $TEST_FILE > my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -n пройден"
else
    echo "Тест на -n НЕ пройден"
fi


# Комбинация флагов (-in)
grep -in "hello" $TEST_FILE > base_output.txt
./s21_grep -in "hello" $TEST_FILE > my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -in пройден"
else
    echo "Тест на -in НЕ пройден"
fi

# Поиск в нескольких файлах
TEST_FILE2="$TEST_DIR/test2.txt"
echo "hello from second file" > $TEST_FILE2

grep "hello" $TEST_FILE $TEST_FILE2 > base_output.txt
./s21_grep "hello" $TEST_FILE $TEST_FILE2 > my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на несколько файлов пройден"
else
    echo "Тест на несколько файлов НЕ пройден"
fi

grep -l "hello" $TEST_FILE1 $TEST_FILE2 > base_output.txt
./s21_grep -l "hello" $TEST_FILE1 $TEST_FILE2 > my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -l пройден"
else
    echo "Тест на -l НЕ пройден"
fi

# Очистка
