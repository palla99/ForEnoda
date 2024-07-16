for compiing the code 
make
./main <message>


Test 1
 
./main 111111111
CPU1: Sent 10 bytes
CPU 2 waiting 
CPU1 : Ack received from CPU2 
CPU2: Received message: 111111111 
CPU2: Received message of 10 bytes


Test 2

/main 1111111111111111111111111111111111111111111111111111111
 CPU1: Sent 58 bytes
CPU 2 waiting 
CPU1 : Ack received from CPU2 
CPU2: Received message: 1111111111111111111111111111111111111111111111111111111 !
CPU2: Received message of 58 bytes


Test 3 ( No Param)

./main
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 
CPU 2 waiting 





Test 4 -> More Bytes

./main 11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
CPU1: Sent 90 bytes
Buffer Overflow detected 
