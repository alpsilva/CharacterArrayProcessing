for ((i = 1; i <= 1000; i++)); do
    time grep -o "lorem" sample.txt | wc -l
done
