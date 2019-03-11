PWD=`pwd`
echo "PWD:$PWD"
ME=`pwd | sed 's!.*/\(.*\)/WORM!\1!'`
echo "ME:$ME"
