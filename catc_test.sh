rm -f R.bsig R.data R.info R.psig R.tsig
make
./create R catc 10100 4 1000

./insert R < data3

./stats R
