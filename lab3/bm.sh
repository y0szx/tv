#!/bin/bash

chmod +x "$0"

sysbench fileio --file-test-mode=seqrewr --file-total-size=80M prepare

sysbench cpu --cpu-max-prime=20000 run > "output_cpu.txt"

sysbench fileio --file-total-size=80M --file-test-mode=rndrd run > "output_fileio_read.txt"

sysbench fileio --file-total-size=80M --file-test-mode=rndwr run > "output_fileio_write.txt"

sysbench memory --memory-block-size=1M --memory-total-size=80M run > "output_memory.txt"

sysbench threads --threads=32 run > "output_threads.txt"

sysbench fileio --file-total-size=80M cleanup