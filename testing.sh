make
rm R.*
./create R simc 10000 6 1000
./gendata 10000 6 1234567 13 > R.in
./insert R < R.in
./stats R