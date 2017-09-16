if g++ -std=c++14 assembly.cpp structure.cpp; then
        echo "Assembly successful."
        ./a.out $1
else
        echo "Compilation error"
fi
