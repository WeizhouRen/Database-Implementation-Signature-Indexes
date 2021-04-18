make
rm R.*
./create R simc 10000 6 1000
./gendata 10000 6 1234567 13 > R.in
./insert R < R.in
./stats R
echo "./select R '?,?,?,?,?,?' x | tail -6"
./select R '?,?,?,?,?,?' x | tail -6

echo "./select R '1234999,?,?,?,?,?' x"
./select R '1234999,?,?,?,?,?' x

echo "./select R '1234999,?,?,?,?,?' t"
./select R '1234999,?,?,?,?,?' t

echo "./select R '1234999,?,?,?,?,?' p"
./select R '1234999,?,?,?,?,?' p

echo "./select R '1234999,?,?,?,?,?' b"
./select R '1234999,?,?,?,?,?' b

grep 'a3-241,a4-158,a5-407' R.in
# 1237049,ovnsbtUWihCcCEoRWKcF,a3-241,a4-158,a5-407,a6-490
# 1242029,eptevNjxFwayfSGeFKrO,a3-241,a4-158,a5-407,a6-490
# search for tuples via several attributes (using no signatures)
./select R '?,?,a3-241,a4-158,a5-407,?' x
# 1237049,ovnsbtUWihCcCEoRWKcF,a3-241,a4-158,a5-407,a6-490
# 1242029,eptevNjxFwayfSGeFKrO,a3-241,a4-158,a5-407,a6-490
# Query Stats:
# sig pages read:    0
# signatures read:   0
# data pages read:   137
# tuples examined:   10000
# false match pages: 135
# search for tuples via several attributes (using tuple signatures)
./select R '?,?,a3-241,a4-158,a5-407,?' t
# 1237049,ovnsbtUWihCcCEoRWKcF,a3-241,a4-158,a5-407,a6-490
# 1242029,eptevNjxFwayfSGeFKrO,a3-241,a4-158,a5-407,a6-490
# Query Stats:
# sig pages read:    27
# signatures read:   10000
# data pages read:   2
# tuples examined:   146
# false match pages: 0
# search for tuples via several attributes (using page signatures)
./select R '?,?,a3-241,a4-158,a5-407,?' p
# 1237049,ovnsbtUWihCcCEoRWKcF,a3-241,a4-158,a5-407,a6-490
# 1242029,eptevNjxFwayfSGeFKrO,a3-241,a4-158,a5-407,a6-490
# Query Stats:
# sig pages read:    28
# signatures read:   137
# data pages read:   2
# tuples examined:   146
# false match pages: 0
# search for tuples via several attributes (using bit-sliced signatures)
./select R '?,?,a3-241,a4-158,a5-407,?' b
# 1237049,ovnsbtUWihCcCEoRWKcF,a3-241,a4-158,a5-407,a6-490
# 1242029,eptevNjxFwayfSGeFKrO,a3-241,a4-158,a5-407,a6-490
# Query Stats:
# sig pages read:    17
# signatures read:   27
# data pages read:   2
# tuples examined:   146
# false match pages: 0