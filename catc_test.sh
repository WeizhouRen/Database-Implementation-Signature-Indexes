rm -f R.bsig R.data R.info R.psig R.tsig
make
./create R catc 10100 4 1000 > catc_test_res_zz

./insert R < data3 >> catc_test_res_zz
./stats R >> catc_test_res_zz
./select R '7663852,?,?,?' >> catc_test_res_zz
# 7663852,ivUryYVexVPJQFjhHxea,a3-069,a4-235
# Query Stats
# sig pages read:    0
# signatures read:   0
# data pages read:   104
# tuples examined:   10000
# false match pages: 103

./select R '7663852,?,?,?' t >> catc_test_res_zz
# 7663852,ivUryYVexVPJQFjhHxea,a3-069,a4-235
#Query Stats
# sig pages read:    20
# signatures read:   10000
# data pages read:   2
# tuples examined:   194
# false match pages: 1

./select R '7663852,?,?,?' p >> catc_test_res_zz
# 7663852,ivUryYVexVPJQFjhHxea,a3-069,a4-235
#Query Stats
# sig pages read:    21
# signatures read:   104
# data pages read:   1
# tuples examined:   97
# false match pages: 0

./select R '7663852,?,?,?' b >> catc_test_res_zz
# 7663852,ivUryYVexVPJQFjhHxea,a3-069,a4-235
#Query Stats
# sig pages read:    4
# signatures read:   7
# data pages read:   1
# tuples examined:   97
# false match pages: 0

./select R '7664096,PjZZsBYoEYAMzgpCgRKg,?,?' >> catc_test_res_zz
# 7664096,PjZZsBYoEYAMzgpCgRKg,a3-064,a4-147
#Query Stats
# sig pages read:    0
# signatures read:   0
# data pages read:   104
# tuples examined:   10000
# false match pages: 103

./select R '7664096,PjZZsBYoEYAMzgpCgRKg,?,?' t >> catc_test_res_zz
# 7664096,PjZZsBYoEYAMzgpCgRKg,a3-064,a4-147
#Query Stats
# sig pages read:    20
# signatures read:   10000
# data pages read:   1
# tuples examined:   97
# false match pages: 0

./select R '7664096,PjZZsBYoEYAMzgpCgRKg,?,?' p >> catc_test_res_zz
# 7664096,PjZZsBYoEYAMzgpCgRKg,a3-064,a4-147
#Query Stats
# sig pages read:    21
# signatures read:   104
# data pages read:   1
# tuples examined:   97
# false match pages: 0

./select R '7664096,PjZZsBYoEYAMzgpCgRKg,?,?' b >> catc_test_res_zz
# 7664096,PjZZsBYoEYAMzgpCgRKg,a3-064,a4-147
#Query Stats
# sig pages read:    8
# signatures read:   14
# data pages read:   1
# tuples examined:   97
# false match pages: 0

./select R '?,?,a3-242,a4-242' >> catc_test_res_zz 
# 7654563,kGdSycHkVRpBAXbPMwIq,a3-242,a4-242
# 7655559,jLsUNyUuDtJxeUirkvXJ,a3-242,a4-242
# 7656555,VngPhvobyzwypmiERBNG,a3-242,a4-242
# 7657551,RuFFnNlYxQHYbYatRfNZ,a3-242,a4-242
# 7658547,bsIHFFHQiGXiRIZLRGdt,a3-242,a4-242
# 7659543,jWMPpkazbXZEsmZfuADc,a3-242,a4-242
# 7660539,ecSinUcJGqXsvSRleEda,a3-242,a4-242
# 7661535,CruzuxQXYSqCctqvDzFW,a3-242,a4-242
# 7662531,lRibeHIcdoIPurlWusYu,a3-242,a4-242
# 7663527,DxQAAntFsMFLfUXzeGGh,a3-242,a4-242
#Query Stats
# sig pages read:    0
# signatures read:   0
# data pages read:   104
# tuples examined:   10000
# false match pages: 94

./select R '?,?,a3-242,a4-242' t >> catc_test_res_zz
# 7654563,kGdSycHkVRpBAXbPMwIq,a3-242,a4-242
# 7655559,jLsUNyUuDtJxeUirkvXJ,a3-242,a4-242
# 7656555,VngPhvobyzwypmiERBNG,a3-242,a4-242
# 7657551,RuFFnNlYxQHYbYatRfNZ,a3-242,a4-242
# 7658547,bsIHFFHQiGXiRIZLRGdt,a3-242,a4-242
# 7659543,jWMPpkazbXZEsmZfuADc,a3-242,a4-242
# 7660539,ecSinUcJGqXsvSRleEda,a3-242,a4-242
# 7661535,CruzuxQXYSqCctqvDzFW,a3-242,a4-242
# 7662531,lRibeHIcdoIPurlWusYu,a3-242,a4-242
# 7663527,DxQAAntFsMFLfUXzeGGh,a3-242,a4-242
# Query Stats
# sig pages read:    20
# signatures read:   10000
# data pages read:   10
# tuples examined:   970
# false match pages: 0

