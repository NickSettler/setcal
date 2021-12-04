DATE=$(date +%Y%m%d)
TIME=$(date +%H%M%S)

FILENAME="log/TEST-$DATE-$TIME-BONUS.txt"

python3 test.py ./cmake-build-debug/setcal --bonus >  $FILENAME

