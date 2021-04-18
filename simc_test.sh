make
rm -f R.bsig R.data R.info R.psig R.tsig
./create R simc 10100 4 1000
./insert R < data3
./stats R > simc_test_res_zz
./select R '7663852,?,?,?' >> simc_test_res_zz
./select R '7663852,?,?,?' t >> simc_test_res_zz
./select R '7663852,?,?,?' p >> simc_test_res_zz
./select R '7663852,?,?,?' b  >> simc_test_res_zz
./select R '7664096,PjZZsBYoEYAMzgpCgRKg,?,?' >> simc_test_res_zz
./select R '7664096,PjZZsBYoEYAMzgpCgRKg,?,?' t >> simc_test_res_zz
./select R '7664096,PjZZsBYoEYAMzgpCgRKg,?,?' p  >> simc_test_res_zz
./select R '7664096,PjZZsBYoEYAMzgpCgRKg,?,?' b  >> simc_test_res_zz
./select R '?,?,a3-242,a4-242' >> simc_test_res_zz
./select R '?,?,a3-242,a4-242' t >> simc_test_res_zz
./select R '?,?,a3-242,a4-242' p  >> simc_test_res_zz
./select R '?,?,a3-242,a4-242' b  >> simc_test_res_zz
./select R '8765432,?,?,?' >> simc_test_res_zz
./select R '8765432,?,?,?' t >> simc_test_res_zz
./select R '8765432,?,?,?' p  >> simc_test_res_zz
./select R '8765432,?,?,?' b  >> simc_test_res_zz
./select R '7664096,tRzgWRUlUEdoYPZjofYr,?,?' >> simc_test_res_zz
./select R '7664096,tRzgWRUlUEdoYPZjofYr,?,?' t  >> simc_test_res_zz
./select R '7664096,tRzgWRUlUEdoYPZjofYr,?,?' p  >> simc_test_res_zz
./select R '7664096,tRzgWRUlUEdoYPZjofYr,?,?' b  >> simc_test_res_zz

diff simc_test_res_zz simc_test_res