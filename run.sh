var=${1:-8}
echo "Кол-во клвстеров: $var"

./bin/f1 527
python points.py ./data/tof.txt $var
python points.py ./data/sig.txt $var
python points.py ./data/cnot.txt $var
./bin/f2 527
./bin/f3
