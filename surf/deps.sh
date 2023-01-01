deps=(
    "bash"
    "clang"
    "curl"
    "git"
    "make"
)

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    sudo apt update
    for dep in "${deps[@]}"; do
        sudo apt install "$dep"
    done
else
    echo "Platform $OSTYPE is not supported. To run surf on $OSTYPE, edit the install.sh script"
fi