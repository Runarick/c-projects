#этот файл в тупую используется только для создания папки с тестами
#создание папки с тестами
mkdir -p tests
#простейший файл
echo "Hello my dear">tests/test1.txt
#файл со строками, пустыми строками
printf "One\nTwo\nThree\n\n\n\nFFFFour">tests/test2.txt
#пустой файл
touch tests/test3_em.txt
#файл со спец символами
printf "Tab\there\nNewline\n\nDouble newline" > tests/sp_sim.txt