./select R '?,?,a3-242,a4-242' p >> catc_test_res_zz
# 7654563,kGdSycHkVRpBAXbPMwIq,a3-242,a4-242
# 7655559,jLsUNyUuDtJxeUirkvXJ,a3-242,a4-242
# 7656555,VngPhvobyzwypmiERBNG,a3-242,a4-242
# 7657551,RuFFnNlYxQHYbYatRfNZ,a3-242,a4-242
# 7658547,bsIHFFHQiGXiRIZLRGdt,a3-242,a4-242
# 7659543,jWMPpkazbXZEsmZfuADc,a3-242,a4-242
# 7660539,ecSinUcJGqXsvSRleEda,a3-242,a4-242
# 7661535,CruzuxQXYSqCctqvDzFW,a3-242,a4-242
# 7662531,lRibeHIcdoIPurlWusYu,a3-242,a4-242
# 7663527,DxQAAntFsMFLfUXzeGGh,a3-242,a4-242
# Query Stats
# sig pages read:    21
# signatures read:   104
# data pages read:   12
# tuples examined:   1164
# false match pages: 2

./select R '?,?,a3-242,a4-242' b >> catc_test_res_zz
# 7654563,kGdSycHkVRpBAXbPMwIq,a3-242,a4-242
# 7655559,jLsUNyUuDtJxeUirkvXJ,a3-242,a4-242
# 7656555,VngPhvobyzwypmiERBNG,a3-242,a4-242
# 7657551,RuFFnNlYxQHYbYatRfNZ,a3-242,a4-242
# 7658547,bsIHFFHQiGXiRIZLRGdt,a3-242,a4-242
# 7659543,jWMPpkazbXZEsmZfuADc,a3-242,a4-242
# 7660539,ecSinUcJGqXsvSRleEda,a3-242,a4-242
# 7661535,CruzuxQXYSqCctqvDzFW,a3-242,a4-242
# 7662531,lRibeHIcdoIPurlWusYu,a3-242,a4-242
# 7663527,DxQAAntFsMFLfUXzeGGh,a3-242,a4-242
# Query Stats
# sig pages read:    8
# signatures read:   14
# data pages read:   12
# tuples examined:   1164
# false match pages: 2

./select R '8765432,?,?,?' >> catc_test_res_zz
#Query Stats
# sig pages read:    0
# signatures read:   0
# data pages read:   104
# tuples examined:   10000
# false match pages: 104

./select R '8765432,?,?,?' t >> catc_test_res_zz
#Query Stats
# sig pages read:    20
# signatures read:   10000
# data pages read:   0
# tuples examined:   0
# false match pages: 0

./select R '8765432,?,?,?' p >> catc_test_res_zz
#Query Stats
# sig pages read:    21
# signatures read:   104
# data pages read:   0
# tuples examined:   0
# false match pages: 0

./select R '8765432,?,?,?' b >> catc_test_res_zz
#Query Stats
# sig pages read:    4
# signatures read:   7
# data pages read:   0
# tuples examined:   0
# false match pages: 0

./select R '7664096,tRzgWRUlUEdoYPZjofYr,?,?' >> catc_test_res_zz
#Query Stats
# sig pages read:    0
# signatures read:   0
# data pages read:   104
# tuples examined:   10000
# false match pages: 104

./select R '7664096,tRzgWRUlUEdoYPZjofYr,?,?' t >> catc_test_res_zz
#Query Stats
# sig pages read:    20
# signatures read:   10000
# data pages read:   0
# tuples examined:   0
# false match pages: 0

./select R '7664096,tRzgWRUlUEdoYPZjofYr,?,?' p >> catc_test_res_zz
#Query Stats
# sig pages read:    21
# signatures read:   104
# data pages read:   0
# tuples examined:   0
# false match pages: 0

./select R '7664096,tRzgWRUlUEdoYPZjofYr,?,?' b >> catc_test_res_zz
#Query Stats
# sig pages read:    8
# signatures read:   14
# data pages read:   0
# tuples examined:   0
# false match pages: 0


diff catc_test_res_zz catc_test_res
