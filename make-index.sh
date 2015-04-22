
rm -f ./index.*
emcc -std=c++11 src/*.cc -o index.html
