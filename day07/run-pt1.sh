name=day07pt1

cc src/$name.c -Wextra -Wall -O3 -o $name
./$name < input/input.txt
rm $name
