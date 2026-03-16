# этот файл уже включает в себя тестирование 
# моего  cat, простосравнением output с базовым cat
TEST1="tests/test1.txt"
TEST2="tests/test2.txt"
TEST3="tests/test3_em.txt"
TEST4="tests/sp_sim.txt"
#сравнение прочтая печать
cat $TEST1>base_output.txt
./s21_cat $TEST1>my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на простую печать пройден"
else
    echo "Тест на на простую печать НЕ пройден"
fi
#сравнение флаг -e
cat -e $TEST4>base_output.txt
./s21_cat -e $TEST4>my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -e пройден"
else
    echo "Тест на -e НЕ пройден"
fi
#сравнение  просто нумерацию (флаг -n)
cat -n $TEST2>base_output.txt
./s21_cat -n $TEST2>my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -n пройден"
else
    echo "Тест на -n НЕ пройден"
fi
#сравнение нумерации (флаг -b)
cat -b $TEST2>base_output.txt
./s21_cat -b $TEST2>my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -b пройден"
else
    echo "Тест на -b НЕ пройден"
fi
#сравнение нумерации (флаг -bn)
cat -bn $TEST2>base_output.txt
./s21_cat -bn $TEST2>my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -bn пройден"
else
    echo "Тест на -bn НЕ пройден"
fi
#сравнение удаления строк (флаг -s)
cat -s $TEST2>base_output.txt
./s21_cat -s $TEST2>my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -s пройден"
else
    echo "Тест на -s НЕ пройден"
fi
#отображение табов (флаг -t)
cat -t $TEST4>base_output.txt
./s21_cat -t $TEST4>my_output.txt
if diff base_output.txt my_output.txt; then
    echo "Тест на -t пройден"
else
    echo "Тест на -t НЕ пройден"
fi

