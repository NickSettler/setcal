for i in {1..10}
do
  DATE=$(date +%Y%m%d)
  TIME=$(date +%H%M%S)

  FILENAME="TEST-BASH-$DATE-$TIME-$i.txt"

  python3 test.py ./cmake-build-debug/setcal >  $FILENAME
done

