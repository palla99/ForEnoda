

This code by default runs in x86, If you want to port this code on other platform  with shared mem address, then please disable FOR_X86 to 0 in headers.h <br />
#ifndef FOR_X86  <br />
  #define FOR_X86                                           1  // Make it enable -> 1 if you want to test in X86   <br />
#endif   <br />




for compiing the code <br />
make <br /> 
./main message <br /> 


Test 1  <br />
 
./main 111111111     <br />
CPU1: Sent 10 bytes   <br />
CPU 2 waiting          <br />
CPU1 : Ack received from CPU2   <br /> 
CPU2: Received message: 111111111   <br />
CPU2: Received message of 10 bytes   <br />


Test 2   <br />

/main 1111111111111111111111111111111111111111111111111111111   <br />
 CPU1: Sent 58 bytes    <br />
CPU 2 waiting           <br />
CPU1 : Ack received from CPU2    <br /> 
CPU2: Received message: 1111111111111111111111111111111111111111111111111111111 ! <br />
CPU2: Received message of 58 bytes  <br />


Test 3 ( No Param)  <br />

./main             <br />
CPU 2 waiting       <br />
CPU 2 waiting       <br />
CPU 2 waiting        <br />
CPU 2 waiting        <br />
CPU 2 waiting         <br />






Test 4 -> More Bytes <br />

./main 11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111   <br />
CPU1: Sent 90 bytes   <br />
Buffer Overflow detected  <br />
