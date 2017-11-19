if nvcc main.cu structure.cpp assembly.cpp device.cu; then
        echo "Assembly successful."
        ./a.out $1
else
        echo "Compilation error"
fi
