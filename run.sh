if nvcc assembly.cu structure.cpp; then
        echo "Assembly successful."
        ./a.out $1
else
        echo "Compilation error"
fi
