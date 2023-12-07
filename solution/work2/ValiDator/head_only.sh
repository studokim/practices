chmod +x head_only.sh

mkdir -p header_only

cat src/*.h src/*.cpp > header_only/ValiDator.h

sed -i '/#include "ValiDator.h"/d' header_only/ValiDator.h

