~cs1521/bin/spim -file worm.s 6 50 58 | sed -e 's/^.*Iteration/Iteration/;s/ *$//;/Loaded:/d'
