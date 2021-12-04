DATE=$(date +%Y%m%d)
TIME=$(date +%H%M%S)

FILENAME="log/TEST-$DATE-$TIME.txt"

python3 test.py ./cmake-build-debug/setcal >  $FILENAME

